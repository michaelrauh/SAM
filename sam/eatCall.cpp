//EAT CALL

int main()
{
#define targetPlant plantPositions[((int)(currentAnimal ->posx*100)) + 100 + ((int)(currentAnimal ->posy))]

if ((targetPlant->fruitBearing) && (currentAnimal->plantHardness) > (targetPlant->hardness))
  {
    if ((targetPlant->fruit) > 0)
      {
	// if there is room in the stomach, and there is enough food left
	if ((currentAnimal->stomach) < (currentAnimal->stomachCapacity) && ((targetPlant->density) * (currentAnimal->size)) < (targetPlant->fruit))
	  {
	    (currentAnimal-> stomach) ++;
	    (currentAnimal->stomachCalories) +=  (targetPlant->density) * (currentAnimal->size) * (((100.0 - fabs (((targetPlant->GISpec) - (currentAnimal->GI)) *12.5)) /100.0));
	    (targetPlant->fruit) -= (targetPlant->density) * (currentAnimal->size); 
	  }
	//If there is less than one bite left
	if ((currentAnimal->stomach) < (currentAnimal->stomachCapacity) && ((targetPlant->density) * (currentAnimal->size)) > (targetPlant->fruit))
	  {
	    (currentAnimal->stomach) ++;
	    (currentAnimal->stomachCalories) += (targetPlant->fruit);
	    (targetPlant->fruit = 0);
	  }
      }
  }


// Here is the scavenge call. It makes the animal eat the stem. Some animals are only stems.(I really should make a boolean referring to that)
if ((currentAnimal->plantHardness) > (targetPlant->hardness))
  {
    if ((currentAnimal->stomach) < (currentAnimal->stomachCapacity) && (100 * .0275 / (targetPlant->volume) * (currentAnimal->size)) < (targetPlant->health))
      {
	(currentAnimal->stomach)++;
	(currentAnimal->stomachCalories) += (targetPlant->stemDensity) * (currentAnimal->size) * (currentAnimal->stemEfficiency); 	
	(targetPlant->health) -= (100 * .0275 / (targetPlant->volume) * (currentAnimal->size));
	(targetPlant->volume) -= .0275 *(currentAnimal->size);
	
	if ((currentAnimal->stomach) < (currentAnimal->stomachCapacity) && (100 * .0275 / (targetPlant->volume) * (currentAnimal->size)) > (targetPlant->health))
	  {
	    (currentAnimal->stomachCalories) += (targetPlant->stemDensity) * (currentAnimal->size) * (((100.0 - fabs (((targetPlant->stemGISpec) - (currentAnimal->GI)) *12.5)) /100.0)) * ((targetPlant->health)/.0275 *(currentAnimal->size));
	    (currentAnimal->stomach)++;
	    (targetPlant->isDead) = true;
	  }
      }
  }

}
