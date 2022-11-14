#include <stdio.h>

//����һ����ʾ�����ö������
enum Direction { ��, ��, ��, �� };

//����һ���洢�ߵ�����
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