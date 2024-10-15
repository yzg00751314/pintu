#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>// 随机数
#include <time.h> //随机数需要调用时间
#include <stdbool.h>
#include <conio.h>//使用_getch()


int puzzle[5][5] = { 0 };
int m, n;
int count = 0;
int level = 0;
int  x = 0, y = 0;
int copy[5][5];
int flag = 0;
int show0 = 0;

void gotoXY(int x, int y)
{
	COORD c;
	c.X = x - 1;
	c.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void setPrintColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void setXY(int x, int y) {
	COORD pos;
	HANDLE obj;
	pos.X = x;
	pos.Y = y;
	obj = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(obj, pos);
}

void clear(int x, int y, int w, int h)
{
	for (int i = 0; i < h; i++) {
		setXY(x, y + i);
		for (int j = 0; j < w; j++) putchar(' ');
	}
}


void printBox(int x, int y, int w, int h)
{
	setPrintColor(0x0a);
	//竖线
	int X = x;
	for (int j = 0; j < n + 1; j++) {
		for (int i = 0; i < h * m + 1; i++) {
			setXY(x, y + i);
			putchar('*');
		}
		x += w;
	}
	//横线
	x = X;
	setXY(x, y + h - 1);
	for (int j = 0; j < m + 1; j++) {
		for (int i = 0; i < w * n; i++) {
			setXY(x + i, y);
			putchar('*');
		}
		y += h;
	}
	//光标挪到其它位置 避免后面的输出覆盖这里的打印
	setXY(x + w, y + h + 1);
	setPrintColor(0x07);
}

void puzzle_show(int x1, int y1, int w, int h) {
	int X = x1;
	int Y = y1;
	setXY(x1, y1);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			setXY(x1, y1);
			if (!show0) {
				if (i == x && j == y) {
					setPrintColor(0x09);
					printf("%d", puzzle[i][j]);
				}
				else {
					if (puzzle[i][j] == 0) {
						printf(" ");
					}
					else {
						setPrintColor(0x07);
						printf("%d", puzzle[i][j]);
					}
				}
			}
			else {
				if (i == x && j == y) {
					setPrintColor(0x09);
					printf("%d", puzzle[i][j]);
				}
				else {
					setPrintColor(0x07);
					printf("%d", puzzle[i][j]);
				}
			}

			x1 += w;
		}
		x1 = X;
		y1 += h;
	}
	setPrintColor(0x07);
}

void shuffle();
void shuffle() {


	char arr[25] = { 0 };
	for (int i = 0; i < n * m; i++) {
		arr[i] = i + 1;
	}//初始化arr一维
	for (int i = n * m - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}//洗牌算法，把倒数第一个数和前面任何一个数随机调换，让后再把倒数第二个数和前面任何一个数调换，以此类推，当然也可能随机到不换位置，这是个伪随机
	int reverse = 0;
	//检查有多少个倒序
	bool isSolvable = false;
	for (int i = 0; i <= m * n - 2; i++) {
		for (int j = i + 1; j <= m * n - 1; j++) {
			if (arr[i] > arr[j] && arr[i] != m * n) {
				//printf("%d %d\n", arr[i], arr[j]);
				reverse++;
			}

		}
	}

	int spaceIndex = 0;//定位空格的下标
	for (int i = 0; i < n * m - 1; i++) {
		if (arr[i] == n * m) {
			spaceIndex = i;
		}
	}
	//判断在哪一行(0,1)
	int rowIndex = 0;
	for (int i = 0; i < m; i++) {
		if (i * n <= spaceIndex && spaceIndex <= (i + 1) * n - 1) {
			rowIndex = i + 1;//后续不使用数组的下标，所以传实际行数
			break;
		}

	}


	if (m % 2 != 0 && reverse % 2 == 0) {
		//奇数行，逆序数为偶数则可解
		isSolvable = true;
	}
	else if (m % 2 == 0 && (reverse + (m - rowIndex)) % 2 == 0) {
		//偶数行，逆序数+行数是偶数则可解
		isSolvable = true;
	}




	int num = 0;
	if (isSolvable) {//赋值表格
		//printf("%d\n", reverse + level - rowIndex);
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (arr[num] != n * m) {
					puzzle[i][j] = arr[num];
					num++;
				}
				else {
					puzzle[i][j] = 0;
					num++;
				}

			}
		}
	}
	else {
		shuffle();
	}
}


void menuview();
int choose_level_view();
void gameview();
void init();
void gameview_show();
void copy_init();
void choose(char choose);
void copy_puzzle();
int move();
int iswin();
void winview();
void member();

