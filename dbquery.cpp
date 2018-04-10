#include "dbquery.h"
#include <QMessageBox>

DBquery::DBquery(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("P:\\1\\123.db");
}

DBquery::~DBquery()
{

}

void DBquery::getAddQuery(int user, int dateTime, QString qquery, QString org, QString fio, QString phone, QString comment)
{
    db.open();
    if (!db.open())
    {
        emit notOpenDB("ERROR");
    } else {
    QSqlQuery query;
    QString strQuery = "INSERT INTO crm(user, dateTime, org, query, fio, telephone, comment)"
                       "VALUES(:user, :dateTime, :org, :query, :fio, :telephone, :comment)";
    query.prepare(strQuery);
    query.bindValue(":user", user);
    query.bindValue(":dateTime", dateTime);
    query.bindValue(":org", org);
    query.bindValue(":query", qquery);
    query.bindValue(":fio", fio);
    query.bindValue(":telephone", phone);
    query.bindValue(":comment", comment);
    query.exec();
    db.close();
    }
}

void DBquery::getTableContext()
{
    db.open();
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
    db.close();
}

void DBquery::checkUser()
{
    db.open();
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
    db.close();
}

void DBquery::updTable()
{
    db.open();
    model = new QSqlRelationalTableModel();
    model->setTable("crm");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Пользователь"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Дата и время"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Организация"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Тема запроса"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Ф.И.О."));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Телефон"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Комментарий"));
    model->setSort(0, Qt::AscendingOrder);
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    emit updateTable(model);
    db.close();

}

void DBquery::queryTypes()
{
    db.open();
    str.clear();
    if (db.open())
    {
        QSqlQuery query;
        query.exec("SELECT * FROM query_type ORDER BY q_type");
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
    db.close();
}

void DBquery::userToID(QString u)
{
    db.open();
    QSqlQuery qq;
    int id;
    qq.exec("SELECT id_user FROM users WHERE user LIKE '"+u+"'");
    while (qq.next())
    {
        id = qq.record().field(0).value().toInt();
        emit userID(id);
    }
    db.close();
}

void DBquery::getAddQueryT(int dateTime, QString sTime)
{
    db.open();
    QSqlQuery queryT;
    QString strQueryT = "INSERT INTO time(unixTime, strTime)"
                        "VALUES(:unixTime, :strTime)";
    queryT.prepare(strQueryT);
    queryT.bindValue(":unixTime", dateTime);
    queryT.bindValue(":strTime", sTime);
    queryT.exec();
    db.close();
}
