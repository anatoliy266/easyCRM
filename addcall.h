#ifndef ADDCALL_H
#define ADDCALL_H

#include <QWidget>

namespace Ui {
class addcall;
}

class addcall : public QWidget
{
    Q_OBJECT

public:
    explicit addcall(QWidget *parent = 0);
    ~addcall();
signals:
    void addQuery(int user, int dateTime, QString query, QString org, QString fio, QString phone, QString comment);
    void addQueryT(int dateTime, QString sTime);
    void askQueryTypes();
    void updTbl();
    void onlyMe();
public slots:
    void getID(int ID);
    void getQueryTypes(QStringList str);
    void notOpenDB(QString dbopen);
private slots:
    void on_pushButton_clicked();

private:
    Ui::addcall *ui;
    int userID;
};

#endif // ADDCALL_H
