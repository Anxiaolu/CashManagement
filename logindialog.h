#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include "mysql_connection_pool/connectionPool.h"
#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = 0);
    ~loginDialog();
    void setDbConnection();
    QSqlDatabase getDbConnection();

private slots:
    void on_LoginButton_clicked();

private:
    Ui::loginDialog *ui;
    QSqlDatabase dbconnection = ConnectionPool::openConnection();
};

#endif // LOGINDIALOG_H
