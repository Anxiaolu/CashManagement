#ifndef VIP_MANAGE_DIALOG_H
#define VIP_MANAGE_DIALOG_H

#include "mysql_connection_pool/connectionPool.h"

#include <QDialog>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QStandardItemModel>

namespace Ui {
class vip_manage_dialog;
}

class vip_manage_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit vip_manage_dialog(QWidget *parent = 0);
    ~vip_manage_dialog();
    void showVipInfoHeader();
    void insertVipInfo(QSqlQuery query);
private slots:
    void on_vipFindBtn_clicked();

private:
    Ui::vip_manage_dialog *ui;
    QSqlDatabase dbconnection = ConnectionPool::openConnection();
    QSqlTableModel *sql_model;
};

#endif // VIP_MANAGE_DIALOG_H
