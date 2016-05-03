#ifndef MARKSWINDOW_H
#define MARKSWINDOW_H

#include <QDialog>
#include <QtSql>
#include <QStandardItemModel>
#include <QPair>
#include <QList>

namespace Ui {
class MarksWindow;
}

class MarksWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MarksWindow(QSqlDatabase &d, QWidget *parent = 0);
    ~MarksWindow();

private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::MarksWindow *ui;
    QSqlDatabase db;
    QStandardItemModel *model=NULL;
    QString idGroup;
    QList<QPair<int, QString> > events; //Pair: id and name
    QList<QPair<int, QString> > students; //Pair: id and name
    void getGroupId();
    void createGroupList();
    void createStudentsList();
    void refreshModel();
    void createListOfEvents();
    void setHeadersName();
    void fillMarks();
};

#endif // MARKSWINDOW_H
