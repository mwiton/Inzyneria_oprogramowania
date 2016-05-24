#ifndef ADDEVENT_H
#define ADDEVENT_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class AddEvent;
}

class AddEvent : public QDialog
{
    Q_OBJECT

public:
    explicit AddEvent(QString idG, QWidget *parent = 0);
    ~AddEvent();

private slots:
    void on_add_pushButton_clicked();

    void on_cancel_pushButton_clicked();

private:
    Ui::AddEvent *ui;
    int id;
    QString idGroup;
};

#endif // ADDEVENT_H
