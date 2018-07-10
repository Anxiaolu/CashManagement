#ifndef WIDGET_H
#define WIDGET_H

#include "front_seal_dialog.h"
#include "vip_manage_dialog.h"
#include <QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <QLabel>
#include <QToolButton>
#include <QTimer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void logOut();
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);
    void showtime_slot();   //显示系统时间
    void help_info();       //使用说明
    void lock_screen();      //锁屏
    void show_calculator();  //显示计算器
    void moneybox_up();        //弹出钱箱
    void show_homepage();   //显示首页

private:
    void createIcons();
private:
    QDialog *homedg;
    front_seal_dialog *pro_seal;
    QDialog *purch;
    QDialog *stock_adjust;
    QDialog *seal;
    QDialog *inventory;
    vip_manage_dialog *member;
    QDialog *stockss;
private:
    Ui::Widget *ui;
    QListWidget *contentsWidget;   //切换界面
    QStackedWidget *pagesWidget;  //切换界面
    QToolButton *logoutBtn;
    QLabel *statuslabel;
    QLabel *adminlabel;      //当前管理员
    QLabel *datatimelabel;  //当前时间
    QTimer *timer;
    QToolButton *helpbutton;    //帮助
    QToolButton *lockbutton;    //锁屏
    QToolButton *calculatebutton; //计算器
    QToolButton *moneyboxbtn; //弹出钱箱
    QToolButton *homepagebtn; //首页

};

#endif // WIDGET_H
