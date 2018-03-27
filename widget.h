#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QApplication>
#include <QtSql>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlField>
#include <QTableView>
#include <QSqlRelationalTableModel>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
signals:
    void giveID(int ID);
    void properties();
    void upd();
public slots:
    void getId(int ID, QString uName);
    void updateTable(QSqlRelationalTableModel* m);
    void getQueryTypes(QStringList strL);
    void getUsername(QList<QSqlRecord> uList);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_checkBox_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Widget *ui;
    int userID;
    QString username, QueryString, qpString;
    QSqlDatabase db;
    QSqlRecord rec;
};

#endif // WIDGET_H
