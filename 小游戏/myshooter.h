#ifndef MYSHOOTER_H  /*如果没有定义XXX_H*/
#define MYSHOOTER_H  /*定义XXX_H为空字符串*/

#include "sa.h"

class myshooters
{
public:
	int num;
	double r;
	double angle;
	HBITMAP bmp;
	double width;
	double height;
	myshooters();
	void shoot();
	void addshooter();
	void perform();
	void show();
	bool delc();
	void init();
};

#endif