void member() {
	gotoXY(50, 3);
	printf("南极科考站\n");
	gotoXY(50, 5);
	printf("季夏（组长）\n");
	gotoXY(50, 7);
	printf("空白（信息官）\n");
	gotoXY(50, 9);
	printf("夏猫（信息官）\n");
	gotoXY(50, 11);
	printf("陈宗（副组长）\n");
	gotoXY(50, 13);
	printf("慢愿（监督官）\n");
	gotoXY(50, 15);
	printf("。（技术官）\n");
	gotoXY(50, 17);
	printf("小明（技术官）\n");
	gotoXY(50, 19);
	printf("圣魔（技术官）\n");
	gotoXY(50, 21);
	printf("路过（产品经理）\n");
	gotoXY(50, 23);
	printf("墨知叶灵（产品经理）\n");
	gotoXY(80, 21);
	printf("特别鸣谢\n");
	gotoXY(80, 23);
	printf("偏偏学长\n");
	gotoXY(100, 26);
	system("pause");
	flag = 0;
	return;
}


void menuview()
{
	int userChoose = 0;
	int shezhi = 0;
	while (1) {
		system("cls");
		// ----------------- 打印界面 -----------------
		gotoXY(60, 3);
		printf("拼图");
		if (userChoose == 0) setPrintColor(0x6f);
		gotoXY(64, 6);
		printf("开始游戏 \n");
		if (userChoose == 0) setPrintColor(0x0f);
		if (userChoose == 1) setPrintColor(0x6f);
		gotoXY(65, 9);
		printf("设置 \n");
		if (userChoose == 1) setPrintColor(0x0f);
		if (userChoose == 2) setPrintColor(0x6f);
		gotoXY(64, 12);
		printf("退出游戏");
		if (userChoose == 2) setPrintColor(0x0f);
		// ---------------- 接收用户输入 --------------
		char input = _getch();
		// -------------判断是方向上下还是回车------------
		switch (input) {
		case 'w':
			userChoose -= 1;
			if (userChoose == -1) userChoose = 2;
			break;
		case 's':
			userChoose = (userChoose + 1) % 3;
			break;
		case '\r':
			clear(3, 2, 80, 20);
			switch (userChoose) {
			case 0:
				flag = 1;
				return;
				break;
			case 1:
				system("cls");
				gotoXY(50, 11);
				printf("是否显示0（输入1显示 输入2不显示）");
				gotoXY(50, 13);
				printf("输入0查看开发人员");
				scanf("%d", &shezhi);
				if (shezhi == 0) {
					flag = 4;
					return;
				}
				else if (shezhi == 1) {
					show0 = 1;
				}
				else if (shezhi == 2) {
					show0 = 0;
				}
				break;
			case 2:
				exit(0);
				return;
				break;
			}
			clear(3, 2, 36, 20);
			break;
		}
	}
}




int choose_level_view() {
	int choice;
	while (1)
	{
		setXY(25, 1);
		printf("4.返回");
		setXY(50, 5);
		printf("1.入门（3*3)");
		setXY(50, 10);
		printf("2.初级（4*4)");
		setXY(50, 15);
		printf("3.困难（5*5)");
		setXY(70, 20);
		printf("请选择难度:");


		scanf("%d", &choice);
		switch (choice) {

		case 1:
			system("cls");
			m = n = 3;
			level = 3;
			flag = 2;
			return 1;
		case 2:
			system("cls");
			m = n = 4;
			level = 4;
			flag = 2;
			return 2;
		case 3:
			system("cls");
			m = n = 5;
			level = 5;
			flag = 2;
			return 3;
		case 4:
			system("cls");
			flag = 0;
			return 4;
		default:
			setXY(70, 25);
			printf("请输入正确的难度序号\n");
		}
	}
}




void gameview() {
	init();
	copy_puzzle();
	while (1) {
		clear(49, 2, 30, 25);
		clear(19, 20, 10, 5);
		gameview_show();
		char userchoose;
		userchoose = _getch();
		choose(userchoose);
		if (userchoose == '1') { // 输入1返回选择难度页面
			flag = 1;
			return;
		}
		if (userchoose == '2') { // 输入2返回总菜单
			flag = 0;
			return;
		}
		if (userchoose == '3') {
			copy_init();
		}
		if (userchoose == '4') {
			init();
			copy_puzzle();
		}
		if (userchoose == '\r') {
			if (move()) {
				setXY(20, 20);
				printf("移动成功");
				Sleep(300);
			}
			else {
				setXY(20, 20);
				printf("周围无空位");
				setXY(20, 23);
				printf("移动失败");
				Sleep(300);
			}
		}
		if (iswin()) {
			return;
		}
	}
}

void init() {
	count = 0;
	shuffle();
}


