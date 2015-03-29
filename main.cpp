#include "mainwindow.h"
#include "logindialog.h"
#include "connection.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    createConnection();

    LoginDialog loginDialog;
    loginDialog.show();

    MainWindow mainWindow;

    QObject::connect(&loginDialog, &LoginDialog::loginSuccessd, &mainWindow, &MainWindow::login);

    return a.exec();
}
