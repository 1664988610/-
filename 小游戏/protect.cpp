#include "protect.h"

extern DWORD tNow;
extern plane myplane;
extern HDC mdc, bufdc;

protect::protect()
{
	int i;
	char filename[40];
	for(i = 0; i < 30; i++)
	{
		if(i < 10)
		{
			sprintf(filename,"spellBulletCa00%d.bmp", i);
			bmp[i] = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}
		else
		{
			sprintf(filename,"spellBulletCa0%d.bmp", i);
			bmp[i] = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}
	}

	BITMAP bitmap;
	GetObject(bmp[1], sizeof(bitmap), &bitmap);
	width = bitmap.bmWidth;
	height = bitmap.bmHeight;
}

void protect::show()
{
	if(tNow - myplane.t_protect < 2000)
	{
		SelectObject(bufdc, bmp[myplane.flag_protect]);
		TransparentBlt(mdc, myplane.x - (width - myplane.width) / 2 + 1, myplane.y - (height - myplane.height) / 2 + 2, width, height,   
			bufdc, 0, 0, 
			width, height, RGB(0, 0, 0));
		myplane.flag_protect = (myplane.flag_protect + 1) % 30;
	}
}