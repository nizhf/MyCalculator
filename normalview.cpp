#include "normalview.h"

NormalView::NormalView(QWidget *parent) : QWidget(parent)
{
    initAll();
    memory = 0;
    _memory = false;
    //layout
    layoutNormal = new QGridLayout;
    this->setLayout(layoutNormal);
    labelNormalSolution = new QLabel;
    labelNormalSolution->setAlignment(Qt::AlignRight | Qt::AlignCenter);
    labelNormalSolution->setMinimumHeight(80);
    labelNormalSolution->setObjectName("labelSolution");
    labelNormalTemp = new QLabel;
    labelNormalTemp->setAlignment(Qt::AlignRight | Qt::AlignCenter);
    labelNormalTemp->setMinimumHeight(30);
    labelNormalTemp->setObjectName("labelTemp");
    solutionRefresh(0);
    for (int i = 0; i < 10; i++) {
        btnNormal[i] = new QPushButton(tr("%1").arg(i));
    }
    btnNormal[10] = new QPushButton(tr("."));
    btnNormal[11] = new QPushButton(tr("±"));
    btnNormal[12] = new QPushButton(tr("+"));
    btnNormal[13] = new QPushButton(tr("-"));
    btnNormal[14] = new QPushButton(tr("×"));
    btnNormal[15] = new QPushButton(tr("÷"));
    btnNormal[16] = new QPushButton(tr("="));
    btnNormal[17] = new QPushButton(tr("CE"));
    btnNormal[18] = new QPushButton(tr("AC"));
    btnNormal[19] = new QPushButton(tr("Backspace"));
    btnNormal[20] = new QPushButton(tr("MC"));
    btnNormal[21] = new QPushButton(tr("MR"));
    btnNormal[22] = new QPushButton(tr("M+"));
    btnNormal[23] = new QPushButton(tr("M-"));
    btnNormal[24] = new QPushButton(tr("MS"));
    for (int i = 0; i < 25; i++) {
        btnNormal[i] ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        if (i < 10) {
            btnNormal[i]->setObjectName("btnNum");
        }
        else if (i > 11 && i < 17){
            btnNormal[i]->setObjectName("btnOp");
        }
        else {
            btnNormal[i]->setObjectName("btnOther");
        }
    }
    memoryEnabled(false);

    layoutNormal->addWidget(labelNormalTemp, 0, 0, 1, 5);
    layoutNormal->addWidget(labelNormalSolution, 1, 0, 1, 5);
    layoutNormal->addWidget(btnNormal[24], 2, 0, 1, 1);
    layoutNormal->addWidget(btnNormal[22], 3, 0, 1, 1);
    layoutNormal->addWidget(btnNormal[23], 4, 0, 1, 1);
    layoutNormal->addWidget(btnNormal[21], 5, 0, 1, 1);
    layoutNormal->addWidget(btnNormal[20], 6, 0, 1, 1);
    layoutNormal->addWidget(btnNormal[17], 2, 1, 1, 1);
    layoutNormal->addWidget(btnNormal[18], 2, 2, 1, 1);
    layoutNormal->addWidget(btnNormal[19], 2, 3, 1, 1);
    layoutNormal->addWidget(btnNormal[12], 2, 4, 1, 1);
    layoutNormal->addWidget(btnNormal[13], 3, 4, 1, 1);
    layoutNormal->addWidget(btnNormal[14], 4, 4, 1, 1);
    layoutNormal->addWidget(btnNormal[15], 5, 4, 1, 1);
    layoutNormal->addWidget(btnNormal[16], 6, 4, 1, 1);
    layoutNormal->addWidget(btnNormal[10], 6, 3, 1, 1);
    layoutNormal->addWidget(btnNormal[11], 6, 1, 1, 1);
    layoutNormal->addWidget(btnNormal[0], 6, 2, 1, 1);
    for (int i = 0, btn = 1; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            layoutNormal->addWidget(btnNormal[btn], 5 - i, 1 + j, 1, 1);
            btn++;
        }
    }

    //shortcuts
    for (int i = 0; i < 10; i++) {
        btnNormal[i]->setShortcut(QKeySequence(tr("%1").arg(i)));
    }
    btnNormal[10]->setShortcut(QKeySequence(tr(".")));
    btnNormal[12]->setShortcut(QKeySequence(tr("+")));
    btnNormal[13]->setShortcut(QKeySequence(tr("-")));
    btnNormal[14]->setShortcut(QKeySequence(tr("*")));
    btnNormal[15]->setShortcut(QKeySequence(tr("/")));
    btnNormal[16]->setShortcut(QKeySequence(Qt::Key_Return));
    QShortcut *key_Enter = new QShortcut(QKeySequence(Qt::Key_Enter),this);
    connect(key_Enter, &QShortcut::activated, btnNormal[16], &QPushButton::click);
    btnNormal[19]->setShortcut(QKeySequence(Qt::Key_Backspace));

    //click events
    //1-9
    for (int i = 1; i < 10; i++) {
        connect(btnNormal[i], &QPushButton::clicked, [=](){
            inputText.append(tr("%1").arg(i));
            _solution = false;
            solutionRefresh(1);
        });
    }
    //0
    connect(btnNormal[0], &QPushButton::clicked, [=](){
        if (inputText.isEmpty()) {
            inputText.append("0");
        }
        else if (inputText.count('0') != inputText.size()) {
            inputText.append("0");
        }
        _solution = false;
        solutionRefresh(1);
    });
    //.
    connect(btnNormal[10], &QPushButton::clicked, [=](){
        if (inputText.isEmpty()) {
            inputText.append("0.");
        }
        else if (!inputText.contains('.')) {
            inputText.append(".");
        }
        _solution = false;
        solutionRefresh(1);
    });
    //±
    connect(btnNormal[11], &QPushButton::clicked, [=](){
        if (inputText.isEmpty()) {
            if (!_op1) {
                solution = 0 - solution;
                solutionRefresh(3);
            }
        }
        else if (inputText.size() > 1) {
            if (inputText.at(0) == '-') {
                inputText.remove(0, 1);
            }
            else {
                inputText.prepend('-');
            }
            solutionRefresh(1);
        }
        else if (inputText.at(0) != '0') {
            inputText.prepend('-');
            solutionRefresh(1);
        }
    });
    //+-×÷
    for (int i = 12; i < 16; i++) {
        connect(btnNormal[i], &QPushButton::clicked, [=](){
            if (inputText.isEmpty()) {
                operation = i - 11;
                if (_op1) {
                    tempText.replace(tempText.size() - 1, btnNormal[i]->text());
                }
                else if (_solution){
                    op1 = solution;
                    _op1 = true;
                    _solution = false;
                    tempText.append(tr("%1 ").arg(op1));
                    tempText.append(btnNormal[i]->text());
                }
            }
            else {
                if (_op1) {
                    op2 = inputText.toDouble();
                    _op2 = true;
                    calculate();
                    _solution = true;
                    op1 = solution;
                    _op1 = true;
                    op2 = 0;
                    _op2 = false;
                    operation = i - 11;
                    inputText.clear();
                    tempText.clear();
                    tempText.append(tr("%1 ").arg(op1));
                    tempText.append(btnNormal[i]->text());
                }
                else {
                    operation = i - 11;
                    tempText.append(inputText);
                    tempText.append(tr(" "));
                    tempText.append(btnNormal[i]->text());
                    op1 = inputText.toDouble();
                    _op1 = true;
                    inputText.clear();
                }
            }
            solutionRefresh(2);
        });
    }
    //=
    connect(btnNormal[16], &QPushButton::clicked, [=](){
        if (inputText.isEmpty()) {
            if (_op1 && !_op2) {
                op2 = op1;
                _op2 = true;
                calculate();
                solutionRefresh(3);
                initWithoutSolution();
            }
            else if (_op1 && _op2) {
                calculate();
                solutionRefresh(3);
                initWithoutSolution();
            }
//            else {
//                solutionRefresh(3);
//                initWithoutSolution();
//            }
        }
        else {
            if (_op1) {
                op2 = inputText.toDouble();
                _op2 = true;
                calculate();
                solutionRefresh(3);
            }
            else {
                solution = inputText.toDouble();
                solutionRefresh(3);
            }
            initWithoutSolution();
        }
        _solution = !divisionByZero;

    });
    //CE
    connect(btnNormal[17], &QPushButton::clicked, [=](){
        inputText.clear();
        _solution = false;
        solutionRefresh(4);
    });
    //AC
    connect(btnNormal[18], &QPushButton::clicked, [=](){
        initAll();
        solutionRefresh(0);
    });
    //Backspace
    connect(btnNormal[19], &QPushButton::clicked, [=](){
        if (inputText.size() > 1) {
            inputText.remove(inputText.size() - 1, 1);
            solutionRefresh(1);
        }
        else if (inputText.size() == 1) {
            inputText.clear();
            _solution = false;
            solutionRefresh(4);
        }
    });
    //MC memory clear
    connect(btnNormal[20], &QPushButton::clicked, [=](){
        memory = 0;
        _memory = false;
        memoryEnabled(false);
    });
    //MR memory represent
    connect(btnNormal[21], &QPushButton::clicked, [=](){
        inputText.clear();
        solution = memory;
        if (_op1) {
            op2 = memory;
            _op2 = true;
        }
        else {
            solution = memory;
            _solution = true;
        }
        solutionRefresh(5);
    });
    //M+ memory plus
    connect(btnNormal[22], &QPushButton::clicked, [=](){
        if (_solution) {
            memory += solution;
            _memory = true;
        }
        else {
            memory += inputText.toDouble();
            _memory = true;
            inputText.clear();
            tempText.clear();
        }
        memoryEnabled(true);
//        else if (!_op1) {
//            memory += inputText.toDouble();
//            _memory = true;
//            inputText.clear();
//            tempText.clear();
//        }
//        else {
//            btnNormal[16]->click();
//            memory += solution;
//            _memory = true;
//        }
    });
    //M- memory minus
    connect(btnNormal[23], &QPushButton::clicked, [=](){
        if (_solution) {
            memory -= solution;
            _memory = true;
        }
        else {
            memory -= inputText.toDouble();
            _memory = true;
            inputText.clear();
            tempText.clear();
        }
        memoryEnabled(true);
//        else if (!_op1) {
//            memory -= inputText.toDouble();
//            _memory = true;
//            inputText.clear();
//            tempText.clear();
//        }
//        else {
//            btnNormal[16]->click();
//            memory -= solution;
//            _memory = true;
//        }
    });
    //MS memory set
    connect(btnNormal[24], &QPushButton::clicked, [=](){
        if (_solution) {
            memory = solution;
            _memory = true;
        }
        else {
            memory = inputText.toDouble();
            _memory = true;
            inputText.clear();
            tempText.clear();
        }
        memoryEnabled(true);
//        else if (!_op1) {
//            memory = inputText.toDouble();
//            _memory = true;
//            inputText.clear();
//            tempText.clear();
//        }
//        else {
//            btnNormal[16]->click();
//            memory = solution;
//            _memory = true;
//        }
    });



    QFile qssFile(":/qss/qss/Normal_View.qss");
    qssFile.open(QFile::ReadOnly);
    this->setStyleSheet(qssFile.readAll());
    qssFile.close();
}

