#include <iostream>
#include <bitset>
#include <stdlib.h>
#include <string>
#include "animal.hpp"
#include <curses.h>
#include <cmath>

#define breedTwo(trait)				\
  for (int i = 0; i < trait.size(); i+=2)	\
    {						\
      bitset<2> kid, mom, dad;			\
      mom[0] = parent1 -> trait[i];		\
      mom[1] = parent1 -> trait[i+1];		\
      dad[0] = parent2 -> trait[i];		\
      dad[1] = parent2 -> trait[i+1];		\
      kid = breed (mom, dad);			\
      trait[i] = kid[0];			\
      trait[i+1] = kid[1];			\
    }

#define setBreed(trait)				\
  for (int i = 0; i < (trait).size(); i++)	\
    {						\
      (trait).set(i, rand() % 2);		\
    }
using namespace std;

Animal::Animal()
{
  
  setBreed (bodySize);
  setBreed (sight);
  setBreed (smell);
  setBreed (legLength);
  setBreed (hearing);
  setBreed (camouflage);
  setBreed (intelligence);
  setBreed (jawStrength);
  setBreed (neckLength);
  setBreed (hide);
  setBreed (fur);
  setBreed (claws);
  setBreed (toothShape);
  setBreed (colorSight);
  setBreed (GITract);
  setBreed (nipples);
  setBreed (venom);
  setBreed (stomachSize);
  
  //This is calculating calorieNeeds, which is made up of all of the traits that take energy.
  size = countSize (bodySize);
  calorieNeeds = ((10.0f/24.0f)*count16(sight) * size) + ((10.0f/24.0f)*count16(smell) * size)
    + ((20.0f/24.0f)*count192(legLength) * size) + ((10.0f/24.0f)*count16(hearing) * size)
    + ((30.0f/24.0f)*count192(intelligence) * size) + ((10.0f/24.0f)*count16(jawStrength) * size)
    + ((10.0f/24.0f)*count16(neckLength) * size) + ((10.0f/24.0f)*count16(hide) * size)
    + ((10.0f/24.0f)*count48(fur) * size) + ((10.0f/24.0f)*count16(claws) * size)
    + ((10.0f/24.0f)*count2(colorSight) * size) + ((60.0f/24.0f)*count16(GITract) * size)
    + ((30.0f/24.0f)*count192(venom) * size);
  
  // If weight >= size then it is an adult (size is a actually a measure of weight. It is just a badly named "adult weight". Maybe I'll change it.
  isDead = false;
  litter = (((count16 (nipples))*16)/100);
  birthWeight = size/10;
  birthCalories = birthWeight * 3500;
  calories = birthCalories + calorieNeeds; //It can't be born with only birthWeight calories or else it'll die right away. Therefore it gets a day's worth.
  weight = (calories * 3500); //keeping it in pounds
  stomach = 0;
  stomachCapacity = count48 (stomachSize)*2; // this is scaling to the idea of large is small *5, and that a small takes ten mouths full.Therefore this represents the number of bites to be taken to fill the stomach.This keeps everything nice integer values. The trick will be tracking how many calories are in the stoamch.
  stomachCalories = 0; // Stomach calories is added to with each eat call. Every so often, some calories get taken out of stomach, and added to global calories, and stomach gets decremented too. This will be done like so. stomachCalories/stomach = averageDensity; stomachCalories -= averageDensity;stomach--;
  plantHardness = ((100 - count48 (toothShape)) + count16 (jawStrength))/2;	//average of jaws and teeth.
	GI = count16 (GITract);
  
  
}

