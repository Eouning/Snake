#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <graphics.h>
#include <easyx.h>
#include <string.h>
#include <conio.h>
#include "Snake.h"//Ϊ�˴���������ԣ�����ΪSnake��ͷ�ļ��洢Snake����Ĵ��뼴��صĲ�������
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

//��ʾ��ͼ��Χ����25*25��ÿ��25*25���ء�
#define X 25
#define Y 25

void Show(Snake* Head, int Meat[2]);//���ߺ����ӡ����Ļ��
void Movement(Snake** pHead);//�����ƶ�
int makeMeat(int count, int Meat[2], Snake* Head);//������
int die(Snake* Head);//���������ж�
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y); //ͼƬ͸��������,xΪҪ����ͼƬ��X���꣬yΪY����
void BGM2();//��Ϸ��������
void BGM4();//������Ч

int Play() {
	//���ɱ���
	initgraph(X * 25, Y * 25);

	HWND hWnd = GetHWnd();
	SetWindowText(hWnd, "������һ����ͨ�Ĵ������� OwO");

	//���ű�������
	BGM2();

	//���ɳ�ʼ����
	Snake* Head = (Snake*)malloc(sizeof(Snake));
	Head->Before = NULL;
	Head->Next = NULL;
	Snake_append(&Head, 10, 10, ��);
	Snake_append(&Head, 10, 9, ��);
	Snake_append(&Head, 10, 8, ��);
	int points = 0;

	int Meat[2];
	int count = 0;

	while (die(Head) == 0) {

		count = makeMeat(count, Meat, Head);

		//��ͷ����ĸı�
		if (GetAsyncKeyState(65) & 0x8000 && Head->direction != ��) {
			Head->direction = ��;
		}
		if (GetAsyncKeyState(68) & 0x8000 && Head->direction != ��) {
			Head->direction = ��;
		}
		if (GetAsyncKeyState(87) & 0x8000 && Head->direction != ��) {
			Head->direction = ��;
		}
		if (GetAsyncKeyState(83) & 0x8000 && Head->direction != ��) {
			Head->direction = ��;
		}

		Movement(&Head);

		//����Ե����ˣ��߾�����
		if (Head->x == Meat[0] && Head->y == Meat[1]) {
			Meat[0] = -1;
			Snake_append(&Head, Head->Before->x, Head->Before->y, Head->Before->direction);
			points++;
			BGM4();
		}

		Show(Head,Meat);

		count++;

		//ˢ��Ƶ�ʣ�100/1000��һ��
		Sleep(100);

	}

	Snake_damage(Head);
	return points;

}

//�ƶ���������ͷָ���Ϊԭ����β����ַ���ٽ����ڵ�ͷָ������Ӧ�ṹ���ڲ��������ƶ�
void Movement(Snake** pHead) {
	*pHead = (*pHead)->Before;
	switch ((*pHead)->Next->direction)
	{
	case ��:
		(*pHead)->y = (*pHead)->Next->y - 1;
		(*pHead)->x = (*pHead)->Next->x;
		(*pHead)->direction = (*pHead)->Next->direction;
		break;
	case ��:
		(*pHead)->y = (*pHead)->Next->y + 1;
		(*pHead)->x = (*pHead)->Next->x;
		(*pHead)->direction = (*pHead)->Next->direction;
		break;
	case ��:
		(*pHead)->x = (*pHead)->Next->x - 1;
		(*pHead)->y = (*pHead)->Next->y;
		(*pHead)->direction = (*pHead)->Next->direction;
		break;
	case ��:
		(*pHead)->x = (*pHead)->Next->x + 1;
		(*pHead)->y = (*pHead)->Next->y;
		(*pHead)->direction = (*pHead)->Next->direction;
		break;
	default:
		break;
	}
}

