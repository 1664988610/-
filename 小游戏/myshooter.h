#ifndef MYSHOOTER_H  /*���û�ж���XXX_H*/
#define MYSHOOTER_H  /*����XXX_HΪ���ַ���*/

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