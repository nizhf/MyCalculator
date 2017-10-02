#ifndef NORMALVIEW_H
#define NORMALVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QFile>
#include <QShortcut>
#include <float.h>
#include <historyview.h>

class NormalView : public QWidget
{
    Q_OBJECT
public:
    explicit NormalView(QWidget *parent = 0);
    void setHistoryView(HistoryView *h);
    HistoryView *historyView();

private:
    //basic
    double memory;
    bool _memory;
    double solution;
    bool _solution;
    double op1;
    bool _op1;
    double op2;
    bool _op2;
    char operation;
    bool divisionByZero;
    QByteArray tempText;
    QByteArray inputText;
    HistoryView *history;

    //layout
    QGridLayout *layoutNormal;
    QPushButton *btnNormal[25];
    QLabel *labelNormalSolution;
    QLabel *labelNormalTemp;

signals:

public slots:
    void solutionRefresh(int mode);
    double calculate();
    void initAll();
    void initWithoutSolution();
    void memoryEnabled(bool enable);
};

#endif // NORMALVIEW_H