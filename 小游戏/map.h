#ifndef MAP_H  /*如果没有定义XXX_H*/
#define MAP_H  /*定义XXX_H为空字符串*/

#include "sa.h"

class map{
public:
	int map_nx, map_ny;
	int m1[30][30];
	int way_index;
	int map_index[30][30];
	POINT road1[400];
	int move_l, road_l;
	int dir[4][2];

	map(int nmap_nx, int nmap_ny);
	bool bfs(int ptx, int pty, int pttx, int ptty);
	bool isroute(int ptx, int pty, int pttx, int ptty);
	void getro(int ptx, int pty);
	void update_map(int nmap[10][10]);

private:

};

class st1
{
public:
	int x, y, r;
	st1(){
		x = 0;
		y = 0;
		r = 0;
	};
	st1(int ax, int ay, int ar):x(ax), y(ay), r(ar){}
};

#endif         /*结束判断*/