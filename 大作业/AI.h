#include"Ѱ·.h"

Direction Change_Direction(Snake* Head, int Meat[2]) 
{
	Direction Dir=Head->direction;
	Direction OriDir = Head->direction;

	if (Ѱ·(Head->x, Head->y, Meat[0], Meat[1], Head, &Dir)) {
		if (Vir_Ѱ·(Head->x, Head->y, Meat[0], Meat[1], Head)) {
			return Dir;
		}
		else
		{
			if (��·(Head->x, Head->y, Head->Before->x, Head->Before->y, Head, &Dir))
			{
				return Dir;
			}
			else
			{
				if (will_die(Head, ��) == 0 && Head->direction != ��) {
					Dir = ��;
				}
				else if (will_die(Head, ��) == 0 && Head->direction != ��)
				{
					Dir = ��;
				}
				else if (will_die(Head, ��) == 0 && Head->direction != ��)
				{
					Dir = ��;
				}
				else if (will_die(Head, ��) == 0 && Head->direction != ��)
				{
					Dir = ��;
				}
				else
				{
					Dir = OriDir;
				}
			}
		}
	}
	else if (��·(Head->x, Head->y, Head->Before->x, Head->Before->y, Head, &Dir))
	{
		return Dir;
	}
	else
	{
		if (will_die(Head, ��) == 0 && Head->direction!=��) {
			Dir = ��;
		}
		else if(will_die(Head, ��) == 0 && Head->direction != ��)
		{
			Dir = ��;
		}
		else if (will_die(Head, ��) == 0 && Head->direction != ��)
		{
			Dir = ��;
		}
		else if (will_die(Head, ��) == 0 && Head->direction != ��)
		{
			Dir = ��;
		}
		else
		{
			Dir = OriDir;
		}
	}

	return Dir;
}
