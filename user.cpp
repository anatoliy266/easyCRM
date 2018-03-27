#include "user.h"
#include "ui_user.h"

user::user(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::user)
{
    ui->setupUi(this);
}

user::~user()
{
    delete ui;
}

void user::on_pushButton_clicked()
{
    emit btnClick();
    emit uCheck();
}

void user::on_pushButton_2_clicked()
{
    QApplication::closeAllWindows();
}

void user::userAuth(QList<QSqlRecord> rec)
{
    lRec = rec;
    bool t = true;
    //QMessageBox::information(this, "ERROR", QString::number(lRec.count()));
            for (int i = 0; i<lRec.count(); i++)
            {
                if (ui->lineEdit->text() == lRec.value(i).field(1).value().toString() && ui->lineEdit_2->text() == lRec.value(i).field(2).value().toString())
                {

                    t = true;
                    username = lRec.value(i).field(1).value().toString();
                    id = i;
                    break;
                } else {
                    t = false;
                }
            }
            if (!t)
            {
                QMessageBox::information(this, "ERROR", "INCORRECT USER OR LOGIN!!!");
            } else {
                emit authSig(lRec.value(id).field(0).value().toInt(), username);

                this->hide();
            }
}
