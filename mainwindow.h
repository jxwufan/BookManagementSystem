#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QSqlTableModel;

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
    void addAccount();
    void deleteAccount();
    void saveAccountChanges();
    void discardAccountChanges();


private:
    Ui::MainWindow *ui;
    QSqlTableModel *accountModel;
    void initAccountTable();
};

#endif // MAINWINDOW_H
