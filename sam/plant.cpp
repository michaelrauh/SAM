#include "plant.hpp"
#include <iostream>
#include <bitset>
#include <stdlib.h>
#include <string>
#include <curses.h>
#include <cmath>


Plant::Plant (plantType type)
{
  if (type == wheat)
    {
      density = 0; 
      GISpec = 0; 
      hardness = 0; 
      maxHeight = 48; 
      adultAge = 0;
      growthRate = 12.0*12.0 / 365.0;
      maxWidth = .1; 
      waterNeed = 90;  
      lightNeed = 50; 
      maxTimeUntilCrop = 1;
      cropSize = 0;
      cropVolume = 0;
      maxVolume = 60;
      stemHardness = 32;
      stemDensity = .0352;
      stemGISpec = 8;
      fruitBearing = false;
    }
  if (type == vines)
    {
      density = 0; 
      GISpec = 0;
      hardness = 0;
      maxHeight = 6;
      adultAge = 0;
      growthRate = 12.0;
      maxWidth = 500; 
      waterNeed = 45;
      lightNeed = 50;
      maxTimeUntilCrop = 1;
      cropSize = 0;
      cropVolume = 0;
      maxVolume = 1147;
      stemHardness = 48;
      stemDensity = .0151;
      stemGISpec = 7;
      fruitBearing = false;
    }
  
  if (type == chokeberry)
    {
      density = .0866; 
      GISpec = 6;
      hardness = 16;
      maxHeight = 36;
      adultAge = 70;
      growthRate = 100.0/365.0;
      maxWidth = 24;
      waterNeed = 45;
      lightNeed = 20;
      maxTimeUntilCrop = 21;
      cropSize = 17600;
      cropVolume = 11000;
      maxVolume = 150000;
      stemHardness = 64;
      stemDensity = .0107;
      stemGISpec = 5;
      fruitBearing = true;
    }
  
  if (type == walnut)
    {
      density = .6353; 
      GISpec = 5;
      hardness = 80;
      maxHeight =70*12;
      adultAge = 10 * 365;
      growthRate = 7.0*12.0/365.0;
      maxWidth = 24;
      waterNeed = 50;
      lightNeed = 25;
      maxTimeUntilCrop;
      cropSize = 35840;
      cropVolume = 11136;
      maxVolume = 1109077;
      stemHardness = 64;
      stemDensity = .0107;
      stemGISpec = 5;
      fruitBearing= true;
    }
  
  if (type == saguaro)
    {
      density = 0; 
      GISpec = 0;
      hardness = 0;
      maxHeight = 40 *12;
      adultAge = 0;
      growthRate = 1.0/365.0;
      maxWidth = 24;
      waterNeed = 0;
      lightNeed = 80;
      maxTimeUntilCrop = 1;
      cropSize = 0;
      cropVolume = 0;
      maxVolume = 1147;
      stemHardness = 16;
      stemDensity = .1980;
      stemGISpec = 6;
      fruitBearing = false;
    }
  
  if (type == raspberry)
    {
      density = .1444; 
      GISpec = 8;
      hardness = 0;
      maxHeight = 40;
      adultAge = 300;
      growthRate = 40.0/365.0;
      maxWidth = 35;
      waterNeed = 90;
      lightNeed = 60;
      maxTimeUntilCrop = 28;
      cropSize = 13000;
      cropVolume = 4680;
      maxVolume = 100000;
      stemHardness = 60;
      stemDensity = .0107;
      stemGISpec = 5;
      fruitBearing = true;
    }
  
  if (type == shrub)
    {
      density =0; 
      GISpec = 0;
      hardness = 0;
      maxHeight = 120;
      adultAge = 90;
      growthRate = 5.0*12.0/365.0;
      maxWidth = 36;
      waterNeed =  0;
      lightNeed = 70;
      maxTimeUntilCrop = 1;
      cropSize = 0;
      cropVolume = 0;
      maxVolume = 250000;
      stemHardness = 48;
      stemDensity = .0107;
      stemGISpec = 5;
      fruitBearing = false;
    }
  
  health = 100.0;
  isDead = false;
  height = 0;
  age = 0;
  volume = 0;
  fruit = 0;
  fruitVolume = 0;
  stemCalories = 0;
  timeUntilCrop = maxTimeUntilCrop;
  volumeFactor = 1;
  
}

void Plant::grow(int light, int water) // if the plant doesn't get proper water and light, it becomes less healthy, and grows less. That is all that health effects though.
{
  int diff;
  diff = 0; //fabs(waterNeed-water) + fabs (lightNeed-light);
  if (diff > 15)
    {
      if (health - log2 (diff) >= 0)
	{
	  health -= log2 (diff); //log2 is an initial guess.
	}
    }
  else
    {
      health += log2 (15); // I admit this is a little made up. This is about 4.
    }
  if (height < maxHeight)
    {
  height += growthRate*(health/100.0);
    }
  age ++;
  volume = height/maxHeight * maxVolume;
  volume = volume * volumeFactor;
  stemCalories = volume * stemDensity;
  // if the plant is mature, bring it closer to producing fruit. If it is time, produce fruit.
  if (age > adultAge && fruitBearing && health>15)
    {
      timeUntilCrop--;
      if (timeUntilCrop == 0)
	{
	  fruit = cropSize; //for now it is all at once. Later it may be staggered.
	  fruitVolume = cropVolume;
	  timeUntilCrop = maxTimeUntilCrop;
	}
    }
}




