#include "editgroupwindow.h"
#include "ui_editgroupwindow.h"

EditGroupWindow::EditGroupWindow(QString i, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditGroupWindow),
    id(i)
{
    ui->setupUi(this);
    QSqlQuery query;
    query.prepare("SELECT NAME, SUBJECT, TEACHER, BEGIN_DATE FROM GROUPS WHERE ID=:id");
    query.bindValue(":id", id);
    query.exec();
    query.next();
    ui->label_ID->setText("ID: " + id);
    ui->lineEdit_name->setText(query.value(0).toString());
    ui->lineEdit_subject->setText(query.value(1).toString());
    ui->lineEdit_teacher->setText(query.value(2).toString());
    ui->lineEdit_date->setText(query.value(3).toString());
}

EditGroupWindow::~EditGroupWindow()
{
    delete ui;
}

void EditGroupWindow::on_pushButton_clicked()
{
    QSqlQuery query;
    query.prepare("UPDATE GROUPS SET NAME=:name, SUBJECT=:subject, TEACHER=teacher, BEGIN_DATE=:date WHERE ID=:id");
    query.bindValue(":id", id);
    query.bindValue(":name", ui->lineEdit_name->text());
    query.bindValue(":subject", ui->lineEdit_subject->text());
    query.bindValue(":teacher", ui->lineEdit_teacher->text());
    query.bindValue(":date", ui->lineEdit_date->text());
    query.exec();
    this->close();
}

void EditGroupWindow::on_pushButton_2_clicked()
{
    this->close();
}