void gameview_show() {
	setXY(20, 1);
	printf("1返回");
	setXY(95, 1);
	printf("2主菜单");
	setXY(25, 5);
	printf("3从头开始");
	setXY(25, 10);
	printf("4新游戏");
	setXY(90, 10);
	printf("已走步数：%d", count);

	if (level == 3) {
		printBox(46, 2, 8, 6);
		puzzle_show(50, 5, 8, 6);
		setXY(90, 20);
		printf("请输入你的选择：");
	}
	else if (level == 4) {
		printBox(46, 2, 7, 5);
		puzzle_show(50, 4, 7, 5);
		setXY(90, 20);
		printf("请输入你的选择：");
	}
	else if (level == 5) {
		printBox(47, 4, 6, 4);
		puzzle_show(50, 5, 6, 4);
		setXY(90, 20);
		printf("请输入你的选择：");
	}
	setXY(0, 0);
	puts(" ");
	setXY(110, 20);
}


void copy_init() {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			puzzle[i][j] = copy[i][j];
		}
	}
}


void choose(char userchoose) {
	// 根据用户输入调整光标位置
	switch (userchoose) {
	case 'w': // 上移
		if (x > 0) {
			x--; // 向上移动光标
		}
		else {
			x = m - 1; // 超出上边界，回到底部
		}
		break;
	case 's': // 下移
		if (x < m - 1) {
			x++; // 向下移动光标
		}
		else {
			x = 0; // 超出下边界，回到顶部
		}
		break;
	case 'a': // 左移
		if (y > 0) {
			y--; // 向左移动光标
		}
		else {
			y = n - 1; // 超出左边界，回到最右边
		}
		break;
	case 'd': // 右移
		if (y < n - 1) {
			y++; // 向右移动光标
		}
		else {
			y = 0; // 超出右边界，回到最左边
		}
		break;
	case '\r': // 按下回车键，确认选择

		return;
	default:
		// 不做任何事情，可以在图形界面中显示提示
		break;
	}
	// 刷新游戏界面，更新光标位置

}


void copy_puzzle() {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			copy[i][j] = puzzle[i][j];
		}
	}
}

int move()
{
	if (x >= 0 && (x + 1) < m && y >= 0 && y < n && puzzle[x + 1][y] == 0)
	{
		puzzle[x + 1][y] = puzzle[x][y];
		puzzle[x][y] = 0;
		count++;
		return 1;
	}//下边有空格
	else if (x >= 0 && x < m && y >= 0 && y + 1 < n && puzzle[x][y + 1] == 0)
	{
		puzzle[x][y + 1] = puzzle[x][y];
		puzzle[x][y] = 0;
		count++;
		return 1;
	}//右边有空格

	else if ((x - 1) >= 0 && x < m && y >= 0 && y < n && puzzle[x - 1][y] == 0)
	{
		puzzle[x - 1][y] = puzzle[x][y];
		puzzle[x][y] = 0;
		count++;
		return 1;
	}//上边有空格
	else if (x >= 0 && x < m && (y - 1) >= 0 && y < n && puzzle[x][y - 1] == 0)
	{
		puzzle[x][y - 1] = puzzle[x][y];
		puzzle[x][y] = 0;
		count++;
		return 1;
	}//左边有空格
	else return 0;//无空格

}


int iswin() {
	int i = 1, count = 0;
	if (puzzle[m - 1][n - 1] == 0) {
		for (int j = 0; j < m; j++) {
			for (int s = 0; s < n; s++) {
				if (puzzle[j][s] == i) {
					i++;
					if (i == (m * n) - 1) {
						flag = 3;
						return 1;
					}
				}
			}
		}
	}
	return 0;
}


void winview() {
	// ----------------- 打印界面 -----------------
	gotoXY(43, 7);
	printf("【 游  戏  胜  利 , 共 用 了 %d 步 】", count);
	gotoXY(3, 3);
	printf("(输入数字以选择按钮)");
	gotoXY(56, 14);
	printf("返回主菜单0");
	gotoXY(43, 14);
	printf("重选难度1");
	gotoXY(71, 14);
	printf("重新开始2");
	gotoXY(85, 14);

	//调用函数
	int choose;
	scanf("%d", &choose);
	switch (choose) {
	case 0:
		flag = 0;
		return;
	case 1:
		flag = 1;
		return;
	case 2:
		flag = 2;
		init();
		copy_puzzle();
		return;
	}
	return;
}



void controller() {
	while (1) {
		system("cls");
		switch (flag) {
		case 0:
			menuview();
			break;
		case 1:
			choose_level_view();
			break;
		case 2:
			gameview();
			break;
		case 3:
			winview();
			break;
		case 4:
			member();
			break;
		}
	}
}








int main()
{
	srand(time(NULL));
	controller();
	return 0;
}