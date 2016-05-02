#ifndef GROUPSWINDOW_H
#define GROUPSWINDOW_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include "addgroupwindow.h"
#include "editgroupwindow.h"
#include "addstudenttogroup.h"

namespace Ui {
class GroupsWindow;
}

class GroupsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GroupsWindow(QSqlDatabase &d, QWidget *parent = 0);
    ~GroupsWindow();

private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_pushButton_addGroup_clicked();

    void on_pushButton_removeGroup_clicked();

    void on_pushButton_editGroup_clicked();

    void on_pushButton_addStudent_clicked();

    void on_pushButton_removeStudent_clicked();

private:
    Ui::GroupsWindow *ui;
    QSqlDatabase db;
    QString id;
    QSqlQueryModel *studentsModel;
    void refreshGroupList();
    void refreshWindow();

};

#endif // GROUPSWINDOW_H
