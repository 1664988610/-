#include "myshooter.h"
#include "plane.h"
#include "shot.h"

extern HDC mdc, bufdc;
extern plane myplane;
const double PI = 3.1415926;
extern shots myshot, enshot;

myshooters::myshooters()
{

	bmp = (HBITMAP)LoadImage(NULL, "myshooter.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	BITMAP bitmap;
	GetObject(bmp, sizeof(bitmap), &bitmap);
	width = bitmap.bmWidth;
	height = bitmap.bmHeight;
}

void myshooters::init()
{
	num = 0;
	r = 60.0;
	angle = 0;
}

void myshooters::addshooter()
{
	num = min(num + 1, 4);
}

void myshooters::show()
{
	SelectObject(bufdc, bmp);
	
	double kl = (2.0 * PI) / num;
	int i;
	for(i = 0; i < num; i++)
	{
		
		TransparentBlt(mdc, myplane.x - (width - myplane.width) / 2 + r * sin(angle + i * kl), 
			myplane.y - (height - myplane.height) / 2  + r * cos(angle + i * kl), width, height,   
			bufdc, 0, 0, 
			width, height, RGB(255, 255, 255));
	}
}

void myshooters::perform()
{
	angle += (PI / 24);
	if(angle > PI * 2)
	{
		angle -= PI * 2;
	}
	show();
}

void myshooters::shoot()
{
	double kl = (2.0 * PI) / num;
	int i;
	for(i = 0; i < num; i++)
	{
		myshot.add(myplane.x + myplane.width / 2 + r * sin(angle + i * kl), myplane.y + myplane.height / 2  + r * cos(angle + i * kl),
			0, -myshot._height / 2, 9);
	}
}

bool myshooters::delc()
{
	if(num)
	{
		num--;
		return 1;
	}
	else
		return 0;
}
