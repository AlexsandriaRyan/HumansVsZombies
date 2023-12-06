#include "../inc/GameSpecs.h"
#include "../inc/Zombie.h"
#include "../inc/City.h"
#include "../inc/Human.h"

#include <algorithm>

// ---------- CONSTRUCTORS / DESTRUCTORS ----------
Zombie::Zombie() { }

Zombie::Zombie(City *city, int x, int y) {
    this->city = city;
    this->x = x;
    this->y = y;
    this->species = ZOMBIE;
    this->moved = false;
    this->starveCounter = 0;
    this->survivalCounter = 0;
}

Zombie::~Zombie() = default;

// ---------- GETTERS ----------
int Zombie::getSpecies() {
    return ZOMBIE;
}

// ---------- FUNCTIONS ----------
void Zombie::turn() {
    if (!moved) {
        move();
        moved = true;
        survivalCounter++;
        if (survivalCounter == ZOMBIE_BREED) { breed(); }
        if (starveCounter == ZOMBIE_STARVE) { starve(); }
    }
}

void Zombie::move() {
    // randomize order of direction selection
    int directionArray[NUM_DIRECTIONS] = {WEST, NORTHWEST, NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST};
    random_shuffle(begin(directionArray), end(directionArray));

    // continue trying until breed succeeds (return) or until all directions exhausted
    for (int direction: directionArray) {
        switch (direction) {
            case WEST:
                if (x-1 >= 0 && city->getOrganism(x-1, y)->getSpecies() == HUMAN) {
                    eat(x-1, y);
                    return;
                }
                break;

            case NORTHWEST:
                if (x-1 >= 0 && y+1 < GRIDSIZE && city->getOrganism(x-1, y+1)->getSpecies() == HUMAN) {
                    eat(x-1, y+1);
                    return;
                }
                break;

            case NORTH:
                if (y+1 < GRIDSIZE && city->getOrganism(x, y+1)->getSpecies() == HUMAN) {
                    eat(x, y+1);
                    return;
                }
                break;

            case NORTHEAST:
                if (x+1 < GRIDSIZE && y+1 < GRIDSIZE && city->getOrganism(x+1, y+1)->getSpecies() == HUMAN) {
                    eat(x+1, y+1);
                    return;
                }
                break;

            case EAST:
                if (x+1 < GRIDSIZE && city->getOrganism(x+1, y)->getSpecies() == HUMAN) {
                    eat(x+1, y);
                    return;
                }
                break;

            case SOUTHEAST:
                if (x+1 < GRIDSIZE && y-1 >= 0 && city->getOrganism(x+1, y)->getSpecies() == HUMAN) {
                    eat(x+1, y-1);
                    return;
                }
                break;

            case SOUTH:
                if (y-1 >= 0 && city->getOrganism(x, y-1)->getSpecies() == HUMAN) {
                    eat(x, y-1);
                    return;
                }
                break;

            case SOUTHWEST:
                if (x-1 >= 0 && y-1 >= 0 && city->getOrganism(x, y-1)->getSpecies() == HUMAN) {
                    eat(x-1, y-1);
                    return;
                }
                break;

            default:
                cout << "direction error...";
        }
    }
    // if zombie was unable to eat, move randomly
    randomMove();
    starveCounter++;
}

void Zombie::eat(int tempX, int tempY) {
    if ((tempX < GRIDSIZE && tempX >= 0 && tempY < GRIDSIZE && tempY >= 0)) {
        // delete human
        delete city->getOrganism(tempX, tempY);

        // set current place as blank organism
        Organism *temp = new Organism(city, x, y);
        city->setOrganism(temp, x, y);

        // set zombie to new x/y coordinates
        this->x = tempX;
        this->y = tempY;
        city->setOrganism(this, x, y);
    }

    starveCounter = 0;
}

