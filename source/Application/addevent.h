#ifndef ADDEVENT_H
#define ADDEVENT_H

#include <QDialog>

namespace Ui {
class AddEvent;
}

class AddEvent : public QDialog
{
    Q_OBJECT

public:
    explicit AddEvent(QWidget *parent = 0);
    ~AddEvent();

private:
    Ui::AddEvent *ui;
};

#endif // ADDEVENT_H
