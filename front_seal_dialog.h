#ifndef FRONT_SEAL_DIALOG_H
#define FRONT_SEAL_DIALOG_H
#include "mysql_connection_pool/connectionPool.h"
#include <QSqlDatabase>
#include <QDialog>
#include <QTableView>
#include <QStandardItemModel>
#include <QMap>

namespace Ui {
class front_seal_dialog;
}

class front_seal_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit front_seal_dialog(QWidget *parent = 0);
    ~front_seal_dialog();
    void showGoodsInfo();
private:
    void flushGoodsCash();

private slots:
    void on_goodsFindBtn_clicked();

    void on_settleBtn_clicked();

    void on_newBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::front_seal_dialog *ui;
    QSqlDatabase dbconnection = ConnectionPool::openConnection();
    QStandardItemModel *model;
};

#endif // FRONT_SEAL_DIALOG_H
