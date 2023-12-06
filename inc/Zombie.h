#ifndef FILES_ZOMBIE_H
#define FILES_ZOMBIE_H

#include "../inc/GameSpecs.h"
#include "Organism.h"


class Zombie : public Organism {

protected:
    int starveCounter;
    int survivalCounter;
    enum directions { WEST, NORTHWEST, NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, NUM_DIRECTIONS };

    ostream& put(ostream &output) override {
        Color(ZOMBIE_COLOR);
        output << " Z ";
        Color(TEXT_COLOR);
        return output;
    }

public:
    Zombie();
    Zombie(City *city, int x, int y);
    virtual ~Zombie();

    int getSpecies();
    void turn();
    void move();
    void eat(int tempX, int tempY);
    void randomMove();
    void breed();
    void convert(int tempX, int tempY);
    void starve();




};

#endif //FILES_ZOMBIE_H
