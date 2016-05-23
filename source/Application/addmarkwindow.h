#ifndef ADDMARKWINDOW_H
#define ADDMARKWINDOW_H

#include <QDialog>

namespace Ui {
class AddMarkWindow;
}

class AddMarkWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddMarkWindow(QWidget *parent = 0);
    ~AddMarkWindow();

private:
    Ui::AddMarkWindow *ui;
};

#endif // ADDMARKWINDOW_H
