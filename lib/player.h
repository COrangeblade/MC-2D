#include<windows.h>
#include<ege.h>
#include<bits/stdc++.h>
#include"world.h"
#include"image.h"
#pragma once
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
using namespace std;
using namespace ege;
class player
{
	public:
		double v_x,v_y ; //速度
		mouse_msg msg,tmp;
		bool test(int x,int y)
		{
			if(x<1||x>=MAXX) return false;
			if(y<1||y+1>=MAXY) return false;
			if(block_inf[worlds.world[y][x]].hit_box) return false;
			if(block_inf[worlds.world[y+1][x]].hit_box) return false;
			return true;
			//检查玩家是否能处于这个位置
		}
		void move(float t)
		{
			for(int i=1;i<=abs(int(v_x));i++)
			{//x移动 
				if(px>=0&&px<MAXX)
				{//判断x方向是否越界
					px+=int(v_x)/abs(int(v_x));
				}
				if(px<0)
				{//判断x方向是否越界
					px=0;
				}
				if(px>=MAXX-1)
				{//判断x方向是否越界
					px=MAXX-1;
				}
				if(!test(px,py))
				{//判断x方向是否可以移动
					px-=int(v_x)/abs(int(v_x));//x移动
					v_x=0;
					break;
				} 
			}
			for(int i=1;i<=abs(int(v_y));i++){//y移动 
				if(py>=1&&py<=MAXY){//判断y方向是否越界
					py+=int(v_y)/abs(int(v_y));
				}
				if(py<=1){//判断y方向是否越界
					py=1;
				}
				if(py>=MAXY){//判断y方向是否越界
					py=MAXY;
				}
				if(!test(px,py)){//判断y方向是否可以移动
					py-=int(v_y)/abs(int(v_y));//y移动
					v_y=0;
					break;
				} 
			}
			v_x*=0.5;//摩擦力 
			v_y+=1;//重力 
		}		
		void check()
		{
			//玩家按键检查
			if ((KEY_DOWN('W')||KEY_DOWN(' '))&&worlds.world[py+2][px])v_y=-1; //跳跃
			if (KEY_DOWN('D'))v_x=1; //向右移动
			if (KEY_DOWN('A'))v_x = -1; //向左移动
			int dx,dy;
			if (KEY_DOWN(key_up)) dx=-1,dy=0;
			if (KEY_DOWN(key_down)) dx=1,dy=0;
			if (KEY_DOWN(key_left)) dx=0,dy=-1;
			if (KEY_DOWN(key_right)) dx=0,dy=1;	
			if(KEY_DOWN(key_esc)&&scenes.flag) scenes.flag=0;
			if(KEY_DOWN('E')) scenes.flag=((scenes.flag==1)?0:1);
			if(KEY_DOWN('1')) nowponit=1;	
			if(KEY_DOWN('2')) nowponit=2;
			if(KEY_DOWN('3')) nowponit=3;
			if(KEY_DOWN('4')) nowponit=4;
			if(KEY_DOWN('5')) nowponit=5;
			if(KEY_DOWN('6')) nowponit=6;
			if(KEY_DOWN('7')) nowponit=7;
			if(KEY_DOWN('8')) nowponit=8;
			if(KEY_DOWN('9')) nowponit=9;
			if(1<=nowline+dx&&nowline+dx<=5) nowline+=dx;
			if(1<=nowponit+dy&&nowponit+dy<=9) nowponit+=dy;	//物品栏选择
			deal_with_mouse(); //
			move(0.5);
		}
		inline void dig(int x,int y)
		{
			if(msg.x<=MAXM*32)
			{
				int realx = y/32+py-7;
				int realy = x/32+px-8;
				int fall_block=block_inf[worlds.world[realx][realy]].FALL;
//				cout<<"xy:"<<realx<<' '<<realy<<endl;
				if(realx<1||realx>=MAXY) return;
				if(worlds.world[realx][realy]==0) return;
//				物品栏寻址
				for(int i=1;i<=5;i++)
				{
					for(int j=1;j<=9;j++)
					{
						if(inventory[i][j].num==0||inventory[i][j].id==fall_block&&inventory[i][j].num<64)
						{
							int no = fall_block;
							inventory[i][j].num++;
							inventory[i][j].id=no;
							inventory[i][j].path=block_inf[no].path2;
							worlds.world[realx][realy]=0;
							return;
						}
					}
				}
			}			
		}
		inline void put(int x,int y)
		{
			if(msg.x<=MAXM*32)
			{
				int realx = y/32+py-7;
				int realy = x/32+px-8;
				if(realx<1||realx>=MAXY) return;
				if(worlds.world[realx][realy]) return;
				if(inventory[nowline][nowponit].num)
				{
					inventory[nowline][nowponit].num--;
					worlds.world[realx][realy]=inventory[nowline][nowponit].id;
					if(inventory[nowline][nowponit].num==0)
					{
						inventory[nowline][nowponit].id=0;
						inventory[nowline][nowponit].path=block_inf[0].path2;
						return;
					}
				}				
			}
		}
		void deal_with_mouse()
		{
			//处理鼠标消息
			int x,y;
			if(KEY_DOWN(key_mouse_l))
			{
				mousepos(&x,&y);
				dig(x,y);
				return;
			}
			if(KEY_DOWN(key_mouse_r))
			{
				mousepos(&x,&y);
				put(x,y);
				return;
			}					
		}
		
}players;
