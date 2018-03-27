#include "user.h"
#include "widget.h"
#include "dbquery.h"
#include "addcall.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    user u;
    Widget w;
    addcall ac;
    DBquery dbq;
    QObject::connect(&u, SIGNAL(authSig(int,QString)), &w, SLOT(getId(int,QString)));
    QObject::connect(&ac, SIGNAL(addQuery(int,int,QString,QString,QString,QString)), &dbq, SLOT(getAddQuery(int,int,QString,QString,QString,QString)));

    QObject::connect(&u, SIGNAL(btnClick()), &dbq, SLOT(updTable()));
    QObject::connect(&ac, SIGNAL(updTbl()), &dbq, SLOT(updTable()));
    QObject::connect(&dbq, SIGNAL(updateTable(QSqlRelationalTableModel*)), &w, SLOT(updateTable(QSqlRelationalTableModel*)));

    QObject::connect(&dbq, SIGNAL(userList(QList<QSqlRecord>)), &u, SLOT(userAuth(QList<QSqlRecord>)));
    QObject::connect(&dbq, SIGNAL(userList(QList<QSqlRecord>)), &w, SLOT(getUsername(QList<QSqlRecord>)));
    QObject::connect(&u, SIGNAL(btnClick()), &dbq, SLOT(checkUser()));

    QObject::connect(&w, SIGNAL(giveID(int)), &ac, SLOT(getID(int)));
    QObject::connect(&w, SIGNAL(properties()), &dbq, SLOT(queryTypes()));
    QObject::connect(&dbq, SIGNAL(giveQueryTypes(QStringList)), &w, SLOT(getQueryTypes(QStringList)));

    QObject::connect(&ac, SIGNAL(askQueryTypes()), &dbq, SLOT(queryTypes()));
    QObject::connect(&dbq, SIGNAL(giveQueryTypes(QStringList)), &ac, SLOT(getQueryTypes(QStringList)));


    //QObject::connect(&w, SIGNAL(giveFoundVal(int,QString,QString,QString,QString,QString,QString,QString)), &dbq, SLOT(getFoundVal(int,QString,QString,QString,QString,QString,QString,QString)));
    QObject::connect(&w, SIGNAL(upd()), &dbq, SLOT(updTable()));
    u.show();
    return a.exec();
}
