#include<bits/stdc++.h>
#include<ege.h>
#include"lib/block.h"
#include"lib/image.h"
#include"lib/player.h"
#include"lib/world.h"
#include"lib/button.h"
#include<windows.h>
using namespace std;
bool chose;
button a,b,home;
void load_home()
{
	ege::setfillcolor(EGERGB(100,255,255));
	ege::fillrect(0,0,SW*32,SH*32);
	a.creat_a_button(3*32,6*32,11*32,32);
	b.creat_a_button(3*32,10*32,11*32,32);
	a.set_image("img\\gui\\newworld.png");
	b.set_image("img\\gui\\quit.png");
	a.show();
	b.show();	
	chose=0;
} //姑且先放这吧，往后搬家
void game(int flag)
{
	block_init(); 
	if(flag)
	{
		worlds.build_world(); 
		
	}
	else ;
	scenes.init(); 
	while(1)
	{
		players.check(); 
		scenes.load(); 
		scenes.buffer(); 
		Sleep(50);
		ege::cleardevice(); 
		if(KEY_DOWN(key_esc)&&!scenes.flag) break; 
	}	
	load_home();
}
int main()
{
	cout<<"loading.........."<<endl;
	ege::initgraph(SW*32,SH*32);
	ShowWindow(GetConsoleWindow(),SW_HIDE); 
	ege::setcaption("MC 2D EGE");
	load_home();
	while(1)
	{
		if(a.isdown()) chose=1;
		if(b.isdown())
		{
			return 0;
		}
		if(chose==1)
		{
			game(1);
		}
	}
	ege::closegraph();
	return 0;
}
