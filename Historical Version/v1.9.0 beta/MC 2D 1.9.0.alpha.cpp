/*
MC 2D 1.9.0.beta
���汾���ϰ汾��д�������ṹ���нϴ�仯��
���Ǹ��������¼�������
- �Ż����巽ʽ������û�в���˫���壬���Ի���ֿ�������
- ��С���������������� 19 kb -> 12 kb
- �޸������� BUG��
	- ָ���ƶ� BUG
	- ��� BUG
	- ��ʼ�˵� BUG
- �Ż������
- ͬʱ�����ڸ�����ԭ��������ʱ�Ƴ����޸ļ�λ�������պ��ָ���
- �˴������������в�������⣬������ʱ������������ĸ���
- ��󣬸�л��λˮ�ѵ�֧�֣�ϣ������Ժ��ܼ������ MC 2D ����������ȥ��
												���¾���
												MC 2D ������
												1.21 ������
1.20 ��ʼ��д��
1.21 �չ���
*/
#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>

using namespace std;

#define DEBUG cout<<666<<endl;
/*----- ������Ϣ -----*/
const int MAXY = 150;
const int MAXX = 500; 		// ��ͼ����
int world[MAXY+20][MAXX+20]; 		// ��ͼ
const int TICK = 10;        // ��(10 tick(s)/s)
int ground_att;             // ˮƽ��߶�
const int BLOCKS_NUM = 5;	// ������������
const int KEY_MAX = 12;		// ������������
/*----- ������Ϣ -----*/
char key[KEY_MAX + 5];  		// ������ĸ
map <char, int> key_id;		// ��������
map <int, string> key_use;  // ��������

/*----- ��Ʒ��Ϣ -----*/
map <string, int> blocks_id;// ������
string blocks[BLOCKS_NUM + 5];			// ��������
string blocks_character[BLOCKS_NUM + 5];	// �����ַ���
int blocks_num[BLOCKS_NUM + 5];			// ӵ�з�������
int block_colors[BLOCKS_NUM + 5];
/*----- ָ�� -----*/
int key_point; 			 	// ����ָ��
int main_menu_point;		// ���˵�ָ��

/*----- ���� -----*/

int screen_left, screen_right;
int screen_up, screen_down; // ��Ļ������
int player_x, player_y;		// �������
int point_x, point_y;		// ָ������
bool flag_point;			// ָ��ģʽ

