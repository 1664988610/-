#include "enemyplane.h"

extern shots enshot;
extern double bulletWidth, bulletHeight;
extern HWND hwnd;
extern fun_x, fun_y;
extern DWORD tNow;
extern HDC mdc, bufdc;
const double PI = 3.1415926;
extern shot2s enshot2;

enemyplane::enemyplane()
{
	int i;
	

	shooters[0].setplace(fun_x / 2, fun_y / 2);
	shooters[1].setplace(fun_x / 3, fun_y / 4);
	shooters[2].setplace(fun_x / 3 * 2, fun_y / 4);
	shooters[3].setplace(fun_x / 4, fun_y / 2);
	shooters[4].setplace(fun_x / 4 * 3, fun_y / 2);


	char filename[25];
	for(i = 0; i < 8; i++)
	{
		sprintf(filename,"stand00%d.bmp",i);
		bmp[i] = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}

	BITMAP bitmap;

	GetObject(bmp[2], sizeof(bitmap), &bitmap);
	width = bitmap.bmWidth;
	height = bitmap.bmHeight;

}

void enemyplane::init()
{
	//fhp = 20;
	fhp = 20;
	fla = 0;
	td = 200;
	tpre = tNow;
	hp = fhp;
	lv = 100;
	x = fun_x / 2;
	y = fun_y / 5;
	t_fla = 100;
	tpre_fla = 0;
	td = 200;
	typenum = 2;
	t2 = 40;
	t1 = 500;
	tpre1 = tNow;
	tpre2 = tNow;

	int i;
	for(i = 0; i < 5; i++)
	{
		shooters[i].init();
	}
	
}

void enemyplane::perform()
{
	int i, j;

	for(i = 0; i < 5; i++)
	{
		shooters[i].perform();
	}

	if(tNow - tpre_fla > t_fla)
	{
		fla = (fla + 1) % 8;
		tpre_fla = tNow;
	}

	if(sleep)
	{
		if(shoot[0])
		{
			if(tNow - tpre1 >= t1)
			{
				tpre1 = tNow;
				addshoot0();
			}
		}
		else if(shoot[1])
		{
			if(tNow - tpre2 >= t2)
			{
				tpre2 = tNow;
				addshoot1();
			}
		}
		return ;
	}
	else if(move)
	{
		move--;
		x += move_flag * 5;
		x = max(x, 0);
		x = min(x, fun_x - width);
	}
	else
	{
		srand(time(NULL));
		int typ = rand() % 2;
		if(typ == 0)
		{
			sleep = 1;
			int addsh = rand() % 2;
			if(addsh == 0)
			{
				addsh = rand() % 2;
				if(addsh == 0)
				{
					shoot[addsh] = 1;
					shoot[0] = 2;
				}
				else if(addsh == 1)
				{
					shoot[addsh] = 1;
					shoot[1] = 2;
					angle = 0.0;
				}
			}
			else if(addsh == 1)
			{
				if((rand() % 3) == 0)
					for(i = 0; i < 5; i++)
					{
						shooters[i].exist = 1;
						shooters[i].hp = 1;
					}
				sleep = 0;
			}
		}
		else if(typ == 1)
		{
			srand(time(NULL));
			move = 4 + rand() % 6;
			if(rand() % 2)
				move_flag = 1;
			else
				move_flag = -1;
		}
		
	}
}

void enemyplane::addshoot0()
{
	double shotx = x + width / 2;
	double shoty = y + height / 2;
	for(angle = 0.0; angle < 2 * 3.1415926; angle += 3.1415926 / 8)
	{
		enshot.add(shotx, shoty, 3.0 * cos(angle), 3.0 * sin(angle), 2);
		if(hp < 10)
		{
			
		}
	}

	shoot[0]--;
	if(!shoot[0])
		sleep = 0;
}

void enemyplane::addshoot1()
{
	double shotx = x + width / 2;
	double shoty = y + height / 2;

	if(angle >= 2 * 3.1415926)
	{
		angle = 0.0;
		shoot[1]--;
		if(!shoot[1])
			sleep = 0;
		return ;
	}
	enshot.add(shotx, shoty, 3.0 * cos(angle), 3.0 * sin(angle), 3);
	angle += 3.1415926 / 8;
}

void enemyplane::addshoot2()
{
//	addshooter();
}

void enemyplane::hurt()
{
	hp -= 1;
}

void enemyplane::show()
{
	SelectObject(bufdc, bmp[fla]);
	TransparentBlt(mdc, x, y, width, height,   
		bufdc, 0, 0, 
		width, height, RGB(0, 123, 139));
}




/////////////////////////////////////////////////////////////



