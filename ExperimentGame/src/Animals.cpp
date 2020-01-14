/*
 * Animals.cpp
 *
 *  Created on: Oct. 25, 2019
 *      Author: zwmsc
 */

#include "Animals.h"

namespace Dino {

Animals::Animals(int winX,int winY,int stretch) {
	// TODO Auto-generated constructor stub
	XSize=winX;
	YSize=winY;
	this->stretch=stretch;
	passingSpeed=stretch * 2;
	stopAll=false;
}

Animals::~Animals() {
	// TODO Auto-generated destructor stub
}
void Animals::reset()
{
	anims.clear();
	passingSpeed=stretch * 2;
	stopAll=false;
}
void Animals::updateAnimals(Environment& en)
{
	if(!stopAll)
	{
		int ran=rand()%500+1;
		if(ran<2)//<2
			anims.push_back(Animal(1, XSize, en.returnGrounds().at(en.returnGrounds().size()-1).y-stretch*5-rand()%400, (passingSpeed+(rand()%passingSpeed))));

		for(int i=0;i<anims.size();i++)
		{
			anims[i].setPos(anims[i].returnX()-anims[i].returnSpeed(),anims[i].returnY()-(anims[i].isCollipsed()?stretch*5:0));//-anims[i].isCollipsed()?stretch:0
		}
		while(!anims.empty() && anims[0].returnX()<-100)
		{
			anims.erase(anims.begin());
		}

	}
}

void Animals::autoAnimateAnimals(paint::graphics& g)
{
	for(int num=0;num<anims.size();num++)
	{
		for(int i=0;i<anims[num].returnYSize();i++)
			for(int j=0;j<anims[num].returnXSize();j++)
			{
				if(anims[num].returnFrame()[i][j]==1)
					g.rectangle({anims[num].returnX()+j*stretch, anims[num].returnY()+i*stretch,stretch,stretch},true,colors::blue_violet);
			}
		anims[num].updateFrame();
	}


}

void Animals::setSpeed(int speed)
{
	passingSpeed=speed;
}

vector<Animal>& Animals::returnAnims()
{
	return anims;
}

void Animals::stop()
{
	stopAll=true;
}
void Animals::continueAll()
{
	stopAll=false;
}
int Animals::returnPassingSpeed()
{
	return passingSpeed;
}


} /* namespace Dino */
