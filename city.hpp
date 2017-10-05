#ifndef __CITY_H__
#define __CITY_H__

using namespace std;
#include<string>
#include"monster.hpp"
class City{

private:
    string name;
    string north;
    string south;
    string east;
    string west;
    Monster monster1;
    Monster monster2;
public:
    City(string name, string east, string west, string south, string north):name(name),
        north(north),
        south(south),
        east(east),
        west(west){
            
        }
    City(){}

    void setMonster1(Monster monster1);
    void setMonster2(Monster monster2);
    int getMonster1();
    int getMonster2();
    string getName();
    string getEast();
    string getWest();
    string getSouth();
    string getNorth();
    friend ostream & operator << (ostream &os, const City &city);
};

#endif // __CITY_H__