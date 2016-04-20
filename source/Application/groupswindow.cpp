#include "groupswindow.h"
#include "ui_groupswindow.h"

GroupsWindow::GroupsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GroupsWindow)
{
    ui->setupUi(this);
}

GroupsWindow::~GroupsWindow()
{
    delete ui;
}
