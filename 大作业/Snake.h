#include <stdio.h>
#include <stdlib.h>

//��ʾ��ͼ��Χ����25*25��ÿ��25*25���ء�
#define X 25
#define Y 25

//����һ����ʾ�����ö������
enum Direction { ��, ��, ��, �� };

//����һ���洢�ߵ���������Ϸ�еı�����ʽΪ����β�ߡ�
typedef struct _none {
	enum Direction direction;//�洢��������ݣ��Է����һ�������ɷ��黻��ͼƬʱ��ͼƬ��ѡ��
	int x;
	int y;
	struct _none* Next;
	struct _none* Before;
} Snake;

//�ߵ�����,������ͷ��ַ�ĵ�ַ
void Snake_append(Snake** pHead, int x, int y, enum Direction direction) {
	Snake* p = (Snake*)malloc(sizeof(Snake));//Ϊ���µĲ��ַ���һ���ڴ�
	p->x = x;//��Ϊ��Щ�ڴ渳ֵ
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

int will_die(Snake* Head,Direction Dir) {

	Snake* VirHead = (Snake*)malloc(sizeof(Snake));
	VirHead->Before = NULL;
	VirHead->Next = NULL;

	Snake_copy(Head, &VirHead);
	VirHead->direction = Dir;
	Movement(&VirHead);

	return die(VirHead);

}