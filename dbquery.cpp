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

void DBquery::getAddQuery(int user, int dateTime, QString qquery, QString org, QString fio, QString phone, QString comment)
{
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

}

void DBquery::queryTypes()
{
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
}

void DBquery::userToID(QString u)
{
    QSqlQuery qq;
    int id;
    qq.exec("SELECT id_user FROM users WHERE user LIKE '"+u+"'");
    while (qq.next())
    {
        id = qq.record().field(0).value().toInt();
        emit userID(id);
    }

}

void DBquery::getAddQueryT(int dateTime, QString sTime)
{
    QSqlQuery queryT;
    QString strQueryT = "INSERT INTO time(unixTime, strTime)"
                        "VALUES(:unixTime, :strTime)";
    queryT.prepare(strQueryT);
    queryT.bindValue(":unixTime", dateTime);
    queryT.bindValue(":strTime", sTime);
    queryT.exec();
}
