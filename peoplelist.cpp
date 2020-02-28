#include "peoplelist.h"
#include <iostream>
#include <fstream>
#include <QString>
#include <QtDebug>
#include <QTextCodec>


PeopleList::PeopleList()
{
    List.clear();
    path.clear();
    updated = 0;
    teamCount = 0;
}


int PeopleList::import(){
    if(path.length() == 0) return 1; //no file set

    string tmpstr;
    QString tmpQstr, name, work, team;


    FILE* fp = fopen( path.c_str(), "r" );
    QTextStream in(fp, QIODevice::ReadOnly);
    in.setAutoDetectUnicode(true);

    if(fp != NULL) qDebug() << "opened" << endl;

    //FOR PRN FILE
    /*do{
        in >> name;
        if(name.size()==0)break;
        in >> work >> team;
        List.push_back(People(name, "", work, 0,team.toInt()));
        qDebug() << name << endl;



    }while(!name.isNull());*/

    do{
        in >> tmpQstr;
        if(tmpQstr.size()==0)break;
        int i;
        name.clear();
        work.clear();
        team.clear();

        for(i = 0; i < tmpQstr.size(); i++){
            if(tmpQstr[i] == ',')break;
            name += tmpQstr[i];
        }
        for(i++; i < tmpQstr.size(); i++){
            if(tmpQstr[i] == ',')break;
            work += tmpQstr[i];
        }
        for(i++; i < tmpQstr.size(); i++){
            team += tmpQstr[i];
        }
        List.push_back(People(name, "", work, 0,team.toInt()));
        if(team.toInt() > teamCount) teamCount = team.toInt();

    }while(!tmpQstr.isNull());

    eachTeam.resize(teamCount+1);
    for(int i = 0; i < List.size(); i++){
        eachTeam[List[i].team]++;
    }
    updated = 1;
    return 0;

}

void PeopleList::setCSV(string p){
    path = p;
    //std::cout << p << endl;

}
