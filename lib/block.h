#include<windows.h>
#include<bits/stdc++.h>
#pragma once
using namespace std;

const int BLOCKS_NUM = 50; //物品数量
int nowponit=1,nowline=1; //物品栏被选择位置
int __n;
void import_inf();
void export_inf();
class blocks
{
	public:
		string path1,path2; //正常皮肤，掉落物皮肤路径
		int fall[20];
		#define FALL fall[0]
		string name; //名字
		int id; //编号
		bool hit_box; //碰撞箱
}block_inf[BLOCKS_NUM];
class things
{
	public:
		int id;  //编号
		int num; //数量
		string name; //名字
		string path; //图片路径
}inventory[6][10];//物品栏
void block_init()
{
	import_inf();
//	export_inf();
	block_inf[BLOCKS_NUM-1].name="bedrock";
	block_inf[BLOCKS_NUM-1].path1="img\\item\\bedrock.png";
	block_inf[BLOCKS_NUM-1].path2="img\\item\\bedrock.png";
	block_inf[BLOCKS_NUM-1].id=BLOCKS_NUM-1;
	block_inf[BLOCKS_NUM-1].hit_box=1;	
}
void import_inf()
{
	ifstream in;
	in.open("info\\block\\block_info.txt");
	in>>__n;
	for(int i=0;i<=__n;i++)
	{
		string p;
		in>>p;
		replace(p.begin(),p.end(),'/','\\');
		block_inf[i].path1=p;
		in>>p;
		replace(p.begin(),p.end(),'/','\\');
		block_inf[i].path2=p;
		in>>p;
		replace(p.begin(),p.end(),'/','\\');
		block_inf[i].name=p;
		in>>block_inf[i].id;
		in>>block_inf[i].hit_box;
		in>>block_inf[i].FALL;
	}
	in.close();
}
void export_inf()
{
	ofstream out;
	out.open("info\\block\\block_info.txt");
	out<<__n<<endl;
	for(int i=0;i<=__n;i++)
	{
//		in>>block_inf[i].
		string p;
		p=block_inf[i].path1;
		replace(p.begin(),p.end(),'\\','/');
		out<<p<<' ';
		p=block_inf[i].path2;
		replace(p.begin(),p.end(),'\\','/');
		out<<p<<' ';
		p=block_inf[i].name;
		replace(p.begin(),p.end(),'\\','/');
		out<<p<<' ';	
		out<<block_inf[i].id<<' ';
		out<<block_inf[i].hit_box<<' ';
		out<<block_inf[i].FALL<<' ';
		out<<endl;
	}
	out.close();	
}
