#ifndef FILES_ORGANISM_H
#define FILES_ORGANISM_H

#include "../inc/GameSpecs.h"

#include <windows.h>
#include <iostream>
#include <sstream>

using namespace std;

class City;

class Organism {
protected:
    int x;
    int y;
    int species;
    bool moved;
    City* city;

    virtual ostream& put(ostream &output) {
        Color(TEXT_COLOR);
        output << " - ";
        return output;
    }

public:
    Organism();
    Organism(City *city, int x, int y);
    virtual ~Organism();

    virtual int getSpecies();
    virtual void turn();
    virtual void move();
    void resetMoved();
    void Color(int c);

    friend ostream& operator<<(ostream &output, Organism *organism) {
        return organism->put(output);
    }
};

#endif //FILES_ORGANISM_H
