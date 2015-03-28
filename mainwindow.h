#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>

class QSqlTableModel;
class QValidator;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void addSingleBook();
    void loadFilePath();
    void addMultipleBooks();

    void searchBooks();

    void confirmBorrowerID();
    void borrowBook();

    void confirmReturnerID();
    void returnBook();

    void addAccount();
    void deleteAccount();
    void saveAccountChanges();
    void discardAccountChanges();


private:
    Ui::MainWindow *ui;
    QSqlTableModel *queryModel;
    QSqlTableModel *accountModel;
    QValidator *yearValidator;
    QValidator *priceValidator;
    QSqlQuery query;

    void initAddTab();
    void initQueryTab();
    void initBorrowTab();
    void initReturnTab();
    void initAccountTab();
    void addOneBook(QString isbn, QString category, QString title, QString publisher, QString year, QString author, QString price, int quantity);
    inline void empty2Null(QString &str);
    inline void str2sqlstr(QString &str);
};

#endif // MAINWINDOW_H
