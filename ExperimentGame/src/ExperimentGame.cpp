//============================================================================
// Name        : ExperimentGame.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <chrono>
#include <time.h>
#include <nana/gui.hpp>
#include <nana/gui/timer.hpp>
#include <nana/threads/pool.hpp>
#include <thread>
#include <fstream>
#include <Windows.h>//

#include "Dino.h"
#include "Environment.h"
#include "Animals.h"

using namespace std;
using namespace nana;

const int windowSizeX=800;
const int windowSizeY=600;
const int pixelStretch=4;

paint::font fpsfnt("fps",10,{400});//create new font for this output
paint::font inifnt("game title",100,{850});//create new font for this output
paint::font inifnt2("game title descr",30,{800});//create new font for this output
paint::font inifnt3("title screen descr",10,{800});//create new font for this output
paint::font fntsc("score",20,{800});//create new font for this output
paint::font fnthi("high score",20+5,{850});//create new font for this output
paint::font fnthp("hp",38,{850});//create new font for this output
paint::font fntgo("Game Over",100,{800});//create new font for this output
paint::font fntgodesc("press space to next round",100/3,{400});//create new font for this output

int main() {
	::ShowWindow(::GetConsoleWindow(),SW_HIDE);//hide console
	time_t fpstime=chrono::system_clock::to_time_t(chrono::system_clock::now());//get the time since epoch for fps counting
	int fps=0;
	int printfps=0;
	clock_t cfps=clock();//fps controller
	srand(time(NULL));//this is to make rand() actually look like random

	bool iniscreen=true;//when player first enter the game, indicate that on the first description screen
	bool isReseting=false;//when player tell the program to reset the game through event listener, event listener will set the flag to true, so the loop thread will do the reset work
						  //we use this flag to solve the synchronize problem if we directly call the reset in event listener (program try to update and paint through the cleaning)
	Dino::Environment envir(windowSizeX,windowSizeY,pixelStretch);
	Dino::Animals anys(windowSizeX,windowSizeY,pixelStretch);
	Dino::Dino dino(windowSizeX,windowSizeY,pixelStretch);

	envir.setGroundPos(envir.returnYSize()*3/4+dino.returnYSize()*pixelStretch/2);//setup the ground altittude

	envir.stopAll();//pause the game on initial screen
	anys.stop();
	//saving file read===============
	fstream sfile;
	sfile.open("save.dino",fstream::out|fstream::in);
	string sline;
	if(getline(sfile,sline))
		dino.setHScore(stoi(sline));
	else cout<<"fail open\n";
	sfile.close();
	//===============================

	form fm { API::make_center(windowSizeX, windowSizeY) };
	fm.caption("Dino");
	API::track_window_size(fm,{windowSizeX, windowSizeY},false);//prevent from resize
	API::track_window_size(fm,{windowSizeX, windowSizeY},true);

	std::thread T([&]{
		srand(time(NULL));//this is to make rand() actually look like random
		while(true){
			//fps++;//for fps conting
			//cfps++;
			///if(cfps>=3000)
			if(((clock()-cfps)/(double)CLOCKS_PER_SEC)>=(0.017))//here we control the fps of the game, normally be 0.017(60fps)
			{
				//std::this_thread::sleep_for(std::chrono::milliseconds(10));//sleep method for fps control
				///cout<<"IR "<<isReseting<<endl;//for testing
				fps++;//real fps counter
				cfps=clock();
				if(!isReseting)//normal progressing the game
				{
					//if(!iniscreen){//if this is the first initializing(on the description screen), pause the game
					//update game contents
					//for(int updatespeed=0;updatespeed<2;updatespeed++){//try to update multi times per frame to control speed
					dino.updateDino(envir,anys,iniscreen);
					envir.updateEnvironment();
					anys.updateAnimals(envir);
					//}
					//}

					API::refresh_window(fm);//refresh the graphic paint
				}
				if(isReseting)//when isReseting set to true, we do the reset job here
				{
					envir.reset();
					dino.reset();
					anys.reset();

					envir.setGroundPos(envir.returnYSize()*3/4+dino.returnYSize()*pixelStretch/2);//re-setup the initial ground altittude
					isReseting=false;///after reset & clean we set this again to false for normal progress
				}

			}

		}//cout<<"looooopend"<<endl;
	});



	drawing dw(fm);//we need preset the painter in order to paint it in this API. After preset, we cannot change it

	dw.draw([&dino,&envir,&fps,&fpstime,&printfps,&anys,&iniscreen](paint::graphics &graph) {//here we preset the method about all elements need to be paint, and set all the variable to control the paint process

		graph.rectangle({0,0,windowSizeX,windowSizeY},true,colors::bisque);//set the background color
		if(chrono::system_clock::to_time_t(chrono::system_clock::now())-fpstime>=1)//for fps counting
		{
			fpstime=chrono::system_clock::to_time_t(chrono::system_clock::now());
			printfps=fps;
			fps=0;
		}

		graph.typeface(fpsfnt);
		graph.string({100,0},to_string(printfps),colors::blue_violet);//print fps
		graph.string({30,0},"vr. 0.06",colors::blue_violet);//print version no.
		//delete fpsfnt;//delete it after used


		//actual game drawing
		//initial drawing
		if(iniscreen)
		{
			string inis="GAME DINO";
			string inis2="press space to start";
			string inis3="use your space bar to jump, ONLY avoid the red plus mark";

			graph.typeface(inifnt);
			graph.string({windowSizeX/2-graph.text_extent_size(inis).width/2,windowSizeY/2-graph.text_extent_size(inis).height/2-50},inis,colors::burly_wood);
			graph.typeface(inifnt2);
			graph.string({windowSizeX/2-graph.text_extent_size(inis2).width/2,windowSizeY/2-graph.text_extent_size(inis2).height/2+50},inis2,colors::burly_wood);
			graph.typeface(inifnt3);
			graph.string({windowSizeX/2-graph.text_extent_size(inis3).width/2,windowSizeY/2-graph.text_extent_size(inis3).height/2+100},inis3,colors::burly_wood);

			//delete inifnt;//delete it after used
			//delete inifnt2;
		}
		//progress drawing
		envir.drawEnvironment(graph);
		anys.autoAnimateAnimals(graph);
		dino.autoAnimateDino(graph);
		dino.printScore(graph,25,55,25,20,fntsc, fnthi);//windowSizeX/2(hiscore old x)
		dino.displayHP(graph,windowSizeX-25,20,fnthp);
		if(dino.deadOrNot())	dino.deadScreen(graph,windowSizeX/2,windowSizeY/2,fntgo,fntgodesc);

	});

	fm.events().key_press([&dino,&envir,&anys,&isReseting,&iniscreen](const arg_keyboard& ak){
		if(ak.key==nana::keyboard::space)
		{
			if(iniscreen)//
			{
				iniscreen=false;
				envir.continueAll();
				anys.continueAll();
			}
			else if(!dino.deadOrNot())
				dino.setJump();
			else
			{
				isReseting=true;//set the reset flag to true
//				envir.reset();
//				dino.reset();
//
//				envir.setGroundPos(envir.returnYSize()/2+dino.returnYSize()*pixelStretch/2);//setup the ground altittude

				//isReseting=false;
			}
		}
	});
	fm.events().unload([&dino,&iniscreen](const arg_unload &arg){
		//cout<<"aasa";
		fstream sfile;
		sfile.open("save.dino",ios::trunc|fstream::out);
		sfile<<dino.returnHScore();
		sfile.close();

		iniscreen=false;
	});


	fm.show();

	::nana::exec();
	///cout<<"aasa";

	T.detach();

	return 0;
}
