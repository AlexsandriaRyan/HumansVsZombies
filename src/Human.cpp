#include "../inc/GameSpecs.h"
#include "../inc/Human.h"
#include "../inc/City.h"

#include <algorithm>

// ---------- CONSTRUCTORS / DESTRUCTORS ----------
Human::Human() { }

Human::Human(City *city, int x, int y) {
    this->city = city;
    this->x = x;
    this->y = y;
    this->species = HUMAN;
    this->moved = false;
    this->survivalCounter = 0;
}

Human::~Human() = default;

// ---------- GETTERS ----------
int Human::getSpecies() {
    return HUMAN;
}

// ---------- FUNCTIONS ----------
void Human::turn() {
    if (!moved) {
        move();
        moved = true;
        survivalCounter++;
        if (survivalCounter == HUMAN_RECRUIT) { recruit(); survivalCounter = 0; }
    }
}

void Human::move() {
    // select a random direction from north/south/east/west
    int tempX = x;
    int tempY = y;
    int direction = rand() % NUM_DIRECTIONS;

    switch (direction) {
        case WEST:
            tempX = x-1;
            tempY = y;
            break;

        case NORTH:
            tempX = x;
            tempY = y+1;
            break;

        case EAST:
            tempX = x+1;
            tempY = y;
            break;

        case SOUTH:
            tempX = x;
            tempY = y-1;
            break;

        default:
            cout << "direction error...";
    }

    // move if the new space is within range & the new space is not occupied
    if ((tempX < GRIDSIZE && tempX >= 0 && tempY < GRIDSIZE && tempY >= 0)) {
        if (city->getOrganism(tempX, tempY)->getSpecies() == ORGANISM) {
            // set current place as blank organism
            Organism *temp = new Organism(city, x, y);
            city->setOrganism(temp, x, y);

            // set human to new x/y coordinates
            this->x = tempX;
            this->y = tempY;
            city->setOrganism(this, x, y);
        }
    }
}

void Human::recruit() {
    // randomize order of direction selection
    int directionArray[NUM_DIRECTIONS] = {WEST, NORTH, EAST, SOUTH};
    random_shuffle(begin(directionArray), end(directionArray));

    // continue trying until recruit succeeds (return) or until all directions exhausted
    for (int direction : directionArray) {
        switch (direction) {
            case WEST:
                if (x-1 >= 0 && city->getOrganism(x-1, y)->getSpecies() == ORGANISM) {
                    Human *temp = new Human(city, x - 1, y);
                    city->setOrganism(temp, x - 1, y);
                    return;
                }
                break;

            case NORTH:
                if (y+1 < GRIDSIZE && city->getOrganism(x, y+1)->getSpecies() == ORGANISM) {
                    Human *temp = new Human(city, x, y + 1);
                    city->setOrganism(temp, x, y + 1);
                    return;
                }
                break;

            case EAST:
                if (x+1 < GRIDSIZE && city->getOrganism(x+1, y)->getSpecies() == ORGANISM) {
                    Human *temp = new Human(city, x + 1, y);
                    city->setOrganism(temp, x + 1, y);
                    return;
                }
                break;

            case SOUTH:
                if (y-1 >= 0 && city->getOrganism(x, y-1)->getSpecies() == ORGANISM) {
                    Human *temp = new Human(city, x, y-1);
                    city->setOrganism(temp, x, y-1);
                    return;
                }
                break;

            default:
                cout << "direction error...";
        }
    }
}