enemyplane2::enemyplane2()
{
	shooters[0].setplace(fun_x / 2, fun_y / 2);
	shooters[1].setplace(fun_x / 4, fun_y / 4);
	shooters[2].setplace(fun_x / 4 * 3, fun_y / 4);
	shooters[3].setplace(fun_x / 4, fun_y / 4 * 3);
	shooters[4].setplace(fun_x / 4 * 3, fun_y / 4 * 3);

	char filename[25];
	for(int i = 0; i < 10; i++)
	{
		sprintf(filename,"boss200%d.bmp",i);
		bmp[i] = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}

	BITMAP bitmap;

	GetObject(bmp[2], sizeof(bitmap), &bitmap);
	width = bitmap.bmWidth;
	height = bitmap.bmHeight;
}

void enemyplane2::init()
{
	move_step = 5;
	move_flag = 1;
	move = (fun_x / 2 + width) / move_step;

	fhp = 40;
	fla = 0;
	td = 200;
	tpre = tNow;
	
	hp = fhp;
	lv = 200;
	x = -width;
	y = fun_y / 5;
	t_fla = 100;
	tpre_fla = 0;
	td = 200;
	typenum = 2;
	t2 = 40;
	t1 = 500;
	tpre1 = tNow;
	tpre2 = tNow;

	int i;
	for(i = 0; i < 5; i++)
	{
		shooters[i].init();
	}
	
}

void enemyplane2::perform()
{
	int i, j;

	for(i = 0; i < 5; i++)
	{
		shooters[i].perform();
	}

	if(tNow - tpre_fla > t_fla)
	{
		fla = (fla + 1) % 10;
		tpre_fla = tNow;
	}

	if(sleep)
	{
		if(shoot[0])
		{
			if(tNow - tpre1 >= t1)
			{
				tpre1 = tNow;
				addshoot0();
			}
		}
		else if(shoot[1])
		{
			if(tNow - tpre2 >= t2)
			{
				tpre2 = tNow;
				addshoot1();
			}
		}
		return ;
	}
	else if(move)
	{
		move--;
		x += move_flag * move_step;
		x = max(x, 0);
		x = min(x, fun_x - width);
	}
	else
	{
		srand(time(NULL));
		int typ = rand() % 2;
		if(typ == 0)
		{
			sleep = 1;
			int addsh = rand() % 2;
			if(addsh == 0)
			{
				addsh = rand() % 2;
				if(addsh == 0)
				{
					shoot[addsh] = 1;
					shoot[0] = 2;
				}
				else if(addsh == 1)
				{
					shoot[addsh] = 1;
					shoot[1] = 2;
					angle = 0.0;
				}
			}
			else if(addsh == 1)
			{
				if((rand() % 3) == 0)
					for(i = 0; i < 5; i++)
					{
						shooters[i].exist = 1;
						shooters[i].hp = 1;
					}
				sleep = 0;
			}
		}
		else if(typ == 1)
		{
			srand(time(NULL));
			move = 4 + rand() % 6;
			if(rand() % 2)
				move_flag = 1;
			else
				move_flag = -1;
		}
		
	}
}

void enemyplane2::addshoot0()
{
	double shotx = x + width / 2;
	double shoty = y + height / 2;
	for(angle = 0.0; angle < 2 * 3.1415926; angle += 3.1415926 / 8)
	{
		enshot.add(shotx, shoty, 3.0 * cos(angle), 3.0 * sin(angle), 2);
		enshot2.add(shotx, shoty, 3.0 * cos(angle), 3.0 * sin(angle), 2);
	}

	shoot[0]--;
	if(!shoot[0])
		sleep = 0;
}

void enemyplane2::addshoot1()
{
	double shotx = x + width / 2;
	double shoty = y + height / 2;

	if(angle >= 2 * 3.1415926)
	{
		angle = 0.0;
		shoot[1]--;
		if(!shoot[1])
			sleep = 0;
		return ;
	}
	enshot.add(shotx, shoty, 3.0 * cos(angle), 3.0 * sin(angle), 3);
	enshot.add(shotx, shoty, 3.0 * cos(angle + PI / 2), 3.0 * sin(angle + PI / 2), 3);
	enshot.add(shotx, shoty, 3.0 * cos(angle + PI), 3.0 * sin(angle + PI), 3);
	enshot.add(shotx, shoty, 3.0 * cos(angle - PI / 2), 3.0 * sin(angle - PI / 2), 3);
	
	angle += PI / 8;
}

void enemyplane2::addshoot2()
{
//	addshooter();
}

void enemyplane2::hurt()
{
	hp -= 1;
}

void enemyplane2::show()
{
	SelectObject(bufdc, bmp[fla]);
	TransparentBlt(mdc, x, y, width, height,   
		bufdc, 0, 0, 
		width, height, RGB(0, 123, 139));
}