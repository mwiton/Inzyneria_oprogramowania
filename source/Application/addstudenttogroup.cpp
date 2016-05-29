#include "addstudenttogroup.h"
#include "ui_addstudenttogroup.h"

AddStudentToGroup::AddStudentToGroup(QString i, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddStudentToGroup),
    id(i)
{
    ui->setupUi(this);
    QSqlQuery query;
    query.exec("SELECT NAME FROM STUDENTS");
    while(query.next()){
        ui->comboBox->insertItem(ui->comboBox->count(),query.value(0).toString());
    }
}

AddStudentToGroup::~AddStudentToGroup()
{
    delete ui;
}

void AddStudentToGroup::on_pushButton_clicked()
{
    QSqlQuery query, query1, query2;
    query.prepare("INSERT INTO MEMBERS_OF_GROUPS(ID, STUDENT_ID, GROUP_ID) VALUES ((SELECT MAX(ID)+1 FROM MEMBERS_OF_GROUPS), :idS, :idG)");
    query.bindValue(":idG", id);
    query1.prepare("SELECT ID FROM STUDENTS WHERE NAME = :name");
    query1.bindValue(":name", ui->comboBox->currentText());
    query1.exec();
    query1.next();
    query2.prepare("SELECT COUNT(ID) FROM MEMBERS_OF_GROUPS WHERE STUDENT_ID = :ids AND GROUP_ID = :idg");
    query2.bindValue(":idg", id);
    query2.bindValue(":ids", query1.value(0).toInt());
    query2.exec();
    query2.next();
    if(query2.value(0).toInt()==1){
        QMessageBox msgBox;
        msgBox.setText("There is student with this name in this group.");
        msgBox.exec();
    }
    else{
        query.bindValue(":idS", query1.value(0).toInt());
        query.exec();
    }
    this->close();
}

void AddStudentToGroup::on_pushButton_2_clicked()
{
    this->close();
}
