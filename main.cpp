#include "mysql_connection_pool/connectionPool.h"
#include "connection_test/connectiontestthread.h"
#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainwindow m;
    loginDialog dlg;
    if(dlg.exec() == QDialog::Accepted)
    {
        m.show();
    }
    return a.exec();
    /*QPushButton *button = new QPushButton("Access Database");
     button->show();

        QObject::connect(button, &QPushButton::clicked, []() {
            for (int i = 0; i < 10; ++i) {
                 ConnectionTestThread *thread = new ConnectionTestThread();
                thread->start();
            }
        });

        int ret = a.exec();
        ConnectionPool::release(); // 程序结束时关闭连接，以免造成连接泄漏

        return ret;*/
}
