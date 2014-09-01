#include <iostream>
#include <list>
#include <stdlib.h>
#include <time.h>
#include <bitset>
#include <curses.h>
#include <cstddef>
#include "animal.hpp"
#include <map>
#include "plant.hpp"

// This refers to the plant that is to the right of the current animal
#define targetPlant plantPositions[((int)currentAnimal ->posx*100) + 100 + ((int)currentAnimal ->posy)]

using namespace std;

// setting up the Animal and Plant lists and their iterators
list<Animal>::iterator currentAnimal, printCurrentAnimal,mapCurrentAnimal,metabolizeCurrentAnimal;
list<Animal> animals;

list<Plant>::iterator currentPlant, printCurrentPlant,mapCurrentPlant;
list<Plant>plants;

// creating the maps for plants and animals. Currently the position is stored in a single integer as posx*100+posy
map <int,Plant*> plantPositions;
map <int,Animal*> animalPositions;

// creating an nCurses window
WINDOW* win;

//////////////////////////////////////////////////////////////////////////////
void refreshGame ()
{
  animalPositions.clear();
  plantPositions.clear();
  // puts non-dead plants into the map, and removes the dead from the list (deletes them)
  mapCurrentPlant = plants.begin();
  for (mapCurrentPlant = plants.begin(); mapCurrentPlant != plants.end(); mapCurrentPlant++)
    {
      if (mapCurrentPlant->isDead)
	{
	  plants.erase(mapCurrentPlant);
	  break;
	}
      else
	{
	  plantPositions [(int)mapCurrentPlant->posx*100+(int)mapCurrentPlant->posy] = &(*mapCurrentPlant);
	}
    }
  //puts non-dead animals into the map and removes the dead from the list (deletes them)
  mapCurrentAnimal=animals.begin();
  for (mapCurrentAnimal = animals.begin(); mapCurrentAnimal != animals.end(); mapCurrentAnimal++)
    {
      if (mapCurrentAnimal->isDead)
	{
	  animals.erase (mapCurrentAnimal);
	  break;
	}
      else
	{
	  animalPositions [(int)mapCurrentAnimal->posx*100+(int)mapCurrentAnimal->posy] = &(*mapCurrentAnimal);
	}
    }
  
  werase (win);
  
  printCurrentAnimal = animals.begin();
  printCurrentPlant = plants.begin();
  
  //displays plants and animals in ASCII  
  while (printCurrentPlant != plants.end())
    {
      mvwprintw (win, printCurrentPlant -> posy, (printCurrentPlant-> posx) * 2, "*" "%f",printCurrentPlant -> stemCalories);
      printCurrentPlant++;
    }
  
  while (printCurrentAnimal != animals.end())
    {
      mvwprintw (win, printCurrentAnimal -> posy, (printCurrentAnimal-> posx) * 2,"#" "%f", printCurrentAnimal->calories);
      printCurrentAnimal++;
    }
  
  
  
  wrefresh(win);
  refresh ();
}

//////////////////////////////////////////////////////////////////////////////
void init ()
{
  //starting ncurses up, getting rid of buffering and echo, and calculating the variables
  int xmax, ymax;
  
  //init ncurses
  initscr();
  cbreak();
  noecho();
  keypad(win, TRUE);
  keypad(stdscr, TRUE);
  
  //set up new window
  getmaxyx (stdscr, ymax, xmax);
  win = newwin(ymax-2, xmax, 1, 0);
  wprintw (stdscr, "Welcome to SAM!");
  mvwprintw (stdscr, ymax-1, 0, "Press \'q\' to quit.");
  
  //show everything
  refresh();
  wrefresh(win);
  
  //random number generator
  srand (time (0));
  
  currentAnimal = animals.begin();
}

