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
    float mark, sum, average, weight, sumOfWeight;
    for(int record=0; record<students.size(); ++record){
        sum=0;
        sumOfWeight = 0;
        index = model->index(record, 0);
        model->setData(index, students[record].second);
        for(int i=0; i<events.size(); ++i){
            marksQuery.prepare("SELECT VALUE, WEIGHT FROM MARKS INNER JOIN EVENTS ON ID_EVENT = EVENTS.ID WHERE ID_EVENT= :idEvent AND ID_STUDENT= :idStudent");
            marksQuery.bindValue(":idEvent", events[i].first);
            marksQuery.bindValue(":idStudent", students[record].first);
            marksQuery.exec();
            if(marksQuery.first()){
                mark = marksQuery.value(0).toFloat();
                weight = marksQuery.value(1).toFloat();
                index = model->index(record, i+1);
                model->setData(index, mark);
                sum+=mark*weight;
                sumOfWeight += weight;
            }
        }
        if(sum>0) average = sum/sumOfWeight;
        else average = 0;
        index = model->index(record, events.size()+1);
        model->setData(index, average);
    }
}

void MarksWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    refreshModel();
}


void MarksWindow::on_tableView_clicked(const QModelIndex &index)
{
    QSqlQuery eventQuery, markQuery;
    ui->date_event_label->setText("Date of event: ");
    ui->date_mark_label->setText("Date of mark: ");
    ui->description_label->setText("Description of event: ");
    ui->info_label->setText("Informations about mark: ");
    ui->name_label->setText("Name of event: ");
    ui->weight_label->setText("Weight: ");
    if (index.column() != 0 && index.column() != events.size()+1){
        int id_student = students[index.row()].first;
        int id_event = events[index.column()-1].first;
        eventQuery.prepare("SELECT NAME, DESCRIPTION, DATE, WEIGHT FROM EVENTS WHERE ID=:id");
        eventQuery.bindValue(":id", id_event);
        eventQuery.exec();
        eventQuery.first();
        ui->name_label->setText(ui->name_label->text()+eventQuery.value(0).toString());
        ui->description_label->setText(ui->description_label->text()+eventQuery.value(1).toString());
        ui->date_event_label->setText(ui->date_event_label->text()+eventQuery.value(2).toString());
        ui->weight_label->setText(ui->weight_label->text()+eventQuery.value(3).toString());
        markQuery.prepare("SELECT DATE, OTHER_INFO FROM MARKS WHERE ID_STUDENT=:ids AND ID_EVENT=:ide");
        markQuery.bindValue(":ids", id_student);
        markQuery.bindValue(":ide", id_event);
        markQuery.exec();
        if(markQuery.first()){
            ui->date_mark_label->setText(ui->date_mark_label->text()+markQuery.value(0).toString());
            ui->info_label->setText(ui->info_label->text()+markQuery.value(1).toString());
        }
    }
}

void MarksWindow::on_pushButton_clicked()
{
    QModelIndexList indexList = ui->tableView->selectionModel()->selectedIndexes();
    if(indexList.size()>0){
        QModelIndex index = indexList.first();
        if (index.column() != 0 && index.column() != events.size()+1){
            bool isEdit;
            if(index.data().isValid()) isEdit=true;
            else isEdit=false;
            AddMarkWindow  window(events[index.column()-1].first, students[index.row()].first, isEdit, this);
            window.setModal(true);
            window.exec();
            fillMarks();
        }
    }
}

void MarksWindow::on_addEventButton_clicked()
{
    AddEvent window(idGroup, this);
    window.setModal(true);
    window.exec();
    refreshModel();
}

void MarksWindow::on_deleteEventButton_clicked()
{
    QModelIndexList indexList = ui->tableView->selectionModel()->selectedIndexes();
    if(indexList.size()==0){
        QMessageBox msg;
        msg.setText("Choose event");
        msg.exec();
        return;
    }
    QModelIndex index = indexList.first();
    if (index.column() != 0 && index.column() != events.size()+1){
        int id;
        id = events[index.column()-1].first;
        QSqlQuery query;
        query.prepare("DELETE FROM EVENTS WHERE ID=:id");
        query.bindValue(":id", id);
        query.exec();
        query.prepare("DELETE FROM MARKS WHERE ID_EVENT=:id");
        query.bindValue(":id", id);
        query.exec();
        refreshModel();
    }
    else{
        QMessageBox msg;
        msg.setText("Choose event");
        msg.exec();
    }
}
