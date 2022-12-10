#include <stdio.h>
#include <stdlib.h>

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