void NormalView::initAll() {
    solution = 0.0;
    _solution = false;
    tempText.clear();
    inputText.clear();
    op1 = 0.0;
    _op1 = false;
    op2 = 0.0;
    _op2 = false;
    operation = 1;
    divisionByZero = false;
}

void NormalView::initWithoutSolution() {
    tempText.clear();
    inputText.clear();
    op1 = 0.0;
    _op1 = false;
    op2 = 0.0;
    _op2 = false;
    operation = 1;
    divisionByZero = false;
}

void NormalView::setHistoryView(HistoryView *h) {
    this->history = h;
}

HistoryView *NormalView::historyView() {
    return history;
}

void NormalView::memoryEnabled(bool _memory) {
    if (_memory) {
        btnNormal[20]->setEnabled(true);
        btnNormal[21]->setEnabled(true);
    }
    else {
        btnNormal[20]->setEnabled(false);
        btnNormal[21]->setEnabled(false);
    }
}

void NormalView::solutionRefresh(int mode) {
    if (divisionByZero) {
        labelNormalSolution->setText("FNMDX!");
        labelNormalTemp->setText("");
        divisionByZero = false;
        return;
    }
    switch (mode) {
    case 0:
        labelNormalSolution->setText("0");
        labelNormalTemp->setText("");
        break;
    case 1:
        labelNormalSolution->setText(inputText);
        labelNormalTemp->setText(tempText);
        break;
    case 2:
        labelNormalSolution->setText(tr("%1").arg(op1));
        labelNormalTemp->setText(tempText);
        break;
    case 3:
        labelNormalSolution->setText(tr("%1").arg(solution));
        labelNormalTemp->setText("");
        break;
    case 4:
        labelNormalSolution->setText("0");
        labelNormalTemp->setText(tempText);
        break;
    case 5:
        labelNormalSolution->setText(tr("%1").arg(solution));
        labelNormalTemp->setText(tempText);
        break;
    }
}

double NormalView::calculate() {
    switch (operation) {
    case 1:
        solution = op1 + op2;
        break;
    case 2:
        solution = op1 - op2;
        break;
    case 3:
        solution = op1 * op2;
        break;
    case 4:
        if (fabs(op2) > DBL_EPSILON) {
            solution = op1 / op2;
        }
        else {
            divisionByZero = true;
            solution = 0.0;
        }
        break;
    }
    if (!divisionByZero) {
        history->addHistory(op1, op2, operation, solution);
    }
    return solution;
}
