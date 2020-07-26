#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QStack>
#include <QTextCursor>

#include "src/Parser.h"
#include "datawindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    std::string jsonText;
    Parser* parser;
    DataWindow* data;

    QTextCursor cursor;
    QTextCharFormat fmt;

    void updateStackList();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void openButtonPressed();
    void resetButtonPressed();
    void parseButtonPressed();
    void dataButtonPressed();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
