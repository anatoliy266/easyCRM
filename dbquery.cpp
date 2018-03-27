#include "dbquery.h"
#include <QMessageBox>

DBquery::DBquery(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("P:\\1\\123.db");
    db.open();
}

DBquery::~DBquery()
{

}

void DBquery::getAddQuery(int user, int dateTime, QString qquery, QString org, QString fio, QString phone)
{
    QSqlQuery query;
    QString strQuery = "INSERT INTO crm(user, dateTime, org, query, fio, telephone)"
                       "VALUES(:user, :dateTime, :org, :query, :fio, :telephone)";
    query.prepare(strQuery);
    query.bindValue(":user", user);
    query.bindValue(":dateTime", dateTime);
    query.bindValue(":org", org);
    query.bindValue(":query", qquery);
    query.bindValue(":fio", fio);
    query.bindValue(":telephone", phone);
    query.exec();
}

void DBquery::getTableContext()
{
    QSqlQuery query;
    query.exec("SELECT * FROM crm");
    if (!query.exec())
    {
    } else {
        while (query.next())
        {
            rList.append(query.record());
        }
    }
    emit updateTableSig(rList);
}

void DBquery::checkUser()
{
    if (db.open())
    {
        QSqlQuery query;
        query.exec("SELECT * FROM users");
        if (!query.exec())
        {
        }
        while(query.next())
        {
            lRec.append(query.record());
        }
        emit userList(lRec);
    }
}

void DBquery::updTable()
{
    model = new QSqlRelationalTableModel();
    model->setTable("crm");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("user"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("dateTime"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("org"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("query"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("fio"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("phone"));
    model->setRelation(1, QSqlRelation("users", "id", "user"));
    model->setSort(0, Qt::AscendingOrder);
    emit updateTable(model);

}

void DBquery::queryTypes()
{
    str.clear();
    if (db.open())
    {
        QSqlQuery query;
        query.exec("SELECT * FROM query_type");
        if (!query.exec())
        {

        } else {
            while (query.next())
            {
                str.append(query.record().field(1).value().toString());
            }
        }
    }
    emit giveQueryTypes(str);
}
