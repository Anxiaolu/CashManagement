#include "front_seal_dialog.h"
#include "ui_front_seal_dialog.h"
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QTableView>
#include <QStandardItemModel>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QMap>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

front_seal_dialog::front_seal_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::front_seal_dialog)
{
    ui->setupUi(this);
    ui->newBtn->setText(tr("新单"));
    ui->openBtn->setText(tr("打开"));
    ui->againBtn->setText(tr("重打小票"));
    ui->floppyBtn->setText(tr("挂单"));
    ui->cancelFloppyBtn->setText(tr("去挂"));
    ui->modifyBtn->setText(tr("修改"));
    ui->cancelBtn->setText(tr("删除"));

    ui->dateEdit->setCalendarPopup(true);
    QDate today = QDate::currentDate();

    QSqlQuery query(this->dbconnection);
    query.exec(QObject::tr("select user_name from user"));
    while(query.next())
    {
        ui->employeeComboBox->addItem(query.value(0).toString());
    }
    showGoodsInfo();
}

front_seal_dialog::~front_seal_dialog()
{
    delete ui;
}

void front_seal_dialog::flushGoodsCash()
{
    int i =0 , price_sum = 0;
    int count = ui->goodsTableView->model()->rowCount();
    QAbstractItemModel *abmodel = ui->goodsTableView->model();
    for(i;i<=count;i++)
    {
        QModelIndex price_index = abmodel->index(i,4);
        price_sum += abmodel->data(price_index).toInt();
    }
    ui->priceSumLabel->setText(QString::number(price_sum));
}

void front_seal_dialog::showGoodsInfo()
{
    model = new QStandardItemModel(ui->goodsTableView);
    model->setHorizontalHeaderItem(0, new QStandardItem(tr("商品条码")));
    model->setHorizontalHeaderItem(1, new QStandardItem(tr("商品名称")));
    model->setHorizontalHeaderItem(2, new QStandardItem(tr("规格型号")));
    model->setHorizontalHeaderItem(3, new QStandardItem(tr("颜色")));
    model->setHorizontalHeaderItem(4, new QStandardItem(tr("销售价")));
    model->setHorizontalHeaderItem(5, new QStandardItem(tr("折后单价")));
    model->setHorizontalHeaderItem(6, new QStandardItem(tr("数量")));
    model->setHorizontalHeaderItem(7, new QStandardItem(tr("单位")));

    ui->goodsTableView->setModel(model);

}

void front_seal_dialog::on_goodsFindBtn_clicked()
{
    QString goodsId = ui->goodsFindLineEdit->text();
    QSqlQuery query(dbconnection);
    query.exec(QString("select * from goods where goods_id "
                                 "= '%1'").arg(goodsId));
    if(query.next())
    {
        qDebug() << "insert";
        int count = ui->goodsTableView->model()->rowCount();
        this->model->setItem(count,0,new QStandardItem(query.value("goods_id").toString()));
        this->model->setItem(count,1,new QStandardItem(query.value("goods_name").toString()));
        this->model->setItem(count,2,new QStandardItem(query.value("goods_category").toString()));
        this->model->setItem(count,3,new QStandardItem(query.value("goods_color").toString()));
        this->model->setItem(count,4,new QStandardItem(query.value("goods_seal_price").toString()));
        this->model->setItem(count,5,new QStandardItem(query.value("goods_bid_price").toString()));
        this->model->setItem(count,6,new QStandardItem("1"));
        this->model->setItem(count,7,new QStandardItem(query.value("goods_units").toString()));
        flushGoodsCash();
    }else{
        QMessageBox::warning(this,"Warning","Dont find this goods!",QMessageBox::Yes);
        ui->goodsFindLineEdit->setFocus();
    }
}

void front_seal_dialog::on_settleBtn_clicked()
{
    int cash_get = ui->cashGetLineEdit->text().toInt();
    int price_sum = ui->priceSumLabel->text().toInt();
    if(cash_get < price_sum){
         QMessageBox::warning(this,"Warning","Cash is not Enough!",QMessageBox::Yes);
    }else{
        ui->cashReturnLabel->setText(QString::number(cash_get - price_sum));
    }
}

void front_seal_dialog::on_newBtn_clicked()
{
    this->model->clear();
    ui->goodsFindLineEdit->clear();
    ui->cashGetLineEdit->clear();
    showGoodsInfo();
    ui->goodsFindLineEdit->setFocus();
}

void front_seal_dialog::on_cancelBtn_clicked()
{
    int curRow = ui->goodsTableView->currentIndex().row();//获取选中的行
    model->removeRow(curRow);
    flushGoodsCash();
}
