#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //this->setStyleSheet("background-image: url(:/resourse/images/bg1.jpg);");
    //this->setAttribute(Qt::WA_TranslucentBackground);
    //brush = new QBrush;
    //palette = new QPalette;
    //brush->setTextureImage(QImage(":/resourse/images/bg1.jpg"));
    //palette->setBrush(QPalette::Window, *brush);
    //this->setPalette(*palette);
    this->setWindowTitle("Фиксатор звонков - 2000");
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
    //delete brush;
    //delete palette;
}

void Widget::getId(int ID, QString uName)
{
    this->show();
    ui->label->setText(uName);
    userID = ID;
    username = uName;
    emit properties();
    emit ui->pushButton_3->clicked();
}

void Widget::on_pushButton_clicked()
{
    emit giveID(userID);
}

void Widget::updateTable(QSqlRelationalTableModel *m)
{
    m->setRelation(1, QSqlRelation("users", "id_user", "user"));
    m->setRelation(2, QSqlRelation("time", "unixTime", "strTime"));
    m->select();
    if (qpString != "")
    {
        m->setFilter(qpString);
        qpString = "";
    } else {}
    ui->tableView->setModel(m);
    ui->tableView->hideColumn(0);
    /*for (int i = 0; i<m->columnCount(); i++)
    {
        ui->tableView->setColumnWidth(i, (ui->tableView->width()-10)/(m->columnCount()-1));
    }*/
    ui->tableView->show();
    ui->dateTimeEdit_4->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());
    if (editStrategy)
    {
        ui->tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);
        editStrategy = false;
    } else {
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
    ui->tableView->setSortingEnabled(true);

    //ui->tableView->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    delegate = new NotEditableDelegate(this);
    Tdelegate = new queryTypeEditDelegate(this);
    connect(this, SIGNAL(giveQTypes(QStringList)), Tdelegate, SLOT(getQTypes(QStringList)));
    emit giveQTypes(qTypes);
    ui->tableView->setItemDelegateForColumn(1, delegate);
    ui->tableView->setItemDelegateForColumn(2, delegate);
    ui->tableView->setItemDelegateForColumn(4, Tdelegate);
}

void Widget::on_pushButton_2_clicked()
{
    int id = userID;
    QString unamestr;
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
        unamestr = ui->comboBox_2->currentText();
        emit userToId(unamestr);
        uname = QString::number(intUName);
        uString = " AND crm.user LIKE '%3%'";
    }
    //ORGANIZATION//
    QString org = ui->lineEdit->text();
    if (org != "")
    {
        oString = " AND crm.org LIKE '%%5%'";
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
        qString = " AND crm.query LIKE '%%4%'";
    }
    //DATE//
    int dateTimeFrom = ui->dateTimeEdit_3->dateTime().toTime_t();
    int dateTimeTo = ui->dateTimeEdit_4->dateTime().toTime_t();
    if (dateTimeFrom > dateTimeTo)
    {
        dateTimeFrom = dateTimeTo;
    }
    QString dTFString = "crm.dateTime BETWEEN '%1' AND '%2'";
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
    emit upd();
    ui->lineEdit->clear();
    Q_UNUSED(id);
}

void Widget::getQueryTypes(QStringList strL)
{
    ui->comboBox->clear();
    for (int i = 0; i<strL.count(); i++)
    {
        ui->comboBox->addItem(strL.value(i));
    }
    qTypes = strL;
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
    if (ui->checkBox->isChecked())
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
    qpString = "crm.dateTime BETWEEN "+QString::number(dateTimeFrom)+" AND "+QString::number(dateTimeTo) + " AND crm.user LIKE "+QString::number(userID);
    //QMessageBox::information(this, "", QString::number(userID));
    //QMessageBox::information(this, "", qpString);
    editStrategy = true;

    emit upd();
}

void Widget::getUserId(int id)
{
    intUName = id;
}

void Widget::dataChange(QModelIndex lT, QModelIndex bR)
{
    changeVal = ui->tableView->model()->data(lT).toString();

    Q_UNUSED(bR);
}

void Widget::on_checkBox_2_clicked()
{
    if (ui->checkBox_2->isChecked())
    {
        ui->comboBox->setEnabled(false);
    } else {
        ui->comboBox->setEnabled(true);
    }
}
