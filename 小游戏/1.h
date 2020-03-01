#include "sa.h"
#include "map.h"
#include "wind.h"
#include "man.h"
#include "shot.h"
#include "plane.h"
#include "enemyplane.h"
#include "crash.h" 
#include "protect.h"
#include "item.h"
#include "myshooter.h"

void msginsert(char* str);
void msgdel();

bool moves();

class bf_step
{
public:
	int x, y, r;
	bf_step(){
		x = 0;
		y = 0;
		r = 0;
	};
	bf_step(int ax, int ay, int ar):x(ax), y(ay), r(ar){}
};

class chr
{
public:

	int		nHp;
	int		fHp;
	int		lv;
	int		w;
	int		kind;
	int		type;
};


bool bfs(int ptx, int pty, int pttx, int ptty);
bool isroute(int ptx, int pty, int pttx, int ptty);
long WINAPI WndProc(HWND hwnd,
					UINT iMessage,
					UINT wParam,
					LONG lParam);
//void DrawBitmap(HINSTANCE, HDC, int, int, int, int);
BOOL InitWindowsClass(HINSTANCE hInstance);		
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);
void mypaint(HDC hdc);
void init();
void func(int x);
void fun1();
void init_fun1();
void fun2();
void init_fun2();
void init_fun3();
void fun3();
void fun_menu();
void init_fun_menu();
void init_fun();
void fun();
void init_fun_2();
void fun_2();
void fun_gameover();
void initgameover();
