#ifndef ADDGROUPWINDOW_H
#define ADDGROUPWINDOW_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class AddGroupWindow;
}

class AddGroupWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddGroupWindow(QWidget *parent = 0);
    ~AddGroupWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AddGroupWindow *ui;
    int id;
};

#endif // ADDGROUPWINDOW_H
