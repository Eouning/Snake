#include <stdio.h>
#include <stdlib.h>

//表示地图范围，共25*25格，每格25*25像素。
#define X 25
#define Y 25

//定义一个表示朝向的枚举类型
enum Direction { 上, 下, 左, 右 };

//定义一个存储蛇的链表，在游戏中的表现形式为“衔尾蛇”
typedef struct _none {
	enum Direction direction;//存储朝向的数据，以方便进一步将蛇由方块换成图片时，图片的选择
	int x;
	int y;
	struct _none* Next;
	struct _none* Before;
} Snake;

//蛇的增长,传入蛇头地址的地址
void Snake_append(Snake** pHead, int x, int y, enum Direction direction) {
	Snake* p = (Snake*)malloc(sizeof(Snake));//为蛇新的部分分配一块内存
	p->x = x;//并为这些内存赋值
	p->y = y;
	p->direction = direction;

	if ((*pHead)->Before) {
		(*pHead)->Before->Next = p;
		p->Before = (*pHead)->Before;
		(*pHead)->Before = p;
		p->Next = (*pHead);
	}
	else
	{
		p->Before = p;
		p->Next = p;
		*pHead = p;
	}

}

void Snake_damage(Snake* Head) {
	Snake* p1 = Head->Next;
	Snake* p2;
	while (p1!=Head)
	{
		p2 = p1;
		p1 = p1->Next;
		free(p2);
	}
	free(p1);
}

void Snake_copy(Snake* Head,Snake** VirHead) {
	Snake* p = Head;

	Snake_append(VirHead, p->x, p->y, p->direction);
	p = p->Next;
	while (p!=Head)
	{
		Snake_append(VirHead, p->x, p->y, p->direction);
		p = p->Next;
	}

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

int will_die(Snake* Head,Direction Dir) {

	Snake* VirHead = (Snake*)malloc(sizeof(Snake));
	VirHead->Before = NULL;
	VirHead->Next = NULL;

	Snake_copy(Head, &VirHead);
	VirHead->direction = Dir;
	Movement(&VirHead);

	return die(VirHead);

}