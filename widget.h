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
#include <QGridLayout>
#include <QList>
#include <QStyledItemDelegate>
#include "noteditabledelegate.h"
#include <QClipboard>

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
    void userToId(QString u);
public slots:
    void getId(int ID, QString uName);
    void updateTable(QSqlRelationalTableModel* m);
    void getQueryTypes(QStringList strL);
    void getUsername(QList<QSqlRecord> uList);
    void getUserId(int id);
    void dataChange(QModelIndex lT, QModelIndex bR);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_checkBox_clicked();

    void on_pushButton_3_clicked();

    void on_checkBox_2_clicked();

protected:

private:
    Ui::Widget *ui;
    int userID, intUName;
    QString username, QueryString, qpString;
    QSqlDatabase db;
    QSqlRecord rec;
    QList<QVariant> uT;
    NotEditableDelegate* delegate;
    QString changeVal;
    //QBrush *brush;
    //QPalette *palette;
    bool editStrategy;

};



#endif // WIDGET_H
