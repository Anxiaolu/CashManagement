#include "vip_manage_dialog.h"
#include "ui_vip_manage_dialog.h"
#include <QSqlQuery>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QStandardItemModel>

vip_manage_dialog::vip_manage_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vip_manage_dialog)
{
    ui->setupUi(this);
    ui->funcFontComboBox->clear();
    ui->funcFontComboBox->addItem(tr("按编号"));
    ui->funcFontComboBox->addItem(tr("按姓名"));
    showVipInfoHeader();
    ui->vipFindLineEdit->setFocus();
}

vip_manage_dialog::~vip_manage_dialog()
{
    this->dbconnection.close();
    delete ui;
}

void vip_manage_dialog::showVipInfoHeader()
{
    sql_model = new QSqlTableModel(this->parent(),dbconnection);
    sql_model->setTable("member");
    sql_model->setSort(1, Qt::AscendingOrder);
    sql_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    sql_model->setHeaderData(0,Qt::Horizontal,tr("会员编号"));
    sql_model->setHeaderData(1,Qt::Horizontal,tr("姓名"));
    sql_model->setHeaderData(2,Qt::Horizontal,tr("会员手机"));
    sql_model->setHeaderData(3,Qt::Horizontal,tr("会员地址"));
    sql_model->setHeaderData(4,Qt::Horizontal,tr("会员等级"));
    sql_model->setHeaderData(5,Qt::Horizontal,tr("会员积分"));
    sql_model->setHeaderData(6,Qt::Horizontal,tr("消费金额"));
    sql_model->setHeaderData(7,Qt::Horizontal,tr("注册日期"));
    sql_model->setHeaderData(8,Qt::Horizontal,tr("会员生日"));
    sql_model->setHeaderData(9,Qt::Horizontal,tr("邮箱"));
    sql_model->setHeaderData(10,Qt::Horizontal,tr("备注"));
    sql_model->select();

    ui->vipInfoTableView->setModel(sql_model);
    ui->vipInfoTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->vipInfoTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->Goods_tableView->setColumnHidden(0, true);
    ui->vipInfoTableView->resizeColumnsToContents();
    ui->vipInfoTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHeaderView *header = ui->vipInfoTableView->horizontalHeader();
    header->setStretchLastSection(true);
}

void vip_manage_dialog::insertVipInfo(QSqlQuery query)
{
    int curRow = ui->vipInfoTableView->currentIndex().row();
    qDebug() <<"curRow" << curRow;
    sql_model->selectRow(curRow);
    /*this->sql_model->clear();
    qDebug() << query.value("member_name").toString();
    ui->vipInfoTableView->setModel(stand_model);
    int count = ui->vipInfoTableView->model()->rowCount();
    qDebug() << "begin";
    this->stand_model->setItem(count,modal0,new QStandardItem(query.value("member_id").toString()));
    this->stand_model->setItem(count,1,new QStandardItem(query.value("member_name").toString()));
    this->stand_model->setItem(count,2,new QStandardItem(query.value("member_phone").toString()));
    this->stand_model->setItem(count,3,new QStandardItem(query.value("member_address").toString()));
    this->stand_model->setItem(count,4,new QStandardItem(query.value("member_class").toString()));
    this->stand_model->setItem(count,5,new QStandardItem(query.value("member_grade").toString()));
    this->stand_model->setItem(count,6,new QStandardItem(query.value("member_cost").toString()));
    this->stand_model->setItem(count,7,new QStandardItem(query.value("member_register").toString()));
    this->stand_model->setItem(count,8,new QStandardItem(query.value("member_birthday").toString()));
    this->stand_model->setItem(count,9,new QStandardItem(query.value("member_email").toString()));
    this->stand_model->setItem(count,10,new QStandardItem(query.value("member_remark").toString()));
    qDebug() << "end";*/
}

void vip_manage_dialog::on_vipFindBtn_clicked()
{
    QSqlQuery query(dbconnection);
    if(ui->funcFontComboBox->currentText() == tr("按姓名"))
    {
        query.exec(QString("select * from member where member_name = "
                           "'%1'").arg(ui->vipFindLineEdit->text()));
        if(query.next()){
            insertVipInfo(query);
        }else{
            QMessageBox::warning(this,"Warning","Dont find this member!",QMessageBox::Yes);
        }
    }
    if(ui->funcFontComboBox->currentText() == tr("按编号"))
    {
        qDebug() << "bianhao";
        query.exec(QString("select * from member where member_id = '%1'")
                .arg(ui->vipFindLineEdit->text().toInt()));
        if(query.next()){
            insertVipInfo(query);
        }else{
            QMessageBox::warning(this,"Warning","Dont find this member!",QMessageBox::Yes);
        }

    }
}
