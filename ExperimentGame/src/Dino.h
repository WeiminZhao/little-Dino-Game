/*
 * Dino.h
 *
 *  Created on: Sep. 25, 2019
 *      Author: zwmsc
 */

#ifndef DINO_H_
#define DINO_H_
#include <nana/gui.hpp>
#include "Environment.h"
#include "Animals.h"
using namespace nana;
namespace Dino {

class Dino {
public:
	Dino(int windowX,int windowY, int s);
	virtual ~Dino();
	void reset();
	void setStretch(int s);
	int (* returnDino())[19];//return the default frame of dino
	int (* returnCurrentFrame())[19];//return the frame indicate by dinoFrame
	void increaseFrame();//change frame from ascendent or descendent way, call by autoFrameChange
	void decreaseFrame();
	void setDead();
	bool deadOrNot();
	void autoFrameChange();///call this if you want to make dino frames change in animation
	void drawCurrentFrame(nana::paint::graphics& g);
	void autoAnimateDino(nana::paint::graphics& g);
	void printScore(nana::paint::graphics& g,int x, int y,int xh,int yh, paint::font& fnt, paint::font& hifnt);//xh yh is highest score location
	void setJump();
	//void calculateJump(Environment& en);
	void calculateGravity(Environment& en);//include ground touch calculation.replacement of calculateJump
	int calculateCollipse(Environment& en,Animals& an);//return the deduction of the HP, <0 means plus HP,>0 means minus HP
	void calculateHp(Environment& en,Animals& an);
	void displayHP(nana::paint::graphics& g,int x, int y, paint::font& fnthp);
	void deadScreen(nana::paint::graphics& g, int x, int y, paint::font& fntgo, paint::font& fntgodesc);
	void updateDino(Environment& en,Animals& an, bool inistat);
	int returnYSize();
	int returnXSize();
	int returnHScore();
	void setHScore(int hs);
private:
	int frameDino;///0 = frame a; 1= frame b; 2=c;3=d
	bool isReverseAminationDino;//the default order of frame is a,b,c,d; this indicate the we want to reverse the order for need. Used to indicate when to call increaseframe and decreaseframe
	bool isJumping;// this flag is to prevent to jump again in jump
	bool secJumping;//flag for double jumping
	int initialJumpSpeed;
	double YAcceleration;//we use double so we can use fraction to micro-change
	double YSpeed;//the speed of y direction. if we want it to jump we set a speed to this and it will be auto-calculate
	//int XRelDistance;//this is position relative to the ground position of the dino
	//int YRelDistance;
	int XPosition;//those are the position to the window
	int YPosition;//higher deeper
	int XInitRecord;//this record initial positions for convenient
	int YInitRecord;//also those are the "fixed" dino position

	int lastHiGround;//record the last highest ground block under dino's foot
	int JumpTimer;
	//bool isCollipse;
	int HP;
	int oldHP;//pure cosmetics, nothing functional
	int aniHP=6;//still cosmetics,

	bool isDead;
	//Environment en;
	int XSize;//the real size=Xsize*stretch
	int YSize;
	int stretch;
	int score;//the score for this dino
	int hiScore;

	int winX;//record the total window size that put dino in
	int winY;


	int dino[19][19]={{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0},
					  {0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1},
					  {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
					  {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
					  {1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
					  {1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
					  {1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0},
					  {1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0},
					  {1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0},
					  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
					  {0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0},
					  {0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
					  {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
					  {0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
					  {0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,1,1,1,0,1,1,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0}};

	int dinA[19][19]={{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0},///////////
					  {0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1},
					  {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
					  {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
					  {1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
					  {1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
					  {1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0},
					  {1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0},
					  {1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0},
					  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
					  {0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0},
					  {0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
					  {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
					  {0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
					  {0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0}};

	int dinB[19][19]={{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0},
					  {0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1},
					  {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
					  {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
					  {1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
					  {1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
					  {1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0},
					  {1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0},
					  {1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0},
					  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
					  {0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0},
					  {0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
					  {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
					  {0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
					  {0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0}};


	int dinC[19][19]={{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0},
					  {0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1},
					  {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
					  {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
					  {1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
					  {1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
					  {1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0},
					  {1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0},
					  {1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0},
					  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
					  {0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0},
					  {0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
					  {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
					  {0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
					  {0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,1,1,1,0,0,1,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0},
					  {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0}};



	int dinD[19][19]={{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0},///////////////
					  {0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1},
					  {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
					  {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
					  {1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
					  {1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
					  {1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0},
					  {1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0},
					  {1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0},
					  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
					  {0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0},
					  {0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
					  {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
					  {0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
					  {0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,0},
					  {0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0}};

};

} /* namespace Dino */

#endif /* DINO_H_ */
