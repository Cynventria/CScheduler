#ifndef PEOPLE_H
#define PEOPLE_H
#include <string>
#include <QString>
using namespace std;

class People
{
public:
    People();
    People(QString,QString,QString,int,int);



    QString name;
    QString nickname;
    QString workGroup;
    int workGroupIndex;
    int team;

    int status;


};

#endif // PEOPLE_H
