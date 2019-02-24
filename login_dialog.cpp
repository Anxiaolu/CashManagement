#include "login_dialog.h"
#include "ui_logindialog.h"
#include "mysql_connection_pool/connectionPool.h"
#include <QFile>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QLineEdit>
#include <QMessageBox>
#include <QFontComboBox>
#include <QDebug>
#include <QKeyEvent>
#include <QPushButton>

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("收银系统"));
    QFile file(":qss/login.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = tr(file.readAll());
    qApp->setStyleSheet(styleSheet);
    ui->RoleComboBox->clear();
    QSqlQuery query(this->dbconnection);
    query.exec("select role_name from role");
    for(int i = 0;i<query.size();i++)
    {
        query.seek(i);
        qDebug() <<" role:" <<i <<query.record().value("role_name").toString();
        ui->RoleComboBox->addItem(query.record().value("role_name").toString());
    }
    //EventListener
    ui->loginButton->installEventFilter(this);
}

loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "loginBtn KeyPress!";
}

bool  loginDialog::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == qpb)
    {
        if(event->type() == QEvent::KeyPress)
            qDebug() <<"login Event!";
        return true;
    }
    return false;
}

void loginDialog::on_loginButton_clicked()
{
    QSqlQuery query(this->dbconnection);
    QString username = ui->userLineEdit->text();
    QString role = ui->RoleComboBox->currentText();
    QString pwd = ui->pwdLineEdit->text();
    if(query.exec(QString("select * from user where user_name "
                          "= '%1'and user_pwd ='%2' and role_id = '%3'")
                  .arg(username).arg(pwd).arg(role)))
    {
        accept();
    }else{
        QMessageBox::warning(this,"Warning","UserName or Password is error!",QMessageBox::Yes);
        ui->userLineEdit->clear();
        ui->pwdLineEdit->clear();
        ui->userLineEdit->setFocus();
    }
}
