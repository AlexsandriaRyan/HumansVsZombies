// Alexsandria Ryan
// PROG 2100
// Assignment #4
// April 11, 2023

#include "../inc/Human.h"
#include "../inc/City.h"

#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main() {
    City *city = new City();
    city->prepareCity();
    int counter = 0;

    while (city->hasDiversity()) {
        chrono:: milliseconds interval(500);
        this_thread::sleep_for(interval);
        cout << *city;
        city->turn();
        counter++;
        if (counter == ITERATIONS) { break; }
    }
}