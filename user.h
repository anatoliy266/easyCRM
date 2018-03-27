#ifndef USER_H
#define USER_H

#include <QWidget>
#include <QApplication>
#include <QtSql>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlField>

namespace Ui {
class user;
}

class user : public QWidget
{
    Q_OBJECT

public:
    explicit user(QWidget *parent = 0);
    ~user();

signals:
    void authSig(int id, QString uName);
    void btnClick();
    void uCheck();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
public slots:
    void userAuth(QList<QSqlRecord> rec);
private:
    Ui::user *ui;
    QSqlDatabase dbb;
    QList<QSqlRecord> lRec;
    int id;
    QString username;
};

#endif // USER_H
