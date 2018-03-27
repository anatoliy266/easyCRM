#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QGridLayout* GL = new QGridLayout();
    for (int i =0; i<3; i++)
    {
        GL->setColumnMinimumWidth(i, this->width()/4);
    }
    for (int j = 0; j<9; j++)
    {
        GL->setRowMinimumHeight(j, this->height()/10);
    }

    GL->addWidget(ui->label, 0, 0);
    GL->addWidget(ui->groupBox, 1, 0, 7, 1);
    GL->addWidget(ui->pushButton, 8, 0, 2, 1);
    GL->addWidget(ui->tableView, 0, 1, 9, 3);
    GL->addWidget(ui->dateTimeEdit, 9, 1);
    GL->addWidget(ui->dateTimeEdit_2, 9, 2);
    GL->addWidget(ui->pushButton_3, 9, 3);
    this->setLayout(GL);
    QGridLayout* cbGL = new QGridLayout();
    cbGL->addWidget(ui->label_2, 0, 0, 1, 4);
    cbGL->addWidget(ui->comboBox_2, 1, 0, 1, 3);
    cbGL->addWidget(ui->checkBox, 1, 3);
    cbGL->addWidget(ui->label_3, 2, 0, 1, 3);
    cbGL->addWidget(ui->lineEdit, 3, 0, 1, 4);
    cbGL->addWidget(ui->label_4, 4, 0, 1, 4);
    cbGL->addWidget(ui->comboBox, 5, 0, 1, 3);
    cbGL->addWidget(ui->checkBox_2, 5, 3);
    cbGL->addWidget(ui->groupBox_2, 6, 0, 3, 4);
    cbGL->addWidget(ui->pushButton_2, 9, 0, 1, 4);
    ui->groupBox->setLayout(cbGL);
    QGridLayout* cb2GL = new QGridLayout();
    cb2GL->addWidget(ui->label_5, 0, 0, 1, 4);
    cb2GL->addWidget(ui->dateTimeEdit_3, 1, 0, 1, 4);
    cb2GL->addWidget(ui->label_6, 2, 0, 1, 4);
    cb2GL->addWidget(ui->dateTimeEdit_4, 3, 0, 1, 4);
    ui->groupBox_2->setLayout(cb2GL);
    ui->dateTimeEdit_4->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_3->setDateTime(QDateTime::fromTime_t(QDateTime::currentDateTime().toTime_t()-86400));
    ui->dateTimeEdit->setDateTime(QDateTime::fromTime_t(QDateTime::currentDateTime().toTime_t()-86400));
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
    //m->setTable("crm");
    m->setRelation(1, QSqlRelation("users", "id_user", "user"));
    //QMessageBox::information(this, "ololo", qpString);

    int coll = m->fieldIndex("dateTime");
    m->select();
    if (qpString != "")
    {

        if (uT.count() != 0)
        {
            for (int j = 0; j<m->rowCount(); j++)
            {
                m->setData(m->index(j, coll), uT.value(j));
            }
            uT.clear();
            m->setFilter(qpString);
            qpString = "";
        }
    } else {

    }
    for (int i = 0; i<m->rowCount(); i++)
    {

        uT.append(m->data(m->index(i, coll)));
        QDateTime dT = QDateTime::fromTime_t(m->data(m->index(i, coll)).toInt());
        m->setData(m->index(i, coll), dT);
    }
    //m->submitAll();
    ui->tableView->setModel(m);
    ui->tableView->hideColumn(0);
    for (int i = 0; i<m->columnCount(); i++)
    {
        ui->tableView->setColumnWidth(i, (ui->tableView->width()-10)/(m->columnCount()-1));
    }
    ui->tableView->show();
    ui->dateTimeEdit_4->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());
    //qpString = "";
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
    //QMessageBox::information(this, "error", qpString);
    emit upd();
    //emit upd();
    Q_UNUSED(id);
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
    int dateTimeFrom = ui->dateTimeEdit->dateTime().toTime_t();
    int dateTimeTo = ui->dateTimeEdit_2->dateTime().toTime_t();
    qpString = "dateTime BETWEEN "+QString::number(dateTimeFrom)+" AND "+QString::number(dateTimeTo);
    emit upd();
}
