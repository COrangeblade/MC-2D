#include<ege.h>
#include<graphics.h>
#include<bits/stdc++.h>
#include"block.h"
#include"world.h"
#include"button.h"
#pragma once
using namespace std;
const int MAXN = 15;
const int MAXM = 17; 
const int SW = 17;
const int SH = 16;
const LPCSTR background1 = "img\\gui\\background1.png";
const LPCSTR background2 = "img\\gui\\background2.png";
string itoa(int i)
{
	string tmp="";
	while(i)
	{
		tmp=char(i%10+'0')+tmp;
		i/=10;
	}
	if(tmp=="") tmp="0";
	return tmp;
}
class scene
{
	public:
		bool buff;
		int sc[MAXN+10][MAXM+10];
		int tool[2/SH+10][SW+10];
		int scl,scr,scu,scd;
		int flag;
		ege::PIMAGE __tmp_image;
		ege::PIMAGE __tmp;
		ege::PIMAGE _large_tmp;
		void outworld(int width,int height)
		{
			for(int i=1;i<=height;i++)
			{
				for(int j=1;j<=width;j++)
				{
					string t;
					t=block_inf[sc[i][j]].path1;
					ege::getimage_pngfile(__tmp_image,block_inf[sc[i][j]].path1.c_str());
					ege::putimage((j-1)*32,(i-1)*32,32,32,__tmp_image,0,0,SRCCOPY);
				}
			}
			ege::setfillcolor(EGERGB(0,255,0));
			ege::fillrect((px-scl)*32,(py-scu)*32,(px-scl+1)*32,(py-scu+2)*32);
		}
		void outtool()
		{
			if(flag==0) return;
			for(int i=2;i<=SH/2;i++)
			{
				for(int j=2;j<=SW-1;j++)
				{
//					__tmp_image=ege::newimage(32,32);
					ege::getimage_pngfile(__tmp_image,background1);
					ege::putimage((j-1)*32,(i-1)*32,32,32,__tmp_image,0,0,SRCCOPY);
				}
			}			
		}
		void outthing()
		{
			if(flag==0) return;
			for(int i=SH/2+1;i<=SH-1;i++)
			{
				for(int j=2;j<=SW-1;j++)
				{
					ege::getimage_pngfile(__tmp_image,background2);
					ege::putimage((j-1)*32,(i-1)*32,32,32,__tmp_image,0,0,SRCCOPY);					
				}
			}
			for(int i=SH/2+3;i<=SH-2;i++)
			{
				for(int j=5;j<=SW-4;j++)
				{
					int x = i-SH/2-2;
					int y = j-4;
					if(x==nowline&&nowponit==y)
					{
						ege::getimage_pngfile(__tmp,"img\\gui\\light.png");
						ege::putimage((j-1)*32,(i-1)*32,32,32,__tmp,0,0,SRCCOPY);
					}	
					ege::getimage_pngfile(__tmp_image,block_inf[inventory[x][y].id].path2.c_str());	
					ege::putimage((j-1)*32+8,(i-1)*32+8,16,16,__tmp_image,0,0,SRCCOPY);				
				}
			}
			for(int i=SH/2+3;i<=SH-2;i++)
			{
				for(int j=5;j<=SW-4;j++)
				{
					int x = i-SH/2-2;
					int y = j-4;
					LPCSTR num=itoa(inventory[x][y].num).c_str();
					ege::outtextrect(j*32-16,i*32-16,16,16,num);			
				}
			}
		}
		void outfooter()
		{
			int i = SH;
			for(int j=1;j<=SW;j++)
			{
				ege::getimage_pngfile(__tmp_image,background2);
				ege::putimage((j-1)*32,(i-1)*32,32,32,__tmp_image,0,0,SRCCOPY);				
			}				
			for(int j=5;j<=SW-4;j++)
			{
				int x = nowline;
				int y = j-4;					
				if(nowponit==y)
				{
					ege::getimage_pngfile(__tmp,"img\\gui\\light.png");
					ege::putimage((j-1)*32,(i-1)*32,32,32,__tmp,0,0,SRCCOPY);
				}	
				ege::getimage_pngfile(__tmp_image,block_inf[inventory[x][y].id].path2.c_str());	
				ege::putimage((j-1)*32+8,(i-1)*32+8,16,16,__tmp_image,0,0,SRCCOPY);				
			}			
			for(int j=5;j<=SW-4;j++)
			{
				int x = nowline;
				int y = j-4;
				LPCSTR num=itoa(inventory[x][y].num).c_str();
				ege::outtextrect(j*32-16,i*32-16,16,16,num);			
			}			
		}
		void buffer() 
		{
			ege::setactivepage(buff);
			ege::setvisualpage(!buff);
			outworld(MAXM,MAXN);
			outtool();
			outthing();
			outfooter();
			ege::setactivepage(!buff);
			ege::setvisualpage(buff);	
			buff=!buff;		
		}
		void init()
		{
			this->buff=0;
			this->__tmp=ege::newimage(32,32);
			this->__tmp_image=ege::newimage(16,16);
		}
		void load()
		{
			this->scl=max(0,px-MAXM/2);
			this->scr=this->scl+MAXM-1;
			this->scu=max(0,py-MAXN/2);
			this->scd=this->scu+MAXN-1;
			for(int i=scu;i<=scd;i++)
			{
				for(int j=scl;j<=scr;j++)
				{
					sc[i-scu+1][j-scl+1]=worlds.world[i][j];
				}
			}
		}
//		void loadhome()
//		{
//			ege::setfillcolor(RGB(0,255,255));
//			ege::fillrect(0,0,SH*32,SW*32);
//			button but1;
//			button but2;
//			but1.creat_a_button()
//		}
}scenes;
