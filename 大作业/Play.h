#include "AI.h"
void Show(Snake* Head, int Meat[2]);//���ߺ����ӡ����Ļ��
void Movement(Snake** pHead);//�����ƶ�
int makeMeat(int count, int Meat[2], Snake* Head,int AI);//������
int die(Snake* Head);//���������ж�
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y); //ͼƬ͸��������,xΪҪ����ͼƬ��X���꣬yΪY����
void BGM2();//��Ϸ��������
void BGM4();//������Ч

int Play(int AI) {
	//���ɱ���
	initgraph(X * 25, Y * 25);

	HWND hWnd = GetHWnd();
	SetWindowText(hWnd, "������һ����ͨ�Ĵ������� OwO");

	IMAGE back;
	loadimage(&back, "19.png", 25 * X, 25 * Y);
	putimage(0, 0, &back);

	//���ű�������
	BGM2();

	//���ɳ�ʼ����
	Snake* Head = (Snake*)malloc(sizeof(Snake));
	Head->Before = NULL;
	Head->Next = NULL;
	Snake_append(&Head, 5, 5, ��);
	Snake_append(&Head, 5, 4, ��);
	Snake_append(&Head, 5, 3, ��);
	int points = 0;

	int Meat[2];
	int count = 0;

	while (die(Head) == 0) {

		count = makeMeat(count, Meat, Head,AI);

		if (AI == 0) {
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
		//����Ե����ˣ��߾�����
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

		//ˢ��Ƶ�ʣ�x/1000��һ��
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

	//ͷ
	switch (Head->direction)
	{
	case ��:
		loadimage(&ph, "00.png", 25, 25);
		drawAlpha(&ph, (Head->x) * 25, (Head->y) * 25);
		break;
	case ��:
		loadimage(&ph, "01.png", 25, 25);
		drawAlpha(&ph, (Head->x) * 25, (Head->y) * 25);
		break;
	case ��:
		loadimage(&ph, "02.png", 25, 25);
		drawAlpha(&ph, (Head->x) * 25, (Head->y) * 25);
		break;
	case ��:
		loadimage(&ph, "03.png", 25, 25);
		drawAlpha(&ph, (Head->x) * 25, (Head->y) * 25);
		break;
	default:
		break;
	}

	Snake* p = Head->Next;
	//��
	if (p->Before->direction == p->Next->direction && p->direction == p->Before->direction || p->Next->direction == p->direction) {
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
		if (p->Before->direction == �� && p->Next->direction == ��) {
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
		if (p->Before->direction == �� && p->Next->direction == �� && p->direction == ��) {
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

	IMAGE p2;
	//β��
	switch (Head->Before->direction)
	{
	case ��:
		loadimage(&p2, "06.png", 25, 25);
		drawAlpha(&p2, (Head->Before->x) * 25, (Head->Before->y) * 25);
		break;
	case ��:
		loadimage(&p2, "07.png", 25, 25);
		drawAlpha(&p2, (Head->Before->x) * 25, (Head->Before->y) * 25);
		break;
	case ��:
		loadimage(&p2, "08.png", 25, 25);
		drawAlpha(&p2, (Head->Before->x) * 25, (Head->Before->y) * 25);
		break;
	case ��:
		loadimage(&p2, "09.png", 25, 25);
		drawAlpha(&p2, (Head->Before->x) * 25, (Head->Before->y) * 25);
		break;
	default:
		break;
	}
}

int makeMeat(int count, int Meat[2], Snake* Head,int AI) {
	//ÿ40��ˢ�£�Ҳ����0.1*40�������һ���⣻�����ⱻ���������������
	if (count % (40+AI*50000*(X+Y)) == 0 or Meat[0] == -1) {
		if (Meat[0] == -1) {
			count = 1;//�����ˢ�¼��ʱ��
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
			//��
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
			//��
			loadimage(&pc, "18.png", 25, 25);
			drawAlpha(&pc, Meat[0] * 25, Meat[1] * 25);
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
	mciSendString("open ./dianzimuyu.mp3 alias 04", 0, 0, 0);
	mciSendString("play 04", 0, 0, 0);
}