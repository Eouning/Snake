#include "AI.h"
void Show(Snake* Head, int Meat[2]);//将蛇和肉打印在屏幕上
void Movement(Snake** pHead);//让蛇移动
int makeMeat(int count, int Meat[2], Snake* Head,int AI);//创造肉
int die(Snake* Head);//对死亡的判定
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y); //图片透明背景化,x为要载入图片的X坐标，y为Y坐标
void BGM2();//游戏背景音乐
void BGM4();//吃肉音效

int Play(int AI) {
	//生成背景
	initgraph(X * 25, Y * 25);

	HWND hWnd = GetHWnd();
	SetWindowText(hWnd, "这是另一个普通的窗口名称 OwO");

	IMAGE back;
	loadimage(&back, "19.png", 25 * X, 25 * Y);
	putimage(0, 0, &back);

	//播放背景音乐
	BGM2();

	//生成初始的蛇
	Snake* Head = (Snake*)malloc(sizeof(Snake));
	Head->Before = NULL;
	Head->Next = NULL;
	Snake_append(&Head, 5, 5, 下);
	Snake_append(&Head, 5, 4, 下);
	Snake_append(&Head, 5, 3, 下);
	int points = 0;

	int Meat[2];
	int count = 0;

	while (die(Head) == 0) {

		count = makeMeat(count, Meat, Head,AI);

		if (AI == 0) {
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
		}
		else
		{
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
				return points+2;
			}
			Head->direction = Change_Direction(Head, Meat);
		}
		
		IMAGE back_piece;
		loadimage(&back_piece, "map_piece.png", 25, 25 );
		putimage(Head->Before->x*25, Head->Before->y*25, &back_piece);
		
		Movement(&Head);
		//如果吃到肉了，蛇就增长
		if (Head->x == Meat[0] && Head->y == Meat[1]) {

			IMAGE back_piece;
			loadimage(&back_piece, "map_piece.png", 25, 25);
			putimage(Meat[0] * 25, Meat[1] * 25, &back_piece);

			Meat[0] = -1;
			Snake_append(&Head, Head->Before->x, Head->Before->y, Head->Before->direction);
			points++;
			BGM4();
		}

		

		Show(Head,Meat);

		count++;

		//刷新频率，x/1000秒一次
		Sleep(55);

	}

	Snake_damage(Head);
	return points + 2;

}

void Show(Snake* Head, int Meat[2]) {
	IMAGE pc;
	IMAGE ph;

	IMAGE back_piece;
	loadimage(&back_piece, "map_piece.png", 25, 25);
	putimage(Head->x * 25, Head->y * 25, &back_piece);
	putimage(Head->Next->x * 25, Head->Next->y* 25, &back_piece);
	putimage(Head->Before->x* 25, Head->Before->y * 25, &back_piece);

	//头
	switch (Head->direction)
	{
	case 上:
		loadimage(&ph, "00.png", 25, 25);
		drawAlpha(&ph, (Head->x) * 25, (Head->y) * 25);
		break;
	case 右:
		loadimage(&ph, "01.png", 25, 25);
		drawAlpha(&ph, (Head->x) * 25, (Head->y) * 25);
		break;
	case 下:
		loadimage(&ph, "02.png", 25, 25);
		drawAlpha(&ph, (Head->x) * 25, (Head->y) * 25);
		break;
	case 左:
		loadimage(&ph, "03.png", 25, 25);
		drawAlpha(&ph, (Head->x) * 25, (Head->y) * 25);
		break;
	default:
		break;
	}

	Snake* p = Head->Next;
	//身
	if (p->Before->direction == p->Next->direction && p->direction == p->Before->direction || p->Next->direction == p->direction) {
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
		if (p->Before->direction == 上 && p->Next->direction == 右) {
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
		if (p->Before->direction == 左 && p->Next->direction == 右 && p->direction == 下) {
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

	IMAGE p2;
	//尾巴
	switch (Head->Before->direction)
	{
	case 上:
		loadimage(&p2, "06.png", 25, 25);
		drawAlpha(&p2, (Head->Before->x) * 25, (Head->Before->y) * 25);
		break;
	case 右:
		loadimage(&p2, "07.png", 25, 25);
		drawAlpha(&p2, (Head->Before->x) * 25, (Head->Before->y) * 25);
		break;
	case 下:
		loadimage(&p2, "08.png", 25, 25);
		drawAlpha(&p2, (Head->Before->x) * 25, (Head->Before->y) * 25);
		break;
	case 左:
		loadimage(&p2, "09.png", 25, 25);
		drawAlpha(&p2, (Head->Before->x) * 25, (Head->Before->y) * 25);
		break;
	default:
		break;
	}
}

int makeMeat(int count, int Meat[2], Snake* Head,int AI) {
	//每40次刷新，也就是0.1*40秒后，生成一块肉；或者肉被吃完后立刻生成肉
	if (count % (40+AI*50000*(X+Y)) == 0 or Meat[0] == -1) {
		if (Meat[0] == -1) {
			count = 1;//吃肉后刷新间隔时间
		}
		else
		{
			IMAGE back_piece;
			loadimage(&back_piece, "map_piece.png", 25, 25);
			putimage(Meat[0] * 25, Meat[1] * 25, &back_piece);
		}

		Node map[X][Y];
		List* list=NULL;
		int num = 0;
		for (int i = 1; i < X-1; i++) {
			for (int j = 1; j < Y-1; j++) {
				map[i][j].x = i;
				map[i][j].y = j;
				map[i][j].f = 0;
			}
		}

		Snake* p = Head;
		while (p->Next!=Head)
		{
			map[p->x][p->y].f = 1;
			p = p->Next;
		}
		map[p->x][p->y].f = 1;

		for (int i = 1; i < X - 1; i++) {
			for (int j = 1; j < Y - 1; j++) {
				if (map[i][j].f == 0) {
					num++;
					ListAppend(&list, &map[i][j]);
				}
			}
		}

		srand((unsigned)time(NULL));
		if (num == 1 ) {
			Meat[0] = list->pnode->x;
			Meat[1] = list->pnode->y;

			IMAGE pc;
			//肉
			loadimage(&pc, "18.png", 25, 25);
			drawAlpha(&pc, Meat[0] * 25, Meat[1] * 25);
		}
		else if (num==0)
		{
			Meat[0] = 0;
			Meat[1] = 0;
		}
		else
		{
			int x = rand() % (num - 1);
			x = rand() % (num - 1);
			x = rand() % (num - 1);
			x = rand() % (num - 1);
			x = rand() % (num - 1);
			x = rand() % (num - 1);
			x = rand() % (num - 1);
			x = rand() % (num - 1);
			x = rand() % (num - 1);

			List* meat = list;
			for (int i = 0; i < x; i++) {
				meat = meat->next;
			}
			Meat[0] = meat->pnode->x;
			Meat[1] = meat->pnode->y;

			IMAGE pc;
			//肉
			loadimage(&pc, "18.png", 25, 25);
			drawAlpha(&pc, Meat[0] * 25, Meat[1] * 25);
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
	mciSendString("open ./dianzimuyu.mp3 alias 04", 0, 0, 0);
	mciSendString("play 04", 0, 0, 0);
}