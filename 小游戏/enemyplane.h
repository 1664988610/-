#ifndef ENEMYPLANE_H  /*如果没有定义XXX_H*/
#define ENEMYPLANE_H  /*定义XXX_H为空字符串*/

#include "sa.h"
#include "shot.h"
#include "shooter.h"

class enemyplane
{
public:

	int fhp;
	double x;
	double y;
	int fla;
	int status;
	int hp;
	int lv;
	int move, sleep;
	int typenum;
	double angle;
	int shoot[10];
	HBITMAP bmp[8];
	double width, height;
	DWORD td;
	DWORD tpre;
	DWORD tpre2;
	DWORD t2;
	DWORD tpre1;
	DWORD t1;
	int move_flag;

	shooter shooters[5];

	int t_fla;
	int tpre_fla;

	void init();
	enemyplane();
	void perform();
	void addshoot0();
	void addshoot1();
	void addshoot2();
	void hurt();
	void show();
};

class enemyplane2
{
public:

	double x;
	double y;
	int fhp;
	int fla;
	int status;
	int hp;
	int lv;
	int move, sleep;
	int typenum;
	double angle;
	int shoot[10];
	DWORD td;
	DWORD tpre;
	DWORD tpre2;
	DWORD t2;
	DWORD tpre1;
	DWORD t1;
	int move_flag;
	HBITMAP bmp[10];
	double height, width;
	int move_step;

	shooter shooters[5];

	int t_fla;
	int tpre_fla;

	void init();
	enemyplane2();
	void perform();
	void addshoot0();
	void addshoot1();
	void addshoot2();
	void hurt();
	void show();
};

#endif