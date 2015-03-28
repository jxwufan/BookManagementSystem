#ifndef CONNECTION
#define CONNECTION

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlDriver>

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("bookdb.db");
    if (! db.open()) {
        QMessageBox::critical(0, "Cannot open database", "Unable to establish a database connection", QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query;
    qDebug() << query.exec("create table manager (ID varchar(20) primary key,"
                                                  "Name varchar(20),"
                                                  "Password varchar(20),"
                                                  "Contact varchar(20));");

    qDebug() << query.exec("create table user (ID varchar(20) primary key,"
                                               "Name varchar(20),"
                                               "Organization varchar(20),"
                                               "Category varchar(20));");

    qDebug() << query.exec("create table book (ISBN varchar(20) primary key,"
                                               "Category varchar(20),"
                                               "Title varchar(20),"
                                               "Publisher varchar(20),"
                                               "Year int,"
                                               "Author varchar(20),"
                                               "Price Decimal(10,2),"
                                               "Amount int,"
                                               "InStock int);");

    qDebug() << query.exec("create table record (ID varchar(20),"
                                                 "ISBN varchar(20),"
                                                 "BorrowDate varchar(20),"
                                                 "DueDate varchar(20),"
                                                 "ManagerID varchar(20));");


    qDebug() << query.exec("insert into manager values('3130000889', 'WuFan', 'wfwfwf', "
               "'1586816398');");

    qDebug() << query.exec("insert into user values('829', 'xx', 'cmu', 'student');");// << "insert student";
    qDebug() << query.exec("insert into book values('234', 'test', 'test', 'tset', 2015, 'me', 2.36, 1, 1);");

//    query.exec("select * from record;");
//    while(query.next())
//        qDebug() << query.value("DueDate").toString();

    return true;
}

#endif // CONNECTION

