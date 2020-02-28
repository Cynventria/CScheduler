#include "mainwindow.h"
#include <QApplication>
#include "peoplelist.h"
#include "workersui.h"
#include "scheduler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //PeopleList Workers;
    //WorkersUI workersUI;
    //workersUI.Workers = &Workers;
    //workersUI.show();

    PeopleList ALLWORKERS;
    //workersUI.setList(&ALLWORKERS);

    Scheduler scheduler;
    scheduler.show();
    scheduler.setList(&ALLWORKERS);


    return a.exec();
}
