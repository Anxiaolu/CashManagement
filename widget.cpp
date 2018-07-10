#include "widget.h"
#include "ui_widget.h"
#include "login_dialog.h"
#include "vip_manage_dialog.h"
#include "calculator_dialog.h"
#include "front_seal_dialog.h"

#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDateTime>
#include <QProcess>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);

    contentsWidget = new QListWidget;
    contentsWidget->setViewMode(QListView::IconMode);
    contentsWidget->setIconSize(QSize(50, 58));
    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setMaximumWidth(120);
    contentsWidget->setSpacing(12);

    /*暂时未实现的界面用QDialog来代替*/
    homedg = new QDialog;
    pro_seal = new front_seal_dialog;
    purch = new QDialog;
    stock_adjust = new QDialog;
    seal = new QDialog;
    inventory = new QDialog;
    member = new vip_manage_dialog;
    stockss = new QDialog;

    pagesWidget = new QStackedWidget;
    pagesWidget->addWidget(homedg);
    pagesWidget->addWidget(pro_seal);
    pagesWidget->addWidget(purch);
    pagesWidget->addWidget(stock_adjust);
    pagesWidget->addWidget(seal);
    pagesWidget->addWidget(inventory);
    pagesWidget->addWidget(stockss);
    pagesWidget->addWidget(member);


    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    logoutBtn = new QToolButton;
    logoutBtn->setIconSize(QSize(20,40));
    statuslabel = new QLabel;
    adminlabel = new QLabel;
    datatimelabel = new QLabel;
    helpbutton = new QToolButton;
    lockbutton = new QToolButton;
    calculatebutton = new QToolButton;
    moneyboxbtn = new QToolButton;
    homepagebtn = new QToolButton(contentsWidget);

    timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(showtime_slot()));
    timer->start(1000);

    logoutBtn->setText(tr("注销"));
    connect(logoutBtn,SIGNAL(clicked()),SLOT(logOut()));
    statuslabel->setText(tr("当前操作员:"));
    adminlabel->setText(tr("admin"));

    helpbutton->setText(tr("帮助(F1)"));
    connect(helpbutton,SIGNAL(clicked()),SLOT(help_info()));

    lockbutton->setText(tr("锁屏(F4)"));
    connect(lockbutton,SIGNAL(clicked()),SLOT(lock_screen()));

    calculatebutton->setText(tr("计算器"));
    connect(calculatebutton,SIGNAL(clicked()),SLOT(show_calculator()));

    moneyboxbtn->setText(tr("弹出钱箱(F12)"));
    connect(moneyboxbtn,SIGNAL(clicked()),SLOT(moneybox_up()));

    homepagebtn->setText(tr("首页"));
    connect(homepagebtn,SIGNAL(clicked()),SLOT(show_homepage()));

    buttonsLayout->addWidget(logoutBtn);
    buttonsLayout->addWidget(statuslabel);
    buttonsLayout->addWidget(adminlabel);
    buttonsLayout->addStretch(2);      //添加弹簧
    buttonsLayout->addWidget(datatimelabel);
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(helpbutton);
    buttonsLayout->addWidget(lockbutton);
    buttonsLayout->addWidget(calculatebutton);
    buttonsLayout->addWidget(moneyboxbtn);
    buttonsLayout->addWidget(homepagebtn);
    buttonsLayout->addStretch(1);   //控件之间间隔

    createIcons();

    QHBoxLayout *horizontalLayout = new QHBoxLayout;

    horizontalLayout->addWidget(pagesWidget);
    horizontalLayout->addWidget(contentsWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addStretch(2);
    mainLayout->addSpacing(16);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("收银系统"));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::logOut()
{
    this->close();
}

void Widget::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;
    pagesWidget->setCurrentIndex(contentsWidget->row(current));
}

void Widget::showtime_slot()
{
    QDateTime  time = QDateTime::currentDateTime();
    QString str= time.toString("yyyy-MM-dd hh:mm:ss dddd");
    datatimelabel->setText(str);
}

void Widget::help_info()
{
    QMessageBox::warning(this,"Warning","Welcome!",QMessageBox::Yes);
}

void Widget::lock_screen()
{
    Widget w;
    loginDialog log;
    w.hide();
    log.show();
}

void Widget::show_calculator()
{
    qDebug() << "cal";
    calculator_dialog cal_dialog;
    cal_dialog.show();
}

void Widget::moneybox_up()
{
    QMessageBox::warning(this,"Warning","MoneyBox POP!",QMessageBox::Yes);
}

void Widget::show_homepage()
{
    this->pagesWidget->currentIndex();
}

void Widget::createIcons()
{
    QListWidgetItem *homebtn = new QListWidgetItem(contentsWidget);

    QListWidgetItem *prosealButton = new QListWidgetItem(contentsWidget);
    prosealButton->setIcon(QIcon(":/myImages/images/manage_home/proseal.png"));
    prosealButton->setText(tr("前台销售"));
    prosealButton->setTextAlignment(Qt::AlignHCenter);
    prosealButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QListWidgetItem *purchButton = new QListWidgetItem(contentsWidget);
    purchButton->setIcon(QIcon(":/myImages/images/manage_home/purchase.png"));
    purchButton->setText(tr("采购进货"));
    purchButton->setTextAlignment(Qt::AlignHCenter);
    purchButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);


    QListWidgetItem *stock_adjjustButton = new QListWidgetItem(contentsWidget);
    stock_adjjustButton->setIcon(QIcon(":/myImages/images/manage_home/stock_adjust.png"));
    stock_adjjustButton->setText(tr("库存调整"));
    stock_adjjustButton->setTextAlignment(Qt::AlignHCenter);
    stock_adjjustButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *sealButton = new QListWidgetItem(contentsWidget);
    sealButton->setIcon(QIcon(":/myImages/images/manage_home/seals_statistics.png"));
    sealButton->setText(tr("销售分析"));
    sealButton->setTextAlignment(Qt::AlignHCenter);
    sealButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QListWidgetItem *inventoryButton = new QListWidgetItem(contentsWidget);
    inventoryButton->setIcon(QIcon(":/myImages/images/manage_home/inventory.png"));
    inventoryButton->setText(tr("库存分析"));
    inventoryButton->setTextAlignment(Qt::AlignHCenter);
    inventoryButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QListWidgetItem *stockButton = new QListWidgetItem(contentsWidget);
    stockButton->setIcon(QIcon(":/myImages/images/manage_home/stock_seal_save.png"));
    stockButton->setText(tr("进销存分析"));
    stockButton->setTextAlignment(Qt::AlignHCenter);
    stockButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *memberButton = new QListWidgetItem(contentsWidget);
    memberButton->setIcon(QIcon(":/myImages/images/manage_home/VIP_manage.png"));
    memberButton->setText(tr("会员管理"));
    memberButton->setTextAlignment(Qt::AlignHCenter);
    memberButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);


    connect(contentsWidget,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
}
