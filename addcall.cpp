#include "addcall.h"
#include "ui_addcall.h"
#include <QDateTime>
#include <QTime>
#include <QComboBox>
#include <QMessageBox>
#include <ctime>
addcall::addcall(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addcall)
{
    ui->setupUi(this);
}

addcall::~addcall()
{
    delete ui;
}

void addcall::on_pushButton_clicked()
{
    QString org = ui->lineEdit->text();
    QString fio = ui->lineEdit_2->text();
    int user = userID;
    QDateTime qdate = QDateTime::currentDateTime();
    int dateTime = qdate.toTime_t();
    QString query = ui->comboBox->currentText();
    QString phone = ui->lineEdit_3->text();
    emit addQuery(user, dateTime, query, org, fio, phone);
    emit updTbl();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    this->hide();
}

void addcall::getID(int ID)
{
    userID = ID;
    emit askQueryTypes();
    this->show();
}

void addcall::getQueryTypes(QStringList str)
{
    //QMessageBox::information(this, "gebug", str.value(2));
    ui->comboBox->clear();
    for (int i = 0; i<str.count(); i++)
    {
        ui->comboBox->addItem(str.value(i));
        ui->comboBox->update();
    }
}
