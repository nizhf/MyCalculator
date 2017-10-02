#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Calculator");
    this->setMinimumHeight(600);
    this->setMinimumWidth(1000);
    this->setWindowOpacity(1);

    widgetMain = new QWidget(this);
    this->setCentralWidget(widgetMain);
    layoutMain = new QHBoxLayout;
    widgetMain->setLayout(layoutMain);

    layoutStacked = new QStackedLayout;
    historyView = new HistoryView;
    historyView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layoutMain->addLayout(layoutStacked, 2);
    layoutMain->addWidget(historyView, 1);

    mode = 1;

    //menubar
    menuStart = this->menuBar()->addMenu("Start");
    menuMode = this->menuBar()->addMenu("Mode");
    menuHelp = this->menuBar()->addMenu("Help");
    actionClear = menuStart->addAction("Clear history");
    menuStart->addSeparator();
    actionExit = menuStart->addAction("Exit");
    actionNormal = menuMode->addAction("Normal");
    actionNormal->setCheckable(true);
    actionScience = menuMode->addAction("Science");
    actionScience->setCheckable(true);
    actionEquation = menuMode->addAction("Equation");
    actionEquation->setCheckable(true);
    actionHandwrite = menuMode->addAction("unlocked in the future");
    actionHelp = menuHelp->addAction("Help");
    actionCredit = menuHelp->addAction("Credit");
    connect(actionClear, &QAction::triggered, historyView, &HistoryView::clearHistory);
    connect(actionExit, &QAction::triggered, this, &MainWindow::close);
    connect(actionNormal, &QAction::triggered, [=](){
        actionNormal->setChecked(true);
        actionScience->setChecked(false);
        actionEquation->setChecked(false);
        mode = 1;
    });
    connect(actionScience, &QAction::triggered, [=](){
        actionNormal->setChecked(false);
        actionScience->setChecked(true);
        actionEquation->setChecked(false);
        mode = 2;
    });
    connect(actionEquation, &QAction::triggered, [=](){
        actionNormal->setChecked(false);
        actionScience->setChecked(false);
        actionEquation->setChecked(true);
        mode = 3;
    });
    switch(mode) {
    case 1:
        actionNormal->setChecked(true);
        actionScience->setChecked(false);
        actionEquation->setChecked(false);
        break;
    case 2:
        actionNormal->setChecked(false);
        actionScience->setChecked(true);
        actionEquation->setChecked(false);
        break;
    case 3:
        actionNormal->setChecked(false);
        actionScience->setChecked(false);
        actionEquation->setChecked(true);
        break;
    default:
        actionNormal->setChecked(true);
        actionScience->setChecked(false);
        actionEquation->setChecked(false);
        break;
    }


    //normal mode
    normalView = new NormalView;
    normalView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    normalView->setHistoryView(historyView);
    layoutStacked->addWidget(normalView);

}

MainWindow::~MainWindow()
{

}

