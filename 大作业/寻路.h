#include "Node.h"

//Ѱ·����Ҫ����

bool Ѱ·(int startX, int startY, int finishX, int finishY,Snake* Head,Direction* pDir) {
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
			map[i][j].���� = ��ͨ;
			map[i][j].before = NULL;
			map[i][j].next = NULL;
		}
	}

	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			map[i][0].���� = �ϰ�;
			map[i][Y - 1].���� = �ϰ�;
			map[0][j].���� = �ϰ�;
			map[X - 1][j].���� = �ϰ�;
		}
	}

	Snake* p = Head->Next;
	while (p!=Head)
	{
		map[p->x][p->y].���� = �ϰ�;
		p = p->Next;
	}

	map[startX][startY].���� = ���;
	map[finishX][finishY].���� = �յ�;

	Node* pstartNode = &map[startX][startY];
	Node* pfinishNode = &map[finishX][finishY];
	pstartNode->f = calculate_F(*pstartNode, *pfinishNode, *pstartNode);
	pstartNode->g = calculate_G(*pstartNode, *pfinishNode, *pstartNode);

	ListAppend(&OpenList, pstartNode);

	while (true)
	{
		Node* pCurrent = OpenList->pnode;

		ListAppend(&CloseList, pCurrent);

		if (pCurrent->x == finishX && pCurrent->y == finishY) {
			break;
		}

		int num = 0;
		Node CurSon[4];//�ӽڵ�

		//��
		if (pCurrent->x - 1 >= 0) {
			CurSon[num] = map[pCurrent->x - 1][pCurrent->y];
			num++;
		}

		//��
		if (pCurrent->x + 1 < X) {
			CurSon[num] = map[pCurrent->x + 1][pCurrent->y];
			num++;
		}

		//��
		if (pCurrent->y - 1 >= 0) {
			CurSon[num] = map[pCurrent->x][pCurrent->y - 1];
			num++;
		}

		//��
		if (pCurrent->y + 1 < Y) {
			CurSon[num] = map[pCurrent->x][pCurrent->y + 1];
			num++;
		}

		for (int i = 0; i < num; i++) {
			CurSon[i].f = calculate_F(*pstartNode, *pfinishNode, CurSon[i]);
			CurSon[i].g = calculate_G(*pstartNode, *pfinishNode, *pCurrent) + 1;
			map[CurSon[i].x][CurSon[i].y].f = CurSon[i].f;
			map[CurSon[i].x][CurSon[i].y].g = CurSon[i].g;

			if (CurSon[i].���� == �ϰ�) {
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
					else if (CurSon[i].���� == ��ͨ)
					{
						map[CurSon[i].x][CurSon[i].y].before = pCurrent;
						ListAppend(&OpenList, &map[CurSon[i].x][CurSon[i].y]);
					}
				}
			}
		}
		ListDelete(&OpenList);

		//�Ҳ��������
		if (OpenList == NULL) {
			return false;
		}

		Sort(&OpenList);
	}

end:

	Node* pos= pfinishNode;
	while(pfinishNode != pstartNode) {
		pos = pfinishNode;
		pfinishNode = pfinishNode->before;
	}

	if (pos->x > pstartNode->x && pos->y == pstartNode->y) {
		*pDir = ��;
	}
	else if(pos->x < pstartNode->x&& pos->y == pstartNode->y)
	{
		*pDir = ��;
	}
	else if(pos->x == pstartNode->x&& pos->y > pstartNode->y)
	{
		*pDir = ��;
	}
	else
	{
		*pDir = ��;
	}


	return true;
}

