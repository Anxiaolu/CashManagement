#include "calculator_dialog.h"
#include "ui_calculator_dialog.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QMenu>
#include <QMenuBar>
#include <QAction>

calculator_dialog::calculator_dialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::calculator_dialog)
{
    ui->setupUi(this);
    mylayout();
    addMenu();
    addMenuAction();
}

calculator_dialog::~calculator_dialog()
{
    delete ui;
}


void calculator_dialog::mylayout()
{
    QWidget *centerWindow = new QWidget;
        this->setCentralWidget(centerWindow);

        label1 = new QLabel("display");
        label2 = new QLabel("result");

        QHBoxLayout *h1 = new QHBoxLayout;
        h1->addWidget(label1);
        h1->addWidget(label2);
        label1->setMaximumHeight(15);
        label2->setMaximumHeight(15);
        h1->setStretch(0,2);
        h1->setStretch(1,1);

        showEdit = new QTextEdit;
        resultEdit = new QTextEdit;

        QHBoxLayout *h2 = new QHBoxLayout;
        h2->addWidget(showEdit);
        h2->addWidget(resultEdit);
        showEdit->setMaximumHeight(30);
        resultEdit->setMaximumHeight(30);
        showEdit->setReadOnly(true);
        resultEdit->setReadOnly(true);
        h2->setStretch(0,2);
        h2->setStretch(1,1);

        backBt = new QPushButton("Back");
        removeBt = new QPushButton("CE");
        clearBt = new QPushButton("CLS");
        sumBt = new QPushButton("+");
        backBt->setMinimumHeight(50);
        removeBt->setMinimumHeight(50);
        clearBt->setMinimumHeight(50);
        sumBt->setMinimumHeight(50);

        QHBoxLayout *h3 = new QHBoxLayout;
        h3->addWidget(backBt);
        h3->addWidget(removeBt);
        h3->addWidget(clearBt);
        h3->addWidget(sumBt);

        sevenBt = new QPushButton("7");
        eightBt = new QPushButton("8");
        nineBt = new QPushButton("9");
        decBt = new QPushButton("-");
        sevenBt->setMinimumHeight(50);
        eightBt->setMinimumHeight(50);
        nineBt->setMinimumHeight(50);
        decBt->setMinimumHeight(50);

        QHBoxLayout *h4 = new QHBoxLayout;
        h4->addWidget(sevenBt);
        h4->addWidget(eightBt);
        h4->addWidget(nineBt);
        h4->addWidget(decBt);

        fourBt = new QPushButton("4");
        fiveBt = new QPushButton("5");
        sixBt = new QPushButton("6");
        starBt = new QPushButton("*");
        fourBt->setMinimumHeight(50);
        fiveBt->setMinimumHeight(50);
        sixBt->setMinimumHeight(50);
        starBt->setMinimumHeight(50);

        QHBoxLayout *h5 = new QHBoxLayout;
        h5->addWidget(fourBt);
        h5->addWidget(fiveBt);
        h5->addWidget(sixBt);
        h5->addWidget(starBt);

        oneBt = new QPushButton("1");
        twoBt = new QPushButton("2");
        threeBt = new QPushButton("3");
        divBt = new QPushButton("/");
        oneBt->setMinimumHeight(50);
        twoBt->setMinimumHeight(50);
        threeBt->setMinimumHeight(50);
        divBt->setMinimumHeight(50);

        QHBoxLayout *h6 = new QHBoxLayout;
        h6->addWidget(oneBt);
        h6->addWidget(twoBt);
        h6->addWidget(threeBt);
        h6->addWidget(divBt);

        _Bt = new QPushButton("+/-");
        zeroBt = new QPushButton("0");
        pointBt = new QPushButton(".");
        equalBt = new QPushButton("=");
        _Bt->setMinimumHeight(50);
        zeroBt->setMinimumHeight(50);
        pointBt->setMinimumHeight(50);
        equalBt->setMinimumHeight(50);

        QHBoxLayout *h7 = new QHBoxLayout;
        h7->addWidget(_Bt);
        h7->addWidget(zeroBt);
        h7->addWidget(pointBt);
        h7->addWidget(equalBt);

        QVBoxLayout *mainLayout = new QVBoxLayout;
        mainLayout->addLayout(h1);
        mainLayout->addLayout(h2);
        mainLayout->addLayout(h3);
        mainLayout->addLayout(h4);
        mainLayout->addLayout(h5);
        mainLayout->addLayout(h6);
        mainLayout->addLayout(h7);

        centerWindow->setLayout(mainLayout);
    }

void calculator_dialog::addMenu()
{
    QMenu *menu1 = new QMenu;
    QMenu *menu2 = new QMenu;
    QMenu *menu3 = new QMenu;

    action1 = new QAction(this);
    action2 = new QAction(this);
    action3 = new QAction(this);
    action4 = new QAction(this);
    action5 = new QAction(this);
    action6 = new QAction(this);
    action7 = new QAction(this);
    action8 = new QAction(this);

    menu1 = menuBar()->addMenu("select");
    menu1->addAction(action1);
    menu1->addAction(action2);

    menu1->addSeparator();
    menu1->addAction(action3);
    menu1->addAction(action4);

    menu2 = menuBar()->addMenu("edit");
    menu2->addAction(action5);
    menu2->addSeparator();
    menu2->addAction(action6);

    menu3 = menuBar()->addMenu("help");
    menu3->addAction(action7);
    menu3->addSeparator();
    menu3->addAction(action8);
}

void calculator_dialog::addMenuAction()
{
    action1 = new QAction("standard",this);
    action1->setShortcut(tr("alt+1"));
    action2 = new QAction("science",this);
    action2->setShortcut(tr("alt+2"));

    action3 = new QAction("history",this);
    action3->setShortcut(tr("alt+3"));
    action4 = new QAction("time",this);
    action4->setShortcut(tr("alt+4"));

    action5 = new QAction("copy",this);
    action5->setShortcut(tr("ctrl+1"));
    action6 = new QAction("paste",this);
    action6->setShortcut(tr("ctrl+2"));

    action7 = new QAction("help",this);
    action7->setShortcut(tr("ctrl+3"));
    action8 = new QAction("about",this);
    action8->setShortcut(tr("ctrl+4"));
}
