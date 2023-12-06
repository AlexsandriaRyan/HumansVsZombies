#ifndef NEWFILES_GAMESPECS_H
#define NEWFILES_GAMESPECS_H

const int GRIDSIZE = 20; // size of the square grid
const int HUMAN_STARTCOUNT = 100; // initial Humans
const int ZOMBIE_STARTCOUNT = 5; //initial Zombie count
const int HUMAN_RECRUIT = 3; // steps until a Human breeds
const int ZOMBIE_BREED = 8; // steps until a Zombie breeds
const int ZOMBIE_STARVE = 3; // steps until a Zombie starves and converts back
const int ITERATIONS = 1000; // max number of steps
enum types { ORGANISM, HUMAN, ZOMBIE };

//Colors
//0  = black				//9  = bright blue
//1  = blue					//10 = bright green
//2  = green				//11 = bright turquoise
//3  = turquoise			//12 = bright red
//4  = red					//13 = bright pink
//5  = pink					//14 = bright yellow
//6  = yellow				//15 = bright white
//7  = white regular		//16+ = solid blocks
//8  = white pale

const int HUMAN_COLOR = 10;
const int ZOMBIE_COLOR = 64;
const int TEXT_COLOR = 7;

#endif //NEWFILES_GAMESPECS_H