void Zombie::randomMove() {
    // select a random direction from west/northwest/north/northeast/east/southeast/south/southwest
    int tempX = x;
    int tempY = y;
    int direction = rand() % NUM_DIRECTIONS;

    switch (direction) {
        case WEST:
            tempX = x-1;
            tempY = y;
            break;

        case NORTHWEST:
            tempX = x-1;
            tempY = y+1;
            break;

        case NORTH:
            tempX = x;
            tempY = y+1;
            break;

        case NORTHEAST:
            tempX = x+1;
            tempY = y+1;
            break;

        case EAST:
            tempX = x+1;
            tempY = y;
            break;

        case SOUTHEAST:
            tempX = x+1;
            tempY = y-1;
            break;

        case SOUTH:
            tempX = x;
            tempY = y-1;
            break;

        case SOUTHWEST:
            tempX = x-1;
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

            // set zombie to new x/y coordinates
            this->x = tempX;
            this->y = tempY;
            city->setOrganism(this, x, y);
        }
    }
}

void Zombie::breed() {
    // randomize order of direction selection
    int directionArray[NUM_DIRECTIONS] = {WEST, NORTH, EAST, SOUTH};
    random_shuffle(begin(directionArray), end(directionArray));

    // continue trying until breed succeeds or until all directions exhausted
    for (int direction: directionArray) {
        switch (direction) {
            case WEST:
            if (x - 1 >= 0 && city->getOrganism(x - 1, y)->getSpecies() == HUMAN) {
                convert(x - 1, y);
                survivalCounter = 0;
                return;
            }
            break;

            case NORTHWEST:
                if (x - 1 >= 0 && y + 1 < GRIDSIZE && city->getOrganism(x - 1, y + 1)->getSpecies() == HUMAN) {
                    convert(x - 1, y + 1);
                    survivalCounter = 0;
                    return;
                }
                break;

            case NORTH:
                if (y + 1 < GRIDSIZE && city->getOrganism(x, y + 1)->getSpecies() == HUMAN) {
                    convert(x, y + 1);
                    survivalCounter = 0;
                    return;
                }
                break;

            case NORTHEAST:
                if (x + 1 < GRIDSIZE && y + 1 < GRIDSIZE && city->getOrganism(x + 1, y + 1)->getSpecies() == HUMAN) {
                    convert(x + 1, y + 1);
                    survivalCounter = 0;
                    return;
                }
                break;

            case EAST:
                if (x + 1 < GRIDSIZE && city->getOrganism(x + 1, y)->getSpecies() == HUMAN) {
                    convert(x + 1, y);
                    survivalCounter = 0;
                    return;
                }
                break;

            case SOUTHEAST:
                if (x + 1 < GRIDSIZE && y - 1 >= 0 && city->getOrganism(x + 1, y)->getSpecies() == HUMAN) {
                    convert(x + 1, y - 1);
                    survivalCounter = 0;
                    return;
                }
                break;

            case SOUTH:
                if (y - 1 >= 0 && city->getOrganism(x, y - 1)->getSpecies() == HUMAN) {
                    convert(x, y - 1);
                    survivalCounter = 0;
                    return;
                }
                break;

            case SOUTHWEST:
                if (x - 1 >= 0 && y - 1 >= 0 && city->getOrganism(x, y - 1)->getSpecies() == HUMAN) {
                    convert(x - 1, y - 1);
                    survivalCounter = 0;
                    return;
                }
                break;

            default:
                cout << "direction error...";
        }
    }
}

void Zombie::convert(int tempX, int tempY) {
    if ((tempX < GRIDSIZE && tempX >= 0 && tempY < GRIDSIZE && tempY >= 0)) {
        // delete human
        delete city->getOrganism(tempX, tempY);

        // move zombie to human's space
        Zombie *temp = new Zombie(city, tempX, tempY);
        city->setOrganism(temp, tempX, tempY);
    }
}

void Zombie::starve() {
    // create human
    Human *temp = new Human(city, x, y);

    // set human where zombie was
    city->setOrganism(temp, x, y);

    // delete zombie
    delete this;
}