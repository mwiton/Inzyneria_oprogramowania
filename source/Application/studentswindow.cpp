#include "studentswindow.h"
#include "ui_studentswindow.h"

StudentsWindow::StudentsWindow(QSqlDatabase &d, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentsWindow)
{
    ui->setupUi(this);
    db = d;
    model = new QSqlTableModel(this);
    model->setTable("STUDENTS");
    model->select();
    ui->tableView->setModel(model);
}

StudentsWindow::~StudentsWindow()
{
    delete ui;
    delete model;
}

void StudentsWindow::on_pushButton_clicked()
{
    AddStudentWindow window(db, this);
    window.setModal(true);
    window.exec();
    model->select();
}

void StudentsWindow::on_pushButton_3_clicked()
{
    QMessageBox messageBox;
    messageBox.setText("Do you want to remove this group?");
    messageBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    messageBox.setDefaultButton(QMessageBox::Yes);
    int ret = messageBox.exec();
    if(ret==QMessageBox::Yes){
        QModelIndexList indexList = ui->tableView->selectionModel()->selectedIndexes();
        int row, id;
        foreach (QModelIndex index, indexList) {
            row = index.row();
            model->removeRow(row);
            id = model->data(model->index(row, 0)).toInt();
            QSqlQuery query;
            query.prepare("DELETE FROM MEMBERS_OF_GROUPS WHERE STUDENT_ID=:id");
            query.bindValue(":id", id);
            query.exec();
            query.prepare("DELETE FROM MARKS WHERE ID_STUDENT=:id");
            query.bindValue(":id", id);
            query.exec();
        }
        model->select();
    }
}
