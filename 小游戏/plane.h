#ifndef PLANE_H  /*如果没有定义XXX_H*/
#define PLANE_H  /*定义XXX_H为空字符串*/

#include "sa.h"
#include "shot.h"
#include "man.h"

class plane
{
public:

	double x;
	double y;
	int fla;
	int status;
	int hp;
	int lv;
	double mov_f;

	int num_shooter;

	DWORD t_fla;
	DWORD tpre_fla;

	int flag_protect;

	DWORD t_protect;

	DWORD td;
	DWORD tpre;
	DWORD t_skill, tskill;

	int dir;
	HBITMAP bmp, _bmp;
	bool skill;
	double width, height;
	int count;
	void init();
	plane();
	void show();
	void perform();
	bool shoo(DWORD t);
	bool hurt(DWORD t);
	void addshooter();

};


#endif