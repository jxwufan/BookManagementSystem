#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlTableModel>
#include <QSqlError>
#include <QMessageBox>
#include <QChar>
#include <QString>
#include <QStringList>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QLineEdit>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    yearValidator =  new QIntValidator(1, 2100, this);
    priceValidator = new QDoubleValidator(0.0, 10000000.0, 2, this);

    initAddTab();
    initQueryTab();
    initBorrowTab();
    initReturnTab();
    initAccountTab();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addSingleBook()
{
    QString isbn = ui->ISBNEdit->text();
    QString category = ui->categoryEdit->text();
    QString title = ui->titleEdit->text();
    QString publisher = ui->publiserEdit->text();
    QString year = ui->yearEdit->text();
    QString author = ui->authorEdit->text();
    QString price = ui->priceEdit->text();
    addOneBook(isbn, category, title, publisher, year, author, price, 1);
}

void MainWindow::loadFilePath()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    ui->fileEdit->setText(fileName);
}

void MainWindow::addMultipleBooks()
{
    if (ui->fileEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "No file selected!", QMessageBox::Cancel);
    } else {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        this->setEnabled(false);
        QFile file(ui->fileEdit->text());
        if (!file.open(QFile::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, "File error", tr("Cannot read file %1:\n%2.").arg(ui->fileEdit->text()).arg(file.errorString()));
            return;
        }
        QTextStream in(&file);
        QStringList list;
        while (!in.atEnd()) {
            list = in.readLine().split(',');
            QString isbn = list[0];
            QString category = list[1];
            QString title = list[2];
            QString publisher = list[3];
            QString year = list[4];
            QString author = list[5];
            QString price = list[6];
            QString quantity = list[7];
            isbn.remove(QChar('('));
            quantity.remove(QChar(')'));
            int tot = quantity.toInt();
                addOneBook(isbn, category, title, publisher, year, author, price, tot);
        }
        this->setEnabled(true);
        QApplication::restoreOverrideCursor();
    }
}

void MainWindow::searchBooks()
{

}

void MainWindow::confirmBorrowerID()
{

}

void MainWindow::borrowBook()
{

}

void MainWindow::confirmReturnerID()
{

}

void MainWindow::returnBook()
{

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
        QMessageBox::warning(this, "Error", tr("Database error: %1").arg(accountModel->lastError().text()));
    }
}

void MainWindow::discardAccountChanges()
{
    accountModel->revertAll();
}

void MainWindow::initAddTab()
{
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::addSingleBook);
    connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::loadFilePath);
    connect(ui->addmultiButton, &QPushButton::clicked, this, &MainWindow::addMultipleBooks);

    ui->yearEdit->setValidator(yearValidator);
    ui->priceEdit->setValidator(priceValidator);
}

void MainWindow::initQueryTab()
{
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::searchBooks);

    ui->yearFromEdit->setValidator(yearValidator);
    ui->yearToEdit->setValidator(yearValidator);
    ui->priceFromEdit->setValidator(priceValidator);
    ui->priceToEdit->setValidator(priceValidator);

    queryModel = new QSqlTableModel(this);
    queryModel->setTable("book");
    queryModel->select();
    queryModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    ui->queryTableView->setModel(queryModel);
}

void MainWindow::initBorrowTab()
{

}

void MainWindow::initReturnTab()
{

}

void MainWindow::initAccountTab()
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

void MainWindow::addOneBook(QString isbn, QString category, QString title, QString publisher, QString year, QString author, QString price, int quantity)
{
    str2sqlstr(isbn);
    str2sqlstr(category);
    str2sqlstr(title);
    str2sqlstr(publisher);
    str2sqlstr(author);

    empty2Null(isbn);
    empty2Null(category);
    empty2Null(title);
    empty2Null(publisher);
    empty2Null(year);
    empty2Null(author);
    empty2Null(price);

    if (isbn == "NULL") {
        QMessageBox::warning(this, "Error", "ISBN is empty, could not add such book!", QMessageBox::Cancel);
        return;
    }

    query.exec("select * from book where ISBN = " + isbn + ";");

    if (query.next()) {
        int amount = query.value("Amount").toInt();
        amount += quantity;
        int instock = query.value("InStock").toInt();
        instock += quantity;
        qDebug() << query.exec("update book set Amount = " + QString::number(amount) + ", InStock = " + QString::number(instock) + " where ISBN = " + isbn + ";") << "update book";
        qDebug() << QString::number(amount) << " " << QString::number(instock);
    } else
        qDebug() << query.exec("insert into book values(" + isbn + "," + category + "," + title + "," + publisher + "," + year + "," + author + "," + price + ", 1, 1);") << " insert new book";
    queryModel->select();
}

void MainWindow::empty2Null(QString &str)
{
    if (str.isEmpty()) str = "NULL";
}

void MainWindow::str2sqlstr(QString &str)
{
    if (!str.isEmpty()) str = "'" + str + "'";
}
