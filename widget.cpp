#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::getId(int ID, QString uName)
{
    this->show();
    ui->label->setText(uName);
    userID = ID;
    username = uName;
    emit properties();
}

void Widget::on_pushButton_clicked()
{
    emit giveID(userID);
}

void Widget::updateTable(QSqlRelationalTableModel *m)
{
    m->setTable("crm");
    ui->tableView->setModel(m);
    if (qpString != "")
    {
        m->setFilter(qpString);
        //qpString = "";
    }
    m->select();
    if (!m->select())
    {
        QMessageBox::information(this, "error", qpString);
    }
    ui->tableView->hideColumn(0);
    ui->tableView->show();
    ui->dateTimeEdit_4->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());
}

void Widget::on_pushButton_2_clicked()
{
    int id = userID;
    QString uname;
    QString uString;
    QString query;
    QString qString;
    QString oString;
    //USER//
    if (ui->checkBox->isChecked())
    {
        uname = "";
        uString = "";
    } else {
        uname = ui->comboBox_2->currentText();
        uString = " AND user IN (%3)";
    }
    //ORGANIZATION//
    QString org = ui->lineEdit->text();
    if (org != "")
    {
        oString = " AND org IN (%5)";
    } else {
        oString = "";
    }
    //QUERY TYPE//
    if (ui->checkBox_2->isChecked())
    {
        query = "";
        qString = "";
    } else {
        query = ui->comboBox->currentText();
        qString = " AND query IN (%4)";
    }
    //DATE//
    int dateTimeFrom = ui->dateTimeEdit_3->dateTime().toTime_t();
    int dateTimeTo = ui->dateTimeEdit_4->dateTime().toTime_t();
    if (dateTimeFrom > dateTimeTo)
    {
        dateTimeFrom = dateTimeTo;
    }
    QString dTFString = "dateTime BETWEEN %1 AND %2";
    QueryString = dTFString+uString+qString+oString;

    if (uString != "")
    {
        if (qString != "")
        {
            if (oString != "")
            {
                qpString = QueryString.arg(QString::number(dateTimeFrom), QString::number(dateTimeTo), uname, query, org);
            } else {
                qpString = QueryString.arg(QString::number(dateTimeFrom), QString::number(dateTimeTo), uname, query);
            }
        } else {
            if (oString != "")
            {
                qpString = QueryString.arg(QString::number(dateTimeFrom), QString::number(dateTimeTo), uname, org);
            } else {
                qpString = QueryString.arg(QString::number(dateTimeFrom), QString::number(dateTimeTo), uname);
            }
        }
    } else {
        if (qString != "")
        {
            if (oString != "")
            {
                qpString = QueryString.arg(QString::number(dateTimeFrom), QString::number(dateTimeTo), query, org);
            } else {
                qpString = QueryString.arg(QString::number(dateTimeFrom), QString::number(dateTimeTo), query);
            }
        } else {
            if (oString != "")
            {
                qpString = QueryString.arg(QString::number(dateTimeFrom), QString::number(dateTimeTo), org);
            } else {
                qpString = QueryString.arg(QString::number(dateTimeFrom), QString::number(dateTimeTo));
            }
        }
    }
    QMessageBox::information(this, "error", qpString);
    emit upd();
}

void Widget::getQueryTypes(QStringList strL)
{
    ui->comboBox->clear();
    for (int i = 0; i<strL.count(); i++)
    {
        ui->comboBox->addItem(strL.value(i));
    }
}

void Widget::getUsername(QList<QSqlRecord> uList)
{
    ui->comboBox_2->clear();
    QStringList sList;
    for (int i = 0; i<uList.count(); i++)
    {
        sList.append(uList.value(i).field(1).value().toString());
    }
    for (int j = 0; j<sList.count(); j++)
    {
        ui->comboBox_2->addItem(sList.value(j));
    }
}


void Widget::on_checkBox_clicked()
{
    if (ui->checkBox_2->isChecked())
    {
        ui->comboBox_2->setEnabled(false);
    } else {
        ui->comboBox_2->setEnabled(true);
    }
}

void Widget::on_pushButton_3_clicked()
{
    qpString = "";
    emit upd();
}
