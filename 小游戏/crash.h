#ifndef CRASH_H
#define CRASH_H 


#include "sa.h"


class crash
{
public:
	int x;
	int y;
	int flash;
	crash()
	{}
	
	crash(int nx, int ny);
};

class crashs
{
public:
	int l, r;
	crash cra[22];
	crashs();
	void addcrash(crash k);
	void show();
	void init();
	double width, height;
	double _width, _height;

	HBITMAP bmp[10];

	void delc();
};


#endif  