bool ��·(int startX, int startY, int finishX, int finishY, Snake* Head,Direction* pDir) {
	if (Head->x == Head->Before->x + 1 && Head->y == Head->Before->y ||
		Head->x == Head->Before->x - 1 && Head->y == Head->Before->y ||
		Head->x == Head->Before->x && Head->y == Head->Before->y + 1 ||
		Head->x == Head->Before->x && Head->y == Head->Before->y - 1) 
	{
		List* OpenList;
		OpenList = NULL;
		List* CloseList;
		CloseList = NULL;

		if (Head->Before->x == Head->Before->Before->x && Head->Before->y == Head->Before->Before->y) {
			//if (true) {
			if (Head->x == Head->Before->x + 1 && Head->y == Head->Before->y ||
				Head->x == Head->Before->x - 1 && Head->y == Head->Before->y ||
				Head->x == Head->Before->x && Head->y == Head->Before->y + 1 ||
				Head->x == Head->Before->x && Head->y == Head->Before->y - 1)
			{
				return false;
			}
		}

		Node map[X][Y];
		for (int i = 0; i < X; i++) {
			for (int j = 0; j < Y; j++) {
				map[i][j].x = i;
				map[i][j].y = j;
				map[i][j].f = -1;
				map[i][j].g = -1;
				map[i][j].���� = ��ͨ;
				map[i][j].before = NULL;
				map[i][j].next = NULL;
			}
		}

		for (int i = 0; i < X; i++) {
			for (int j = 0; j < Y; j++) {
				map[i][0].���� = �ϰ�;
				map[i][Y - 1].���� = �ϰ�;
				map[0][j].���� = �ϰ�;
				map[X - 1][j].���� = �ϰ�;
			}
		}

		Snake* p = Head->Next;
		while (p != Head)
		{
			map[p->x][p->y].���� = �ϰ�;
			p = p->Next;
		}

		map[startX][startY].���� = ���;
		map[finishX][finishY].���� = �յ�;

		Node* pstartNode = &map[startX][startY];
		Node* pfinishNode = &map[finishX][finishY];
		pstartNode->f = calculate_F(*pstartNode, *pfinishNode, *pstartNode);
		pstartNode->g = calculate_G(*pstartNode, *pfinishNode, *pstartNode);

		ListAppend(&OpenList, pstartNode);

		while (true)
		{
			Node* pCurrent = OpenList->pnode;

			ListAppend(&CloseList, pCurrent);

			int num = 0;
			Node CurSon[4];//�ӽڵ�

			//��
			if (pCurrent->x - 1 >= 0) {
				CurSon[num] = map[pCurrent->x - 1][pCurrent->y];
				num++;
			}

			//��
			if (pCurrent->x + 1 < X) {
				CurSon[num] = map[pCurrent->x + 1][pCurrent->y];
				num++;
			}

			//��
			if (pCurrent->y - 1 >= 0) {
				CurSon[num] = map[pCurrent->x][pCurrent->y - 1];
				num++;
			}

			//��
			if (pCurrent->y + 1 < Y) {
				CurSon[num] = map[pCurrent->x][pCurrent->y + 1];
				num++;
			}

			for (int i = 0; i < num; i++) {
				CurSon[i].f = calculate_F(*pstartNode, *pfinishNode, CurSon[i]);
				CurSon[i].g = calculate_G(*pstartNode, *pfinishNode, *pCurrent) + 1;
				map[CurSon[i].x][CurSon[i].y].f = CurSon[i].f;
				map[CurSon[i].x][CurSon[i].y].g = CurSon[i].g;

				if (CurSon[i].���� == �ϰ�) {
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

						if (CurSon[i].g > p->pnode->g)
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
						}
						else if (isInList(CloseList, CurSon[i]))
						{
							continue;
						}
						else if (CurSon[i].���� == ��ͨ)
						{
							map[CurSon[i].x][CurSon[i].y].before = pCurrent;
							ListAppend(&OpenList, &map[CurSon[i].x][CurSon[i].y]);
						}
					}
				}
			}
			ListDelete(&OpenList);

			//�Ҳ��������
			if (OpenList == NULL) {
				goto end1;
			}

			Sort_Max(&OpenList);
		}

	end1:

		Node* pos = pfinishNode;
		while (pfinishNode != pstartNode) {
			pos = pfinishNode;
			pfinishNode = pfinishNode->before;
		}

		if (pos->x > pstartNode->x && pos->y == pstartNode->y) {
			*pDir = ��;
		}
		else if (pos->x < pstartNode->x && pos->y == pstartNode->y)
		{
			*pDir = ��;
		}
		else if (pos->x == pstartNode->x && pos->y > pstartNode->y)
		{
			*pDir = ��;
		}
		else if (pos->x == pstartNode->x && pos->y < pstartNode->y)
		{
			*pDir = ��;
		}

		return true;
	}
	else
	{
		List* OpenList;
		OpenList = NULL;
		List* CloseList;
		CloseList = NULL;

		if (Head->Before->x == Head->Before->Before->x && Head->Before->y == Head->Before->Before->y) {
			//if (true) {
			if (Head->x == Head->Before->x + 1 && Head->y == Head->Before->y ||
				Head->x == Head->Before->x - 1 && Head->y == Head->Before->y ||
				Head->x == Head->Before->x && Head->y == Head->Before->y + 1 ||
				Head->x == Head->Before->x && Head->y == Head->Before->y - 1)
			{
				return false;
			}
		}

		Node map[X][Y];
		for (int i = 0; i < X; i++) {
			for (int j = 0; j < Y; j++) {
				map[i][j].x = i;
				map[i][j].y = j;
				map[i][j].f = -1;
				map[i][j].g = -1;
				map[i][j].���� = ��ͨ;
				map[i][j].before = NULL;
				map[i][j].next = NULL;
			}
		}

		for (int i = 0; i < X; i++) {
			for (int j = 0; j < Y; j++) {
				map[i][0].���� = �ϰ�;
				map[i][Y - 1].���� = �ϰ�;
				map[0][j].���� = �ϰ�;
				map[X - 1][j].���� = �ϰ�;
			}
		}

		Snake* p = Head->Next;
		while (p != Head)
		{
			map[p->x][p->y].���� = �ϰ�;
			p = p->Next;
		}

		map[startX][startY].���� = ���;
		map[finishX][finishY].���� = �յ�;

		Node* pstartNode = &map[startX][startY];
		Node* pfinishNode = &map[finishX][finishY];
		pstartNode->f = calculate_F(*pstartNode, *pfinishNode, *pstartNode);
		pstartNode->g = calculate_G(*pstartNode, *pfinishNode, *pstartNode);

		ListAppend(&OpenList, pstartNode);

		while (true)
		{
			Node* pCurrent = OpenList->pnode;

			ListAppend(&CloseList, pCurrent);

			if (pCurrent->x == finishX && pCurrent->y == finishY) {
				break;
			}

			int num = 0;
			Node CurSon[4];//�ӽڵ�

			//��
			if (pCurrent->x - 1 >= 0) {
				CurSon[num] = map[pCurrent->x - 1][pCurrent->y];
				num++;
			}

			//��
			if (pCurrent->x + 1 < X) {
				CurSon[num] = map[pCurrent->x + 1][pCurrent->y];
				num++;
			}

			//��
			if (pCurrent->y - 1 >= 0) {
				CurSon[num] = map[pCurrent->x][pCurrent->y - 1];
				num++;
			}

			//��
			if (pCurrent->y + 1 < Y) {
				CurSon[num] = map[pCurrent->x][pCurrent->y + 1];
				num++;
			}

			for (int i = 0; i < num; i++) {
				CurSon[i].f = calculate_F(*pstartNode, *pfinishNode, CurSon[i]);
				CurSon[i].g = calculate_G(*pstartNode, *pfinishNode, *pCurrent) + 1;
				map[CurSon[i].x][CurSon[i].y].f = CurSon[i].f;
				map[CurSon[i].x][CurSon[i].y].g = CurSon[i].g;

				if (CurSon[i].���� == �ϰ�) {
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

						if (CurSon[i].g > p->pnode->g)
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
						else if (CurSon[i].���� == ��ͨ)
						{
							map[CurSon[i].x][CurSon[i].y].before = pCurrent;
							ListAppend(&OpenList, &map[CurSon[i].x][CurSon[i].y]);
						}
					}
				}
			}
			ListDelete(&OpenList);

			//�Ҳ��������
			if (OpenList == NULL) {
				return false;
			}

			Sort_Max(&OpenList);
		}

	end:

		Node* pos = pfinishNode;
		while (pfinishNode != pstartNode) {
			pos = pfinishNode;
			pfinishNode = pfinishNode->before;
		}

		if (pos->x > pstartNode->x && pos->y == pstartNode->y) {
			*pDir = ��;
		}
		else if (pos->x < pstartNode->x && pos->y == pstartNode->y)
		{
			*pDir = ��;
		}
		else if (pos->x == pstartNode->x && pos->y > pstartNode->y)
		{
			*pDir = ��;
		}
		else if (pos->x == pstartNode->x && pos->y < pstartNode->y)
		{
			*pDir = ��;
		}

		return true;
	}

}

