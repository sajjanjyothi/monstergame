#include "city.hpp"
#include <iostream>
void City::setMonster1(Monster monster1)
{
    this->monster1 = monster1;
}
void City::setMonster2(Monster monster2)
{
    this->monster2 = monster2;
}
int City::getMonster1()
{
    return monster1.getNumber();
}

int City::getMonster2()
{
    return monster2.getNumber();
}

string City::getName()
{
    return name;
}
string City::getEast()
{
    return east;
}
string City::getWest()
{
    return west;
}

string City::getSouth()
{
    return south;
}
string City::getNorth()
{
    return north;
}
ostream &operator<<(ostream &os, const City &city)
{
    return os << city.name << " East=" << city.east << " West=" << city.west << " South=" << city.south << " North=" << city.north;
}