/*
 * Animals.h
 *
 *  Created on: Oct. 25, 2019
 *      Author: zwmsc
 */

#ifndef ANIMALS_H_
#define ANIMALS_H_

#include <nana/gui.hpp>
#include <vector>
#include "Animal.h"
#include "Environment.h"
using namespace nana;
using namespace std;
namespace Dino {

class Animals {//the control class of animal
public:
	Animals(int winX, int winY, int stretch);
	virtual ~Animals();
	void reset();
	void autoAnimateAnimals(paint::graphics& g);
	void updateAnimals(Environment& en);
	void stop();
	void continueAll();
	void setSpeed(int speed);
	vector<Animal>& returnAnims();
	int returnPassingSpeed();

private:
	vector<Animal> anims;
	int stretch;
	int passingSpeed;//this is for globel passingspeed for animals
	int XSize;
	int YSize;
	bool stopAll;

};

} /* namespace Dino */

#endif /* ANIMALS_H_ */
