#include "man.h"

bool man::hurt(int x)
{
	if(!protect)
	{
		nHp -= x;
		return 1;
	}
	return 0;
}

void man::addHp(int x)
{
	nHp += x;
	if(nHp > fHp)
		nHp = fHp;
}