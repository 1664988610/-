#include "shot.h"


extern int fun_x;
extern int fun_y;
extern HWND hwnd;
extern HDC mdc, bufdc;
extern RECT rect1, rect2, impact;
extern plane myplane;
extern enemyplane enemy;
extern enemyplane2 enemy2;
extern int win, gameover;
extern DWORD tNow;
extern crashs crashs;
extern int _fun_2, _fun;
const double PI = 3.1415926;

shot::shot()
{
	exist = 1;
}

shot::shot(double nx, double ny, double nsx, double nsy):x(nx), y(ny), sx(nsx), sy(nsy)
{
	exist = 1;
}
bool shot::out()
{
	if(x < 0 || x > fun_x || y < 0 || y > fun_y || exist == 0)
	{
		
		return 1;
	}
	return 0;
}

void shot::move()
{
	x += sx;
	y += sy;
}

shots::shots()
{
	
	char filename[30];
	int i;
	for(i = 0; i < 9; i++)
	{
		sprintf(filename,"BulletAb00%d.bmp",i);
		bmp[i] = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}

	bmp[9] = (HBITMAP)LoadImage(NULL, "bullet00.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bmp[10] = (HBITMAP)LoadImage(NULL, "bullet01.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	BITMAP bitmap;
	GetObject(bmp[1], sizeof(bitmap), &bitmap);
	width = bitmap.bmWidth;
	height = bitmap.bmHeight;

	GetObject(bmp[9], sizeof(bitmap), &bitmap);
	_width = bitmap.bmWidth;
	_height = bitmap.bmHeight;

	GetObject(bmp[10], sizeof(bitmap), &bitmap);
	_width = bitmap.bmWidth;
	_height = bitmap.bmHeight;


}

void shots::init()
{
	l = 0;
	r = 0;
}

void shots::decl()
{
	while(sh[l].out() && l != r)
	{
		l = (l + 1) % 1000;
	}
}
void shots::add(double nx, double ny, double nsx, double nsy, int type)
{
	shot a(nx - width / 2, ny - height / 2, nsx, nsy);
	a.type = type;
	if(type >= 9)
	{
		a.x = nx - _width / 2;
		a.y = ny - _height / 2;
	}
	
	int kk = (r + 1) % 1000;
	if(kk != l)
	{
		sh[r] = a;
		r = kk;
	}
}

void shots::perform()
{
	int i;
	for(i = l; i != r; )
	{	
		if(sh[i].exist)
		{
			if(sh[i].type >= 9)
			{
				SetRect(&rect2, sh[i].x, sh[i].y, 
					sh[i].x + _width, sh[i].y + _height); 
			}
			else
				SetRect(&rect2, sh[i].x + width / 4, sh[i].y + height / 4, 
					sh[i].x + width / 4 * 3, sh[i].y + height / 4 * 3); 
			IntersectRect(&impact, &rect1, &rect2);
			if(!IsRectEmpty(&impact))
			{
				
				sh[i].exist = 0;
				if(hero == 0)
				{
					myplane.hurt(tNow);
				}
				else
				{
					if(_fun)
					{
						enemy.hurt();
						if(enemy.hp <= 0)
						{
							PlaySound("explosion.wav", NULL,SND_ASYNC|SND_NODEFAULT|SND_FILENAME);
						}
					}
					else if(_fun_2)
					{
						enemy2.hurt();
						if(enemy2.hp <= 0)
						{
							PlaySound("explosion.wav", NULL,SND_ASYNC|SND_NODEFAULT|SND_FILENAME);
							gameover = 1;
							win = 1;
						}
					}
				}
				
				crash a(sh[i].x + width / 2, sh[i].y + height / 2);
				crashs.addcrash(a);
			}
			else
			{
				SelectObject(bufdc, bmp[sh[i].type]);
				if(sh[i].type < 9)
					TransparentBlt(mdc, sh[i].x, sh[i].y, width, height,   
						bufdc, 0, 0, 
						width, height, RGB(0, 0, 0));
				else
					TransparentBlt(mdc, sh[i].x, sh[i].y, _width, _height,   
						bufdc, 0, 0, 
						_width, _height, RGB(255, 255, 255));
				sh[i].move();
			}
			
		}
		
		i = (i + 1) % 1000;
	}
}
////////////////////////////////////////////////////////////////////////////////////////



shot2::shot2()
{}

shot2::shot2(double nx, double ny, double nsx, double nsy):x(nx), y(ny), sx(nsx), sy(nsy)
{
	exist = 1;
	r = 50;
	angle_move = PI / 20.0;
}
bool shot2::out()
{
	if(x < -r || x > fun_x + r || y < -r || y > fun_y + r || exist == 0)
	{
		return 1;
	}
	return 0;
}

void shot2::move()
{
	x += sx;
	y += sy;
	angle += angle_move;
	rx = x + sin(angle) * r;
	ry = y + cos(angle) * r;
}
///////////////////////////////////////////////////////////////////////////////
shot2s::shot2s()
{

	char filename[30];
	int i;
	for(i = 0; i < 9; i++)
	{
		sprintf(filename,"BulletAb00%d.bmp",i);
		bmp[i] = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}

	BITMAP bitmap;
	GetObject(bmp[1], sizeof(bitmap), &bitmap);
	width = bitmap.bmWidth;
	height = bitmap.bmHeight;
}

void shot2s::init()
{
	l = 0;
	r = 0;
}

void shot2s::decl()
{
	while(sh[l].out() && l != r)
	{
		l = (l + 1) % 1000;
	}
}

void shot2s::add(double nx, double ny, double nsx, double nsy, int type)
{
	shot2 a(nx - width / 2, ny - height / 2, nsx, nsy);
	a.type = type;
	for(int i = 0; i < 4; i++)
	{
		a.angle = PI / 4 * (double)i;
		a.rx = a.x + cos(a.angle) * a.r;
		a.ry = a.y + cos(a.angle) * a.r;
		int kk = (r + 1) % 1000;
		if(kk != l)
		{
			sh[r] = a;
			r = kk;
		}
	}
}

void shot2s::perform()
{
	int i;
	for(i = l; i != r; )
	{	
		if(sh[i].exist)
		{
			SetRect(&rect2, sh[i].rx + width / 4, sh[i].ry + height / 4, 
				sh[i].rx + width / 4 * 3, sh[i].ry + height / 4 * 3); 
			IntersectRect(&impact, &rect1, &rect2);
			if(!IsRectEmpty(&impact))
			{
				sh[i].exist = 0;
				if(hero)
				{
				
				}
				else
				{
					myplane.hurt(tNow);
				}
				crash a(sh[i].rx + width / 2, sh[i].ry + height / 2);
				crashs.addcrash(a);
				
			}
			else
			{
				SelectObject(bufdc, bmp[sh[i].type]);
				TransparentBlt(mdc, sh[i].rx, sh[i].ry, width, height,   
					bufdc, 0, 0, 
					width, height, RGB(0, 0, 0));
				sh[i].move();
			}
			
		}
		
		i = (i + 1) % 1000;
	}
}