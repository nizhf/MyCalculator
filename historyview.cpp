#include "historyview.h"

HistoryView::HistoryView(QWidget *parent) : QWidget(parent)
{
    historySize = 0;

    model = new QStandardItemModel;

    QFile qssFile(":/qss/qss/History_View.qss");
    qssFile.open(QFile::ReadOnly);
    QByteArray styleMain = qssFile.readAll();
    this->setStyleSheet(styleMain);
    qssFile.close();

    layoutHistory = new QVBoxLayout;
    this->setLayout(layoutHistory);
    labelTitle = new QLabel("History", this);
    labelTitle->setObjectName("listTitle");
    listView = new QListView(this);
    listView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    listView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    listView->verticalScrollBar()->setStyleSheet(styleMain);
    listView->setSpacing(3);
    listView->setSelectionMode(QAbstractItemView::NoSelection);
    listView->setModel(model);
    layoutHistory->addWidget(labelTitle);
    layoutHistory->addWidget(listView);


}

void HistoryView::addHistory(double op1, double op2, char operation, double solution) {
    QStandardItem *item1, *item2;
    switch (operation) {
    case 1:
        item1 = new QStandardItem(tr("%1 + %2 =   ").arg(op1).arg(op2));
        break;
    case 2:
        item1 = new QStandardItem(tr("%1 - %2 =   ").arg(op1).arg(op2));
        break;
    case 3:
        item1 = new QStandardItem(tr("%1 × %2 =   ").arg(op1).arg(op2));
        break;
    case 4:
        item1 = new QStandardItem(tr("%1 ÷ %2 =   ").arg(op1).arg(op2));
        break;
    default:
        item1 = new QStandardItem;
        break;
    }
    item1->setTextAlignment(Qt::AlignRight);
    item1->setForeground(QBrush(QColor(102, 102, 102)));
    item1->setEditable(false);
    item1->setSelectable(false);
    item2 = new QStandardItem(tr("%1  ").arg(solution));
    item2->setTextAlignment(Qt::AlignRight);
    item2->setForeground(QBrush(Qt::black));
    item2->setEditable(false);
    item2->setSelectable(false);
    model->insertRow(0, item2);
    model->insertRow(0, item1);
    if (historySize < maxHistorySize) {
        historySize++;
        historyContent[historySize - 1].op1 = op1;
        historyContent[historySize - 1].op2 = op2;
        historyContent[historySize - 1].operation = operation;
        historyContent[historySize - 1].solution = solution;
    }
    else {
        for (int i = historySize - 2; i >= 0; i--) {
            historyContent[i] = historyContent[i + 1];
        }
        historyContent[historySize - 1].op1 = op1;
        historyContent[historySize - 1].op2 = op2;
        historyContent[historySize - 1].operation = operation;
        historyContent[historySize - 1].solution = solution;
        model->removeRow(model->rowCount() - 1);
        model->removeRow(model->rowCount() - 1);
    }

}

void HistoryView::clearHistory() {
    model->clear();
    historySize = 0;
}
