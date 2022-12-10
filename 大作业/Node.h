#include <windows.h>
#include <math.h>
#include <time.h>
#include <graphics.h>
#include <easyx.h>
#include <string.h>
#include <conio.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include"Snake.h"

//表示地图范围，共25*25格，每格25*25像素。
#define X 25
#define Y 25

enum 性质类型
{
	普通,
	起点,
	终点,
	障碍
};

typedef struct _non {
	int x;
	int y;
	性质类型 性质;
	int f;
	int g;
	struct _non* next;
	struct _non* before;
}Node;

typedef struct _no {
	Node* pnode;
	struct _no* next;
	struct _no* before;
}List;

//计算节点的F
int calculate_F(Node startNode, Node finishNode, Node Current) {
	return abs(startNode.x - Current.x) + abs(startNode.y - Current.y) + abs(finishNode.x - Current.x) + abs(finishNode.y - Current.y);
}

//计算节点的G
int calculate_G(Node startNode, Node finishNode, Node Current) {
	return abs(startNode.x - Current.x) + abs(startNode.y - Current.y);
}

//列表的增长
void ListAppend(List** plist, Node* pnode) {
	List* p = (List*)malloc(sizeof(List));
	p->before = NULL;
	p->next = NULL;
	p->pnode = pnode;

	if (*plist == NULL) {
		*plist = p;
	}
	else
	{
		List* pLast = *plist;
		while (pLast->next)
		{
			pLast = pLast->next;
		}
		pLast->next = p;
		p->before = pLast;
	}
}

//第一个节点的删除
void ListDelete(List** plist) {
	List* p = *plist;
	*plist = p->next;

	if (*plist) {
		(*plist)->before = NULL;
		free(p);
	}
	else
	{
		free(p);
	}
}

//在该列表中
bool isInList(List* list, Node node) {

	List* p = list;
	while (p)
	{
		if (p->pnode->x == node.x && p->pnode->y == node.y) {
			return true;
		}
		p = p->next;
	}
	return false;
}

//根据f将列表中最小的放在第一位
void Sort(List** list) {
	List* p = *list;
	List* min = *list;
	while (p)
	{
		if (min->pnode->f > p->pnode->f) {
			min = p;
		}
		p = p->next;
	}
	Node* pno = min->pnode;
	min->pnode = (*list)->pnode;
	(*list)->pnode = pno;
}

