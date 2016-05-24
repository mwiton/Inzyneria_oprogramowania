#include "addmarkwindow.h"
#include "ui_addmarkwindow.h"
#include <QDebug>

AddMarkWindow::AddMarkWindow(int event, int student, bool isEdit, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMarkWindow),
    eventID(event),
    studentID(student),
    editMode(isEdit)
{
    ui->setupUi(this);
    QSqlQuery query;
    if(isEdit){
        query.prepare("SELECT ID, VALUE, OTHER_INFO FROM MARKS WHERE ID_STUDENT=:ids AND ID_EVENT=:ide");
        query.bindValue(":ids", studentID);
        query.bindValue(":ide", eventID);
        query.exec();
        query.first();
        markID = query.value(0).toInt();
        ui->doubleSpinBox->setValue(query.value(1).toDouble());
        ui->lineEdit_2->setText(query.value(2).toString());
    }
    else {
        query.prepare("SELECT MAX(ID) FROM MARKS");
        query.exec();
        query.first();
        markID = query.value(0).toInt()+1;
    }
    ui->id_label->setText(QString::number(markID));
    QDate currentDay = QDate::currentDate();
    ui->date_label->setText(currentDay.toString(Qt::ISODate));
}

AddMarkWindow::~AddMarkWindow()
{
    delete ui;
}

void AddMarkWindow::on_pushButton_clicked()
{
    QSqlQuery query;
    if(editMode){
        query.prepare("UPDATE MARKS SET DATE=:date, VALUE=:value, OTHER_INFO=:info WHERE ID=:id");
        query.bindValue(":date", ui->date_label->text());
        query.bindValue(":value", ui->doubleSpinBox->value());
        query.bindValue(":info", ui->lineEdit_2->text());
        query.bindValue(":id", markID);
        query.exec();
    }
    else{
        query.prepare("INSERT INTO MARKS VALUES (:id, :value, :ids, :date, :ide, :info)");
        query.bindValue(":date", ui->date_label->text());
        query.bindValue(":value", ui->doubleSpinBox->value());
        query.bindValue(":info", ui->lineEdit_2->text());
        query.bindValue(":id", markID);
        query.bindValue(":ids", studentID);
        query.bindValue(":ide", eventID);
        query.exec();
    }
    this->close();
}

void AddMarkWindow::on_pushButton_2_clicked()
{
    this->close();
}
