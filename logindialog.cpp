#include "logindialog.h"
#include "ui_logindialog.h"
#include "mysql_connection_pool/connectionPool.h"
#include <QFile>
#include <QSqlQuery>
#include <QString>
#include <QLineEdit>
#include <QMessageBox>
#include <QFontComboBox>
#include <QDebug>

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    QFile file(":qss/login.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = tr(file.readAll());
    qApp->setStyleSheet(styleSheet);
    ui->RoleComboBox->clear();
    QSqlQuery query(this->dbconnection);
    int i = 0;
    query.exec("select role_name from role");
    while (query.next()) {
        qDebug() <<" role:" <<query.value(i).toString();
        ui->RoleComboBox->addItem(query.value(i).toString());
        i++;
    }
}

loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::setDbConnection()
{
    dbconnection = ConnectionPool::openConnection();
}

void loginDialog::on_LoginButton_clicked()
{
    QSqlQuery query(this->dbconnection);
    QString username = ui->userLineEdit->text();
    QString role = ui->RoleComboBox->currentText();
    QString pwd = ui->pwdLineEdit->text();
    if(query.exec(QString("select password from user where user_name "
                          "= '%1'and user_pwd ='%2' and role_id = '%3'").arg(username).arg(pwd).arg(role)))
    {
        qDebug() << "error";
        accept();
    }else{
        QMessageBox::warning(this,"Warning","UserName or Password is error!",QMessageBox::Yes);
        ui->userLineEdit->clear();
        ui->pwdLineEdit->clear();
        ui->userLineEdit->setFocus();
    }
}
