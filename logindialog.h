#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

class QString;

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
signals:
    void loginSuccessd();

private slots:
    void login();

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
