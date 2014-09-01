#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <cmath>
#include <bitset>

using namespace std;

class Animal
{
public:
  pair <double, double> position;
  double posx, posy;
  string name;
  bool isDead;
  int litter;
  float birthWeight;
  float weight;
  float calories;
  float birthCalories;
  double movementScalar;
  
  //these bitsets represent the genome of the animal
  bitset <224> bodySize;
  bitset <16> sight;
  bitset <16> smell;
  bitset <192> legLength;
  bitset <16> hearing;
  bitset <16> camouflage;
  bitset <192> intelligence;
  bitset <16> jawStrength;
  bitset <16> neckLength;
  bitset <16> hide;
  bitset <48> fur;
  bitset <16> claws;
  bitset <48> toothShape;
  bitset <2> colorSight;
  bitset <16> GITract;
  bitset <16> nipples;
  bitset <192> venom;
  bitset <48> stomachSize;

 
  float size;
  float calorieNeeds;
  int stomach;
  int stomachCapacity;
  float stomachCalories;
  int plantHardness;
  int GI;

  //Member Functions
  Animal();
  Animal (Animal* parent1, Animal* parent2);
  bitset<2> breed (bitset<2> parent1, bitset<2> parent2);
  double distance (Animal* animal1);
  void print ();
  int count2 (bitset <2> set);
  int count16 (bitset <16> set);
  int count48 (bitset <48> set);
  int count192 (bitset <192> set);
  float countSize (bitset <224> set);
  void move (int ch);
  void kill ();
  void eat ();

};

#endif
