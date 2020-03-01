#ifndef SHOT_H  /*如果没有定义XXX_H*/
#define SHOT_H  /*定义XXX_H为空字符串*/

#include "sa.h"
#include "crash.h"
#include "plane.h"
#include "enemyplane.h"

class shot
{
public:
	double x;
	double y;
	double sx;
	double sy;
	bool exist;
	int type;
	shot();
	shot(double nx, double ny, double nsx, double nsy);
	bool out();
	void move();
};


class shots
{
public:
	shot sh[1000];
	int l, r;
	HBITMAP bmp[11];
	double height, width;
	double _height, _width;
	bool hero;
	shots();
	void decl();
	void add(shot k);
	void add(double nx, double ny, double nsx, double nsy, int type);
	void perform();
	void init();
	
};

class shot2
{
public:
	double x;
	double y;
	double sx;
	double sy;
	double r;
	double rx, ry;
	double angle, angle_move;
	bool exist;
	int type;
	shot2();
	shot2(double nx, double ny, double nsx, double nsy);
	bool out();
	void move();
};

class shot2s
{
public:
	shot2 sh[1000];
	int l, r;
	bool hero;
	HBITMAP bmp[9];
	double height, width;
	shot2s();
	void decl();
	void add(double nx, double ny, double nsx, double nsy, int type);
	void perform();
	void init();
};
#endif