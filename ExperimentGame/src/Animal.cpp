/*
 * Animal.cpp
 *
 *  Created on: Oct. 28, 2019
 *      Author: zwmsc
 */

#include "Animal.h"

namespace Dino {

Animal::Animal(int type,int x,int y, int speed) {
	// TODO Auto-generated constructor stub
	this->type=type;
	if(type==1)
	{
		YSize=12;
		XSize=16;

		this->speed=speed;
	}
	XPos=x;
	YPos=y;
	frameCount=1;
	reverseFrame=false;

	hasBeenCollipsed=false;
}

Animal::~Animal() {
	// TODO Auto-generated destructor stub
}

int (*(Animal::returnFrame()))[16]
{
	if(frameCount==1)
	{
		return bird1;
	}
	else if(frameCount==2)
	{
		return bird2;
	}
	else if(frameCount==3)
	{
		return bird3;
	}
	else
		return 0;
}
void Animal::updateFrame()
{
	if(frameCount>=3)
			this->reverseFrame=true;
	if(frameCount<=1)
			this->reverseFrame=false;

	if(!reverseFrame)
		frameCount++;
	else
		frameCount--;

}
void Animal::setPos(int x, int y)
{
	XPos=x;
	YPos=y;
}
int Animal::returnX()
{
	return XPos;
}
int Animal::returnY()
{
	return YPos;
}
int Animal::returnXSize()
{
	return XSize;
}
int Animal::returnYSize()
{
	return YSize;
}

void Animal::collipsed()
{
	hasBeenCollipsed=true;
}
bool Animal::isCollipsed()
{
	return hasBeenCollipsed;
}
int Animal::returnSpeed()
{
	return speed;
}


} /* namespace Dino */
