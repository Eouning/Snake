#include "Node.h"

//寻路的主要函数
void 寻路(int startX, int startY, int finishX, int finishY) {
	List* OpenList;
	OpenList = NULL;
	List* CloseList;
	CloseList = NULL;

	Node map[X][Y];
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			map[i][j].x = i;
			map[i][j].y = j;
			map[i][j].f = -1;
			map[i][j].g = -1;
			map[i][j].性质 = 普通;
			map[i][j].before = NULL;
			map[i][j].next = NULL;
		}
	}

	map[startX][startY].性质 = 起点;
	map[finishX][finishY].性质 = 终点;

	Node* pstartNode = &map[startX][startY];
	Node* pfinishNode = &map[finishX][finishY];
	pstartNode->f = calculate_F(*pstartNode, *pfinishNode, *pstartNode);
	pstartNode->g = calculate_G(*pstartNode, *pfinishNode, *pstartNode);
	printf("pstartNode->f=%d\n", pstartNode->f);//测试

	ListAppend(&OpenList, pstartNode);

	while (true)
	{
		if (OpenList == NULL) {
			//找不到，该程序下一般不可能。
			printf("111\n");
			getchar();
		}

		Node* pCurrent = OpenList->pnode;

		ListAppend(&CloseList, pCurrent);

		if (pCurrent->x == finishX && pCurrent->y == finishY) {
			break;
		}

		int num = 0;
		Node CurSon[4];//子节点

		//左
		if (pCurrent->x - 1 >= 0) {
			CurSon[num] = map[pCurrent->x - 1][pCurrent->y];
			num++;
		}

		//右
		if (pCurrent->x + 1 < X) {
			CurSon[num] = map[pCurrent->x + 1][pCurrent->y];
			num++;
		}

		//上
		if (pCurrent->y - 1 >= 0) {
			CurSon[num] = map[pCurrent->x][pCurrent->y - 1];
			num++;
		}

		//下
		if (pCurrent->y + 1 < Y) {
			CurSon[num] = map[pCurrent->x][pCurrent->y + 1];
			num++;
		}

		for (int i = 0; i < num; i++) {
			CurSon[i].f = calculate_F(*pstartNode, *pfinishNode, CurSon[i]);
			CurSon[i].g = calculate_G(*pstartNode, *pfinishNode, *pCurrent) + 1;
			map[CurSon[i].x][CurSon[i].y].f = CurSon[i].f;
			map[CurSon[i].x][CurSon[i].y].g = CurSon[i].g;

			if (CurSon[i].性质 == 障碍) {
				continue;
			}
			else
			{
				if (isInList(OpenList, CurSon[i])) {
					List* p = OpenList;
					while (p->pnode->x != CurSon[i].x || p->pnode->y != CurSon[i].y)
					{
						p = p->next;
					}

					if (CurSon[i].g < p->pnode->g)
					{
						p->pnode->before = pCurrent;
						p->pnode->f = CurSon[i].f;
						p->pnode->g = CurSon[i].g;
					}
					else
					{
						continue;
					}
				}
				else
				{
					if (CurSon[i].x == pfinishNode->x && CurSon[i].y == pfinishNode->y) {
						map[CurSon[i].x][CurSon[i].y].before = pCurrent;
						goto end;
					}
					else if (isInList(CloseList, CurSon[i]))
					{
						continue;
					}
					else
					{
						map[CurSon[i].x][CurSon[i].y].before = pCurrent;
						ListAppend(&OpenList, &map[CurSon[i].x][CurSon[i].y]);
					}
				}
			}
		}
		ListDelete(&OpenList);
		Sort(&OpenList);
	}

end:
	int i=0;
}
