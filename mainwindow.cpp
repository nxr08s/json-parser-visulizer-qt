#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::updateStackList()
{

    ui->stackListWidget->clear();

    for (auto st = parser->getStack()->begin(); st != parser->getStack()->end(); st++){
        ui->stackListWidget->addItem(QString(Parser::StateStrings[(unsigned int)(*st)->getStateName()]));
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    parser(nullptr)
{
    ui->setupUi(this);

    connect(ui->openButton, SIGNAL(clicked(bool)),
            this, SLOT(openButtonPressed()));
    connect(ui->resetButton, SIGNAL(clicked(bool)),
            this, SLOT(resetButtonPressed()));
    connect(ui->parseButton, SIGNAL(clicked(bool)),
            this, SLOT(parseButtonPressed()));
    connect(ui->dataButton, SIGNAL(clicked(bool)),
            this, SLOT(dataButtonPressed()));

    cursor = ui->mainTextEdit->textCursor();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openButtonPressed()
{
    QFile file(QFileDialog::getOpenFileName(nullptr,
                                            QStringLiteral(""),
                                            QStringLiteral(""),
                                            QStringLiteral("JSON (*.json)")));
    if (file.fileName() == "")  return;
    if (!file.open(QIODevice::ReadOnly)){
        QMessageBox::critical(nullptr,
                              tr("Открыть файл"),
                              tr("Не удалось открыть файл"));
        return;
    }
    ui->mainTextEdit->setPlainText(file.readAll());
}

void MainWindow::resetButtonPressed()
{
    ui->mainTextEdit->setReadOnly(false);
    ui->parseButton->setEnabled(true);
    ui->clearButton->setEnabled(true);
    ui->openButton->setEnabled(true);
    ui->dataButton->setEnabled(false);
    ui->stateLabel->setText(tr("Начальное"));
    ui->errorLabel->setText(tr("Без ошибок"));
    ui->stackListWidget->clear();
    if (parser){
        delete parser;
        parser = nullptr;
    }
    jsonText.clear();
    fmt.setBackground(Qt::white);
    fmt.setForeground(Qt::black);
    cursor.setPosition(QTextCursor::End);
    cursor.setPosition(QTextCursor::Start, QTextCursor::KeepAnchor);
    cursor.mergeCharFormat(fmt);
}

void MainWindow::parseButtonPressed()
{
    if (!parser){
        jsonText = ui->mainTextEdit->toPlainText().toStdString();
        parser = new Parser(jsonText.c_str(), jsonText.length());
        ui->dataButton->setEnabled(true);
        if (!ui->autoCheckBox->isChecked()){
            ui->clearButton->setEnabled(false);
            ui->openButton->setEnabled(false);
            ui->mainTextEdit->setReadOnly(true);
        }
    }
    if (ui->autoCheckBox->isChecked()){
        parser->parse();
        if (parser->success()){
            ui->stateLabel->setText(tr("Завершено"));
        }else{
            ui->errorLabel->setText(QString(parser->getError()) +
                                    QChar('(') + QString::number(parser->getPos()) + QChar(')')
                                    );
            cursor.setPosition(parser->getPos());
            cursor.movePosition(QTextCursor::PreviousCharacter, QTextCursor::MoveAnchor);
            cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::MoveAnchor);
            cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
            fmt.setForeground(Qt::white);
            fmt.setBackground(Qt::black);
            cursor.mergeCharFormat(fmt);
        }
        ui->parseButton->setEnabled(false);
    }else{
        parser->parse(false);
        ui->stateLabel->setText(parser->getState());
        updateStackList();

        if (parser->done()){
            ui->stateLabel->setText(tr("Завершено"));
            ui->parseButton->setEnabled(false);
        }else if (!parser->success()){
            ui->errorLabel->setText(QString(parser->getError()) +
                                    QChar('(') + QString::number(parser->getPos()) + QChar(')')
                                    );
            ui->parseButton->setEnabled(false);
        }

        fmt.setForeground(Qt::black);
        fmt.setBackground(Qt::white);
        cursor.mergeCharFormat(fmt);
        cursor.movePosition(QTextCursor::PreviousCharacter, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
        fmt.setForeground(Qt::white);
        fmt.setBackground(Qt::black);
        cursor.mergeCharFormat(fmt);
    }
}

void MainWindow::dataButtonPressed()
{
    data = new DataWindow(parser->getData());
    data->show();
}