//////////////////////////////////////////////////////////////////////////////
int main (int argc, char* argv[])
{
  int count = 1;
  bool quit;
  int ch;
  
  // create starting plants
  Plant* tempPlant;
  tempPlant = new Plant (wheat);
  tempPlant -> posx = 2;
  tempPlant -> posy =2;
  plants.push_back (*tempPlant);
  
  tempPlant = new Plant (chokeberry);
  tempPlant -> posx = 4;
  tempPlant -> posy = 4;
  plants.push_back (*tempPlant);
  
  //creating the starting animals
  Animal* temp;
  for (int incr=0;incr<2;incr++)
    {
      temp = new Animal;
      temp -> posx = 0;
      temp -> posy = 0;
      animals.push_back (*temp);
    }
  
  init ();
  
  // MAIN LOOP
  while (!quit)
    {
      refreshGame();
      ch = getch();
      
      
      //requesting keystrokes and responding in a switch
      switch (ch)
	{
	  ////////
	  //quit//
	  ////////
	case 'q':
	  quit = true;
	  break;
	  
	  /////////////////
	  //movement keys//
	  /////////////////
	case KEY_DOWN:
	  currentAnimal->move (ch);
	  break;
	case KEY_UP:
	  currentAnimal->move (ch);
	  break;
	case KEY_LEFT:
	  currentAnimal->move (ch);
	  break;
	case KEY_RIGHT:
	  currentAnimal->move (ch);
	  break;
	  
	  //breed
	case 'b':
	  if (animalPositions.count((int)currentAnimal ->posx*100 + 100 + ((int)currentAnimal ->posy) )!= 0)
	    {
	      if ((animalPositions.count((int)currentAnimal ->posx*100)+100 + ((int)currentAnimal ->posy) >0) && (((int)currentAnimal->posx) > 0) && (currentAnimal->litter * (currentAnimal->birthCalories)) < ((currentAnimal->calories) - currentAnimal->birthCalories))
		{
		  currentAnimal->calories -= (currentAnimal->litter * currentAnimal->birthCalories);
		  for (int incr=0;incr<(currentAnimal->litter);incr++)
		    {
		      temp = new Animal (animalPositions[((int)currentAnimal ->posx*100) + ((int)currentAnimal ->posy)], animalPositions[((int)currentAnimal ->posx*100)+100 + ((int)currentAnimal ->posy)]);
		      temp -> posx = (int)currentAnimal->posx-1;
		      temp -> posy = (int)currentAnimal->posy;
		      animals.push_back (*temp);
		    }
		}
	    }
	  break;
	  
	  //kill
	case 'k':
	  if (animalPositions.count((int)currentAnimal ->posx*100 + 100 + ((int)currentAnimal ->posy) )!= 0)
	    {
	      animalPositions [((int)currentAnimal ->posx*100) + 100 + ((int)currentAnimal ->posy)] -> kill();
	    }
	  break;
	  
	  //eat
	case 'e':
	  if (plantPositions.count((int)currentAnimal ->posx*100 + 100 + ((int)currentAnimal ->posy) )!= 0)
	    {
	      if ((targetPlant->fruitBearing))
		
		if (true /*(currentAnimal->plantHardness) > (targetPlant->hardness)*/)
		  {
		    {
		      if ((targetPlant->fruit) > 0)
			{
			  if ((currentAnimal->stomach) < (currentAnimal->stomachCapacity))
			    {
			      if (((targetPlant->density) * (currentAnimal->size)) < (targetPlant->fruit))
				{
				  (currentAnimal-> stomach)++;
				  (currentAnimal->stomachCalories) +=  (targetPlant->density) * (currentAnimal->size) * ((fabs (currentAnimal->GI * 12.5) - ( targetPlant->GISpec)))/100.0;
				  (targetPlant->fruit) -= (targetPlant->density) * (currentAnimal->size); 
				}
			      //If there is less than one bite left
			      else
				{
				  (currentAnimal->stomach) ++;
				  (currentAnimal->stomachCalories) += (targetPlant->fruit) * ((fabs (currentAnimal->GI * 12.5) - ( targetPlant->GISpec)))/100.0;
				  (targetPlant->fruit = 0);
				}
			    }
			}
		    }
		  }
	    }
	  break;
	  //scavenge. This is when the plant eats the stem.
	case 't':
	  if (plantPositions.count((int)currentAnimal ->posx*100 + 100 + ((int)currentAnimal ->posy) )!= 0)
	    {
	      if ((currentAnimal->stomach) < (currentAnimal->stomachCapacity))
		{
		  if (true/*(currentAnimal->plantHardness) > (targetPlant->hardness)*/)
		    {
		      if ((.275 * (currentAnimal->size)) < (targetPlant->volume))
			{
			  (currentAnimal->stomach)++;
			  (currentAnimal->stomachCalories) += (targetPlant->stemDensity) * (currentAnimal->size) * (((fabs (((targetPlant->stemGISpec) - (currentAnimal->GI)) *12.5)) /100.0)); 	
			  (targetPlant->health) -= (.275 * (currentAnimal->size))/(targetPlant->volume);
			  (targetPlant->volumeFactor) -= (.275 * (currentAnimal->size))/(targetPlant->volume);
			}
		      
		      // This is the case in which there is only a little bit left.
		      else
			{
			  (currentAnimal->stomachCalories) += (targetPlant->stemCalories) * (((fabs (((targetPlant->stemGISpec) - (currentAnimal->GI)) *12.5)) /100.0));
			  (currentAnimal->stomach)++;
			  (targetPlant->isDead) = true;
			}
		    }
		  
		}
	    }
	  break;
	  
	  //The metabolize call. This also takes a propertional amount of the calorieNeeds of the animal. It is meant to be called 6 times per day.
	case 'm' :
	  for (metabolizeCurrentAnimal = animals.begin(); metabolizeCurrentAnimal != animals.end(); metabolizeCurrentAnimal++)
	    {
	      metabolizeCurrentAnimal-> stomach=0;
	      metabolizeCurrentAnimal-> calories += (metabolizeCurrentAnimal->stomachCalories);
	      metabolizeCurrentAnimal->stomachCalories = 0;
	      metabolizeCurrentAnimal-> calories -= (metabolizeCurrentAnimal->calorieNeeds/6.0);
	    }
	  
	  break;
	  
	case 'g' :
	  for (currentPlant = plants.begin(); currentPlant != plants.end(); currentPlant++)
	    {
	      currentPlant->grow(90,50); 
	    }
	  break;
	  //change players 
	case 'y':
	  if (count < animals.size())
	    {
	      currentAnimal++;
	      count++;
	    }
	  else
	    {
	      currentAnimal = animals.begin();
	      count = 1;
	    }
	  break;
	}
    }
  endwin();
  return 0;
}
