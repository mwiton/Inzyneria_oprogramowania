#ifndef EDITGROUPWINDOW_H
#define EDITGROUPWINDOW_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class EditGroupWindow;
}

class EditGroupWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditGroupWindow(QString i, QWidget *parent = 0);
    ~EditGroupWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::EditGroupWindow *ui;
    QString id;
};

#endif // EDITGROUPWINDOW_H
