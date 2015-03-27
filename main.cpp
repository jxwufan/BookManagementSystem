#include "mainwindow.h"
#include "logindialog.h"
#include "connection.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    createConnection();

//    LoginDialog loginDialog;
//    loginDialog.show();

    MainWindow mainWindow;
    mainWindow.show();

 //   QObject::connect(&loginDialog, &LoginDialog::loginSuccessd, &mainWindow, &MainWindow::show);

    return a.exec();
}
