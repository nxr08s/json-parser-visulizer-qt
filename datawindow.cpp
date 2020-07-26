#include "datawindow.h"

void DataWindow::recUpdate(const DataTree* currentNode,QTreeWidgetItem* parentItem)
{
    QTreeWidgetItem* newItem = new QTreeWidgetItem(parentItem);
    newItem->setText(0, currentNode->getName());
    newItem->setText(1, currentNode->getTypeName());
    newItem->setText(2, currentNode->getData());
    newItem->setExpanded(true);
    for (auto it = currentNode->getChildren()->begin(); it != currentNode->getChildren()->end(); it++)
        recUpdate(*it, newItem);
}

void DataWindow::update()
{

    if (!root) return;
    treeWidget->clear();

    QTreeWidgetItem* newItem = new QTreeWidgetItem(treeWidget);
    newItem->setText(0, root->getName());
    newItem->setText(1, root->getTypeName());
    newItem->setText(2, root->getData());
    newItem->setExpanded(true);
    for (auto it = root->getChildren()->begin(); it != root->getChildren()->end(); it++)
        recUpdate(*it, newItem);

    for (int i = 0 ;i < 3; i++)
        treeWidget->resizeColumnToContents(i);
}

DataWindow::DataWindow(const DataTree *rt, QWidget *parent) : QWidget(parent), root(rt){
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle(tr("Извлеченные данные"));

    updateButton = new QPushButton(tr("Обновить"), this);
    layout = new QVBoxLayout(this);
    treeWidget = new QTreeWidget(this);

    layout->addWidget(treeWidget);
    layout->addWidget(updateButton);

    setLayout(layout);

    connect(updateButton, SIGNAL(clicked(bool)), this, SLOT(updateButtonPressed()));

    treeWidget->setColumnCount(3);
    QStringList headers;
    headers << tr("Имя")
            << tr("Тип")
            << tr("Данные");
    treeWidget->setHeaderLabels(headers);
    
    update();
}

void DataWindow::updateButtonPressed()
{
    update();
}
