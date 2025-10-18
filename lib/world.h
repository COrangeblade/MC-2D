#include<bits/stdc++.h>
#include"block.h"
#pragma once
using namespace std;
const int MAXY = 150;
const int MAXX = 2000; //地图长宽
int ground_att,dirt_att; //地面海拔
int px, py; //玩家位置
class this_world {
	public:
		int world[MAXY + 20][MAXX + 20];//地图
		int att[MAXX+20],datt[MAXX+20];
		void build_world() {
			srand(time(0));
			ground_att=64;
			dirt_att=68;
			for(int i = 0 ;i < MAXX;i++)
			{
				if(ground_att<MAXY-50)
					if(rand()%2)
						ground_att++;			
				if(ground_att>20)
					if(rand()%2==0)
						ground_att--;
				if(dirt_att<MAXY-40&&dirt_att-ground_att<=6)
					if(rand()%2)
						dirt_att++;
				if(dirt_att>30&&dirt_att>ground_att+2)
					if(rand()%2)
						dirt_att--;
				att[i]=ground_att;	
				datt[i]=dirt_att;			
			}
			for (int i = 0; i < MAXY; i++) {
		
				for (int j = 0; j < MAXX; j++) {
					if (i == att[j]) {
						world[i][j] = 1;
					} else if (i > att[j]&&i<=datt[j]) {
						world[i][j] = 7;
					} else if(i > datt[j]){
						world[i][j] = 2;
					}else {
						int sj_tree;
						sj_tree = rand() % 10;
						if (sj_tree == 0) {
							world[i][j] = 5;
						} else {
							world[i][j] = 0;
						}
					}
				}
			}
			for(int j = 0;j < MAXX;j++)
			{
				world[MAXY][j]=BLOCKS_NUM-1;
			}
			for (int i = 0; i < MAXY; i++) { // 移除浮空树苗
				for (int j = 0; j < MAXX; j++) {
					if (world[i][j] == 5) {
						if (world[i + 1][j] != 1) {
							world[i][j] = 0;
						}
					}
				}
			}
			for (int i = 3; i < MAXY; i++) { // 树苗拓展生成树
				for (int j = 2; j < MAXX - 3; j++) {
					if (world[i][j] == 5) {
						world[i][j] = 3;
						world[i - 1][j] = 3;
						world[i - 2][j] = 3;
						world[i - 1][j + 1] = 4;
						world[i - 1][j - 1] = 4;
						world[i - 1][j + 2] = 4;
						world[i - 1][j - 2] = 4;
						world[i - 2][j + 1] = 4;
						world[i - 2][j - 1] = 4;
						world[i - 2][j + 2] = 4;
						world[i - 2][j - 2] = 4;
						world[i - 3][j + 1] = 4;
						world[i - 3][j - 1] = 4;
						world[i - 3][j] = 4;
						j += 8; // 防止连续生成树，但又不破坏树苗
					}
				}
			}
			px = rand()%MAXX;
			py=5;
		}
}worlds;
