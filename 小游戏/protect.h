#ifndef PROTECT_H  /*如果没有定义XXX_H*/
#define PROTECT_H  /*定义XXX_H为空字符串*/

#include "sa.h"
#include "plane.h"

class protect
{
public:
	double width;
	double height;

	HBITMAP bmp[30];
	protect();
	void show();

};

#endif