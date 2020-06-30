#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <QWidget>
#include "events.h"
#include <vector>
#include "peoplelist.h"
#include "workersui.h"
#include "workerselector.h"
using namespace std;

namespace Ui {
class Scheduler;
}

class Scheduler : public QWidget
{
    Q_OBJECT

public:
    explicit Scheduler(QWidget *parent = nullptr);
    ~Scheduler();

    vector<Events> events;
    int selectedEvent;
    int teamCount;
    void updateScheduler();
    PeopleList *ALLworkers;
    bool peopleUpdated;
    void setList(PeopleList* PList){ALLworkers = PList; workersUI.setList(PList);}
    bool nameMode;
    WorkerSelector wSelector;

    //QObject::connect(&wSelector, SIGNAL(workerChanged()), this, SLOT(EXTupdateScheduler()));

    WorkersUI workersUI;

public slots:
    void EXTupdateScheduler();

private slots:
    void on_pushButton_clicked();

    void on_tableWidget_itemSelectionChanged();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_textEdit_textChanged();

    void on_pushButton_5_clicked();

    void on_timeEdit_userTimeChanged(const QTime &time);

    void on_timeEdit_2_userTimeChanged(const QTime &time);

    void on_pushButton_7_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Scheduler *ui;
};

#endif // SCHEDULER_H
