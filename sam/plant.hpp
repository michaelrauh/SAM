#ifndef PLANT_H
#define PLANT_H

enum plantType
  {
    wheat,
    vines,
    chokeberry,
    walnut,
    saguaro,
    raspberry,
    shrub
  };

class Plant
{
public:
  // constructor (hard) variables
  float density; 
  int GISpec;
  int hardness;
  int maxHeight;
  int adultAge;
  float growthRate;
  int maxWidth;
  int waterNeed;
  int lightNeed;
  int maxTimeUntilCrop;
  int timeUntilCrop;
  int cropSize;
  int cropVolume;
  int maxVolume;
  int stemHardness;
  float stemDensity;
  int stemGISpec;
  bool fruitBearing;
  
  // regular variables 
  float health;
  bool isDead;
  float height;
  float width;
  double posx;
  double posy;
  int age;
  float volume;
  float fruit;
  float fruitVolume;
  float stemCalories;
  float volumeFactor;
	
  //member functions
  Plant (plantType type);
  void grow (int light, int water);
  void checkDeath();
};

#endif
