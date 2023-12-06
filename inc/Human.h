#ifndef _Human_H
#define _Human_H

#include "../inc/GameSpecs.h"
#include "Organism.h"

class Human : public Organism {

protected:
    int survivalCounter;
    enum directions { WEST, NORTH, EAST, SOUTH, NUM_DIRECTIONS };

    ostream& put(ostream &output) override {
        Color(HUMAN_COLOR);
        output << " H ";
        Color(TEXT_COLOR);
        return output;
    }

public:
	Human(); 
	Human(City *city, int x, int y);
	virtual ~Human();

    int getSpecies();
    void turn();
	void move();
    void recruit();
};

#endif
