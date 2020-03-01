#include "shooter.h"
#include "shot.h"
#include "crash.h"

extern DWORD tNow;
extern shots myshot, enshot;
extern crashs crashs;
extern HDC mdc, bufdc;

shooter::shooter()
{
	
	char filename[30];
	int i;
	for(i = 0; i < 10; i++)
	{
		sprintf(filename,"spellBulletF%d00%d.bmp", type, i);
		bmp[i] = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}

	BITMAP bitmap;
	GetObject(bmp[1], sizeof(bitmap), &bitmap);
	width = bitmap.bmWidth;
	height = bitmap.bmHeight;

}

void shooter::init()
{
	exist = 0;
	hp = 1;
	t_sleep = 200;
	tpre = 0;

	t_pre_shoot = 0;
	t_shoot = 2000;

	type = rand() % 5 + 1;

	flash = 0;
}

void shooter::setplace(double nx, double ny)
{
	x = nx;
	y = ny;
}

void shooter::perform()
{
	if(exist)
	{
		
		if(tNow - t_pre_shoot > t_shoot)
		{
			t_pre_shoot = tNow;
			double angle;
			double shotx = x + width / 2;
			double shoty = y + height / 2;
			for(angle = 0.0; angle < 2 * 3.1415926; angle += 3.1415926 / 8)
			{
				enshot.add(shotx, shoty, 3.0 * cos(angle), 3.0 * sin(angle), 2);
			}
		}

		RECT rect1, rect2, impact;
		SetRect(&rect1, x + width / 4, y + height / 4, 
			x + width / 4 * 3, y + height / 4 * 3);
		int i, j;

		for(i = myshot.l; i != myshot.r;)
		{
			if(myshot.sh[i].exist)
			{
				SetRect(&rect2, myshot.sh[i].x + myshot.width / 4, myshot.sh[i].y + myshot.height / 4, 
					myshot.sh[i].x + myshot.width / 4 * 3, myshot.sh[i].y + myshot.height / 4 * 3); 
				IntersectRect(&impact, &rect1, &rect2);
				if(!IsRectEmpty(&impact))
				{
					myshot.sh[i].exist = 0;
					hurt();
					crash a(myshot.sh[i].x + myshot.width / 2, myshot.sh[i].y + myshot.height / 2);
					crashs.addcrash(a);
				}
			}
			i = (i + 1) % 1000;
		}
		SelectObject(bufdc, bmp[flash]);  
		TransparentBlt(mdc, x, y, width, height,   
			bufdc, 0, 0, 
			width, height, RGB(0, 0, 0));
		if(tNow - tpre > t_sleep)
		{
			tpre = tNow;
			flash = (flash + 1) % 10;
		}

	}
}

void shooter::hurt()
{
	hp--;
	if(hp == 0)
	{
		PlaySound("explosion.wav", NULL,SND_ASYNC|SND_NODEFAULT|SND_FILENAME);
		exist = 0;
	}
}