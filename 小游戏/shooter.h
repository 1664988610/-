#ifndef SHOOTER_H  /*���û�ж���XXX_H*/
#define SHOOTER_H  /*����XXX_HΪ���ַ���*/

#include "sa.h"

class shooter
{
public:
	int before;
	double x, y;
	bool exist;
	int hp;
	DWORD tpre;
	DWORD t_sleep;
	DWORD t_pre_shoot,t_shoot;
	int flash;
	int type;
	double width, height;
	HBITMAP bmp[10];
	shooter();
	void setplace(double nx, double ny);
	void perform();
	void hurt();
	void init();
};

#endif