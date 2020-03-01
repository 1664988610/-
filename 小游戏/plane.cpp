#include "plane.h"
#include "myshooter.h"

extern int fun_x, fun_y;
extern HDC mdc, bufdc;
extern shots myshot, enshot;
extern shot2s enshot2;
extern DWORD tNow;
extern int gameover;
extern man man;
extern HWND hwnd;
extern int _fun_2, _fun;
extern myshooters myshooters;
const double PI = 3.1415926;

plane::plane()
{
	bmp = (HBITMAP)LoadImage(NULL, "hero-.bmp", IMAGE_BITMAP, 0, 0,LR_LOADFROMFILE);
	_bmp = (HBITMAP)LoadImage(NULL, "hero_.bmp", IMAGE_BITMAP, 0, 0,LR_LOADFROMFILE);

	BITMAP bitmap;
	GetObject(bmp, sizeof(bitmap), &bitmap);
	width = bitmap.bmWidth / 8.0;
	height = bitmap.bmHeight / 3.0;
}

void plane::init()
{
	t_skill = tNow;
	tskill = 5000;
	td = 200;
	skill = 0;
	tpre_fla = tNow;
	t_fla = 50;
	tpre = tNow;
	hp = man.nHp;
	lv = man.lv;
	x = fun_x / 2;
	y = fun_y / 5 * 4;
	t_protect = tNow;

	count = 0;
	flag_protect = 0;
	fla = 1;
	mov_f = 5.0;
}

void plane::show()
{
	if(skill)
	{
		SelectObject(bufdc, _bmp);
		TransparentBlt(mdc, x, y, width, height,   
			bufdc, fla * width, dir * height, 
			width, height, RGB(255, 255, 255));
	}
	else
	{
		SelectObject(bufdc, bmp);
		TransparentBlt(mdc, x, y, width, height,   
			bufdc, fla * width, dir * height, 
			width, height, RGB(255, 255, 255));
	}
}

void plane::perform()
{
	if(tNow - t_skill > tskill && skill)
	{
		enshot.l = enshot.r;
		enshot2.l = enshot2.r;
		skill = 0;
	}
	int flag = 0;
	if(GetAsyncKeyState(VK_LEFT))
	{
		x = max(0, x - mov_f);
		flag++;
	}
	if(GetAsyncKeyState(VK_RIGHT))
	{
		x = min(fun_x - width, x + mov_f);
		flag--;
	}
	if(GetAsyncKeyState(VK_UP))
	{
		y = max(0, y - mov_f);
	}
	if(GetAsyncKeyState(VK_DOWN))
	{
		y = min(fun_y - height, y + mov_f);
	}
	if(flag == -1)
	{
		if(dir == 2 && tNow - tpre_fla > t_fla)
		{
			tpre_fla = tNow;
			fla = fla + 1;
			if(fla == 8)
			{
				fla = 4;
			}
		}
		else if(dir != 2)
		{
			dir = 2;
			fla = 0;
		}
	}
	else if(!flag)
	{
		if(dir == 0 && tNow - tpre_fla > t_fla)
		{
			tpre_fla = tNow;
			fla = (fla + 1) % 8;
		}
		else if(dir != 0)
		{
			dir = 0;
			fla = 0;
		}
	}
	else
	{
		if(dir == 1 && tNow - tpre_fla > t_fla)
		{
			tpre_fla = tNow;
			fla = fla + 1;
			if(fla == 8)
			{
				fla = 4;
			}
		}
		else if(dir != 1)
		{
			dir = 1;
			fla = 0;
		}
	}

	if(GetAsyncKeyState(VK_SPACE))
	{
		count++;
		if(count >= 3)
		{
			
			count = 0;
			if(_fun)
			{
			//	if(shoo(tNow))
			//	{
					myshooters.shoot();
					myshot.add(x + width / 2 + 8, y + height / 2, 0, -myshot._height / 2, 9);
					myshot.add(x + width / 2 - 8, y + height / 2, 0, -myshot._height / 2, 9);
			//	}
			}
			else if(_fun_2)
			{
			//	if(shoo(tNow))
		//		{
					myshooters.shoot();
					myshot.add(x + width / 2 + 8, y + height / 2, 0, -myshot._height / 2, 9);
					myshot.add(x + width / 2 - 8, y + height / 2, 0, -myshot._height / 2, 9);
				//	myshot.add(x + width / 2, y + height / 2, 10 * sin(PI / 12.0), -10 * cos(PI / 12.0), 8);
				//	myshot.add(x + width / 2, y + height / 2, -10 * sin(PI / 12.0), -10 * cos(PI / 12.0), 8);
		//		}
			}
		}
	}

	if(GetAsyncKeyState(VK_SHIFT))
	{
		if(!skill && myshooters.num)
		{
			myshooters.num--;
			t_skill = tNow;
			skill = 1;
		}
	}
}

bool plane::shoo(DWORD t)
{
	if(t - tpre > td)
	{
		tpre = t;
		return 1;
	}
	return 0;
}

bool plane::hurt(DWORD t)
{
	if(skill == 0)
		if(t - t_protect > 2000)
		{
			myshooters.num = 0;
			PlaySound("explosion.wav", NULL,SND_ASYNC|SND_NODEFAULT|SND_FILENAME);
			hp -= 1;
			x = fun_x / 2;
			y = fun_y / 5 * 4;
			t_protect = t;
			if(hp <= 0)
			{
				gameover = 1;
			}
			return 1;
		}
	return 0;
}
