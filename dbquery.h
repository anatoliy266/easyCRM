#ifndef DBQUERY_H
#define DBQUERY_H

#include <QObject>
#include <QApplication>
#include <QtSql>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlField>
#include <QList>

class DBquery : public QObject
{
    Q_OBJECT
public:
    explicit DBquery(QObject *parent = nullptr);
    ~DBquery();

signals:
    void updateTableSig(QList<QSqlRecord> recordList);
    void userList(QList<QSqlRecord> uRec);
    void updateTable(QSqlRelationalTableModel* model);
    void giveQueryTypes(QStringList string);
    void getFoundRes(QList<QSqlRecord> fRecord, bool ch);
public slots:
    void getAddQuery(int user, int dateTime, QString qquery, QString org, QString fio, QString phone);
    void getTableContext();
    void checkUser();
    void updTable();
    void queryTypes();
private:
    QSqlDatabase db;
    QList<QSqlRecord> rList;
    QList<QSqlRecord> lRec;
    QList<QSqlRecord> fRec;
    QSqlRelationalTableModel *model;
    QStringList str;
    QString QueryString, username, organization, queryT, dT, dF,tT, tF, prepString;
};

#endif // DBQUERY_H
