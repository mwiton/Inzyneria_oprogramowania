#include "addgroupwindow.h"
#include "ui_addgroupwindow.h"

AddGroupWindow::AddGroupWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddGroupWindow)
{
    ui->setupUi(this);
    QSqlQuery query;
    query.exec("SELECT MAX(ID) FROM GROUPS");
    query.next();
    id = query.value(0).toInt()+1;
    ui->label_ID->setText("ID: " + QString::number(id));
}

AddGroupWindow::~AddGroupWindow()
{
    delete ui;
}

void AddGroupWindow::on_pushButton_clicked()
{
    QSqlQuery query;
    query.prepare("INSERT INTO GROUPS(ID, NAME, SUBJECT, TEACHER, BEGIN_DATE) VALUES (:id, :name, :subject, :teacher, :date)");
    query.bindValue(":id", id);
    query.bindValue(":name", ui->lineEdit_name->text());
    query.bindValue(":subject", ui->lineEdit_subject->text());
    query.bindValue(":teacher", ui->lineEdit_teacher->text());
    query.bindValue(":date", ui->lineEdit_date->text());
    query.exec();
    this->close();
}

void AddGroupWindow::on_pushButton_2_clicked()
{
    this->close();
}
