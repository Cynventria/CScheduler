#ifndef EVENTS_H
#define EVENTS_H
#include <QTime>
#include "people.h"
#include <vector>
using namespace std;


class Events
{
public:
    Events();

    QTime startTime;
    QTime endTime;
    QString title;
    QString note;
    vector<People> away;
    bool NoteEndTime;

};

#endif // EVENTS_H
