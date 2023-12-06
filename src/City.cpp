#include "../inc/GameSpecs.h"
#include "../inc/City.h"
#include "../inc/Organism.h"
#include "../inc/Human.h"
#include "../inc/Zombie.h"

// ---------- CONSTRUCTORS / DESTRUCTORS ----------
City::City() {
    this->humans = HUMAN_STARTCOUNT;
    this->zombies = ZOMBIE_STARTCOUNT;
    this->generation = 0;
}

City::~City() { }

// ---------- GETTERS ----------
Organism* City::getOrganism(int x, int y) {
    return grid[x][y];
}

// ---------- SETTERS ----------
void City::setOrganism (Organism *organism, int x, int y) {
    grid[x][y] = organism;
}

// ---------- OVERRIDE ----------
ostream& operator<< (ostream &output, City &city) {

    int humanCount = 0;
    int zombieCount = 0;

    // print grid & count species
    for (int y = 0; y < GRIDSIZE; y++) {
        for (int x = 0; x < GRIDSIZE; x++) {
            output << city.grid[x][y];
            if (city.grid[x][y]->getSpecies() == HUMAN) {
                humanCount++;
            } else if (city.grid[x][y]->getSpecies() == ZOMBIE) {
                zombieCount++;
            }
        }

        output << "\n";
    }

    city.generation++;
    city.humans = humanCount;
    city.zombies = zombieCount;

    output << "\nGENERATION: " + to_string(city.generation);
    output << "     HUMANS: " + to_string(city.humans);
    output << "     ZOMBIES: " + to_string(city.zombies);
    output << "\n\n\n";

    return output;
}

// ---------- FUNCTIONS ----------
void City::prepareCity() {
    // filling grid with blank organisms
    for (int y = 0; y < GRIDSIZE; y++) {
        for (int x = 0; x < GRIDSIZE; x++) {
            Organism *temp = new Organism(this, x, y);
            setOrganism(temp, x, y);
        }
    }

    // random coordinates for humans
    srand(time(0));
    int counter = 0;
    while (counter < HUMAN_STARTCOUNT) {
        int x = rand() % GRIDSIZE;
        int y = rand() % GRIDSIZE;

        if (getOrganism(x, y)->getSpecies() == ORGANISM) {
            Human *temp = new Human(this, x, y);
            setOrganism(temp, x, y);
            counter++;
        }
    }

    // random coordinates for zombies
    counter = 0;
    while (counter < ZOMBIE_STARTCOUNT) {
        int x = rand() % GRIDSIZE;
        int y = rand() % GRIDSIZE;

        if (getOrganism(x, y)->getSpecies() == ORGANISM) {
            Zombie *temp = new Zombie(this, x, y);
            setOrganism(temp, x, y);
            counter++;
        }
    }
}

void City::turn() {

    // move
    for (int y = 0; y < GRIDSIZE; y++) {
        for (int x = 0; x < GRIDSIZE; x++) {
            grid[x][y]->turn();
        }
    }

    // reset
    for (int y = 0; y < GRIDSIZE; y++) {
        for (int x = 0; x < GRIDSIZE; x++) {
            grid[x][y]->resetMoved();
        }
    }
}

bool City::hasDiversity() {
    if (humans > 0 && zombies > 0) {
        return true;

    } else {
        return false;
    }
}