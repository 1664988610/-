#include "crash.h"

extern HWND hwnd;
extern HDC mdc, bufdc;

crash::crash(int nx, int ny)
{
	x = nx;
	y = ny;
	flash = 0;
}

crashs::crashs()
{
	char filename[40];
	int i;
	for(i = 0; i < 10; i++)
	{
		sprintf(filename,"explode%d.bmp", i);
		bmp[i] = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	}
	HBITMAP _crash_bmp = (HBITMAP)LoadImage(NULL, "spellBulletCa000.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	BITMAP bitmap;
	GetObject(_crash_bmp, sizeof(bitmap), &bitmap);
	_width = bitmap.bmWidth / 2;
	_height = bitmap.bmHeight / 2;

	GetObject(bmp[1], sizeof(bitmap), &bitmap);
	width = bitmap.bmWidth;
	height = bitmap.bmHeight;

	
}

void crashs::init()
{
	l = 0;
	r = 0;
}


void crashs::addcrash(crash a)
{
	int k;
	k = r + 1;
	k %= 20;
	if(k != l)
	{
		cra[r].flash = a.flash;
		cra[r].x = a.x - _width / 2;
		cra[r].y = a.y - _height / 2;
		r = k;
	}
	
}

void crashs::show()
{
	int i;
	for(i = l; i != r;)
	{	
		if(cra[i].flash < 10)
		{
			SelectObject(bufdc, bmp[cra[i].flash]);

			TransparentBlt(mdc, cra[i].x, cra[i].y, _width, _height,   
				bufdc, 0, 0, 
				width, height, RGB(255, 255, 255));
		}
		cra[i].flash++;
		i = (i + 1) % 20;
	}
}

void crashs::delc()
{
	while(cra[l].flash == 10 && l != r)
	{
		l++;
		l %= 20;
	}
}