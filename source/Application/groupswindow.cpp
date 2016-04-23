#include "groupswindow.h"
#include "ui_groupswindow.h"
#include <QtDebug>

GroupsWindow::GroupsWindow(QSqlDatabase &d, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GroupsWindow)
{
    ui->setupUi(this);
    db=d;
    studentsModel = new QSqlQueryModel();
    refreshGroupList();
}

void GroupsWindow::refreshGroupList(){
    QSqlQuery query;
    ui->comboBox->clear();
    query.exec("SELECT NAME FROM GROUPS");
    while(query.next()){
        ui->comboBox->insertItem(ui->comboBox->count(),query.value(0).toString());
    }
}

void GroupsWindow::refreshWindow(){
    studentsModel->setQuery("SELECT STUDENTS.ID, STUDENTS.NAME FROM STUDENTS INNER JOIN MEMBERS_OF_GROUPS ON STUDENTS.ID=MEMBERS_OF_GROUPS.STUDENT_ID WHERE GROUP_ID="+id);
    ui->tableView->setModel(studentsModel);
    ui->tableView->show();
}

GroupsWindow::~GroupsWindow()
{
    delete ui;
    delete studentsModel;
}

void GroupsWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(ui->comboBox->count()==0) return;
    QSqlQuery query;
    query.prepare("SELECT ID, NAME, SUBJECT, TEACHER, BEGIN_DATE FROM GROUPS WHERE NAME=:name");
    query.bindValue(":name", arg1);
    query.exec();
    query.next();
    ui->label_id->setText("ID: " + query.value(0).toString());
    ui->label_name->setText("Name: " + query.value(1).toString());
    ui->label_subject->setText("Subject: " + query.value(2).toString());
    ui->label_teacher->setText("Teacher: " + query.value(3).toString());
    ui->label_date->setText("Date of begin: " + query.value(4).toString());
    id = query.value(0).toString();
    refreshWindow();
}

void GroupsWindow::on_pushButton_addGroup_clicked()
{
    AddGroupWindow window(this);
    window.setModal(true);
    window.exec();
    refreshGroupList();
}

void GroupsWindow::on_pushButton_removeGroup_clicked()
{
    QSqlQuery query, query1;
    query.prepare("DELETE FROM GROUPS WHERE ID=:id");
    query1.prepare("DELETE FROM MEMBERS_OF_GROUPS WHERE GROUP_ID=:id");
    query.bindValue(":id", id);
    query.exec();
    query1.bindValue(":id", id);
    query1.exec();
    refreshGroupList();
}
