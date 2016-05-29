#ifndef ADDSTUDENTTOGROUP_H
#define ADDSTUDENTTOGROUP_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class AddStudentToGroup;
}

class AddStudentToGroup : public QDialog
{
    Q_OBJECT

public:
    explicit AddStudentToGroup(QString i, QWidget *parent = 0);
    ~AddStudentToGroup();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AddStudentToGroup *ui;
    QString id;
};

#endif // ADDSTUDENTTOGROUP_H
