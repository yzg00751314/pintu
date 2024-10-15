#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>// �����
#include <time.h> //�������Ҫ����ʱ��
#include <stdbool.h>
#include <conio.h>//ʹ��_getch()


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
	//����
	int X = x;
	for (int j = 0; j < n + 1; j++) {
		for (int i = 0; i < h * m + 1; i++) {
			setXY(x, y + i);
			putchar('*');
		}
		x += w;
	}
	//����
	x = X;
	setXY(x, y + h - 1);
	for (int j = 0; j < m + 1; j++) {
		for (int i = 0; i < w * n; i++) {
			setXY(x + i, y);
			putchar('*');
		}
		y += h;
	}
	//���Ų������λ�� �������������������Ĵ�ӡ
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
	}//��ʼ��arrһά
	for (int i = n * m - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}//ϴ���㷨���ѵ�����һ������ǰ���κ�һ��������������ú��ٰѵ����ڶ�������ǰ���κ�һ�����������Դ����ƣ���ȻҲ�������������λ�ã����Ǹ�α���
	int reverse = 0;
	//����ж��ٸ�����
	bool isSolvable = false;
	for (int i = 0; i <= m * n - 2; i++) {
		for (int j = i + 1; j <= m * n - 1; j++) {
			if (arr[i] > arr[j] && arr[i] != m * n) {
				//printf("%d %d\n", arr[i], arr[j]);
				reverse++;
			}

		}
	}

	int spaceIndex = 0;//��λ�ո���±�
	for (int i = 0; i < n * m - 1; i++) {
		if (arr[i] == n * m) {
			spaceIndex = i;
		}
	}
	//�ж�����һ��(0,1)
	int rowIndex = 0;
	for (int i = 0; i < m; i++) {
		if (i * n <= spaceIndex && spaceIndex <= (i + 1) * n - 1) {
			rowIndex = i + 1;//������ʹ��������±꣬���Դ�ʵ������
			break;
		}

	}


	if (m % 2 != 0 && reverse % 2 == 0) {
		//�����У�������Ϊż����ɽ�
		isSolvable = true;
	}
	else if (m % 2 == 0 && (reverse + (m - rowIndex)) % 2 == 0) {
		//ż���У�������+������ż����ɽ�
		isSolvable = true;
	}




	int num = 0;
	if (isSolvable) {//��ֵ���
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
	printf("�ϼ��ƿ�վ\n");
	gotoXY(50, 5);
	printf("���ģ��鳤��\n");
	gotoXY(50, 7);
	printf("�հף���Ϣ�٣�\n");
	gotoXY(50, 9);
	printf("��è����Ϣ�٣�\n");
	gotoXY(50, 11);
	printf("���ڣ����鳤��\n");
	gotoXY(50, 13);
	printf("��Ը���ල�٣�\n");
	gotoXY(50, 15);
	printf("���������٣�\n");
	gotoXY(50, 17);
	printf("С���������٣�\n");
	gotoXY(50, 19);
	printf("ʥħ�������٣�\n");
	gotoXY(50, 21);
	printf("·������Ʒ����\n");
	gotoXY(50, 23);
	printf("ī֪Ҷ�飨��Ʒ����\n");
	gotoXY(80, 21);
	printf("�ر���л\n");
	gotoXY(80, 23);
	printf("ƫƫѧ��\n");
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
		// ----------------- ��ӡ���� -----------------
		gotoXY(60, 3);
		printf("ƴͼ");
		if (userChoose == 0) setPrintColor(0x6f);
		gotoXY(64, 6);
		printf("��ʼ��Ϸ \n");
		if (userChoose == 0) setPrintColor(0x0f);
		if (userChoose == 1) setPrintColor(0x6f);
		gotoXY(65, 9);
		printf("���� \n");
		if (userChoose == 1) setPrintColor(0x0f);
		if (userChoose == 2) setPrintColor(0x6f);
		gotoXY(64, 12);
		printf("�˳���Ϸ");
		if (userChoose == 2) setPrintColor(0x0f);
		// ---------------- �����û����� --------------
		char input = _getch();
		// -------------�ж��Ƿ������»��ǻس�------------
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
				printf("�Ƿ���ʾ0������1��ʾ ����2����ʾ��");
				gotoXY(50, 13);
				printf("����0�鿴������Ա");
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
		printf("4.����");
		setXY(50, 5);
		printf("1.���ţ�3*3)");
		setXY(50, 10);
		printf("2.������4*4)");
		setXY(50, 15);
		printf("3.���ѣ�5*5)");
		setXY(70, 20);
		printf("��ѡ���Ѷ�:");


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
			printf("��������ȷ���Ѷ����\n");
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
		if (userchoose == '1') { // ����1����ѡ���Ѷ�ҳ��
			flag = 1;
			return;
		}
		if (userchoose == '2') { // ����2�����ܲ˵�
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
				printf("�ƶ��ɹ�");
				Sleep(300);
			}
			else {
				setXY(20, 20);
				printf("��Χ�޿�λ");
				setXY(20, 23);
				printf("�ƶ�ʧ��");
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
	printf("1����");
	setXY(95, 1);
	printf("2���˵�");
	setXY(25, 5);
	printf("3��ͷ��ʼ");
	setXY(25, 10);
	printf("4����Ϸ");
	setXY(90, 10);
	printf("���߲�����%d", count);

	if (level == 3) {
		printBox(46, 2, 8, 6);
		puzzle_show(50, 5, 8, 6);
		setXY(90, 20);
		printf("���������ѡ��");
	}
	else if (level == 4) {
		printBox(46, 2, 7, 5);
		puzzle_show(50, 4, 7, 5);
		setXY(90, 20);
		printf("���������ѡ��");
	}
	else if (level == 5) {
		printBox(47, 4, 6, 4);
		puzzle_show(50, 5, 6, 4);
		setXY(90, 20);
		printf("���������ѡ��");
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
	// �����û�����������λ��
	switch (userchoose) {
	case 'w': // ����
		if (x > 0) {
			x--; // �����ƶ����
		}
		else {
			x = m - 1; // �����ϱ߽磬�ص��ײ�
		}
		break;
	case 's': // ����
		if (x < m - 1) {
			x++; // �����ƶ����
		}
		else {
			x = 0; // �����±߽磬�ص�����
		}
		break;
	case 'a': // ����
		if (y > 0) {
			y--; // �����ƶ����
		}
		else {
			y = n - 1; // ������߽磬�ص����ұ�
		}
		break;
	case 'd': // ����
		if (y < n - 1) {
			y++; // �����ƶ����
		}
		else {
			y = 0; // �����ұ߽磬�ص������
		}
		break;
	case '\r': // ���»س�����ȷ��ѡ��

		return;
	default:
		// �����κ����飬������ͼ�ν�������ʾ��ʾ
		break;
	}
	// ˢ����Ϸ���棬���¹��λ��

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
	}//�±��пո�
	else if (x >= 0 && x < m && y >= 0 && y + 1 < n && puzzle[x][y + 1] == 0)
	{
		puzzle[x][y + 1] = puzzle[x][y];
		puzzle[x][y] = 0;
		count++;
		return 1;
	}//�ұ��пո�

	else if ((x - 1) >= 0 && x < m && y >= 0 && y < n && puzzle[x - 1][y] == 0)
	{
		puzzle[x - 1][y] = puzzle[x][y];
		puzzle[x][y] = 0;
		count++;
		return 1;
	}//�ϱ��пո�
	else if (x >= 0 && x < m && (y - 1) >= 0 && y < n && puzzle[x][y - 1] == 0)
	{
		puzzle[x][y - 1] = puzzle[x][y];
		puzzle[x][y] = 0;
		count++;
		return 1;
	}//����пո�
	else return 0;//�޿ո�

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
	// ----------------- ��ӡ���� -----------------
	gotoXY(43, 7);
	printf("�� ��  Ϸ  ʤ  �� , �� �� �� %d �� ��", count);
	gotoXY(3, 3);
	printf("(����������ѡ��ť)");
	gotoXY(56, 14);
	printf("�������˵�0");
	gotoXY(43, 14);
	printf("��ѡ�Ѷ�1");
	gotoXY(71, 14);
	printf("���¿�ʼ2");
	gotoXY(85, 14);

	//���ú���
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