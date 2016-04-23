#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./database.db");
    db.open();
}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}

/*void MainWindow::init(){
    students.pushback(Student("aaa", "01-01-1995", "aaa@gmail.com", "ul. Wojska Polskiego 1, Szczecin"));
    students.pushback(Student("bbb", "01-02-1995", "bbb@gmail.com", "ul. Wojska Polskiego 2, Szczecin"));
    students.pushback(Student("ccc", "01-03-1995", "ccc@gmail.com", "ul. Wojska Polskiego 3, Szczecin"));
}*/

void MainWindow::on_pushButton_clicked()
{
    StudentsWindow studentsWindow(db, this);
    studentsWindow.setModal(true);
    studentsWindow.exec();
}



void MainWindow::on_pushButton_2_clicked()
{
    GroupsWindow groupsWindow(db, this);
    groupsWindow.setModal(true);
    groupsWindow.exec();
}
