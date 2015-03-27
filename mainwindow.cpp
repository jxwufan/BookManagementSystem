#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlTableModel>
#include <QSqlError>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initAccountTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addAccount()
{
    accountModel->insertRow(accountModel->rowCount());
}

void MainWindow::deleteAccount()
{
    accountModel->removeRow(ui->accountTableView->currentIndex().row());
    if (QMessageBox::warning(this, "Waring", "Do you really want to delete this item?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        accountModel->submitAll();
    else
        accountModel->revertAll();
}

void MainWindow::saveAccountChanges()
{
    accountModel->database().transaction();
    if (accountModel->submitAll())
        accountModel->database().commit();
    else {
        accountModel->database().rollback();
        QMessageBox::warning(this, "Warning", tr("Database error: %1").arg(accountModel->lastError().text()));
    }
}

void MainWindow::discardAccountChanges()
{
    accountModel->revertAll();
}

void MainWindow::initAccountTable()
{
    accountModel = new QSqlTableModel(this);
    accountModel->setTable("user");
    accountModel->select();
    accountModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    ui->accountTableView->setModel(accountModel);

    connect(ui->addAccountButton, &QPushButton::clicked, this, &MainWindow::addAccount);
    connect(ui->deleteAccountButton, &QPushButton::clicked, this, &MainWindow::deleteAccount);
    connect(ui->confirmEditButton, &QPushButton::clicked, this, &MainWindow::saveAccountChanges);
    connect(ui->cancelEditButton, &QPushButton::clicked, this, &MainWindow::discardAccountChanges);
}
