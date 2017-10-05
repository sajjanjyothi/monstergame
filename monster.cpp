#include "monster.hpp"

int Monster::getNumber()
{
    return monster;
}

string Monster::getCity()
{
    return cityName;
}

void Monster::setCity(string city)
{
    cityName = city;
}