void Show(Snake* Head, int Meat[2]) {
	IMAGE pc;

	IMAGE back;
	loadimage(&back, "19.png", 625, 625);
	putimage(0, 0, &back);

	//��
	loadimage(&pc, "18.png", 25, 25);
	drawAlpha(&pc, Meat[0] * 25, Meat[1] * 25);

	//ͷ
	switch (Head->direction)
	{
	case ��:
		loadimage(&pc, "00.png", 25, 25);
		drawAlpha(&pc, (Head->x) * 25, (Head->y) * 25);
		break;
	case ��:
		loadimage(&pc, "01.png", 25, 25);
		drawAlpha(&pc, (Head->x) * 25, (Head->y) * 25);
		break;
	case ��:
		loadimage(&pc, "02.png", 25, 25);
		drawAlpha(&pc, (Head->x) * 25, (Head->y) * 25);
		break;
	case ��:
		loadimage(&pc, "03.png", 25, 25);
		drawAlpha(&pc, (Head->x) * 25, (Head->y) * 25);
		break;
	default:
		break;
	}
	Snake* p = Head->Next;

	//��
	while (p->Next != Head) {
		if (p->Before->direction == p->Next->direction && p->direction==p->Before->direction|| p->Next->direction == p->direction) {
			switch (p->direction)
			{
			case ��:
				loadimage(&pc, "04.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
				break;
			case ��:
				loadimage(&pc, "05.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
				break;
			case ��:
				loadimage(&pc, "04.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
				break;
			case ��:
				loadimage(&pc, "05.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
				break;
			default:
				break;
			}
		}
		else {
			if (p->Before->direction == �� && p->Next->direction == �� ) {
				loadimage(&pc, "10.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == �� && p->Next->direction == ��) {
				loadimage(&pc, "11.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == �� && p->Next->direction == ��) {
				loadimage(&pc, "12.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == �� && p->Next->direction == ��) {
				loadimage(&pc, "13.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == �� && p->Next->direction == ��) {
				loadimage(&pc, "14.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == �� && p->Next->direction == ��) {
				loadimage(&pc, "15.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == �� && p->Next->direction == ��) {
				loadimage(&pc, "16.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == �� && p->Next->direction == ��) {
				loadimage(&pc, "17.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == �� && p->Next->direction == �� && p->direction==��) {
				loadimage(&pc, "14.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == �� && p->Next->direction == �� && p->direction == ��) {
				loadimage(&pc, "15.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == �� && p->Next->direction == �� && p->direction == ��) {
				loadimage(&pc, "13.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == �� && p->Next->direction == �� && p->direction == ��) {
				loadimage(&pc, "11.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == �� && p->Next->direction == �� && p->direction == ��) {
				loadimage(&pc, "10.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == �� && p->Next->direction == �� && p->direction == ��) {
				loadimage(&pc, "11.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == �� && p->Next->direction == �� && p->direction == ��) {
				loadimage(&pc, "12.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == �� && p->Next->direction == �� && p->direction == ��) {
				loadimage(&pc, "13.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == �� && p->Next->direction == �� && p->direction == ��) {
				loadimage(&pc, "12.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == �� && p->Next->direction == �� && p->direction == ��) {
				loadimage(&pc, "13.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == �� && p->Next->direction == �� && p->direction == ��) {
				loadimage(&pc, "15.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == �� && p->Next->direction == �� && p->direction == ��) {
				loadimage(&pc, "17.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == �� && p->Next->direction == �� && p->direction == ��) {
				loadimage(&pc, "10.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == �� && p->Next->direction == �� && p->direction == ��) {
				loadimage(&pc, "12.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == �� && p->Next->direction == �� && p->direction == ��) {
				loadimage(&pc, "17.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == �� && p->Next->direction == �� && p->direction == ��) {
				loadimage(&pc, "16.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
		}
		p = p->Next;
	}

	//β��
	switch (p->direction)
	{
	case ��:
		loadimage(&pc, "06.png", 25, 25);
		drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
		break;
	case ��:
		loadimage(&pc, "07.png", 25, 25);
		drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
		break;
	case ��:
		loadimage(&pc, "08.png", 25, 25);
		drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
		break;
	case ��:
		loadimage(&pc, "09.png", 25, 25);
		drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
		break;
	default:
		break;
	}
}

int die(Snake* Head) {
	//�����ҧ���Լ�������
	if (Head->x < 1 || Head->x >X - 2 || Head->y < 1 || Head->y >Y - 2) {
		return 1;
	}
	Snake* p = Head;
	while (p->Next != Head) {
		if (p->Next->x == Head->x && p->Next->y == Head->y) {
			return 1;
		}
		p = p->Next;
	}
	return 0;
}

int makeMeat(int count, int Meat[2], Snake* Head) {
	//ÿ40��ˢ�£�Ҳ����0.1*40�������һ���⣻�����ⱻ���������������
	if (count % 40 == 0 or Meat[0] == -1) {
		if (Meat[0] == -1) {
			count = 1;//�����ˢ�¼��ʱ��
		}

	Rand:
		srand((unsigned)time(NULL));
		Meat[0] = rand() % (X-2)+1;
		Meat[1] = rand() % (Y-2)+1;

		Snake* p = Head;
		while (p->Next !=Head) {
			//��ֹ��������������
			if (p->x == Meat[0] && p->y == Meat[1] || p->Next->x == Meat[0] && p->Next->y == Meat[1])
			{
				goto Rand;
			}
			p = p->Next;
		}
		if (p->x == Meat[0] && p->y == Meat[1] || p->Next->x == Meat[0] && p->Next->y == Meat[1])
		{
			goto Rand;
		}

	}
	return count;
}

void drawAlpha(IMAGE* picture, int  picture_x, int picture_y) //xΪ����ͼƬ��X���꣬yΪY����
{

	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}

void BGM2() {
	mciSendString("close 02", NULL, 0, NULL);
	//�����֣���������
	mciSendString("open ./02gameTime.wav alias 02 type MPEGVideo", 0, 0, 0);
	mciSendString("play 02 repeat", 0, 0, 0);
}

void BGM4() {
	mciSendString("close 04", NULL, 0, NULL);
	//�����֣���������
	mciSendString("open ./04eat.wav alias 04", 0, 0, 0);
	mciSendString("play 04", 0, 0, 0);
}