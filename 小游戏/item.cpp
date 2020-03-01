#include "item.h"
#include "myshooter.h"

extern HDC mdc, bufdc;
extern DWORD tNow;
extern int fun_x, fun_y;
extern plane myplane;
extern HWND hwnd;
extern myshooters myshooters;


item::item()
{}

item::item(double nx, double ny, double nsx, double nsy, int ntype)
{
	x = nx;
	y = ny;
	sx = nsx;
	sy = nsy;
	type = ntype;
	exist = 1;
}

void item::move()
{
	x += sx;
	y += sy;
}


items::items()
{}

void items::init()
{
	l = 0;
	r = 0;
	tpre = tNow;
	t_add = 5000;

	bmp[0] = (HBITMAP)LoadImage(NULL, "item_p.bmp", IMAGE_BITMAP, 0, 0,LR_LOADFROMFILE);

	BITMAP bitmap;
	GetObject(bmp[0], sizeof(bitmap), &bitmap);
	width = bitmap.bmWidth;
	height = bitmap.bmHeight;
}
void items::additem(double nx, double ny, double nsx, double nsy, int ntype)
{
	item a(nx, ny, nsx, nsy, ntype);
	int k = r + 1;
	k %= 100;
	if(k != l)
	{
		ite[r] = a;
		r = k;
	}
}

void items::perform()
{
	if(tNow - tpre > t_add)
	{
		tpre = tNow;
		additem(rand() % (int)(fun_x - width), -20, 0, 2, 0);
	}
	int i;
	for(i = l; i != r; )
	{	
		if(ite[i].exist)
		{
			SetRect(&rect2, ite[i].x, ite[i].y, 
				ite[i].x + width, ite[i].y + height); 
			IntersectRect(&impact, &rect1, &rect2);
			if(!IsRectEmpty(&impact))
			{
				ite[i].exist = 0;

				myshooters.addshooter();
			}
			else
			{
				SelectObject(bufdc, bmp[ite[i].type]);
				TransparentBlt(mdc, ite[i].x, ite[i].y, width, height,   
					bufdc, 0, 0, 
					width, height, NULL);
			/*	char str[100];
				sprintf(str, "%d %lf", fun_x, width);
				MessageBox(hwnd, str, "result", MB_OK);	*/
			}
			
		}
		ite[i].move();
		i = (i + 1) % 100;
	}
}

void items::show()
{
	int i;
	for(i = l; i != r;)
	{
		SelectObject(bufdc, bmp[ite[i].type]);
		TransparentBlt(mdc, ite[i].x, ite[i].y, width, height,   
			bufdc, 0, 0, 
			width, height, NULL);
		
		i = (i + 1) % 100;
	}
	
}

void items::delc()
{
	while(l != r && ite[l].y >= fun_y + height)
	{
		l = (l + 1) % 100;
	}
}