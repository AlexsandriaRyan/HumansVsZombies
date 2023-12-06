#ifndef FILES_CITY_H
#define FILES_CITY_H

#include "../inc/GameSpecs.h"

#include <iostream>
#include <sstream>

using namespace std;

class Organism;

class City {
protected:
    Organism *grid[GRIDSIZE][GRIDSIZE];
    int humans;
    int zombies;
    int generation;

public:
    City();
    virtual ~City();

    Organism *getOrganism (int x, int y);
    void setOrganism (Organism *organism, int x, int y);
    friend ostream& operator<< (ostream &output, City &city);
    void prepareCity();
    void turn();
    bool hasDiversity();
};

#endif //FILES_CITY_H