bool Vir_Ѱ·(int startX, int startY, int finishX, int finishY, Snake* Head) {
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
			map[i][j].���� = ��ͨ;
			map[i][j].before = NULL;
			map[i][j].next = NULL;
		}
	}

	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			map[i][0].���� = �ϰ�;
			map[i][Y - 1].���� = �ϰ�;
			map[0][j].���� = �ϰ�;
			map[X - 1][j].���� = �ϰ�;
		}
	}

	Snake* p = Head->Next;
	while (p != Head)
	{
		map[p->x][p->y].���� = �ϰ�;
		p = p->Next;
	}

	map[startX][startY].���� = ���;
	map[finishX][finishY].���� = �յ�;

	Node* pstartNode = &map[startX][startY];
	Node* pfinishNode = &map[finishX][finishY];
	pstartNode->f = calculate_F(*pstartNode, *pfinishNode, *pstartNode);
	pstartNode->g = calculate_G(*pstartNode, *pfinishNode, *pstartNode);
	printf("pstartNode->f=%d\n", pstartNode->f);//����

	ListAppend(&OpenList, pstartNode);

	while (true)
	{
		Node* pCurrent = OpenList->pnode;

		ListAppend(&CloseList, pCurrent);

		if (pCurrent->x == finishX && pCurrent->y == finishY) {
			break;
		}

		int num = 0;
		Node CurSon[4];//�ӽڵ�

		//��
		if (pCurrent->x - 1 >= 0) {
			CurSon[num] = map[pCurrent->x - 1][pCurrent->y];
			num++;
		}

		//��
		if (pCurrent->x + 1 < X) {
			CurSon[num] = map[pCurrent->x + 1][pCurrent->y];
			num++;
		}

		//��
		if (pCurrent->y - 1 >= 0) {
			CurSon[num] = map[pCurrent->x][pCurrent->y - 1];
			num++;
		}

		//��
		if (pCurrent->y + 1 < Y) {
			CurSon[num] = map[pCurrent->x][pCurrent->y + 1];
			num++;
		}

		for (int i = 0; i < num; i++) {
			CurSon[i].f = calculate_F(*pstartNode, *pfinishNode, CurSon[i]);
			CurSon[i].g = calculate_G(*pstartNode, *pfinishNode, *pCurrent) + 1;
			map[CurSon[i].x][CurSon[i].y].f = CurSon[i].f;
			map[CurSon[i].x][CurSon[i].y].g = CurSon[i].g;

			if (CurSon[i].���� == �ϰ�) {
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

		//�Ҳ��������
		if (OpenList == NULL) {
			return false;
		}

		Sort(&OpenList);
	}

end:

	Node* pos= pstartNode;
	Node *pf = pfinishNode;
	while (pf != pstartNode) {
		pos = pf;
		pf = pf->before;
		pf->next =pos;
	}
	pf->next = pos;
	Snake* VirHead = (Snake*)malloc(sizeof(Snake));
	VirHead->Before = NULL;
	VirHead->Next = NULL;

	Snake_copy(Head, &VirHead);

	while (pos!=pfinishNode)
	{
		if (pos->x > VirHead->x && pos->y == VirHead->y) {
			VirHead->direction = ��;
		}
		else if (pos->x < VirHead->x && pos->y == VirHead->y)
		{
			VirHead->direction = ��;
		}
		else if (pos->x == VirHead->x && pos->y > VirHead->y)
		{
			VirHead->direction = ��;
		}
		else if(pos->x == VirHead->x && pos->y < VirHead->y)
		{
			VirHead->direction = ��;
		}
		Movement(&VirHead);

		pos = pos->next;
	}

	if (pos->x > VirHead->x && pos->y == VirHead->y) {
		VirHead->direction = ��;
	}
	else if (pos->x < VirHead->x && pos->y == VirHead->y)
	{
		VirHead->direction = ��;
	}
	else if (pos->x == VirHead->x && pos->y > VirHead->y)
	{
		VirHead->direction = ��;
	}
	else if (pos->x == VirHead->x && pos->y < VirHead->y)
	{
		VirHead->direction = ��;
	}

	Movement(&VirHead);

	Direction ռλ��;
	if (VirHead->x == VirHead->Before->x && VirHead->y == VirHead->Before->y+1 ||
		VirHead->x == VirHead->Before->x && VirHead->y == VirHead->Before->y-1 ||
		VirHead->x == VirHead->Before->x+1 && VirHead->y == VirHead->Before->y ||
		VirHead->x == VirHead->Before->x-1 && VirHead->y == VirHead->Before->y) {
		return false;
	}
	else
	{
		return Ѱ·(VirHead->x, VirHead->y, VirHead->Before->x, VirHead->Before->y, VirHead, &ռλ��);
	}
}