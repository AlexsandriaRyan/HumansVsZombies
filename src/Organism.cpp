#include "../inc/Organism.h"

// ---------- CONSTRUCTORS / DESTRUCTORS ----------
Organism::Organism() = default;

Organism::Organism(City *city, int x, int y) {
    this->city = city;
    this->x = x;
    this->y = y;
    this->species = ORGANISM;
    this->moved = false;
}

Organism::~Organism() = default;

// ---------- GETTERS ----------
int Organism::getSpecies() {
    return ORGANISM;
}

// ---------- FUNCTIONS ----------
void Organism::turn() { }

void Organism::move() { }

void Organism::resetMoved() {  moved = false; }

void Organism::Color(int c) {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, c);
}