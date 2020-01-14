/*
 * Environment.h
 *
 *  Created on: Sep. 27, 2019
 *      Author: zwmsc
 */

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_
#include <nana/gui.hpp>
#include <vector>
//#include <bits/stdc++.h>
//#include <stl_algobase>
#include "Obstacle.h"
using namespace nana;
using namespace std;
namespace Dino {

class Environment {
public:
	Environment(int windowX, int windowY, int s);
	virtual ~Environment();

	void reset();
	//int (* returnATree())[19];
	void setStretch(int s);

	void updateEnvironment();

	void drawEnvironment(nana::paint::graphics& g);

	void drawGround(nana::paint::graphics& g);

	void drawObstacle(nana::paint::graphics& g);

	vector<Obstacle>& returnObstacles();

	vector<point> returnGrounds();

	void stop();//this will only set the passingSpeed to 0

	void stopAll();//this will stop environment from updates(I think will call this when dino dead)

	void continueAll();

	void setPassingSpeed(int v);

	void setGroundPos(int a);

	int returnGroundPos();

	int returnYSize();

	int returnXSize();

	int returnPassingSpeed();

	//==================
	void backgroundAnimation(nana::paint::graphics& g);//play some animation

private:

	bool isStopAll;//this flag indicate updates for calculation is stopped or not(speed not changed, location not changed, no new generation)
	int XSize;//size
	int YSize;
	int passingSpeed;
	int groundYPos;//indicate the altittude of current ground generate
	int stretch;
	vector<Obstacle> obstacles;
	vector<point> groundBlocks;//record groundblocks positions

	//those variables used to control abyss generation
	int abyssCount;//this will count the total pixels of abyss the program will generate, abyss width
	int abyssInterval;//this will pause the abyss generation for certain frame if an abyss already generated, limited the minimum generate density

	//those control the obstacle generation
	int obsInterval;//used to control the minimum distance between obs cluster
	int obsInnerInterval;//used to control the width of each cluster
	int obsSingleInterval;//control the interval between single obs within the clusters
	//================
	int backgroundAnimationStage;//control background animation
	vector<point> meteors;
};

} /* namespace Dino */

#endif /* ENVIRONMENT_H_ */