void setcolor(int a) {
	//��ɫ����
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}
//struct node {				// ������
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
void save() {	//�浵
	system("cls");
	string name; //����
	cout << "������浵��:";
	cin >> name;
	name += ".json";
	Sleep(1000);
	system("cls");
	cout << "���ڴ浵,���Ժ󡤡�������" << endl;
	FILE* fp = fopen(name.c_str(), "wb");
	if (fp == NULL) {
		cout << "δ�ҵ��浵�ļ�������ϵ�����ߡ� ��ַ��https://www.luogu.com.cn/team/98501" << endl;
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
	cout << "�浵�ɹ���" << endl;
	Sleep(2000);
	exit(0);
}
void key_place_show() { //��λ����
	string area;
	for (int i = 1; i <= KEY_MAX; i++)
		area += key_use[i] + ": " + key[i] + ((key_point == i) ? "��\n" : "\n");
	system("cls");
	cout << area;
}
void buffer() { // ͼ�񻺳�
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
	cout << "��Ļ����x:" << screen_left << "\n��Ļ����x:" << screen_right << "\n��Ļ����" << 150 - screen_up << "\n��Ļ����" << 150 - screen_down << "\n�ҵ�����" << "(" << player_x << "," << 150 - player_y << ")";
}
void check_G() { //�������
	if (!world[player_y + 2][player_x] && !world[player_y][player_x] && player_y <= 150) {
		player_y++;
		if (screen_down - player_y <= 3) {
			screen_up++;
			screen_down = screen_up + 9;
		}
		buffer();
	}
	if (player_y >= 150 ) {
		cout << "�����������" << endl;
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
	cout << "����\n";
	for (int i = 1; i <= BLOCKS_NUM; i++)
		cout << blocks[i] << "��" << blocks_num[i] << "��\n";
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
	cout << "����˵����\n����ģʽ��" << key[1] << "�� " << key[2] << "�� " << key[3] << "�� " << key[4] << "�� " << key[9] << "�л�ָ��ģʽ " << key[11] << "����˵�� " << key[5] << "���� " << key[10] << "�޸ļ�λ\n\nָ��ģʽ��" << key[1] << "�� " << key[2] << "�� " << key[3] << "�� " << key[4] << "�� " << key[9] << "�л�����ģʽ " << key[6] << "�ھ� " << key[7] << "���ã��ո�ȷ�ϣ�����wsadѡ��\n��+����(�޷����İ���)\n��" << key[11] << "�����˳�Ŷ~~~";
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
	cout << "�ݻ�";
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
	cout << "����\n";
	for (int i = 1; i <= BLOCKS_NUM; i++)
		cout << blocks[i] << "��" << blocks_num[i] << "�� " << ((flag == i) ? "��\n" : "\n");
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
					cout << "���鲻��" << endl;
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
void key_check() {  //�������
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
void main_menu() { //���˵�
	system("cls");
	cout << "��w��s��ѡ��ɣ�" << endl;
	cout << "1.����Ϸ";
	if (main_menu_point == 0) {
		cout << "��";
	}
	cout << endl;
	cout << "2.��Ҫ����������";
	if (main_menu_point == 1) {
		cout << "��";
	}
	cout << endl;
	cout << "�ո�ȷ��" << endl;
}
void ad() { //����
	system("cls");
	cout << endl << endl << endl << endl << endl << endl;
	cout << "        " << "MC 2D �����ҳ�Ʒ" << endl;
	cout << "        " << "�����Ϸ�Ų��շ�" << endl;
	cout << "        " << "  �Ŷ�������Ա  " << endl;
	cout << "        " << " ����Ŷ�:98501 " << endl;
	Sleep(5000);
	system("cls");
	cout << endl << endl << endl << endl << endl << endl;
	cout << "    " << "       ������Ϸ�Ҹ�" << endl;
	cout << "    " << "���Ʋ�����Ϸ���ܾ�������Ϸ��" << endl;
	cout << "    " << "ע�����ұ�����������ƭ�ϵ���" << endl;
	cout << "    " << "�ʶ���Ϸ���ԣ�������Ϸ����" << endl;
	cout << "    " << "������ʱ�䣬���ܽ������" << endl;
	Sleep(3000);
	system("cls");
}
void start() { //��ʼ
	/*��������*/
	system("mode con cols=36 lines=20");
	system("color F0");
	/*ѡ��ģʽ*/
	ad(); /*���鴿�����뽫����ע��*/
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
void init() { //��ʼ��
	blocks[1] = "����";
	blocks_id["����"] = 1;
	blocks_character[1] = '^';
	blocks[2] = "ʯͷ";
	blocks_id["ʯͷ"] = 2;
	blocks_character[2] = '#';
	blocks[3] = "ԭľ";
	blocks_id["ԭľ"] = 3;
	blocks_character[3] = '$';
	blocks[4] = "��Ҷ";
	blocks_id["��Ҷ"] = 4;
	blocks_character[4] = '%';
	blocks[5] = "����";
	blocks_id["����"] = 5;
	blocks_character[5] = '*';
	blocks[0] = "NULL";
	blocks_id["NULL"] = 0;
	blocks_character[0] = ' ';
	key[1] = 'w';
	key_id['w'] = 1;
	key_use[1] = "��";
	key[2] = 's';
	key_id['s'] = 2;
	key_use[2] = "��";
	key[3] = 'a';
	key_id['a'] = 3;
	key_use[3] = "��";
	key[4] = 'd';
	key_id['d'] = 4;
	key_use[4] = "��";
	key[5] = 'b';
	key_id['b'] = 5;
	key_use[5] = "����";
	key[6] = 'j';
	key_id['j'] = 6;
	key_use[6] = "�ݻ�";
	key[7] = 'k';
	key_id['k'] = 7;
	key_use[7] = "����";
	key[8] = ' ';
	key_id[' '] = 8;
	key_use[8] = "ȷ��";
	key[9] = '~';
	key_id['~'] = 9;
	key_use[9] = "�л�ָ��";
	key[10] = '?';
	key_id['?'] = 10;
	key_use[10] = "�޸�";
	key[11] = 'p';
	key_id['p'] = 11;
	key_use[11] = "�İ���(�ݻ�)";
	key[12] = '+';
	key_id['+'] = 12;
	key_use[12] = "����+�浵";
	block_colors[0] = 255;
	block_colors[1] = 34;
	block_colors[2] = 136;
	block_colors[3] = 102;
	block_colors[4] = 170;
	block_colors[5] = 224;
}
void build_world() { //��������
	for (int i = 0; i < MAXY; i++) { // ���ɵ���������
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
	for (int i = 0; i < MAXY; i++) { // �Ƴ���������
		for (int j = 0; j < MAXX; j++) {
			if (world[i][j] == 5) {
				if (world[i + 1][j] != 1) {
					world[i][j] = 0;
				}
			}
		}
	}
	for (int i = 3; i < MAXY; i++) { // ������չ������
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
				j += 3; // ��ֹ���������������ֲ��ƻ�����
			}
		}
	}
	buffer();
}
void Set_Born_Point() { //����������
	cout << "����*��Ļ����x��0~469��:";
	cin >> screen_left;
	screen_right = screen_left + 31;
	while (screen_left <= -1 || screen_right >= 501) {
		cout << "���������������x���꣨0~469��:";
		cin >> screen_left;
		screen_right = screen_left + 31;
	}
	cout << "����*����߶�(145~5):";
	cin >> ground_att;
	while (ground_att < 5 || ground_att > 145) {
		cout << "����*����߶�(145~5):";
		cin >> ground_att;
	}
	ground_att = 150 - ground_att;
	player_x = screen_left + 16;
	player_y = ground_att - 1;
	screen_up = player_y - 4;
	screen_down = screen_up + 9;
}
void load() {  //����
	string name;
	cout << "��������Ĵ浵���ƣ������.json����\n";
	cin >> name;
	name += ".json";
	FILE* fp = fopen(name.c_str(), "rb");
	if (fp == NULL) {
		cout << "�޷����ļ����ж�ȡ" << endl;
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
		key_11();//���ֺ����������Ϸǰ��һ�ΰ���
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
