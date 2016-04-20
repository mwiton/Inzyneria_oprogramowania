#ifndef GROUPSWINDOW_H
#define GROUPSWINDOW_H

#include <QDialog>

namespace Ui {
class GroupsWindow;
}

class GroupsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GroupsWindow(QWidget *parent = 0);
    ~GroupsWindow();

private:
    Ui::GroupsWindow *ui;
};

#endif // GROUPSWINDOW_H
