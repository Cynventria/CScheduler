#include "people.h"

People::People()
{

}
People::People(QString name,QString nickname,QString workGroup,int workID,int team){

    this->name = name;
    this->nickname = nickname;
    this->workGroup = workGroup;
    this->workGroupIndex = workID;
    this->team = team;


    status = 1;
}
