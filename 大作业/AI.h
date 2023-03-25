#include"寻路.h"

Direction Change_Direction(Snake* Head, int Meat[2]) 
{
	Direction Dir=Head->direction;
	Direction OriDir = Head->direction;

	if (寻路(Head->x, Head->y, Meat[0], Meat[1], Head, &Dir)) {
		if (Vir_寻路(Head->x, Head->y, Meat[0], Meat[1], Head)) {
			return Dir;
		}
		else
		{
			if (绕路(Head->x, Head->y, Head->Before->x, Head->Before->y, Head, &Dir))
			{
				return Dir;
			}
			else
			{
				if (will_die(Head, 上) == 0 && Head->direction != 下) {
					Dir = 上;
				}
				else if (will_die(Head, 下) == 0 && Head->direction != 上)
				{
					Dir = 下;
				}
				else if (will_die(Head, 左) == 0 && Head->direction != 右)
				{
					Dir = 左;
				}
				else if (will_die(Head, 右) == 0 && Head->direction != 左)
				{
					Dir = 右;
				}
				else
				{
					Dir = OriDir;
				}
			}
		}
	}
	else if (绕路(Head->x, Head->y, Head->Before->x, Head->Before->y, Head, &Dir))
	{
		return Dir;
	}
	else
	{
		if (will_die(Head, 上) == 0 && Head->direction!=下) {
			Dir = 上;
		}
		else if(will_die(Head, 下) == 0 && Head->direction != 上)
		{
			Dir = 下;
		}
		else if (will_die(Head, 左) == 0 && Head->direction != 右)
		{
			Dir = 左;
		}
		else if (will_die(Head, 右) == 0 && Head->direction != 左)
		{
			Dir = 右;
		}
		else
		{
			Dir = OriDir;
		}
	}

	return Dir;
}
