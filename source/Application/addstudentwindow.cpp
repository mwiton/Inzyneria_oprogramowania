#include "addstudentwindow.h"
#include "ui_addstudentwindow.h"
#include<QDebug>

AddStudentWindow::AddStudentWindow(QSqlDatabase &d, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddStudentWindow)
{
    ui->setupUi(this);
    db = d;
    QSqlQuery query;
    query.exec("SELECT MAX(ID) FROM STUDENTS");
    query.next();
    id = query.value(0).toInt()+1;
    ui->label_ID->setText(QString::number(id));
}

AddStudentWindow::~AddStudentWindow()
{
    delete ui;
}

void AddStudentWindow::on_pushButton_clicked()
{
    QSqlQuery query;
    query.prepare("INSERT INTO STUDENTS(ID, NAME, ADDRESS, PHONE, EMAIL) VALUES (:id, :name, :address, :phone, :email)");
    query.bindValue(":id", id);
    query.bindValue(":name", ui->lineEditName->text());
    query.bindValue(":address", ui->lineEditAddress->text());
    query.bindValue(":phone", ui->lineEditPhone->text());
    query.bindValue(":email", ui->lineEditEmail->text());
    query.exec();
    this->close();
}

void AddStudentWindow::on_pushButton_2_clicked()
{
    this->close();
}
