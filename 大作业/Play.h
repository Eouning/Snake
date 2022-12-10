#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <graphics.h>
#include <easyx.h>
#include <string.h>
#include <conio.h>
#include "Snake.h"//为了代码的美观性，用名为Snake的头文件存储Snake链表的代码即相关的操作函数
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

//表示地图范围，共25*25格，每格25*25像素。
#define X 25
#define Y 25

void Show(Snake* Head, int Meat[2]);//将蛇和肉打印在屏幕上
void Movement(Snake** pHead);//让蛇移动
int makeMeat(int count, int Meat[2], Snake* Head);//创造肉
int die(Snake* Head);//对死亡的判定
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y); //图片透明背景化,x为要载入图片的X坐标，y为Y坐标
void BGM2();//游戏背景音乐
void BGM4();//吃肉音效

int Play() {
	//生成背景
	initgraph(X * 25, Y * 25);

	HWND hWnd = GetHWnd();
	SetWindowText(hWnd, "这是另一个普通的窗口名称 OwO");

	//播放背景音乐
	BGM2();

	//生成初始的蛇
	Snake* Head = (Snake*)malloc(sizeof(Snake));
	Head->Before = NULL;
	Head->Next = NULL;
	Snake_append(&Head, 10, 10, 下);
	Snake_append(&Head, 10, 9, 下);
	Snake_append(&Head, 10, 8, 下);
	int points = 0;

	int Meat[2];
	int count = 0;

	while (die(Head) == 0) {

		count = makeMeat(count, Meat, Head);

		//蛇头朝向的改变
		if (GetAsyncKeyState(65) & 0x8000 && Head->direction != 右) {
			Head->direction = 左;
		}
		if (GetAsyncKeyState(68) & 0x8000 && Head->direction != 左) {
			Head->direction = 右;
		}
		if (GetAsyncKeyState(87) & 0x8000 && Head->direction != 下) {
			Head->direction = 上;
		}
		if (GetAsyncKeyState(83) & 0x8000 && Head->direction != 上) {
			Head->direction = 下;
		}

		Movement(&Head);

		//如果吃到肉了，蛇就增长
		if (Head->x == Meat[0] && Head->y == Meat[1]) {
			Meat[0] = -1;
			Snake_append(&Head, Head->Before->x, Head->Before->y, Head->Before->direction);
			points++;
			BGM4();
		}

		Show(Head,Meat);

		count++;

		//刷新频率，100/1000秒一次
		Sleep(100);

	}

	Snake_damage(Head);
	return points;

}

