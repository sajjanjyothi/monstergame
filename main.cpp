#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <random>
#include "main.hpp"

using namespace std;

//Load the city from file to map
int loadMap(vector<City> &mapVector)
{
    string line;
    std::ifstream infile("map.txt");

    while (getline(infile, line))
    {
        string cityName = "";
        string east = "";
        string west = "";
        string south = "";
        string north = "";

        istringstream iss(line);
        iss >> cityName;
        string subLine;
        while (iss)
        {
            //read line by line and tokenize it
            iss >> subLine;
            //Parsing cardinal directions
            size_t found = subLine.find("east");
            if (found != string::npos)
            {
                east = subLine.substr(subLine.find("=") + 1, (subLine.size() - subLine.find("=")));
            }
            found = subLine.find("west");
            if (found != string::npos)
            {
                west = subLine.substr(subLine.find("=") + 1, (subLine.size() - subLine.find("=")));
            }
            found = subLine.find("south");
            if (found != string::npos)
            {
                south = subLine.substr(subLine.find("=") + 1, (subLine.size() - subLine.find("=")));
            }
            found = subLine.find("north");
            if (found != string::npos)
            {
                north = subLine.substr(subLine.find("=") + 1, (subLine.size() - subLine.find("=")));
            }
        }
        City obj(cityName, east, west, south, north);
        mapVector.push_back(obj);
    }
    infile.close();
    return 0;
}

//Deploy monsters initially
int deployMonsters(int count, vector<City> &mapVector, vector<Monster *> &monsterVector)
{
    random_device rd;
    mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, count); //Random generation

    while (count > 0)
    {
        int num = dis(gen);
        City city = mapVector[num];
        Monster *obj = new Monster(num, city.getName());
        monsterVector.push_back(obj);

        if (!city.getMonster1()) //check whether monster is NULL
        {
            city.setMonster1(obj);
        }
        else if (!city.getMonster2()) //check whether monster is NULL
        {
            city.setMonster2(obj);
        }
        else //both monsters met each other in initialisation itself , destroy city and monster
        {
            auto it = find_if(mapVector.begin(), mapVector.end(), [&](City a) { return a.getName() == city.getName(); });
            if (it != mapVector.end())
            {
                mapVector.erase(it);
            }
            auto monstIt1 = find_if(monsterVector.begin(), monsterVector.end(), [&](Monster *a) { return a->getNumber() == city.getMonster1()->getNumber(); });
            if (monstIt1 != monsterVector.end())
            {
                monsterVector.erase(monstIt1);
                delete (*monstIt1);
            }
            auto monstIt2 = find_if(monsterVector.begin(), monsterVector.end(), [&](Monster *a) { return a->getNumber() == city.getMonster2()->getNumber(); });
            if (monstIt2 != monsterVector.end())
            {
                monsterVector.erase(monstIt2);
                delete (*monstIt2);
            }
        }
        count--;
    }
    return 0;
}

