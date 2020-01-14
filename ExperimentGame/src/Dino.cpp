/*
 * Dino.cpp
 *
 *  Created on: Sep. 25, 2019
 *      Author: zwmsc
 */

#include "Dino.h"
#include "Environment.h"
#include <nana/gui.hpp>
#include <iostream>
//#include <nana/>
using namespace nana;
using namespace std;
namespace Dino{

Dino::Dino(int windowX, int windowY, int s){ //:en(windowX, windowY){
	// TODO Auto-generated constructor stub
	XSize=19;
	YSize=19;
	frameDino = 0;

	isReverseAminationDino = false;

	isJumping =false;
	secJumping=false;
	HP=5;
	oldHP=HP;
	isDead=false;
	//isCollipse=false;
	initialJumpSpeed=18;//18//28/2;//velocity of jump in y direction
	YAcceleration=-1;//-1//-2/2;//acceleration for gravity
	YSpeed=0;//the speed of y direction. if we want it to jump we set a speed to this and it will be auto-calculate
	//XRelDistance=0;
	//YRelDistance=0;
	setStretch(s);
	XPosition=0+XSize*stretch;//windowX/2-XSize*stretch/2;
	YPosition=windowY*3/4-YSize*stretch/2;
	XInitRecord=XPosition;
	YInitRecord=YPosition;
	lastHiGround=YPosition;//record last high ground dino standon
	JumpTimer=0;
	//this->en=en;

	score=0;
	hiScore=score;

	winX=windowX;
	winY=windowY;
}
Dino::~Dino() {
	// TODO Auto-generated destructor stub
}
void Dino::reset()
{
	frameDino = 0;

	isReverseAminationDino = false;

	isJumping =false;
	secJumping=false;
	HP=5;
	oldHP=HP;
	isDead=false;
	initialJumpSpeed=18;//18//28/2;//velocity of jump in y direction
	YAcceleration=-1;//-1//-2/2;//acceleration for gravity
	YSpeed=0;//the speed of y direction. if we want it to jump we set a speed to this and it will be auto-calculate

	XPosition=0+XSize*stretch;//windowX/2-XSize*stretch/2;
	YPosition=winY*3/4-YSize*stretch/2;
	lastHiGround=YPosition;//record last high ground dino standon
	JumpTimer=0;

	score=0;
}
void Dino::setStretch(int s)
{
	this->stretch=s;
}
int (* Dino::returnDino())[19]
{
	return dino;
}
int (* Dino::returnCurrentFrame())[19]
{
	if (frameDino == 0)
		return dinA;
	if (frameDino == 1)
		return dinB;
	if (frameDino == 2)
		return dinC;
	if (frameDino == 3)
		return dinD;
	return dino;//the last one is for special use
}
void Dino::increaseFrame() {
	this->frameDino++;
}
void Dino::decreaseFrame() {
	this->frameDino--;
}
void Dino::setDead(){
	frameDino=-1;//let say -1 indicate dead
	isDead=true;
}
bool Dino::deadOrNot()
{
	return isDead;
}
void Dino::autoFrameChange() {
	if (frameDino >= 3)
		isReverseAminationDino = true;
	if (frameDino <= 0)
		isReverseAminationDino = false;

	if (!isReverseAminationDino)
		increaseFrame();
	else
		decreaseFrame();
}
void Dino::drawCurrentFrame(nana::paint::graphics& g)
{
	for(int i=0;i<YSize;i++)
	{
			for(int j=0;j<XSize;j++)
			{
				if(returnCurrentFrame()[i][j]==1)
					g.rectangle({XPosition+j*stretch,YPosition+i*stretch,stretch,stretch},true,colors::red);
			}
	}
}
void Dino::autoAnimateDino(nana::paint::graphics& g)
{
	if(!isDead)
		autoFrameChange();
	drawCurrentFrame(g);
}
void Dino::printScore(nana::paint::graphics& g,int x ,int y,int xh,int yh, paint::font& fnt, paint::font& fnthi)
{
	//set font//score print
	g.typeface(fnt);
	g.string({x,y},to_string(score),colors::brown);//text will align right//-g.text_extent_size(to_string(score)).width
	//delete fnt;//delete font after used

	//high score print
	g.typeface(fnthi);
	g.string({xh,yh},to_string(hiScore),colors::tomato);//text will align center for x only //-g.text_extent_size(to_string(hiScore)).width/2(old)
	//delete fnthi;//delete font after used
}

void Dino::setJump()
{
	if(!isDead)
	{
		if(isJumping==false)
		{
			YSpeed=initialJumpSpeed;// we set a initial speed of jump
			isJumping=true;// this flag is to prevent to jump again in jump
		}
		else if(secJumping==false)
		{
			YSpeed=initialJumpSpeed;
			secJumping=true;
		}
	}
}
//void Dino::calculateJump(Environment& en)
//{
//	//if()
//	if(isJumping)
//	{
//		JumpTimer++;
//		YSpeed=YSpeed+YAcceleration;
//		YPosition=YPosition-(YSpeed+0.5*YAcceleration);//*JumpTimer*JumpTimer);
//
//		if(en.returnGroundPos()-YPosition<95)
//		{
//			///YRelDistance=0;
//			YPosition=en.returnGroundPos()-95;
//			JumpTimer=0;
//			isJumping=false;
//			YSpeed=0;
//		}
//	}
//}
void Dino::calculateGravity(Environment& en)
{
	//dino y movement
	YSpeed=YSpeed+YAcceleration;

	//dino will falls until he stand on the ground
	int hiGround=10000000;//this used to determine the highest ground dino should stand on, remember the higher the deeper for y value
	for(int num=0;num<en.returnGrounds().size();num++)
	{	//only need to search the ground under dino for x values
		if((this->XPosition+stretch)<en.returnGrounds().at(num).x && en.returnGrounds().at(num).x+stretch  < (this->XPosition+XSize*stretch)-stretch)
		{	//if the dino cannot reach the ground he will fall 'till y=10000000 or another ground available;the reachable ground is (1-0.65) tall of the body of dino for now
			if(en.returnGrounds().at(num).y<hiGround)//the ground must be reachable for dino with his yposition & the ground must be highest available
			{///////en.returnGrounds().at(num).y>=this->YPosition+YSize*stretch*0.65  &&//this is an old method to detect standing ground
				hiGround=en.returnGrounds().at(num).y;
			}

		}
	}
	//the newest method to identify the standing ground for dino: if the last highest ground not equal abyss AND the recent highest ground not equals abyss, which means the dino is on a continued ground,
	//it should not fall below the ground by any mean. if the lastGround is an abyss depth, which mean even recent is not, the dino still has a chance falling under ground, unless dino is above the ground.
	//if the recent highest ground is abyss, then dino is falling(or jumping). benefit is the unlimited max speed
	//if the Yspeed>0 which indicate that dino is jumping up, so now YSpeed<=0 we will only do the ground collipse detection when dino falling or after he reach the highest pos(which is still falling)
	if(lastHiGround!=10000000 && hiGround!=10000000 && hiGround-YPosition-6<=YSize*stretch && YSpeed<=0)//here we determine where the dino stop dropping(collapse with ground)(the final position dino stop on)
	{//remember before here we already select the ground that dino will stand on, this just the detection collipse(final standing position) based on the selection

		YPosition=hiGround-YSize*stretch;
		isJumping=false;//whenever dino touch the ground this is false;
		secJumping=false;//same as above
		YSpeed=0;

	}
	else
		YPosition=YPosition-(YSpeed+0.5*YAcceleration);

	if(hiGround-YPosition>=YSize*stretch)//if the ground position is under dino's foot we record it //if not means dino probably already is falling to abyss
		lastHiGround=hiGround;

}
int Dino::calculateCollipse(Environment& en,Animals& an)
{
	int collapseResult=0;//this will return to the call and this variable is the final deduction of hp for dino
	//===============for obstacle========================
	if(!en.returnObstacles().empty())
	for(int num=0;num<en.returnObstacles().size();num++)
	{
		bool DCollipse =en.returnObstacles().at(num).isCollipsed();//to see if the obstacle has already been hit, if yes then it will not be hit again
		//std::cout<<DCollipse<<endl;
		int obX=en.returnObstacles().at(num).returnPosX() +stretch*2;//we would like to add some margin to the obstacle collipse area
		int obY=en.returnObstacles().at(num).returnPosY() +stretch*2;
		int obSizeX=en.returnObstacles().at(num).returnSizeX() -4;
		int obSizeY=en.returnObstacles().at(num).returnSizeY() -4;
		if(!DCollipse && XPosition <= obX+obSizeX*stretch && XPosition+XSize*stretch>= obX && YPosition<=obY+obSizeY*stretch && YPosition+YSize*stretch>=obY)
		{//when collipse
			if(en.returnObstacles().at(num).type()>0)//hit with damage
			{
				en.returnObstacles().at(num).collipsed();
				this->XPosition-=stretch*10;
				//return en.returnObstacles().at(num).type();
				collapseResult++;
			}
			if(en.returnObstacles().at(num).type()<0)//hit with life box
			{
				en.returnObstacles().at(num).collipsed();
				//return en.returnObstacles().at(num).type();
				collapseResult--;
			}
		}
	}

	//=======================for animals=======================
	if(!an.returnAnims().empty())
		for(int num=0;num<an.returnAnims().size();num++)
		{
			bool DCollipse =an.returnAnims().at(num).isCollipsed();//to see if the obstacle has already been hit, if yes then it will not be hit again
			//std::cout<<DCollipse<<endl;
			int obX=an.returnAnims().at(num).returnX() +stretch*2;//we would like to add some margin to the obstacle collipse area
			int obY=an.returnAnims().at(num).returnY() +stretch*2;
			int obSizeX=an.returnAnims().at(num).returnXSize() -4;
			int obSizeY=an.returnAnims().at(num).returnYSize() -4;
			if(!DCollipse && XPosition <= obX+obSizeX*stretch && XPosition+XSize*stretch>= obX && YPosition<=obY+obSizeY*stretch && YPosition+YSize*stretch>=obY)
			{//when collipse

				an.returnAnims().at(num).collipsed();
				this->XPosition-=stretch*10;
				//return en.returnObstacles().at(num).type();
				collapseResult++;

			}
		}

	return collapseResult;
}
void Dino::calculateHp(Environment& en,Animals& an)
{
	HP-=calculateCollipse(en,an);//the calculateCollipse() will auto return the total increase and decrease for the dino in this frame
	//if(HP>5) HP=5;//limit the max hp

	if(this->YPosition>1000)//falling death
	{
		HP=0;//setDead();
	}
	if(HP<=0)
	{
		setDead();
	}
}
void Dino::displayHP(nana::paint::graphics& g,int x, int y, paint::font& fnthp)
{
	int xl=x,yl=y;
	if(oldHP!=HP)
	{
		aniHP=6;
		oldHP=HP;
	}//fnthp.size()
		double fontsize=fnthp.size(1)+aniHP;
		x-=aniHP/2;
		y-=aniHP/2;

		aniHP-=(aniHP>0?1:0);//aniHP is pure cosmetic XD (the font size change after the number change)

	string shp="x"+to_string(HP);
	g.typeface(paint::font("loc hp",fontsize,fnthp.weight()));
	g.string({x-g.text_extent_size(shp).width,y},shp,colors::red);//text will align right
	//the normal one digit width of the hp string is 48.
	for(int i=0;i<19;i++)
			for(int j=0;j<19;j++)
				if(dino[i][j]==1)
					g.rectangle({xl-50-80+j*2,yl+i*2+10,2,2},true,colors::red);


	//delete fnthp;//delete font after used


}
void Dino::deadScreen(nana::paint::graphics& g,int x, int y, paint::font& fntgo,paint::font& fntgodesc)
{
	//set font

	g.typeface(fntgo);
	g.string({x-g.text_extent_size("Game Over").width/2,y-g.text_extent_size("Game Over").height/2-50},"Game Over",colors::brown);//text will align right
	//delete fnt;//delete font after used


	g.typeface(fntgodesc);
	g.string({x-g.text_extent_size("press space to next round").width/2,y-g.text_extent_size("press space to next round").height/2+50},"press space to next round",colors::brown);//text will align right
	//delete fnt2;//delete font after used
}
void Dino::updateDino(Environment& en,Animals& an, bool inistat)
{
	//calculateJump(en);
	calculateGravity(en);
	calculateHp(en,an);

	if(!isDead &&!inistat)
		score++;

	if(hiScore<score)
		hiScore=score;

	if(isDead)
	{
		en.stopAll();//stop the environment update
		an.stop();//stop animal update
	}

	if(XPosition<XInitRecord)//after hit dino will fall back a little and he should recover to his original x position after, this help him to do that
	{
		XPosition+=stretch;
	}
	if(XPosition>XInitRecord)
	{
		XPosition=XInitRecord;
	}

	if(score%2000==0 && score>0)//increase difficulty
	{
		en.setPassingSpeed(en.returnPassingSpeed()+stretch);
		an.setSpeed(an.returnPassingSpeed()+stretch);
	}
//	if(score==2000)///increasing difficulty when reach score==those numbers
//	{
//		en.setPassingSpeed(stretch*3);
//		an.setSpeed(stretch*3);
//	}
//	else if(score==4000)
//	{
//		en.setPassingSpeed(stretch*4);
//		an.setSpeed(stretch*4);
//	}
//	else if(score==6000)
//	{
//		en.setPassingSpeed(stretch*5);
//		an.setSpeed(stretch*5);
//	}
//	else if(score==8000)
//	{
//		en.setPassingSpeed(stretch*6);
//		an.setSpeed(stretch*6);
//	}

}
int Dino::returnYSize()
{
	return YSize;
}
int Dino::returnXSize()
{
	return XSize;
}
int Dino::returnHScore()
{
	return hiScore;
}
void Dino::setHScore(int hs)
{
	hiScore=hs;
}

} /* namespace Dino */
