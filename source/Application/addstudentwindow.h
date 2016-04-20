#ifndef ADDSTUDENTWINDOW_H
#define ADDSTUDENTWINDOW_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class AddStudentWindow;
}

class AddStudentWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddStudentWindow(QSqlDatabase &d, QWidget *parent = 0);
    ~AddStudentWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AddStudentWindow *ui;
    QSqlDatabase db;
    int id;
};

#endif // ADDSTUDENTWINDOW_H
