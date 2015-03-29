#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QString>
#include <QSqlQuery>
#include <QDebug>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    connect(ui->loginButton, &QPushButton::clicked, this, &LoginDialog::login);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::login()
{
    QString id = ui->ID_edit->text();
    QString password = ui->password_edit->text();
    QSqlQuery query;
    query.exec("select Password from manager where ID = " + id + ";");
    bool ok = query.next();
    if (!ok)
        QMessageBox::critical(0, "Error", "Invalid ID!", QMessageBox::Cancel);
    else
    {
        if (query.value(0).toString() == password)
        {
            QMessageBox::information(0, "Success", "Login Success!", QMessageBox::Ok);
            this->hide();
            emit loginSuccessd(ui->ID_edit->text());
            this->close();
        }
        else
            QMessageBox::critical(0, "Error", "Woring Password!!!", QMessageBox::Cancel);
    }
}
