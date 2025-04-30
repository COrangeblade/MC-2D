/*
MC 2D 1.9.0.beta
本版本由上版本重写而来，结构上有较大变化。
我们更新了如下几个方面
- 优化缓冲方式，但并没有采用双缓冲，所以会出现卡屏现象。
- 缩小程序体量，代码由 19 kb -> 12 kb
- 修复了如下 BUG：
	- 指针移动 BUG
	- 虚空 BUG
	- 开始菜单 BUG
- 优化了码风
- 同时，由于各方面原因，我们暂时移除了修改键位操作，日后会恢复。
- 此次升级，难免有不足和问题，请您及时反馈，让他变的更好
- 最后，感谢各位水友的支持，希望大家以后能继续陪伴 MC 2D 制作组走下去。
												此致敬礼
												MC 2D 制作组
												1.21 日晚上
1.20 开始编写。
1.21 收工。
*/
#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>

using namespace std;

#define DEBUG cout<<666<<endl;
/*----- 世界信息 -----*/
const int MAXY = 150;
const int MAXX = 500; 		// 地图长宽
int world[MAXY+20][MAXX+20]; 		// 地图
const int TICK = 10;        // 刻(10 tick(s)/s)
int ground_att;             // 水平面高度
const int BLOCKS_NUM = 5;	// 方块种类数量
const int KEY_MAX = 12;		// 按键种类数量
/*----- 按键信息 -----*/
char key[KEY_MAX + 5];  		// 按键字母
map <char, int> key_id;		// 按键索引
map <int, string> key_use;  // 按键功能

/*----- 物品信息 -----*/
map <string, int> blocks_id;// 方块编号
string blocks[BLOCKS_NUM + 5];			// 方块名称
string blocks_character[BLOCKS_NUM + 5];	// 方块字符画
int blocks_num[BLOCKS_NUM + 5];			// 拥有方块数量
int block_colors[BLOCKS_NUM + 5];
/*----- 指针 -----*/
int key_point; 			 	// 按键指针
int main_menu_point;		// 主菜单指针

/*----- 窗口 -----*/

int screen_left, screen_right;
int screen_up, screen_down; // 屏幕四至点
int player_x, player_y;		// 玩家坐标
int point_x, point_y;		// 指针坐标
bool flag_point;			// 指针模式

