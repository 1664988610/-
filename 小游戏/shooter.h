#ifndef SHOOTER_H  /*如果没有定义XXX_H*/
#define SHOOTER_H  /*定义XXX_H为空字符串*/

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