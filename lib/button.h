#include<ege.h>
#include<bits/stdc++.h>
#pragma once
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)

using namespace std;
using namespace ege;

class button
{
	public:
		int color;
		int x,y;
		int w,h;
		PIMAGE img;
		LPCSTR word;
		int ele;
		void creat_a_button(int x,int y,int w,int h)
		{
			this->x=x;
			this->y=y;
			this->h=h;
			this->w=w;
			this->img=newimage(this->w,this->h);
			this->ele=0;
		}
		void setcolor(int color)
		{
			this->color=color;
		}
		void set_image(LPCSTR path)
		{
			getimage_pngfile(this->img,path);
			ele|= 1;
		}
		void move_to(int x,int y)
		{
			this->x=x;
			this->y=y;
		}
		void set_word(LPCSTR word)
		{
			this->word=word;
		}
		void show()
		{
			ege::setactivepage(0);
			ege::setvisualpage(1);
			ege::setfillcolor(color);
			ege::fillrect(x,y,x+w-1,y+h-1);
			if(ele&1)putimage(x,y,img);
			outtextrect(x,y,w,h,word);
			ege::setactivepage(1);
			ege::setvisualpage(0);
		}
		bool is_in()
		{
			int xx,yy;
			ege::mousepos(&xx,&yy);
			int left=x,right=x+w-1;
			int top=y,but=y+h-1;
			if(left<=xx&&xx<=right&&yy>=top&&yy<=but) return 1;
			else return 0;
		}
		bool isdown()
		{
			return (KEY_DOWN(key_mouse_l)||KEY_DOWN(key_mouse_r))&&is_in();
		}
};
