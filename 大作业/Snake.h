#include <stdio.h>
#include <stdlib.h>

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
