#ifndef ITEM_H  /*���û�ж���XXX_H*/
#define ITEM_H  /*����XXX_HΪ���ַ���*/

#include "sa.h"
#include "plane.h"

extern RECT rect1, rect2, impact;

class item
{
public:
	double x, y, sx, sy;
	int type;
	bool exist;
	item();
	item(double x, double y, double sx, double sy, int ntype);
	void move();
};

class items
{
public:
	int l, r;
	DWORD tpre, t_add;
	item ite[100];
	HBITMAP bmp[10];
	double width, height;
	items();
	void init();
	void additem(double x, double y, double sx, double sy, int ntype);
	void perform();
	void delc();
	void show();

};

#endif