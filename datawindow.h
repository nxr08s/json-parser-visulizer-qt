#ifndef DATAWINDOW_H
#define DATAWINDOW_H

#include <QWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QPushButton>
#include <QVBoxLayout>

#include "src/DataTree.h"

class DataWindow : public QWidget{
    Q_OBJECT

    const DataTree* root;
    QTreeWidget* treeWidget;
    QPushButton* updateButton;
    QVBoxLayout* layout;

    void recUpdate(const DataTree*, QTreeWidgetItem*);
    void update();

public:
    explicit DataWindow(const DataTree*, QWidget* parent = 0);

public slots:
    void updateButtonPressed();
};

#endif // DATAWINDOW_H