void setcolor(int a) {
	//颜色设置
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}
//struct node {				// 缓冲区
//	int color;
//	char character;
//	void set_it(int a, char b) {
//		this ->color = a;
//		this ->character = b;
//	}
//	void show() {
//		setcolor(this ->color);
//		putchar(character);
//	}
//} gragh[MAXY + 10][MAXX + 10];
void save() {	//存档
	system("cls");
	string name; //档名
	cout << "请输入存档名:";
	cin >> name;
	name += ".json";
	Sleep(1000);
	system("cls");
	cout << "正在存档,请稍后·····" << endl;
	FILE* fp = fopen(name.c_str(), "wb");
	if (fp == NULL) {
		cout << "未找到存档文件，请联系开发者。 网址：https://www.luogu.com.cn/team/98501" << endl;
		return;
	}
	for (int i = 0; i < MAXY; i++) {
		for (int j = 0; j < MAXX; j++)
			fprintf(fp, "%d ", world[i][j]);
		fprintf(fp, "\n");
	}
	fprintf(fp, "%d %d %d %d \n", screen_left, screen_right, player_x, player_y);
	for (int i = 0; i <= BLOCKS_NUM; i++)
		fprintf(fp, "%d\n", blocks_num[i]);
	fclose(fp);
	cout << "存档成功！" << endl;
	Sleep(2000);
	exit(0);
}
void key_place_show() { //键位缓冲
	string area;
	for (int i = 1; i <= KEY_MAX; i++)
		area += key_use[i] + ": " + key[i] + ((key_point == i) ? "√\n" : "\n");
	system("cls");
	cout << area;
}
void buffer() { // 图像缓冲
	system("cls");
	for (int i = screen_up; i < screen_down; i++) {
		for (int j = screen_left; j < screen_right; j++) {
			if (i == point_y && j == point_x && flag_point) {
				setcolor(240);
				putchar('.');
			} else if (i == player_y && j == player_x) {
				setcolor(240);
				putchar('@');
			} else {
				setcolor(block_colors[world[i][j]]);
				putchar(blocks_character[world[i][j]].c_str()[0]);
			}
		}
		cout << '\n';
	}
	setcolor(240);
	cout << "屏幕最左x:" << screen_left << "\n屏幕最右x:" << screen_right << "\n屏幕最上" << 150 - screen_up << "\n屏幕最下" << 150 - screen_down << "\n我的坐标" << "(" << player_x << "," << 150 - player_y << ")";
}
void check_G() { //重力检查
	if (!world[player_y + 2][player_x] && !world[player_y][player_x] && player_y <= 150) {
		player_y++;
		if (screen_down - player_y <= 3) {
			screen_up++;
			screen_down = screen_up + 9;
		}
		buffer();
	}
	if (player_y >= 150 ) {
		cout << "你在虚空死了" << endl;
		exit(0);
	}
}
void key_12() {
	save();
}
void key_3() {
	if (flag_point) {
		point_x--;
		if (point_x < screen_left) point_x++;
	} else {
		player_x--;
		if (!player_x || world[player_y][player_x]) {
			player_x++;
		}
		if (player_x - screen_left < 10 && screen_left > 0)
			screen_left--, screen_right = screen_left + 31;
	}
	buffer();
}
void key_4() {
	if (flag_point) {
		point_x++;
		if (point_x >= screen_right) point_x--;
	} else {
		player_x++;
		if (player_x == MAXX || world[player_y][player_x]) {
			player_x--;
		}
		if (screen_right - player_x < 10 && screen_right < MAXX)
			screen_left++, screen_right = screen_left + 31;
	}
	buffer();
}
void key_1() {
	if (flag_point) {
		if (point_y - 1 < 0 || point_y - 1 < screen_up) return;
		point_y--;
		buffer();
	} else {
		if (player_y - 1 < 0)  return;
		player_y--;
		if (world[player_y][player_x]) player_y++;
		else if (!world[player_y + 2][player_x] && !world[player_y + 1][player_x] && player_y <= 150)
			player_y++;
		if (player_y - screen_up == 3) screen_up--, screen_down = screen_up + 9;
		buffer();
	}
}
void key_2() {
	if (flag_point) {
		if (point_y + 1 >= 150 || point_y + 1 >= screen_down) return;
		point_y++;
		buffer();
	} else {
		if (player_y + 1 >= 150)  return;
		player_y++;
		if (world[player_y][player_x]) player_y--;
		if (screen_down - player_y == 3) screen_down++, screen_up = screen_down - 9;
		buffer();
	}
}
void key_5() {
	if (flag_point) return;
	system("cls");
	cout << "背包\n";
	for (int i = 1; i <= BLOCKS_NUM; i++)
		cout << blocks[i] << "有" << blocks_num[i] << "个\n";
	while (1) {
		if (kbhit()) {
			return;
		}
	}
}
void key_9() {
	if (flag_point) {
		flag_point = 0;
	} else {
		flag_point = 1;
		point_x = player_x;
		point_y = player_y;
	}
	buffer();
}
void key_11() {
	key_point = 0;
	system("cls");
	cout << "按键说明：\n正常模式：" << key[1] << "上 " << key[2] << "下 " << key[3] << "左 " << key[4] << "右 " << key[9] << "切换指针模式 " << key[11] << "按键说明 " << key[5] << "背包 " << key[10] << "修改键位\n\n指针模式：" << key[1] << "上 " << key[2] << "下 " << key[3] << "左 " << key[4] << "右 " << key[9] << "切换正常模式 " << key[6] << "挖掘 " << key[7] << "放置（空格确认）（用wsad选择）\n按+保存(无法更改按键)\n按" << key[11] << "即可退出哦~~~";
	while (1) {
		if (kbhit()) {
			char c = getch();
			if (c == key[11]) {
				buffer();
				return;
			}
		}
	}
}
void key_10() {
	system("cls");
	cout << "暂缓";
	Sleep(1000);
	system("cls");
	buffer();
}
void key_6() {
	if (!flag_point) return;
	blocks_num[world[point_y][point_x]]++;
	world[point_y][point_x] = 0;
	buffer();
}
void show_block(int flag) {
	system("cls");
	cout << "背包\n";
	for (int i = 1; i <= BLOCKS_NUM; i++)
		cout << blocks[i] << "有" << blocks_num[i] << "个 " << ((flag == i) ? "√\n" : "\n");
}
void key_7() {
	if (point_x == player_x && point_y == player_y) return;
	int block_point = 1;
	show_block(block_point);
	while (1) {
		if (kbhit()) {
			char c = getch();
			if (c == key[2]) {
				block_point++;
				if (block_point > BLOCKS_NUM) block_point = 1;
				show_block(block_point);
			} else if (c == key[1]) {
				block_point--;
				if (block_point == 0) block_point = BLOCKS_NUM;
				show_block(block_point);
			}
			if (c == key[8]) {
				if (blocks_num[block_point]) {
					blocks_num[block_point]--;
					world[point_y][point_x] = block_point;
					buffer();
					break;
				} else {
					system("cls");
					cout << "方块不足" << endl;
					Sleep(1000);
					break;
				}
			} else if (c == key[7]) {
				buffer();
				return;
			}
		}
	}
}
void key_8() {
	return;
}
void key_check() {  //按键检测
	if (kbhit()) {
		char c = getch();
		switch (key_id[c]) {
			case 1:
				key_1();
				break;
			case 2:
				key_2();
				break;
			case 3:
				key_3();
				break;
			case 4:
				key_4();
				break;
			case 5:
				key_5();
				break;
			case 6:
				key_6();
				break;
			case 7:
				key_7();
				break;
			case 8:
				key_8();
				break;
			case 9:
				key_9();
				break;
			case 10:
				key_10();
				break;
			case 11:
				key_11();
				break;
			case 12:
				key_12();
				break;
		}
	}
}
void main_menu() { //主菜单
	system("cls");
	cout << "按w，s来选择吧！" << endl;
	cout << "1.新游戏";
	if (main_menu_point == 0) {
		cout << "√";
	}
	cout << endl;
	cout << "2.我要读档！！！";
	if (main_menu_point == 1) {
		cout << "√";
	}
	cout << endl;
	cout << "空格确定" << endl;
}
void ad() { //广子
	system("cls");
	cout << endl << endl << endl << endl << endl << endl;
	cout << "        " << "MC 2D 工作室出品" << endl;
	cout << "        " << "免费游戏概不收费" << endl;
	cout << "        " << "  团队招宣传员  " << endl;
	cout << "        " << " 洛谷团队:98501 " << endl;
	Sleep(5000);
	system("cls");
	cout << endl << endl << endl << endl << endl << endl;
	cout << "    " << "       健康游戏忠告" << endl;
	cout << "    " << "抵制不良游戏，拒绝盗版游戏。" << endl;
	cout << "    " << "注意自我保护，谨防受骗上当。" << endl;
	cout << "    " << "适度游戏益脑，沉迷游戏伤身。" << endl;
	cout << "    " << "合理安排时间，享受健康生活。" << endl;
	Sleep(3000);
	system("cls");
}
void start() { //开始
	/*窗口设置*/
	system("mode con cols=36 lines=20");
	system("color F0");
	/*选择模式*/
	ad(); /*体验纯净版请将此行注释*/
	main_menu();
	while (1) {
		if (kbhit()) {
			char kscd_ch;
			kscd_ch = getch();
			if (kscd_ch == 'w') {
				main_menu_point--;
				if (main_menu_point == -1) {
					main_menu_point++;
				}
				main_menu();
			}
			if (kscd_ch == 's') {
				main_menu_point++;
				if (main_menu_point == 2) {
					main_menu_point--;
				}
				main_menu();
			}
			if (kscd_ch == ' ') {
				break;
			}
		}
	}
}
void init() { //初始化
	blocks[1] = "泥土";
	blocks_id["泥土"] = 1;
	blocks_character[1] = '^';
	blocks[2] = "石头";
	blocks_id["石头"] = 2;
	blocks_character[2] = '#';
	blocks[3] = "原木";
	blocks_id["原木"] = 3;
	blocks_character[3] = '$';
	blocks[4] = "树叶";
	blocks_id["树叶"] = 4;
	blocks_character[4] = '%';
	blocks[5] = "树苗";
	blocks_id["树苗"] = 5;
	blocks_character[5] = '*';
	blocks[0] = "NULL";
	blocks_id["NULL"] = 0;
	blocks_character[0] = ' ';
	key[1] = 'w';
	key_id['w'] = 1;
	key_use[1] = "上";
	key[2] = 's';
	key_id['s'] = 2;
	key_use[2] = "下";
	key[3] = 'a';
	key_id['a'] = 3;
	key_use[3] = "左";
	key[4] = 'd';
	key_id['d'] = 4;
	key_use[4] = "右";
	key[5] = 'b';
	key_id['b'] = 5;
	key_use[5] = "背包";
	key[6] = 'j';
	key_id['j'] = 6;
	key_use[6] = "摧毁";
	key[7] = 'k';
	key_id['k'] = 7;
	key_use[7] = "放置";
	key[8] = ' ';
	key_id[' '] = 8;
	key_use[8] = "确定";
	key[9] = '~';
	key_id['~'] = 9;
	key_use[9] = "切换指针";
	key[10] = '?';
	key_id['?'] = 10;
	key_use[10] = "修改";
	key[11] = 'p';
	key_id['p'] = 11;
	key_use[11] = "改按键(暂缓)";
	key[12] = '+';
	key_id['+'] = 12;
	key_use[12] = "结束+存档";
	block_colors[0] = 255;
	block_colors[1] = 34;
	block_colors[2] = 136;
	block_colors[3] = 102;
	block_colors[4] = 170;
	block_colors[5] = 224;
}
void build_world() { //生成世界
	for (int i = 0; i < MAXY; i++) { // 生成地形与树苗
		for (int j = 0; j < MAXX; j++) {
			if (i == ground_att) {
				world[i][j] = 1;
			} else if (i > ground_att) {
				world[i][j] = 2;
			} else {
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
				j += 3; // 防止连续生成树，但又不破坏树苗
			}
		}
	}
	buffer();
}
void Set_Born_Point() { //出生点设置
	cout << "设置*屏幕最左x（0~469）:";
	cin >> screen_left;
	screen_right = screen_left + 31;
	while (screen_left <= -1 || screen_right >= 501) {
		cout << "请重新输入最左端x坐标（0~469）:";
		cin >> screen_left;
		screen_right = screen_left + 31;
	}
	cout << "设置*地面高度(145~5):";
	cin >> ground_att;
	while (ground_att < 5 || ground_att > 145) {
		cout << "设置*地面高度(145~5):";
		cin >> ground_att;
	}
	ground_att = 150 - ground_att;
	player_x = screen_left + 16;
	player_y = ground_att - 1;
	screen_up = player_y - 4;
	screen_down = screen_up + 9;
}
void load() {  //读档
	string name;
	cout << "请输入你的存档名称（无需带.json）：\n";
	cin >> name;
	name += ".json";
	FILE* fp = fopen(name.c_str(), "rb");
	if (fp == NULL) {
		cout << "无法打开文件进行读取" << endl;
		throw (114514);
		exit(0);
	}
	for (int i = 0; i < MAXY; i++) {
		for (int j = 0; j < MAXX; j++) {
			fscanf(fp, "%d ", &world[i][j]);
		}
	}
	fscanf(fp, "%d %d %d %d\n", &screen_left, &screen_right, &player_x, &player_y);
	for (int i = 1; i <= BLOCKS_NUM; i++) {
		fscanf(fp, "%d", &blocks_num[i]);
	}
	fclose(fp);
	screen_up = player_y - 4;
	screen_down = screen_up + 9;
	buffer();
}

int main() {
	start();
	init();
	if (main_menu_point == 0) {
		Set_Born_Point();
		key_11();//新手和新世界进游戏前弹一次按键
		build_world();
	} else{
		load();
	}
	while (1) {
		key_check();
		check_G();
		Sleep(1000 / TICK);
	}
	return 0;
}
