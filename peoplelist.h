#ifndef PEOPLELIST_H
#define PEOPLELIST_H


#include <vector>
#include <people.h>

class PeopleList
{
public:
    PeopleList();
    //int total;
    vector<People> List;
    vector<string> workGroupList;


    //IMPORT USE
    int import();
    int importNick();
    void setCSV(string);
    string path;
    bool updated;

    int teamCount;
    vector<int> eachTeam;

    //SEARCH USE
    vector<People> searchByWork(int);
    vector<People> searchByTeam(int);

    int InTeam(int);

};


#endif // PEOPLELIST_H
