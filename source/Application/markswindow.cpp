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
    refreshModel();
    ui->tableView->setModel(model);
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
    QSqlQuery query;
    int numOfEvents, numOfStudents;
    query.prepare("SELECT ID FROM GROUPS WHERE NAME=:name");
    query.bindValue(":name", ui->comboBox->currentText());
    query.exec();
    query.next();
    idGroup = query.value(0).toString();
    query.prepare("SELECT COUNT(ID) FROM EVENTS WHERE ID_GROUP = :id");
    query.bindValue(":id", idGroup);
    query.exec();
    query.next();
    numOfEvents = query.value(0).toInt();
    query.prepare("SELECT COUNT(ID) FROM MEMBERS_OF_GROUPS WHERE GROUP_ID = :id");
    query.bindValue(":id", idGroup);
    query.exec();
    query.next();
    numOfStudents = query.value(0).toInt();
    createListOfEvents();
    if(model) delete model;
    model = new QStandardItemModel(numOfStudents, numOfEvents + 2, this);
    setHeadersName();
    fillMarks();
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
    QSqlQuery studentsQuery, eventsQuery;
    int record=0;
    QModelIndex index;
    studentsQuery.prepare("SELECT STUDENTS.ID, STUDENTS.NAME FROM MEMBERS_OF_GROUPS INNER JOIN STUDENTS ON STUDENTS.ID = MEMBERS_OF_GROUPS.STUDENT_ID WHERE MEMBERS_OF_GROUPS.GROUP_ID = :id");
    studentsQuery.bindValue(":id", idGroup);
    studentsQuery.exec();
    while(studentsQuery.next()){
        index = model->index(record, 0);
        model->setData(index, studentsQuery.value(1).toString());
        for(int i=0; i<events.size(); ++i){
            eventsQuery.prepare("SELECT VALUE FROM MARKS WHERE ID_EVENT= :idEvent AND ID_STUDENT= :idStudent");
            eventsQuery.bindValue(":idEvent", events[i].first);
            eventsQuery.bindValue(":idStudent", studentsQuery.value(0).toString());
            eventsQuery.exec();
            if(eventsQuery.first()){
                index = model->index(record, i+1);
                model->setData(index, eventsQuery.value(0).toFloat());
            }
            eventsQuery.first();

        }
        ++record;
    }
}
