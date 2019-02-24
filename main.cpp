#include "mysql_connection_pool/connectionPool.h"
#include "connection_test/connectiontestthread.h"
#include "login_dialog.h"
#include "widget.h"
#include "vip_manage_dialog.h"
#include "front_seal_dialog.h"
#include "calculator_dialog.h"
#include <QApplication>
#include <QPushButton>
#include <QMap>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    front_seal_dialog seal_dialog;
    loginDialog dlg;
    Widget w;
    calculator_dialog cal;
    vip_manage_dialog vip;
        if(dlg.exec() == QDialog::Accepted)
        {
            w.show();
        }
        return a.exec();
    /*QPushButton *button = new QPushButton("Access Database");
     button->show();

        QObject::connect(button, &QPushButton::clicked, []() {
            for (int i = 0; i < 1; ++i) {
                 ConnectionTestThread *thread = new ConnectionTestThread();
                thread->start();
            }
        });

        int ret = a.exec();
        ConnectionPool::release(); // 程序结束时关闭连接，以免造成连接泄漏

        return ret;

    */    
}
