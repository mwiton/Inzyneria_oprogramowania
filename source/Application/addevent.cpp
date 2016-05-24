#include "addevent.h"
#include "ui_addevent.h"

AddEvent::AddEvent(QString idG, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEvent),
    idGroup(idG)
{
    ui->setupUi(this);
    QSqlQuery query;
    query.prepare("SELECT MAX(ID) FROM EVENTS");
    query.exec();
    query.first();
    id = query.value(0).toInt()+1;
    ui->id_label->setText(QString::number(id));
}

AddEvent::~AddEvent()
{
    delete ui;
}

void AddEvent::on_add_pushButton_clicked()
{
    QSqlQuery query;
    query.prepare("INSERT INTO EVENTS VALUES (:id, :name, :description, :date, :weight, :idGroup)");
    query.bindValue(":date", ui->date_lineEdit->text());
    query.bindValue(":name", ui->name_lineEdit->text());
    query.bindValue(":description", ui->description_lineEdit->text());
    query.bindValue(":id", id);
    query.bindValue(":weight", ui->doubleSpinBox->value());
    query.bindValue(":idGroup", idGroup);
    query.exec();
    this->close();
}

void AddEvent::on_cancel_pushButton_clicked()
{
    this->close();
}
