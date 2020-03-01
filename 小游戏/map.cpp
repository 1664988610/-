#include "map.h"

//1 未知
//0 空地
//2 出口

map::map(int nmap_nx, int nmap_ny)
{
	int i, j;
	map_nx = nmap_nx;
	map_ny = nmap_ny;
	/*for(i = 0; i < map_nx; i++)
	{
		for(j = 0; j < map_ny; j++)
		{
			map_index[i][j] = nmap[i][j];
		}
	}
	dir[0][0] = 1; dir[0][1] = 0;
	dir[1][0] = 0; dir[1][1] = 1;
	dir[2][0] = -1; dir[2][1] = 0;
	dir[3][0] = 0; dir[3][1] = -1;
	*/
	dir[0][0] = 0; dir[0][1] = 1;
	dir[1][0] = 1; dir[1][1] = 0;
	dir[2][0] = 0; dir[2][1] = -1;
	dir[3][0] = -1; dir[3][1] = 0;
	
	
	/*case 's':
				{
					i = 0;
					break;
				}
				case 'd':
				{
					i = 1;
					break;
				}
				case 'w':
				{
					i = 2;
					break;
				}
				case 'a':
				{
					i = 3;
					break;
				}
				*/
	road_l = 0;
	move_l = 1;
}

void map::update_map(int nmap[10][10])
{
	int i, j;
	for(i = 0; i < map_nx; i++)
	{
		for(j = 0; j < map_ny; j++)
		{
			map_index[i][j] = nmap[i][j];
		}
	}
}

//dir  st1
bool map::bfs(int ptx, int pty, int pttx, int ptty)
{
	int flag;
	int l = 0;
	int r = 1;
	int round = 0;
	st1 road[430];

	st1 a(pttx, ptty, round);
	road[0] = a;
	while(l <= r)
	{
		flag = 1;
		a = road[l++];
		if(a.x == ptx && a.y == pty)
		{
//			char str[100];
//			sprintf(str, "%d %d %d", a.x, a.y, a.r);
//			MessageBox(hWnd, str, "result", MB_OK);
			return 1;
		}
		a.r++;
		for(int i = 0; i < 4; i++)
		{
			if(a.x + dir[i][0] >= 0 && a.x + dir[i][0] < map_nx && a.y + dir[i][1] >= 0 && a.y + dir[i][1] < map_ny)
			{
				if(!m1[a.x + dir[i][0]][a.y + dir[i][1]])
				{
					a.x += dir[i][0];
					a.y += dir[i][1];
					m1[a.x][a.y] = a.r;
					road[r++] = a;
					r %= 420;
					a.x -= dir[i][0];
					a.y -= dir[i][1];
				}
			}
		}
	
	}
	return 0;
}

bool map::isroute(int ptx, int pty, int pttx, int ptty)
{
	for(int i = 0; i < map_nx; i++)
	{
		for(int j = 0; j < map_ny; j++)
		{
			if(map_index[i][j] != way_index)
				m1[i][j] = 1000;
			else
				m1[i][j] = 0;
		}
	}
	return bfs(ptx, pty, pttx, ptty);
}

//move_l  road_l  road1[ro]  m1[x][y]
void map::getro(int ptx, int pty)
{
	move_l = 1;//////////////////////////////////////////////////////////////////////////////////
//	char str[100];
	
	int x = ptx;
	int y = pty;

	int ro = m1[x][y];

//	sprintf(str, "%d %d %d", x, y, ro);
//	MessageBox(hWnd, str, "result", MB_OK);
	road_l = ro;

	road1[ro].x = x;
	road1[ro--].y = y;
	while(ro != 0)
	{
		for(int i = 0; i < 4; i++)
		{
			if(x + dir[i][0] >= 0 && x + dir[i][0] < map_nx && y + dir[i][1] >= 0 && y + dir[i][1] < map_ny)
				if(m1[x + dir[i][0]][y + dir[i][1]] == ro)
				{
					x = x + dir[i][0];
					y = y + dir[i][1];
					road1[ro].x = x;
					road1[ro--].y = y;
					break;
				}
		}
	}

	//sprintf(str, "%d %d", ptt.x, ptt.y);
	//MessageBox(hWnd, str, "result", MB_OK);
}