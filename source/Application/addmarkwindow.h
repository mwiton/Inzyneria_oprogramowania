#ifndef ADDMARKWINDOW_H
#define ADDMARKWINDOW_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class AddMarkWindow;
}

class AddMarkWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddMarkWindow(int event, int student, bool isEdit, QWidget *parent = 0);
    ~AddMarkWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AddMarkWindow *ui;
    int eventID;
    int studentID;
    int markID;
    bool editMode;
};

#endif // ADDMARKWINDOW_H
