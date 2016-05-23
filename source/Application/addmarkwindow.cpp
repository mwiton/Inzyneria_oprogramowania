#include "addmarkwindow.h"
#include "ui_addmarkwindow.h"

AddMarkWindow::AddMarkWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMarkWindow)
{
    ui->setupUi(this);
}

AddMarkWindow::~AddMarkWindow()
{
    delete ui;
}
