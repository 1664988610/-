#ifndef MAN_H  /*���û�ж���XXX_H*/
#define MAN_H  /*����XXX_HΪ���ַ���*/

#include "sa.h"

class man
{
public:
	int x, y, gx, gy;
	int dir, gdir;
	int fla, gfla;
	int tpre, gtpre;
	int sleep, gsleep;
	int pttx, gpttx;
	int ptty, gptty;
	int ptx, gptx;
	int pty, gpty;

	int nHp;
	int	fHp;
	int	lv;
	int	w;
	int	kind;
	int protect;
	bool hurt(int x);
	void addHp(int x);
};

#endif