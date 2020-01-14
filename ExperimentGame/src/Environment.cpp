/*
 * Environment.cpp
 *
 *  Created on: Sep. 27, 2019
 *      Author: zwmsc
 */

#include "Environment.h"
#include "Obstacle.h"
#include <nana/gui.hpp>
#include <iostream>
//#include <vector>
//#include <bits/stdc++.h>
using namespace nana;
using namespace std;
namespace Dino {

Environment::Environment(int windowX, int windowY, int s) {
	// TODO Auto-generated constructor stub
	XSize=windowX;
	YSize=windowY;



	isStopAll=false;

	setStretch(s);
	groundYPos=0;//YSize/2+19*5/2;
	passingSpeed=stretch*2;//2//12;//now must be stretchx

	for(int i=0;i<XSize;i+=stretch)
		groundBlocks.push_back((point(i,groundYPos)));

	abyssCount=0;
	abyssInterval=0;

	obsInterval=0;
	obsInnerInterval=0;
	obsSingleInterval=0;
	//======
	backgroundAnimationStage=1;
}

Environment::~Environment() {
	// TODO Auto-generated destructor stub
}
void Environment::reset()
{
	isStopAll=false;
	passingSpeed=stretch*2;//2
	obstacles.clear();
	groundBlocks.clear();

	groundYPos=0;

	for(int i=0;i<XSize;i+=stretch)
			groundBlocks.push_back((point(i,groundYPos)));

	abyssCount=0;
	abyssInterval=0;

	obsInterval=0;
	obsInnerInterval=0;
	obsSingleInterval=0;
	//========
	backgroundAnimationStage=1;
}
void Environment::setStretch(int s)
{
	this->stretch=s;
}

void Environment::updateEnvironment()
{
	if(!isStopAll)
	{
		///Ground update==========================================================

//		int rAbyss;//abyss density control variable;
//		if(abyssCount==0)
//			rAbyss=std::rand()%40+1;//control abys generation density(the actual density controlled by this variable and abyssInterval)
//		else//if the abyss is in generation we continue it by not refresh the density control variable
//			rAbyss=1;
		for(int num=0;num<passingSpeed/stretch;num++)//generate new ground base on speed. the passingSpeed is higher means more blocks should be generated at once
		{
			//rAbyss<2 && backup line
			if(abyssInterval>=passingSpeed*40 && abyssCount<=passingSpeed*5)//if there is abyss. the total pixel of abyss is passingSpeed*4
			{
				groundBlocks.push_back((point(XSize+num*stretch,10000000)));//the deep of the deep
				abyssCount++;//count the pixel already generated
				if(abyssCount ==passingSpeed*5)//when this one is generated, complete reset the interval to control the minimum density and reset the counter for next generation
				{
					abyssInterval=0;//restart the interval count
					abyssCount=0;
				}

			}
			else//there is no abyss
			{
				//random height a little bit
				int r0=std::rand()%10;
				if(r0==0)
					groundYPos+=stretch;//let's actually make this variable a control ground generate variable
				else if(r0==1)
					groundYPos-=stretch;
				else
					;
				//limited the generate max heights for now in case ground goes out of screen
				if(groundYPos>YSize-YSize*0.15) groundYPos=YSize-YSize*0.15;//add margin top and button 0.15 of total//600;
				if(groundYPos<YSize*0.5) groundYPos=YSize*0.5;//stretch;
				//actual add the new ground with its data
				groundBlocks.push_back((point(XSize+num*stretch,groundYPos)));//real y pos =ground y pos+ relY

				abyssInterval+=(rand()%2);//the abyss interval count, random the process of count result in the random distance between abyss
			}
		}
		//cout<<abyssInterval<<endl;
		for(int num=0;num<groundBlocks.size();num++)//update ground locations
		{
			groundBlocks.at(num).x=groundBlocks.at(num).x-passingSpeed;
		}
		while(groundBlocks.at(0).x<-10)//erase the unusable ones at the start of the list, which is normally out of screen
		{
			groundBlocks.erase(groundBlocks.begin());
		}

		///Obstacles update===========================================================
		//use random number to control when we generate the obstacle and their frequency


		//int r=std::rand()%500+1;
		//r<50 && backup line
		if(obsInterval>=passingSpeed*15)//if the count is < ps*15 the generation is not allowed
		{
			if(obsSingleInterval>=stretch*2.0*stretch/passingSpeed*1.0)//minimum required interval between obs. since we generate >1 stretch terrain per frame, the real interval is (this number here*terrain per frame)//terrain pf = passingSpeed pixel without stretch
			{
				int robs=std::rand()%3+1;//type control (randomize the obs type)
				//robs=(robs<9)?1:2;
				obstacles.push_back((Obstacle((robs==3?2:1))));//here we generate obstacle to the environment
				obstacles.at(obstacles.size()-1).setPos(this->XSize, this->groundBlocks.at(groundBlocks.size()-1).y - obstacles.at(obstacles.size()-1).returnSizeY()*stretch);//we place the obstacle based on the position of the last groundBlocks

				obsSingleInterval=0;//after place recount the distance
			}

			obsSingleInterval+=((rand()%3)==0?1:0);//control the distance between obs

			obsInnerInterval+=(passingSpeed/(stretch*2));//count the cluster width
			if(obsInnerInterval>=passingSpeed*2)//when we reach the width limit we close the permission of generating obs and start a new the interval count
			{
				obsInterval=0;
				obsInnerInterval=0;
				obsSingleInterval=stretch*10;//(rand()%(stretch*10));
			}

		}
		else obsInterval+=(rand()%2)*passingSpeed/(2*stretch);//obs interval count, randomize the added number to control the random distance between clusters

		if((std::rand()%500+1)>499)///this is the place to generate life boxes for now
		{
			obstacles.push_back((Obstacle(-1)));
			obstacles.at(obstacles.size()-1).setPos(this->XSize, this->groundBlocks.at(groundBlocks.size()-1).y - obstacles.at(obstacles.size()-1).returnSizeY()*stretch-(std::rand()%300));
		}
		if(!obstacles.empty())//control the obstacles movement & position
		{
			for(int num=0;num<obstacles.size();num++)//updata the location of the obstacles
			{
				obstacles.at(num).setPos(obstacles.at(num).returnPosX()-passingSpeed,obstacles.at(num).returnPosY());

			}
			while(!obstacles.empty() && obstacles.at(0).returnPosX()<-100)//delete the not useful obstacles
			{
				obstacles.erase(obstacles.begin());//when obstacle out of screen we delete it
			}
		}

	}
//	cout<<"obss "<<returnObstacles().size()<<endl;//for testing
//	if(returnObstacles().size()>0){
//		cout<<"obsm  "<<obstacles.at(0).returnThisObstacleModel().size()<<endl;//for t3sting
//		cout<<"obsmobs  "<<obstacles.at(0).returnThisObstacleModel().at(0).size()<<endl;
//	}
}

void Environment::drawGround(nana::paint::graphics& g)
{
	for(int i=0;i<groundBlocks.size();i++)//=stretch)//XSize//remember the size not always relate to XSize when added five but delete one
	{
		g.rectangle({groundBlocks.at(i).x,groundBlocks.at(i).y,stretch,1000000},true,colors::dark_gray);
		g.rectangle({groundBlocks.at(i).x,groundBlocks.at(i).y,stretch,stretch},true,colors::black);
	}
}
void Environment::drawObstacle(nana::paint::graphics& g)
{
	if(!obstacles.empty())
		for(int num=0;num<obstacles.size();num++)
		{
			if(!obstacles.at(num).isCollipsed())//when not collipsed (considering do this or not)
				for(int i=0;i<obstacles.at(num).returnSizeY();i++)
				{
						for(int j=0;j<obstacles.at(num).returnSizeX();j++)
						{
							if(obstacles.at(num).returnThisObstacleModel()[i][j]==1)
								if(obstacles.at(num).type()>0)//the damage obstacles will draw in different colors from life boxes
									g.rectangle({obstacles.at(num).returnPosX()+j*stretch,obstacles.at(num).returnPosY()+i*stretch,stretch,stretch},true,colors::green);
								else if(obstacles.at(num).type()<0)
									g.rectangle({obstacles.at(num).returnPosX()+j*stretch,obstacles.at(num).returnPosY()+i*stretch,stretch,stretch},true,colors::red);

						}
				}
			if(obstacles.at(num).isCollipsed() && obstacles.at(num).type()>0)///try to draw a collipse effect; the obstacle should be the damage type for this effect
			{
				for(int i=0;i<obstacles.at(num).returnSizeY()*stretch+4*stretch;i++)
				{
						for(int j=0;j<obstacles.at(num).returnSizeX()*stretch+8*stretch;j++)
						{
							int rCC=std::rand()%500+1;
							if(rCC<2)
								g.rectangle({obstacles.at(num).returnPosX()+j-4*stretch,obstacles.at(num).returnPosY()+i-4*stretch,20,20},true,colors::green);
						}
				}
			}
		}
}
void Environment::drawEnvironment(nana::paint::graphics& g)
{
	backgroundAnimation(g);
	drawGround(g);
	drawObstacle(g);
}

vector<Obstacle>& Environment::returnObstacles()
{
	return obstacles;
}

vector<point> Environment::returnGrounds()
{
	return groundBlocks;
}

void Environment::stop()
{
	passingSpeed=0;
}
void Environment::stopAll()
{
	isStopAll=true;
}
void Environment::continueAll()
{
	isStopAll=false;
}
void Environment::setPassingSpeed(int v)
{
	passingSpeed=v;
}

void Environment::setGroundPos(int a)
{
	//initY=a;
	this->groundYPos=a;
	for(int i=0;i<groundBlocks.size();i++)
			groundBlocks.at(i).y=groundYPos;
}
int Environment::returnGroundPos()
{
	return groundYPos;
}
int Environment::returnYSize()
{
	return YSize;
}
int Environment::returnXSize()
{
	return XSize;
}
int Environment::returnPassingSpeed()
{
	return passingSpeed;
}

//==========
void Environment::backgroundAnimation(nana::paint::graphics& g)//draw a background animation
{
	if(backgroundAnimationStage==0)
		;
	if(backgroundAnimationStage==1)
	{
		int rmetenumbercontrol=std::rand()%200+1;//generation density
		if(rmetenumbercontrol<2)
		{
			int rnum=std::rand()%3+1;//numbers of meteors generated each time
			for(int i=0;i<rnum;i++)
			{
				int rm=std::rand()%this->XSize*2-this->XSize;
				meteors.push_back(point(rm,0));
			}
		}
		for(int i=0;i<meteors.size();i++)
		{
			meteors[i].x++;
			meteors[i].y++;

			for(int j=0;j<10;j++)
			{
				g.rectangle({meteors[i].x-j*5,meteors[i].y-j*5,10-j,10-j},true,colors::brown);
			}
		}

	}

	while(!meteors.empty() && meteors[0].y>5000)
	{
			meteors.erase(meteors.begin());
	}
}
} /* namespace Dino */