//移动函数，把头指针变为原来的尾部地址，再将现在的头指针所对应结构体内参数进行移动
void Movement(Snake** pHead) {
	*pHead = (*pHead)->Before;
	switch ((*pHead)->Next->direction)
	{
	case 上:
		(*pHead)->y = (*pHead)->Next->y - 1;
		(*pHead)->x = (*pHead)->Next->x;
		(*pHead)->direction = (*pHead)->Next->direction;
		break;
	case 下:
		(*pHead)->y = (*pHead)->Next->y + 1;
		(*pHead)->x = (*pHead)->Next->x;
		(*pHead)->direction = (*pHead)->Next->direction;
		break;
	case 左:
		(*pHead)->x = (*pHead)->Next->x - 1;
		(*pHead)->y = (*pHead)->Next->y;
		(*pHead)->direction = (*pHead)->Next->direction;
		break;
	case 右:
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

	//肉
	loadimage(&pc, "18.png", 25, 25);
	drawAlpha(&pc, Meat[0] * 25, Meat[1] * 25);

	//头
	switch (Head->direction)
	{
	case 上:
		loadimage(&pc, "00.png", 25, 25);
		drawAlpha(&pc, (Head->x) * 25, (Head->y) * 25);
		break;
	case 右:
		loadimage(&pc, "01.png", 25, 25);
		drawAlpha(&pc, (Head->x) * 25, (Head->y) * 25);
		break;
	case 下:
		loadimage(&pc, "02.png", 25, 25);
		drawAlpha(&pc, (Head->x) * 25, (Head->y) * 25);
		break;
	case 左:
		loadimage(&pc, "03.png", 25, 25);
		drawAlpha(&pc, (Head->x) * 25, (Head->y) * 25);
		break;
	default:
		break;
	}
	Snake* p = Head->Next;

	//身
	while (p->Next != Head) {
		if (p->Before->direction == p->Next->direction && p->direction==p->Before->direction|| p->Next->direction == p->direction) {
			switch (p->direction)
			{
			case 上:
				loadimage(&pc, "04.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
				break;
			case 右:
				loadimage(&pc, "05.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
				break;
			case 下:
				loadimage(&pc, "04.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
				break;
			case 左:
				loadimage(&pc, "05.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
				break;
			default:
				break;
			}
		}
		else {
			if (p->Before->direction == 上 && p->Next->direction == 右 ) {
				loadimage(&pc, "10.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == 上 && p->Next->direction == 左) {
				loadimage(&pc, "11.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == 下 && p->Next->direction == 右) {
				loadimage(&pc, "12.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == 下 && p->Next->direction == 左) {
				loadimage(&pc, "13.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == 左 && p->Next->direction == 上) {
				loadimage(&pc, "14.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == 左 && p->Next->direction == 下) {
				loadimage(&pc, "15.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == 右 && p->Next->direction == 上) {
				loadimage(&pc, "16.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == 右 && p->Next->direction == 下) {
				loadimage(&pc, "17.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == 左 && p->Next->direction == 右 && p->direction==下) {
				loadimage(&pc, "14.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == 左 && p->Next->direction == 右 && p->direction == 上) {
				loadimage(&pc, "15.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == 右 && p->Next->direction == 左 && p->direction == 下) {
				loadimage(&pc, "13.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == 右 && p->Next->direction == 左 && p->direction == 上) {
				loadimage(&pc, "11.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == 上 && p->Next->direction == 下 && p->direction == 左) {
				loadimage(&pc, "10.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == 上 && p->Next->direction == 下 && p->direction == 右) {
				loadimage(&pc, "11.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == 下 && p->Next->direction == 上 && p->direction == 左) {
				loadimage(&pc, "12.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == 下 && p->Next->direction == 上 && p->direction == 右) {
				loadimage(&pc, "13.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == 上 && p->Next->direction == 上 && p->direction == 左) {
				loadimage(&pc, "12.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == 上 && p->Next->direction == 上 && p->direction == 右) {
				loadimage(&pc, "13.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == 下 && p->Next->direction == 下 && p->direction == 左) {
				loadimage(&pc, "15.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == 下 && p->Next->direction == 下 && p->direction == 右) {
				loadimage(&pc, "17.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == 右 && p->Next->direction == 右 && p->direction == 上) {
				loadimage(&pc, "10.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == 右 && p->Next->direction == 右 && p->direction == 下) {
				loadimage(&pc, "12.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == 左 && p->Next->direction == 左 && p->direction == 上) {
				loadimage(&pc, "17.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
			if (p->Before->direction == 左 && p->Next->direction == 左 && p->direction == 下) {
				loadimage(&pc, "16.png", 25, 25);
				drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
			}
		}
		p = p->Next;
	}

	//尾巴
	switch (p->direction)
	{
	case 上:
		loadimage(&pc, "06.png", 25, 25);
		drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
		break;
	case 右:
		loadimage(&pc, "07.png", 25, 25);
		drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
		break;
	case 下:
		loadimage(&pc, "08.png", 25, 25);
		drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
		break;
	case 左:
		loadimage(&pc, "09.png", 25, 25);
		drawAlpha(&pc, (p->x) * 25, (p->y) * 25);
		break;
	default:
		break;
	}
}

int die(Snake* Head) {
	//出界或咬到自己就死亡
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
	//每40次刷新，也就是0.1*40秒后，生成一块肉；或者肉被吃完后立刻生成肉
	if (count % 40 == 0 or Meat[0] == -1) {
		if (Meat[0] == -1) {
			count = 1;//吃肉后刷新间隔时间
		}

	Rand:
		srand((unsigned)time(NULL));
		Meat[0] = rand() % (X-2)+1;
		Meat[1] = rand() % (Y-2)+1;

		Snake* p = Head;
		while (p->Next !=Head) {
			//防止肉生成在蛇身上
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

void drawAlpha(IMAGE* picture, int  picture_x, int picture_y) //x为载入图片的X坐标，y为Y坐标
{

	// 变量初始化
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}

void BGM2() {
	mciSendString("close 02", NULL, 0, NULL);
	//打开音乐，播放音乐
	mciSendString("open ./02gameTime.wav alias 02 type MPEGVideo", 0, 0, 0);
	mciSendString("play 02 repeat", 0, 0, 0);
}

void BGM4() {
	mciSendString("close 04", NULL, 0, NULL);
	//打开音乐，播放音乐
	mciSendString("open ./04eat.wav alias 04", 0, 0, 0);
	mciSendString("play 04", 0, 0, 0);
}