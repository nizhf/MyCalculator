#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "math.h"
#include "stdlib.h"
#include "float.h"
#include <normalview.h>
#include <historyview.h>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QFile>
#include <QShortcut>
#include <QScrollArea>



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    //basic
    char mode;

    //Menu
    QMenu *menuStart;
    QMenu *menuMode;
    QMenu *menuHelp;
    QAction *actionClear;
    QAction *actionExit;
    QAction *actionNormal;
    QAction *actionScience;
    QAction *actionEquation;
    QAction *actionHandwrite;
    QAction *actionHelp;
    QAction *actionCredit;

    QWidget *widgetMain;
    QHBoxLayout *layoutMain;
    QStackedLayout *layoutStacked;    

    //history
    HistoryView *historyView;

    //normal mode
    NormalView *normalView;

public slots:






};

#endif // MAINWINDOW_H
