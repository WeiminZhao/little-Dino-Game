/*
 * Obstacle.cpp
 *
 *  Created on: Sep. 30, 2019
 *      Author: zwmsc
 */

#include "Obstacle.h"

namespace Dino {

Obstacle::Obstacle(int obType) {
	// TODO Auto-generated constructor stub

	this->obType=obType;
	hasBeenCollipsed=false;

	if(this->obType==0)
	{
		YSize=sizeof(obs0)/sizeof(obs0[0]);
		XSize=sizeof(obs0[0])/sizeof(obs0[0][0]);
		for(int i=0;i<YSize;i++)//remember i=>y j=>x in those drawing condition
		{
			obs.push_back((vector<int>()));
			for(int j=0;j<XSize;j++)
			{
				obs.at(i).push_back(obs0[i][j]);
			}
		}

	}
	if(this->obType==1)
	{
		YSize=sizeof(obs1)/sizeof(obs1[0]);
		XSize=sizeof(obs1[0])/sizeof(obs1[0][0]);
		for(int i=0;i<YSize;i++)
		{
			obs.push_back((vector<int>()));
			for(int j=0;j<XSize;j++)
			{
				obs.at(i).push_back(obs1[i][j]);
			}
		}
	}
	if(this->obType==2)
	{
		YSize=sizeof(obs2)/sizeof(obs2[0]);
		XSize=sizeof(obs2[0])/sizeof(obs2[0][0]);
		for(int i=0;i<YSize;i++)
		{
			obs.push_back((vector<int>()));
			for(int j=0;j<XSize;j++)
			{
				obs.at(i).push_back(obs2[i][j]);
			}
		}
	}
	if(this->obType==-1)
	{
		YSize=sizeof(obsN1)/sizeof(obsN1[0]);
		XSize=sizeof(obsN1[0])/sizeof(obsN1[0][0]);
		for(int i=0;i<YSize;i++)
		{
			obs.push_back((vector<int>()));
			for(int j=0;j<XSize;j++)
			{
				obs.at(i).push_back(obsN1[i][j]);
			}
		}
	}

	XPosition=0;//envirSizeX;
	YPosition=0;//envirSizeY/2-YSize/2*5;
}

Obstacle::~Obstacle() {
	// TODO Auto-generated destructor stub
}


void Obstacle::setPos(int x, int y)
{
	XPosition=x;
	YPosition=y;
}
//template<typename T>
vector<vector<int>> Obstacle::returnThisObstacleModel()//[19]
{
//	if(obType==1)
//		return obs1;

	return obs;
}
int Obstacle::returnPosX()
{
	return XPosition;
}
int Obstacle::returnPosY()
{
	return YPosition;
}
int Obstacle::returnSizeX(){
	return XSize;
}
int Obstacle::returnSizeY(){
	return YSize;
}
int Obstacle::type()
{
	return obType;
}
void Obstacle::collipsed(){
	this->hasBeenCollipsed=true;
}
bool Obstacle::isCollipsed()
{
	return hasBeenCollipsed;
}
} /* namespace Dino */