// place monsters randomly within east/west/south/north
//Randomly placed 1->East,2->West,3->South,4->North
void processMonsters(vector<Monster *> &monsterVector, vector<City> &mapVector)
{
    int movements = 0;
    random_device rd;
    mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 4);

    while (movements < 100)
    {

        string nextCity;
        int monsterCount = 0;

        while (monsterCount < monsterVector.size())
        {
            int num = dis(gen);
            Monster *monster = monsterVector[monsterCount];
            auto it = find_if(mapVector.begin(), mapVector.end(), [&](City a) { return a.getName() == monster->getCity(); });
            //Set city Monsters
            if (!it->getMonster1())
            {
                //Same number monsters should not be there in same city
                if (it->getMonster2())
                {
                    if (it->getMonster2()->getNumber() != monster->getNumber())
                    {
                        it->setMonster1(monster);
                    }
                }
                else
                {
                    it->setMonster1(monster);
                }
            }
            else if (!it->getMonster2())
            {
                 //Same number monsters should not be there in same city
                if (it->getMonster1()->getNumber() != monster->getNumber())
                {
                    it->setMonster2(monster);
                }
            }
            bool addMonster = false;
            switch (num)
            {
            case 1: //east
            {
                if (it != mapVector.end())
                {
                    nextCity = it->getEast();
                    /* two monsters available in city */
                    if (it->getMonster1() && it->getMonster2())
                    {
                        auto monstIt1 = find_if(monsterVector.begin(), monsterVector.end(), [&](Monster *a) { return a->getNumber() == it->getMonster1()->getNumber(); });
                        if (monstIt1 != monsterVector.end())
                        {
                            delete (*monstIt1);
                            monsterVector.erase(monstIt1);
                        }
                        auto monstIt2 = find_if(monsterVector.begin(), monsterVector.end(), [&](Monster *a) { return a->getNumber() == it->getMonster2()->getNumber(); });
                        if (monstIt2 != monsterVector.end())
                        {
                            delete (*monstIt2);
                            monsterVector.erase(monstIt2);
                        }
                        mapVector.erase(it);
                    }
                    else
                    {
                        addMonster = true;
                    }
                }
            }
            break;
            case 2: //west
            {
                if (it != mapVector.end())
                {
                    nextCity = it->getWest();
                    /* two monsters available in city */
                    if (it->getMonster1() && it->getMonster2())
                    {

                        auto monstIt1 = find_if(monsterVector.begin(), monsterVector.end(), [&](Monster *a) { return a->getNumber() == it->getMonster1()->getNumber(); });
                        if (monstIt1 != monsterVector.end())
                        {
                            delete (*monstIt1);
                            monsterVector.erase(monstIt1);
                        }
                        auto monstIt2 = find_if(monsterVector.begin(), monsterVector.end(), [&](Monster *a) { return a->getNumber() == it->getMonster2()->getNumber(); });
                        if (monstIt2 != monsterVector.end())
                        {
                            delete (*monstIt2);
                            monsterVector.erase(monstIt2);
                        }
                        mapVector.erase(it);
                    }
                    else
                    {
                        addMonster = true;
                    }
                }
            }
            break;
            case 3: //south
            {
                if (it != mapVector.end())
                {
                    nextCity = it->getSouth();
                    /* two monsters available in city */
                    if (it->getMonster1() && it->getMonster2())
                    {

                        auto monstIt1 = find_if(monsterVector.begin(), monsterVector.end(), [&](Monster *a) { return a->getNumber() == it->getMonster1()->getNumber(); });
                        if (monstIt1 != monsterVector.end())
                        {
                            delete (*monstIt1);
                            monsterVector.erase(monstIt1);
                        }
                        auto monstIt2 = find_if(monsterVector.begin(), monsterVector.end(), [&](Monster *a) { return a->getNumber() == it->getMonster2()->getNumber(); });
                        if (monstIt2 != monsterVector.end())
                        {
                            delete (*monstIt2);
                            monsterVector.erase(monstIt2);
                        }
                        mapVector.erase(it);
                    }
                    else
                    {
                        addMonster = true;
                    }
                }
            }
            break;
            case 4: //north
            {
                if (it != mapVector.end())
                {
                    nextCity = it->getNorth();
                    /* two monsters available in city */
                    if (it->getMonster1() && it->getMonster2())
                    {

                        auto monstIt1 = find_if(monsterVector.begin(), monsterVector.end(), [&](Monster *a) { return a->getNumber() == it->getMonster1()->getNumber(); });
                        if (monstIt1 != monsterVector.end())
                        {
                            delete (*monstIt1);
                            monsterVector.erase(monstIt1);
                        }
                        auto monstIt2 = find_if(monsterVector.begin(), monsterVector.end(), [&](Monster *a) { return a->getNumber() == it->getMonster2()->getNumber(); });
                        if (monstIt2 != monsterVector.end())
                        {
                            delete (*monstIt2);
                            monsterVector.erase(monstIt2);
                        }
                        mapVector.erase(it);
                    }
                    else
                    {
                        addMonster = true;
                    }
                }
            }
            break;
            default:
                break;
            }
            //Monster can be changed
            if (addMonster)
            {
                monster->setCity(nextCity);
                monsterVector[monsterCount] = monster;
            }
            monsterCount++;
        }
        movements++;
    }
}

int main(int argc, char *argv[])
{
    vector<City> mapVector;
    vector<Monster *> monsterVector;

    loadMap(mapVector);

    int monsterCount = stoi(argv[1]);

    deployMonsters(monsterCount, mapVector, monsterVector);

    processMonsters(monsterVector, mapVector);

    //Print remaining city

    for (auto city : mapVector)
    {
        cout << city << endl;
    }

    return 0;
}
