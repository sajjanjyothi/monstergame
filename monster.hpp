#ifndef __MONSTER_H__
#define __MONSTER_H__
#include<string>
using namespace std;
class Monster
{
    int monster;
    string cityName;
public:
    Monster(int number, string cityRef):monster(number),cityName(cityRef){}
    Monster(){}
    int getNumber();
    string getCity();
    void setCity(string city);
};
#endif //__MONSTER_H__
