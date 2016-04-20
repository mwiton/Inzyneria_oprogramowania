#ifndef STUDENTSWINDOW_H
#define STUDENTSWINDOW_H

#include <QDialog>
#include <QtSql>
#include "addstudentwindow.h"

namespace Ui {
class StudentsWindow;
}

class StudentsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StudentsWindow(QSqlDatabase &d, QWidget *parent=0);
    ~StudentsWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::StudentsWindow *ui;
    QSqlDatabase db;
    QSqlTableModel *model;
};

#endif // STUDENTSWINDOW_H
