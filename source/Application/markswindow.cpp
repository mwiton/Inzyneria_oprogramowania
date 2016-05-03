#include "markswindow.h"
#include "ui_markswindow.h"
#include <QtDebug>

MarksWindow::MarksWindow(QSqlDatabase &d, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MarksWindow),
    db(d)
{
    ui->setupUi(this);
    createGroupList();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

MarksWindow::~MarksWindow()
{
    delete ui;
    if(model) delete model;
}

void MarksWindow::createGroupList(){
    QSqlQuery query;
    ui->comboBox->clear();
    query.exec("SELECT NAME FROM GROUPS");
    while(query.next()){
        ui->comboBox->insertItem(ui->comboBox->count(),query.value(0).toString());
    }
}

void MarksWindow::refreshModel(){
    getGroupId();
    createListOfEvents();
    createStudentsList();
    if(model) delete model;
    model = new QStandardItemModel(students.size(), events.size() + 2, this);
    ui->tableView->setModel(model);
    setHeadersName();
    fillMarks();  
}

void MarksWindow::getGroupId(){
    QSqlQuery query;
    query.prepare("SELECT ID FROM GROUPS WHERE NAME=:name");
    query.bindValue(":name", ui->comboBox->currentText());
    query.exec();
    query.first();
    idGroup = query.value(0).toString();
}


void MarksWindow::createListOfEvents(){
    QSqlQuery query;
    query.prepare("SELECT ID, NAME FROM EVENTS WHERE ID_GROUP = :id");
    query.bindValue(":id", idGroup);
    query.exec();
    events.clear();
    while(query.next()){
        events.append(qMakePair(query.value(0).toInt(), query.value(1).toString()));
    }
}

void MarksWindow::createStudentsList(){
    QSqlQuery query;
    query.prepare("SELECT STUDENTS.ID, STUDENTS.NAME FROM MEMBERS_OF_GROUPS INNER JOIN STUDENTS ON STUDENTS.ID = MEMBERS_OF_GROUPS.STUDENT_ID WHERE MEMBERS_OF_GROUPS.GROUP_ID = :id");
    query.bindValue(":id", idGroup);
    query.exec();
    students.clear();
    while(query.next()){
        students.append(qMakePair(query.value(0).toInt(), query.value(1).toString()));
    }
}

void MarksWindow::setHeadersName(){
    QStringList labels;
    labels.append("Name of student");
    for(int i=0; i<events.size(); ++i){
        labels.append(events[i].second);
    }
    labels.append("Average");
    model->setHorizontalHeaderLabels(labels);
}

void MarksWindow::fillMarks(){
    QSqlQuery marksQuery;
    QModelIndex index;
    for(int record=0; record<students.size(); ++record){
        index = model->index(record, 0);
        model->setData(index, students[record].second);
        for(int i=0; i<events.size(); ++i){
            marksQuery.prepare("SELECT VALUE FROM MARKS WHERE ID_EVENT= :idEvent AND ID_STUDENT= :idStudent");
            marksQuery.bindValue(":idEvent", events[i].first);
            marksQuery.bindValue(":idStudent", students[record].first);
            marksQuery.exec();
            if(marksQuery.first()){
                index = model->index(record, i+1);
                model->setData(index, marksQuery.value(0).toFloat());
            }
        }
    }
}

void MarksWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    refreshModel();
}
