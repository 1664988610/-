#ifndef PROTECT_H  /*���û�ж���XXX_H*/
#define PROTECT_H  /*����XXX_HΪ���ַ���*/

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