#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include "mysql_connection_pool/connectionPool.h"
#include <QDialog>
#include <QSqlDatabase>
#include <QKeyEvent>

namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = 0);
    ~loginDialog();
    bool eventFilter(QObject *obj, QEvent *event);

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_loginButton_clicked();

private:
    Ui::loginDialog *ui;
    QSqlDatabase dbconnection = ConnectionPool::openConnection();
    QPushButton *qpb;
};

#endif // LOGINDIALOG_H
