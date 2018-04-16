#ifndef HISTORYVIEW_H
#define HISTORYVIEW_H

#include <QWidget>
#include <QLabel>
#include <QFile>
#include <QListView>
#include <QAction>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QScrollBar>

class HistoryView : public QWidget
{
    Q_OBJECT
public:
    explicit HistoryView(QWidget *parent = 0);

private:
    QVBoxLayout *layoutHistory;
    int historySize;
    const static int maxHistorySize = 32;
    struct history {
        double op1;
        double op2;
        char operation;
        double solution;
    } historyContent[maxHistorySize];
    QLabel *labelTitle;
    QListView *listView;
    QStandardItemModel *model;




signals:

public slots:
    void addHistory(double op1, double op2, char operation, double solution);
    void clearHistory();
};

#endif // HISTORYVIEW_H