Animal::Animal (Animal* parent1, Animal* parent2)
{
  breedTwo(bodySize);
  breedTwo(sight);
  breedTwo(smell);
  breedTwo(legLength);
  breedTwo(hearing);
  breedTwo(camouflage);
  breedTwo(intelligence);
  breedTwo(jawStrength);
  breedTwo(neckLength);
  breedTwo(hide);
  breedTwo(fur);
  breedTwo(claws);
  breedTwo(toothShape);
  breedTwo(colorSight);
  breedTwo(GITract);
  breedTwo(nipples);
  breedTwo(venom);
  breedTwo(stomachSize);
  
  //This is creating the different parts of calorie needs. It requires floats as some animals need less than 1 calorie, and the need from any given trait can be tiny.
  size = countSize (bodySize);
  calorieNeeds = ((10.0f/24.0f)*count16(sight) * size) + ((10.0f/24.0f)*count16(smell) * size)
    + ((20.0f/24.0f)*count192(legLength) * size) + ((10.0f/24.0f)*count16(hearing) * size)
    + ((30.0f/24.0f)*count192(intelligence) * size) + ((10.0f/24.0f)*count16(jawStrength) * size)
    + ((10.0f/24.0f)*count16(neckLength) * size) + ((10.0f/24.0f)*count16(hide) * size)
    + ((10.0f/24.0f)*count48(fur) * size) + ((10.0f/24.0f)*count16(claws) * size)
    + ((10.0f/24.0f)*count2(colorSight) * size) + ((60.0f/24.0f)*count16(GITract) * size)
    +((30.0f/24.0f)*count192(venom) * size);
  
  // If weight >= size then it is an adult (size is a actually a measure of weight. It is just a badly named "adult weight". Maybe I'll change it.
  isDead = false;
  litter = (((count16 (nipples))*16)/100); // scaling from percentage to integer number
  birthWeight = size/10;
  birthCalories = birthWeight * 3500;
  calories = birthCalories + calorieNeeds; //It can't be born with only birthWeight calories or else it'll die right away. Therefore it gets a day's worth.
  weight = (calories * 3500); //keeping it in pounds
  stomach = 0;
  stomachCapacity = count48 (stomachSize)*2; // this is scaling to the idea of large is small *5, and that a small takes ten mouths full.Therefore this represents the number of bites to be taken to fill the stomach.
  stomachCalories = 0;
	plantHardness = ((100 - count48 (toothShape)) + count16 (jawStrength))/2; // This determines what an animal can physically eat.
	GI = count16 (GITract);
}

bitset<2> Animal::breed (bitset<2> parent1, bitset<2> parent2)
{
  bitset<2> child;
  
  int randomNumber = rand() % 4;
  
  if (randomNumber == 0)
    {
      child[0] = parent1[0];
      child[1] = parent2[0];
    }
  
  if (randomNumber == 1)
    {
      child[0] = parent1[1];
      child[1] = parent2[0];
    }
  
  if (randomNumber == 2)
    {
      child[0] = parent1[0];
      child[1] = parent2[1];
    }
  
  if (randomNumber == 3)
    {
      child[0] = parent1[1];
      child[1] = parent2[1];
    }
  
  return child;
}

int Animal::count2 (bitset <2> set)
{
  int ans=0;
  
  for (int i=0;i<2; i+=2)
    {
      if (set[i]==1 || set[i+1] ==1)
	{
	  ans++;
	}
    }
  ans *= 100;
  ans /= 2;
  
  return ans;
}

int Animal::count16 (bitset <16> set)
{
  int ans=0;
  
  for (int i=0;i<16; i+=2)
    {
      if (set[i]==1 || set[i+1] ==1)
	{
	  ans++;
	}
    }
  ans *= 100;
  ans /= 16;
  
  return ans;
}

int Animal::count48 (bitset <48> set)
{
  int ans=0;
  
  for (int i=0;i<48; i+=2)
    {
      if (set[i]==1 || set[i+1] ==1)
	{
	  ans++;
	}
    }
  ans *= 100;
  ans /= 48;
  
  return ans;
}

int Animal::count192 (bitset <192> set)
{
  int ans=0;
  
  for (int i=0;i<192; i+=2)
    {
      if (set[i]==1 || set[i+1] ==1)
	{
	  ans++;
	}
    }
  ans *= 100;
  ans /= 192;
  
  return ans;
}

float Animal::countSize (bitset <224> set)
{
  float ans=0;
  
  for (int i=0;i<224; i+=2)
    {
      if (set[i]==1 || set[i+1] ==1)
	{
	  ans++;
	}
    }
  
  if (ans==0)
    {
      ans=.25;
    }
  
  if (ans==1)
    {
      ans=.5;
    }
  
  if (ans==2)
    {
      ans=.75;
    }
  
  if (ans>2)
    {
      ans-=2;
    }
  
  ans=pow(ans,2);
}

void Animal::move (int ch)
{
  movementScalar = 1; // (3+sqrt(countSize(bodySize))/2.0*3.0) * (.0033 +count192(legLength)*.002); // these constants need to be declared
  if (ch == KEY_UP)
    {
      if (posy - movementScalar >= 0)
	{
	  posy-=movementScalar;
	}
    }
  
  if (ch == KEY_DOWN)
    {
      if (posy + movementScalar <= 16)
	{
	  posy+=movementScalar;
	}
    }
  
  if (ch == KEY_LEFT)
    {
      if (posx - movementScalar >= 0)
	{
	  posx-=movementScalar;
	}
    }
  
  if (ch == KEY_RIGHT)
    {
      if (posx + movementScalar <= 16)
	{
	  posx+=movementScalar; 
	}
    }
  calories -= (size*4.448*3) + sqrt (countSize(bodySize))/2.0*3.0 * (.0033 +count192(legLength)*.002) * (.0254*4.19/1000.0); // here are some constants that need to be worked out.
}

void Animal::kill ()
{
  isDead = true;
}

void Animal::eat ()
{
  calories += birthCalories;


}
	
