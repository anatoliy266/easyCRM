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
    void userID(int id);
    void notOpenDB(QString dbopen);
public slots:
    void getAddQuery(int user, int dateTime, QString qquery, QString org, QString fio, QString phone, QString comment);
    void getAddQueryT(int dateTime, QString sTime);
    void getTableContext();
    void checkUser();
    void updTable();
    void queryTypes();
    void userToID(QString u);
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
