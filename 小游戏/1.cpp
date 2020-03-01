#include "1.h"
#include <string>
#include <vector>

using namespace std;

const int client_x = 640;
const int client_y = 640;
int _fun_x = 400;
int _fun_y = 600;
int fun_x, fun_y;
const int map_nx = 10;
const int map_ny = 10;
const int block_x = 64;
const int block_y = 64;
const int move = 10;
const double PI = 3.1415926;

PAINTSTRUCT ps;		
HPEN hpen;			
HBRUSH hbrush;
HFONT hf;
TEXTMETRIC tm;
HWND hwnd;	
HDC		hdc,mdc,bufdc,maskdc;
POINT    pt, now;  
HBITMAP fullmap;
DWORD	tPre,tNow;
RECT rect1, rect2, impact;
char music_buffer[256];  

///////////////////////////////////////////

bool over1, over2;

int _fun1, _fun2, _fun3, menu, _fun, _fun_2;
//1 monster
//2 hp
//3 out
//4 bonus1
int gameover;
int _gameover, gameover_choice;
int gameover_choices;
HBITMAP bg_gameover, gamewin_bmp[2];
HBITMAP menu_bmp[2];

double bg_gameover_width, bg_gameover_height, bg_menu_width, bg_menu_height;
int win;

int exit_;
int exit_x, exit_y;

//////////////////////////////////////////////////

int text_t;
char text[5][100];
int txtnum;

//////////////////////////////////////////////////////////////////


HBITMAP map_block[10], man_bmp;
int map_num;
int _map1[map_nx][map_ny] = {
	{4, 1, 0, 0, 0, 1, 0, 0, 1, 0},
	{3, 0, 2, 0, 0, 0, 2, 0, 0, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
	{0, 0, 0, 1, 2, 1, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
	{1, 0, 0, 2, 0, 1, 0, 0, 0, 0},
	{0, 0, 2, 1, 0, 0, 0, 0, 1, 1},
	{1, 0, 0, 0, 0, 1, 2, 0, 0, 0},
	{1, 0, 0, 1, 0, 1, 0, 0, 1, 0}
};

int _map2[map_nx][map_ny] = {
	{1, 0, 0, 2, 0, 1, 4, 3, 1, 3},
	{0, 0, 0, 1, 0, 0, 0, 0, 3, 1},
	{0, 2, 0, 2, 0, 3, 0, 0, 1, 1},
	{0, 0, 0, 1, 3, 1, 0, 0, 0, 0},
	{0, 4, 0, 0, 0, 4, 2, 0, 3, 0},
	{0, 2, 0, 0, 0, 1, 0, 0, 1, 0},
	{1, 0, 0, 2, 0, 1, 0, 4, 2, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 1, 1},
	{1, 0, 2, 4, 0, 1, 3, 0, 0, 0},
	{1, 0, 0, 1, 0, 1, 0, 0, 1, 0}
};

const int way_index = 0;

//int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}};

map map(map_nx, map_ny), map2(map_nx, map_ny), gmap(map_nx, map_ny);
man man;

HBITMAP out_bmp[6];
int out_flash;

//////////////////////////////////////////////////////////////

const int wind_num = 7;
wind1 wind1[wind_num];
wind2 wind2[wind_num];
wind3 wind3[wind_num];
wind4 wind4[wind_num];
int round_f2;

HBITMAP wind_bmp[12];

/////////////////////////////////////////////////////////////
chr		monster;
bool	attack,over;
int pNum, ff;
HBITMAP	bg1,sheep_bmp[2],girl,skill,skillult,slash,magic,recover,gameover_bmp, win_bmp;

///////////////////////////////////////////////////////

HBITMAP bg_menu;
int m_iSelectionMax = 2;
int m_iFocus = 0;
string m_MenuStrings[4];
string m_gameoverStrings[4];

////////////////////////////////////////////////////////

HBITMAP hero, bg_ame[12];
int bg_num;
double planeWidth;
double planeHeight;
double bulletWidth;
double bulletHeight;
int mov_f = 5;
plane myplane;
enemyplane enemy;
enemyplane2 enemy2;
shots enshot;
shots myshot;
shot2s enshot2;
HBITMAP bullet[9];
HBITMAP enemy_bmp[8];
double protectWidth;
double protectHeight;
double winWidth,winHeight;
HBITMAP protect_bmp[30], crash_bmp[10];
crashs crashs;
//double shooterWidth, shooterHeight;
HBITMAP hp_bmp;
double hpheight;
protect protect;
items items;
myshooters myshooters;

////////////////////////////////////////////////////////


int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow)
{
	MSG msg;
	 
	if(!InitWindowsClass(hInstance))
		return FALSE;
	if(!InitWindows(hInstance,nCmdShow))
		return FALSE;

	GetMessage(&msg,NULL,NULL,NULL);         

    while(msg.message!=WM_QUIT)
    {
        if( PeekMessage(&msg, NULL, 0,0 ,PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
		else
		{
			tNow = GetTickCount();
			if(tNow-tPre >= 40)
				mypaint(hdc);
		}
    }
	return msg.wParam;
}

BOOL InitWindows(HINSTANCE hInstance, int nCmdShow)
{
	hwnd=CreateWindow("my window",			
					"my window",	
					WS_OVERLAPPEDWINDOW,
					CW_USEDEFAULT,		
					0,
					CW_USEDEFAULT,	
					0,
					NULL,		
					NULL,			
					hInstance,			
					NULL);				
	if(!hwnd)	
		return FALSE;
	
	
/*	MoveWindow(hwnd,10,10,640,510,true);
	ShowWindow(hwnd, nCmdShow);
	*/UpdateWindow(hwnd);	

	hdc = GetDC(hwnd);
	mdc = CreateCompatibleDC(hdc);
	bufdc = CreateCompatibleDC(hdc);
	maskdc = CreateCompatibleDC(hdc);
	
	fullmap = CreateCompatibleBitmap(hdc,block_x * map_nx, block_y * map_ny);
	SelectObject(mdc,fullmap);

	///////// 加载位图
	int i;
	char filename[20] = "";
	for(i = 0; i < 5; i++)
	{
		sprintf(filename,"map%d.bmp",i);
		map_block[i] = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, block_x, block_y, LR_LOADFROMFILE);
	}
	for(i = 0; i < 12; i++)
	{
		sprintf(filename,"wind%d.bmp",i);
		wind_bmp[i] = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, block_x, block_y, LR_LOADFROMFILE);
	}

	for(i = 0; i < 6; i++)
	{
		sprintf(filename,"out%d.bmp",i);
		out_bmp[i] = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, block_x, block_y, LR_LOADFROMFILE);
	}
	out_flash = 0;
	

	for(i = 0; i < 2; i++)
	{
		sprintf(filename,"sheep%d.bmp",i);
		sheep_bmp[i] = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 200, 220, LR_LOADFROMFILE);
	}

	man_bmp = (HBITMAP)LoadImage(NULL, "renwu.bmp", IMAGE_BITMAP, block_x * 4, block_y * 4, LR_LOADFROMFILE);

	bg1 = (HBITMAP)LoadImage(NULL,"bg.bmp",IMAGE_BITMAP,640,510,LR_LOADFROMFILE);
	girl = (HBITMAP)LoadImage(NULL,"girl.bmp",IMAGE_BITMAP,480,148,LR_LOADFROMFILE);
	skill = (HBITMAP)LoadImage(NULL,"skill.bmp",IMAGE_BITMAP,50,50,LR_LOADFROMFILE);
	skillult = (HBITMAP)LoadImage(NULL,"skillult.bmp",IMAGE_BITMAP,50,50,LR_LOADFROMFILE);
	slash = (HBITMAP)LoadImage(NULL,"slash.bmp",IMAGE_BITMAP,196,162,LR_LOADFROMFILE);
	magic = (HBITMAP)LoadImage(NULL,"magic.bmp",IMAGE_BITMAP,200,100,LR_LOADFROMFILE);
	recover = (HBITMAP)LoadImage(NULL,"recover.bmp",IMAGE_BITMAP,300,150,LR_LOADFROMFILE);
	gameover_bmp = (HBITMAP)LoadImage(NULL,"over.bmp",IMAGE_BITMAP,289,74,LR_LOADFROMFILE);
	
	bg_gameover = (HBITMAP)LoadImage(NULL, "bg_gameover.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	bg_menu = (HBITMAP)LoadImage(NULL,"bg_menu.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

	gamewin_bmp[0] = (HBITMAP)LoadImage(NULL,"start.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	gamewin_bmp[1] = (HBITMAP)LoadImage(NULL,"quit.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

	menu_bmp[0] = (HBITMAP)LoadImage(NULL,"start.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	menu_bmp[1] = (HBITMAP)LoadImage(NULL,"quit.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

	BITMAP bitmap;
	GetObject(bg_gameover, sizeof(bitmap), &bitmap);
	bg_gameover_width = bitmap.bmWidth;
	bg_gameover_height = bitmap.bmHeight;

	GetObject(bg_menu, sizeof(bitmap), &bitmap);
	bg_menu_width = bitmap.bmWidth;
	bg_menu_height = bitmap.bmHeight;


	MoveWindow(hwnd,block_x * 3,block_x, bg_menu_width + 10, bg_menu_height + 23, true);
	ShowWindow(hwnd,nCmdShow);	

	SetBkMode(mdc, TRANSPARENT);  
 
	init();
	init_fun_menu();

	mypaint(hdc);

	return TRUE;
}

void msginsert(char* str)
{
	if(txtnum < 5)
	{
		sprintf(text[txtnum],str);
		txtnum++;
	}
	else
	{
		for(int i=0;i<txtnum;i++)
			sprintf(text[i],text[i+1]);

		sprintf(text[4],str);
	}
}

void msgdel()
{
	for(int i=0;i<txtnum;i++)
		sprintf(text[i],text[i+1]);
	txtnum--;
}

bool moves()
{
	if(man.x < man.pttx)
	{
		man.dir = 3;
		man.x = min(man.pttx, man.x + move);
	}
	else if(man.x > man.pttx)
	{
		man.dir = 1;
		man.x = max(man.pttx, man.x - move);
	}
	else if(man.y < man.ptty)
	{
		man.dir = 0;
		man.y = min(man.ptty, man.y + move);
	}
	else if(man.y > man.ptty)
	{
		man.dir = 2;
		man.y = max(man.ptty, man.y - move);
	}
	else if(map.move_l <= map.road_l)
	{
		man.ptty = map.road1[map.move_l].y * block_y;
		man.pttx = map.road1[map.move_l++].x * block_x;
		moves();
	}
	else
	{
		man.fla = 0;
		return 0;
	}
	return 1;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////


void fun_menu()
{
	SelectObject(bufdc, bg_menu);  
	BitBlt(mdc,0,0,block_x * map_nx,block_y * map_ny,bufdc,0,0,SRCCOPY);

	int textY = 300;
	COLORREF oldColor;

	SetBkMode(mdc, TRANSPARENT);

	for (int i=0; i<m_iSelectionMax; i++)
	{
		SelectObject(bufdc, menu_bmp[i]);
		if (i == m_iFocus)
		{
			TransparentBlt(mdc, 145, textY - 5, 133, 37, 
				bufdc, 0, 0, 
				128, 32, RGB(255, 255, 255));
			textY += 30;
		}
		else
		{
			TransparentBlt(mdc, 150, textY, 128, 32,   
				bufdc, 128, 0, 
				128, 32, RGB(255, 255, 255));
			textY += 30;
		}
	}
}
void init_fun_menu()
{
	menu = 1;
	m_MenuStrings[0].assign("开始游戏");
	m_MenuStrings[1].assign("退出游戏");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
void init_fun1()
{

	_fun1 = 1;
	attack = 0;

	monster.nHp = monster.fHp = 120;	//设定怪物角色生命值及上限
	monster.lv = 1;						//设定怪物角色等级
	monster.w = 1;					//设定攻击伤害加权值
	monster.type = rand() % 2;

	over = false;
	txtnum = 0;

	ff = 0;
}

void CheckDie(int hp,bool player)
{
	char str[100];

	if(hp <= 0)
	{
		over = 1;
		_fun1 = 0;
		
		if(player)
		{
			gameover = 1;
			sprintf(str,"胜败乃兵家常事，大侠请重新来过");
			msginsert(str);
		}
		else
		{
			sprintf(str, "终于击退了怪兽！");
			msginsert(str);	
			MoveWindow(hwnd,block_x * 3,block_x, client_x, client_y + 30, true);
			UpdateWindow(hwnd);	
		}
	}
	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void fun1()//attack
{
	char str[100];
	int i,damage;

	//贴上背景图
	SelectObject(bufdc,bg1);
	BitBlt(mdc,0,0,640,510,bufdc,0,0,SRCCOPY);

	//贴上怪物图
	if(monster.nHp>0)
	{
		SelectObject(bufdc,sheep_bmp[monster.type]);
		TransparentBlt(mdc, 70, 180, 200, 110,   
			bufdc, 0, 0, 
			200, 220, RGB(255, 255, 255));

		sprintf(str,"%d / %d",monster.nHp,monster.fHp);
		TextOut(mdc,100,320,str,strlen(str));
	}

	//贴上玩家图
	if(man.nHp>0)
	{
		SelectObject(bufdc,girl);
		BitBlt(mdc,500,200,60,74,bufdc,pNum*60,74,SRCAND);
		BitBlt(mdc,500,200,60,74,bufdc,pNum*60,0,SRCPAINT);
		sprintf(str,"%d / %d",man.nHp,man.fHp);
		TextOut(mdc,510,320,str,strlen(str));
	}

	if(over)				//贴上游戏结束图画
	{
		_fun1 = 0;
	}
	else if(!attack)		//贴上攻击命令图画
	{
		SelectObject(bufdc,skill);
		BitBlt(mdc,500,350,50,50,bufdc,0,0,SRCCOPY);
		SelectObject(bufdc,skillult);
		BitBlt(mdc,430,350,50,50,bufdc,0,0,SRCCOPY);
		//BitBlt(mdc,500,350,74,30,bufdc,0,30,SRCAND);
		//BitBlt(mdc,500,350,74,30,bufdc,0,0,SRCPAINT);
	}	
	else
	{
		ff++;

		//第5~10个画面时显示玩家攻击图标
		if(ff>=5 && ff<=10)
		{
			SelectObject(bufdc,slash);
			
			BitBlt(mdc,100,160,98,162,bufdc,98,0,SRCAND);
			BitBlt(mdc,100,160,98,162,bufdc,0,0,SRCPAINT);

			//第10个画面时计算怪物受伤害程度并加入显示消息
			if(ff == 10)
			{

				if (4==rand()%5)                   // 20%几率触发幻影刺客的大招，恩赐解脱，4倍暴击伤害
				{
					damage = 4*(rand()%10 + man.lv*man.w);
					monster.nHp -= (int)damage;

					sprintf(str,"恩赐解脱触发，这下牛逼了，4倍暴击...对怪物照成了%d点伤害",damage);
				} 
				else
				{
					damage = rand()%10 + man.lv*man.w;
					monster.nHp -= (int)damage;

					sprintf(str,"玩家使用了无敌斩，伤害一般般...对怪物照成了%d点伤害",damage);
				}


				
				msginsert(str);

				CheckDie(monster.nHp,false);
			}
		}

		srand(tPre);

		//第15个画面时判断怪物进行哪项动作
		if(ff == 15)
		{
			if(monster.nHp > 20)				//生命值大于20
			{
				if(rand()%5 != 1)          //进行利爪攻击概率4/5
					monster.kind = 0;
				else                       //进行闪电链攻击概率1/5
					monster.kind = 1;    
			}
			else								//生命值小于20
			{
				switch(rand()%4)
				{
					case 0:						//利爪攻击
						monster.kind = 0;
						break;
					case 1:						//释放闪电链
						monster.kind = 1;
						break;
					case 2:						//致命一击
						monster.kind = 2;
						break;
					case 3:						//使用梅肯斯姆回复
						monster.kind = 3;
						break;

				}
			}
		}

		//第26~30个画面时显示玩家攻击图标
		if(ff>=26  && ff<=30)
		{
			switch(monster.kind)
			{
				case 0:							//利爪攻击
					SelectObject(bufdc,slash);
					BitBlt(mdc,480,150,98,162,bufdc,98,0,SRCAND);
					BitBlt(mdc,480,150,98,162,bufdc,0,0,SRCPAINT);

					if(ff == 30)
					{
						damage = rand()%10 + monster.lv*monster.w;
						man.hurt(damage);
						
						sprintf(str,"怪物利爪攻击...对玩家照成 %d 点伤害",damage);
						msginsert(str);

						CheckDie(man.nHp,true);
					}
					break;
				case 1:							//释放闪电链
					SelectObject(bufdc,magic);
					BitBlt(mdc,480,190,100,100,bufdc,100,0,SRCAND);
					BitBlt(mdc,480,190,100,100,bufdc,0,0,SRCPAINT);

					if(ff == 30)
					{
						damage = rand()%10 + 3*monster.w;
						man.hurt(damage);
						
						sprintf(str,"怪物释放闪电链...对玩家照成 %d 点伤害",damage);
						msginsert(str);

						CheckDie(man.nHp,true);
					}
					break;
				case 2:						
					SelectObject(bufdc,slash);
					BitBlt(mdc,480,150,98,162,bufdc,98,0,SRCAND);
					BitBlt(mdc,480,150,98,162,bufdc,0,0,SRCPAINT);

					//第30个画面时计算玩家受伤害程度并加入显示消息
					if(ff == 30)
					{
						damage = rand()%10 + monster.lv*monster.w*5;
						man.hurt(damage);
						
						sprintf(str,"怪物致命一击...对玩家照成 %d 点伤害.",damage);
						msginsert(str);

						CheckDie(man.nHp,true);
					}
					break;
				case 3:						
					SelectObject(bufdc,recover);
					BitBlt(mdc,60,160,150,150,bufdc,150,0,SRCAND);
					BitBlt(mdc,60,160,150,150,bufdc,0,0,SRCPAINT);

					if(ff == 30)
					{
						monster.nHp += 30;
						
						sprintf(str,"怪物使用梅肯斯姆...恢复了30点生命值",damage);
						msginsert(str);
					}
					break;
			}
		}

		if(ff == 30)	
		{
			attack = false;
			ff = 0;
		}
	}

	BitBlt(hdc,0,0,640,510,mdc,0,0,SRCCOPY);

	tPre = GetTickCount();

	pNum++;
	if(pNum == 8)
		pNum = 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////

void init_fun2()
{
	int i, j;
	man.gx = 5 * block_x;
	man.gy = 5 * block_y;
	man.gsleep = -1000;
	man.gpttx = man.gx;
	man.gptty = man.gy;
	man.gptx = man.gx;
	man.gpty = man.gy;
	man.gdir = 1;
	man.gfla = 0;
	man.gtpre = tNow;
	_fun2 = 1;
	for(i = 0; i < wind_num; i++)
	{
		wind1[i].y = -block_y;
		wind1[i].x = (rand() % map_nx) * block_x;
		wind1[i].fla = rand() % 12;
		wind2[i].x = -block_x;
		wind2[i].y = (rand() % map_ny) * block_y;
		wind2[i].fla = rand() % 12;
		wind3[i].x = (rand() % map_nx) * block_x;
		wind3[i].y = map_ny * block_y + block_y;
		wind3[i].fla = rand() % 12;
		wind4[i].x = map_nx * block_x + block_x;
		wind4[i].y = (rand() % map_ny) * block_y;
		wind4[i].fla = rand() % 12;
	}
	round_f2 = 10;

	for(i = 0; i < map_nx; i++)
	{
		for(j = 0; j < map_ny; j++)
		{
			gmap.map_index[i][j] = 0;
		}
	}

	man.protect = 0;

	char str[50];
	sprintf(str,"失足掉入了一个洞窟，周围都是强劲的暗流！");
	msginsert(str);
}

void fun2()
{
	int i, j;
	int x, y;
	for (i = 0; i < map_nx; i++)
	{
		for(j = 0; j < map_ny; j++)
		{
			SelectObject(bufdc, map_block[3]);
			x = i * block_x;
			y = j * block_y;

			BitBlt(mdc,x,y,block_x,block_y,bufdc,0,0,SRCCOPY);  
		}
	}

	if(GetAsyncKeyState(VK_LEFT))
	{
		man.gdir = 1;
		man.gx = max(man.gx - move, 0);
	}
	else if(GetAsyncKeyState(VK_RIGHT))
	{
		man.gdir = 3;
		man.gx = min(man.gx + move, map_nx * block_x - block_x);
	}
	else if(GetAsyncKeyState(VK_UP))
	{
		man.gdir = 2;
		man.gy = max(man.gy - move, 0);
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		man.gdir = 0;
		man.gy = min(man.gy + move, map_ny * block_y - block_y);
	}

	if(tNow - man.gtpre >= 100)
	{
		man.gtpre = tNow;
		man.gfla = (man.gfla + 1) % 4;
	}
	SelectObject(bufdc, man_bmp);  

	TransparentBlt(mdc, man.gx, man.gy, block_x, block_y,   
			bufdc, man.gfla * block_x, man.gdir * block_y, 
			block_x, block_y, RGB(255, 255, 255));

	char str[50];
	for (i = 0; i < wind_num; i++)
	{
		wind1[i].move();
		if(sqrt((wind1[i].x - man.gx) * (wind1[i].x - man.gx) + (wind1[i].y - man.gy) * (wind1[i].y - man.gy)) < block_x / 4 * 3)
		{
			if(man.hurt(1))
			{
				sprintf(str,"受到暗流攻击，血量-1！");
				man.protect = 1;
				msginsert(str);
			}
		}
		SelectObject(bufdc, wind_bmp[wind1[i].fla]);
		TransparentBlt(mdc, wind1[i].x, wind1[i].y, block_x, block_y,   
				bufdc, 0, 0, 
				block_x, block_y, RGB(255, 255, 255));

		wind2[i].move();
		if(sqrt((wind2[i].x - man.gx) * (wind2[i].x - man.gx) + (wind2[i].y - man.gy) * (wind2[i].y - man.gy)) < block_x / 4 * 3)
		{
			if(man.hurt(1))
			{
				sprintf(str,"受到暗流攻击，血量-1！");
				man.protect = 1;
				msginsert(str);
			}
		}
		SelectObject(bufdc, wind_bmp[wind2[i].fla]);
		TransparentBlt(mdc, wind2[i].x, wind2[i].y, block_x, block_y,   
				bufdc, 0, 0, 
				block_x, block_y, RGB(255, 255, 255));

		wind3[i].move();
		if(sqrt((wind3[i].x - man.gx) * (wind3[i].x - man.gx) + (wind3[i].y - man.gy) * (wind3[i].y - man.gy)) < block_x / 4 * 3)
		{
			if(man.hurt(1))
			{
				sprintf(str,"受到暗流攻击，血量-1！");
				man.protect = 1;
				msginsert(str);
			}
		}
		SelectObject(bufdc, wind_bmp[wind3[i].fla]);
		TransparentBlt(mdc, wind3[i].x, wind3[i].y, block_x, block_y,   
				bufdc, 0, 0, 
				block_x, block_y, RGB(255, 255, 255));

		wind4[i].move();
		if(sqrt((wind4[i].x - man.gx) * (wind4[i].x - man.gx) + (wind4[i].y - man.gy) * (wind4[i].y - man.gy)) < block_x / 4 * 3)
		{
			if(man.hurt(1))
			{
				sprintf(str,"受到暗流攻击，血量-1！");
				man.protect = 1;
				msginsert(str);
			}
		}
		SelectObject(bufdc, wind_bmp[wind4[i].fla]);
		TransparentBlt(mdc, wind4[i].x, wind4[i].y, block_x, block_y,   
				bufdc, 0, 0, 
				block_x, block_y, RGB(255, 255, 255));
	}
	if(wind1[i].x > map_ny * block_y + block_y)
	{
		for(i = 0; i < wind_num; i++)
		{
			wind1[i].y = -block_y;
			wind1[i].x = (rand() % map_nx) * block_x;
			wind1[i].fla = rand() % 12;
			wind2[i].x = -block_x;
			wind2[i].y = (rand() % map_ny) * block_y;
			wind2[i].fla = rand() % 12;
			wind3[i].x = (rand() % map_nx) * block_x;
			wind3[i].y = map_ny * block_y + block_y;
			wind3[i].fla = rand() % 12;
			wind4[i].x = map_nx * block_x + block_x;
			wind4[i].y = (rand() % map_ny) * block_y;
			wind4[i].fla = rand() % 12;				
		}
		round_f2--;
		man.protect = 0;
		if(!round_f2)
		{
			sprintf(str,"终于从洞窟中逃离，松了口气");
			msginsert(str);
			_fun2 = 0;
		}
	}

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////

void init()
{
	exit_x = 1, exit_y = 0;
	txtnum = 0;	
	man.sleep = -1000;
	man.x = block_x;
	man.y = block_y;
	man.pttx = man.x;
	man.ptty = man.y;
	man.ptx = man.x;
	man.pty = man.y;
	man.dir = 1;
	man.fla = 0;
	man.tpre = tNow;
	man.nHp = man.fHp = 50;	
	man.lv = 2;				
	man.w  = 40;				
	gameover = 0;			

	int i, j;
	for(i = 0; i < map_nx; i++)
	{
		for(j = 0; j < map_ny; j++)
		{
			map.map_index[i][j] = 1;
		}
	}
	map.map_index[man.x / block_x][man.y / block_y] = 0;
}

void init_fun()
{
	MoveWindow(hwnd,block_x * 5,block_x, _fun_x, _fun_y, true);
	UpdateWindow(hwnd);

	RECT rect;
	GetClientRect(hwnd,&rect);
	fun_x = rect.right-rect.left;
	fun_y = rect.bottom-rect.top;


//	MessageBox(hwnd, "遭遇bo111ss", "result", MB_OK);
	myshot.init();
	enshot.init();
	enshot2.init();
	crashs.init();
	myshooters.init();
	items.init();
	myplane.init();
	enemy.init();
	myshot.hero = 1;
	enshot.hero = 0;
	enshot2.hero = 0;

	hpheight = 30;

	_fun = 1;
	int i;
	char filename[25] = "";
	for(i = 0; i < 12; i++)
	{
		sprintf(filename,"ame%d.bmp",i);
		bg_ame[i] = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, fun_x, fun_y, LR_LOADFROMFILE);
	}
	for(i = 0; i < 9; i++)
	{
		sprintf(filename,"BulletAb00%d.bmp",i);
		bullet[i] = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
	
	
	for(i = 0; i < 30; i++)
	{
		if(i < 10)
		{
			sprintf(filename,"spellBulletCa00%d.bmp", i);
			protect_bmp[i] = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}
		else
		{
			sprintf(filename,"spellBulletCa0%d.bmp", i);
			protect_bmp[i] = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}
	}

	hp_bmp = (HBITMAP)LoadImage(NULL, "hp.bmp", IMAGE_BITMAP, fun_x, hpheight, LR_LOADFROMFILE);

	win_bmp = (HBITMAP)LoadImage(NULL,"win.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

	BITMAP bitmap;

	GetObject(win_bmp, sizeof(bitmap), &bitmap);
	winWidth = bitmap.bmWidth;
	winHeight = bitmap.bmHeight;

	mciSendString("close all", NULL, 0, NULL);
	sprintf(music_buffer, "play 04.mid");
	mciSendString(music_buffer, NULL, 0, NULL);
	mciSendString("play music repeat", 0, 0, 0);
}

void fun()
{
	int i;
	SelectObject(bufdc, bg_ame[bg_num]);  
	BitBlt(mdc,0,0,fun_x,fun_y,bufdc,0,0,SRCCOPY);  
	bg_num = (bg_num + 1) % 12;

	myplane.perform();

	enemy.perform();

	SetRect(&rect1, enemy.x + enemy.width / 4, enemy.y + enemy.height / 4, 
		enemy.x + enemy.width / 4 * 3, enemy.y + enemy.height / 4 * 3);

	myshot.perform();

	SetRect(&rect1, myplane.x + myplane.width / 3, myplane.y + myplane.height / 3, 
		myplane.x + myplane.width / 3 * 2, myplane.y + myplane.height / 3 * 2);

	items.perform();
	enshot.perform();

	protect.show();

	enemy.show();

	myplane.show();

	crashs.show();

	myshooters.perform();

	crashs.delc();
	items.delc();
	myshot.decl();
	enshot.decl();

	SelectObject(bufdc, hp_bmp);
	BitBlt(mdc,10,50,(fun_x - 20) * (double)(enemy.hp * 1.0 / enemy.fhp),4,bufdc,0,0,SRCCOPY);  

	if(enemy.hp <= 0)
	{
		_fun = 0;
		_fun_2 = 1;
	}

	if(_fun == 0 && _fun_2 == 1)
	{
		init_fun_2();
	}
		
}

void init_fun_2()
{
	enemy2.init();
	mciSendString("close all", NULL, 0, NULL);
	sprintf(music_buffer, "play 05.mid");
	mciSendString(music_buffer, NULL, 0, NULL);
	mciSendString("play movie repeat", 0, 0, 0);
}
void fun_2()
{
	int i;
	SelectObject(bufdc, bg_ame[bg_num]);  
	BitBlt(mdc,0,0,fun_x,fun_y,bufdc,0,0,SRCCOPY);  
	bg_num = (bg_num + 1) % 12;



	myplane.perform();
	
	enemy2.perform();

	SetRect(&rect1, enemy2.x + enemy2.width / 4, enemy2.y + enemy2.height / 4,
		enemy2.x + enemy2.width / 4 * 3, enemy2.y + enemy2.height / 4 * 3);

	
	myshot.perform();

	SetRect(&rect1, myplane.x + myplane.width / 4, myplane.y + myplane.height / 4, 
		myplane.x + myplane.width / 4 * 3, myplane.y + myplane.height / 4 * 3);

	items.perform();
	enshot.perform();

	enshot2.perform();

	protect.show();

	enemy2.show();

	myplane.show();

	crashs.show();

	myshooters.perform();



	myshot.decl();
	enshot.decl();
	enshot2.decl();
	items.delc();
	crashs.delc();

	SelectObject(bufdc, hp_bmp);
	BitBlt(mdc,10,50,(fun_x - 20) * (double)(enemy2.hp * 1.0 / enemy2.fhp),4,bufdc,0,0,SRCCOPY);  
	
}




BOOL InitWindowsClass(HINSTANCE hInstance)
{
	WNDCLASS WndClass;

	WndClass.cbClsExtra=0;	
	WndClass.cbWndExtra=0;	
	WndClass.hbrBackground=(HBRUSH)(GetStockObject(WHITE_BRUSH));
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;		
	WndClass.lpfnWndProc=WndProc;		
	WndClass.lpszClassName="my window";		
	WndClass.lpszMenuName="Menu3";		
	WndClass.style=0;					
	return RegisterClass(&WndClass);
}

void mypaint(HDC hdc)
{
	int i, j;
	char str[100];
	if(_gameover)
	{
		fun_gameover();
	}
	else if(gameover)
	{
		if(win)
		{
			SelectObject(bufdc,win_bmp);
			TransparentBlt(mdc, 0, 0, fun_x, fun_y,   
				bufdc, 0, 0, 
				winWidth, winHeight, RGB(255, 255, 255));
		}
		else
		{
			SelectObject(bufdc,gameover_bmp);
			TransparentBlt(mdc, 0, fun_y / 3, fun_x, fun_y / 3,   
				bufdc, 0, 0, 
				289, 37, RGB(0, 0, 0));
		}
		
	}
	else if(_fun_2)
	{
		fun_2();
	}
	else if(_fun)
	{
		fun();
	}
	else if(menu)
	{
		init_fun_menu();
		fun_menu();
	}
	else if(_fun2)
	{
		fun2();
	}
	else if(_fun1)
	{
		MoveWindow(hwnd,block_x * 3,block_x, 640, 510, true);
		UpdateWindow(hwnd);	
		fun1();
	}
	else
	{
		int i, j;
		
		int x, y;
		for (i = 0; i < map_nx; i++)
		{
			for(j = 0; j < map_ny; j++)
			{
				x = i * block_x;
				y = j * block_y;

				if(map.map_index[i][j] == 2)
				{
					SelectObject(bufdc, map_block[0]);
					BitBlt(mdc,x,y,block_x,block_y,bufdc,0,0,SRCCOPY);  

					SelectObject(bufdc, out_bmp[out_flash++]);
					out_flash %= 6;
					TransparentBlt(mdc, x, y, block_x, block_y,   
						bufdc, 0, 0, 
						block_x, block_y, RGB(255, 255, 255));
				}
				else
				{
					SelectObject(bufdc, map_block[map.map_index[i][j]]);
					BitBlt(mdc,x,y,block_x,block_y,bufdc,0,0,SRCCOPY);  
				}
			}
		}

		if(moves())
		{
			if(tNow - man.tpre >= 100)
			{
				man.tpre = tNow;
				man.fla = (man.fla + 1) % 4;
			}
		}

		SelectObject(bufdc, man_bmp);
		
		TransparentBlt(mdc, man.x, man.y, block_x, block_y,   
				bufdc, man.fla * block_x, man.dir * block_y, 
				block_x, block_y, RGB(255, 255, 255));

		//sprintf(str,"%d %d", _map1[1][2], _map1[2][1]);
		

	}

	if(txtnum > 0)
	{
		text_t++;
	}

	if(text_t > 40)
	{
		text_t = 0;
		msgdel();
	}

	
	if(!menu)
	{
		COLORREF oldColor = SetTextColor(mdc, RGB(255, 255, 255));
		if(_fun || _fun_2)
			sprintf(str,"LV:%d HP:%d", myplane.lv, myplane.hp);
		else
			sprintf(str,"LV:%d HP:%d / %d", man.lv, man.nHp,man.fHp);
	
		
		TextOut(mdc,10,10,str,strlen(str));
		SetTextColor(mdc, oldColor);
	}

	if(!_fun)
		for(i=0;i<txtnum;i++)
			TextOut(mdc,0,360+i*18,text[i],strlen(text[i]));

	BitBlt(hdc,0,0,block_x * map_nx,block_y * map_ny,mdc,0,0,SRCCOPY);	//mdc -> hdc

	tPre = GetTickCount();
}


long WINAPI WndProc(HWND hwnd,
					UINT iMessage,
					UINT wParam,
					LONG lParam)
{
	int x, y;
	switch(iMessage)
	{

	case WM_KEYUP:
		{
			map.road_l = -1;
			break;
		}
	case WM_LBUTTONDOWN:
		{
			if(_fun1)
			{
				if(!attack)
				{
					x = LOWORD(lParam);		//X坐标
					y = HIWORD(lParam);		//Y坐标
				
				//	if(x >= 500 && x <= 550 && y >= 350 && y <= 400)
				//		attack = true;
				}
				break;
			}
			else if(_fun || _fun2)
			{
				break;
			}
			else
			{
				x = LOWORD(lParam) / block_x;
				y = HIWORD(lParam) / block_y;
								
				if(x < map_nx && y < map_ny)
					if(!map.map_index[x][y] && (x != man.pttx / block_x || y != man.ptty / block_y))
					{
							
						man.ptx = x * block_x;
						man.pty = y * block_y;
						if(map.isroute(man.ptx / block_x, man.pty / block_y, man.pttx / block_x, man.ptty / block_y))
						{
							map.getro(man.ptx / block_x, man.pty / block_y);
						//				
						//						char str[100];
						//				sprintf(str, "%d %d", x, y);
						//				MessageBox(hwnd, str, "result", MB_OK);	
						}
					}
				break;
			}
		}
	case WM_KEYDOWN:
		{
			if(_gameover)
			{
				switch(wParam)
				{
					case VK_DOWN:
					{
						gameover_choice  = ( ( gameover_choice + gameover_choices ) - 1 ) % 2;

						break;
					}
					case VK_UP:
					{
						gameover_choice = (gameover_choice + 1) % 2;
						break;
					}
					case VK_RETURN:
					{
						if(gameover_choice == 0)
						{
							
							menu = 1;
							MoveWindow(hwnd,block_x * 3,block_x, bg_menu_width, bg_menu_height, true);
							UpdateWindow(hwnd);	
							init();
							init_fun_menu();
							_gameover = 0;
						}
						else
						{
							PostQuitMessage(WM_QUIT);
						}
						break;
					}
				}
				break;
			}
			else if(gameover)
			{
				initgameover();
				gameover = 0;
				win = 0;
			}
			else if(_fun || _fun_2)
			{
				break;
			}

			else if(menu)
			{
				switch(wParam)
				{
					case VK_DOWN:
					{
						m_iFocus  = ( ( m_iFocus + m_iSelectionMax ) - 1 ) % 2;

						break;
					}
					case VK_UP:
					{
						m_iFocus = (m_iFocus + 1) % 2;
						break;
					}
					case VK_RETURN:
					{
						if(m_iFocus == 0)
						{
							MoveWindow(hwnd,block_x * 3,block_x, client_x, client_y + 30, true);
							UpdateWindow(hwnd);	
							menu = 0;
						}
						else
						{
							PostQuitMessage(WM_QUIT);
						}
						break;
					}
				}
				break;
			}
							
			int x, y, i = -1;
			switch(wParam)
			{
				case VK_DOWN:
				{
					i = 0;
					break;
				}
				case VK_RIGHT:
				{
					i = 1;
					break;
				}
				case VK_UP:
				{
					i = 2;
					break;
				}
				case VK_LEFT:
				{
					i = 3;
					break;
				}
				case VK_SPACE:
				{
					attack = 1;
				}
			}
			if(i >= 0 && i < 4)
			{
				if(_fun2)
				{

				}
				else if(_fun1)
				{
				
				}
				else
				{
					x = man.pttx / block_x + map.dir[i][0];
					y = man.ptty / block_y + map.dir[i][1];
					if(i == 1) man.dir = 3;
					else if(i == 3) man.dir = 1;
					else man.dir = i;
					if(x < map_nx && y < map_ny && x >= 0 && y >= 0)
					{
						
						if(!map.map_index[x][y])
						{
							man.ptx = x * block_x;
							man.pty = y * block_y;
							if(map.isroute(x, y, man.pttx / block_x, man.ptty / block_y))
							{
								map.getro(man.ptx / block_x, man.pty / block_y);
						//		MessageBox(hwnd, "111", "result", MB_OK);
							}
						}
						else if(man.x % block_x == 0 && man.y % block_y == 0)
						{
							if(map.map_index[x][y] == 1)
							{
								map.map_index[x][y] = 0;
								func(_map1[x][y]);
							}
							else if(map.map_index[x][y] == 2)
							{
								map_num++;// escape
								init_fun();
								MessageBox(hwnd, "遭遇boss", "result", MB_OK);
							}
						}
					}
				
				}
				
			}

			break;
		}

	case WM_DESTROY:
		DeleteDC(mdc);
		DeleteDC(bufdc);

		ReleaseDC(hwnd,hdc);
		PostQuitMessage(0);
		return 0;
	default:
		return(DefWindowProc(hwnd,iMessage,wParam,lParam));
	}
	return 0;
}

void func(int x)
{
	switch(x)
	{
	case 0:
		break;
	case 1:
		{
			init_fun1();

			break;
		}
	case 2:
		{
			man.addHp(rand() % 10 + 10);

			char str[100];
			sprintf(str, "找到了血瓶，回复血量");
			msginsert(str);				
			break;
		}
	case 3:
		{
			char str[100];
			sprintf(str, "发现了一个奇怪的传送门，要不要进去呢");
			msginsert(str);
			map.map_index[exit_x][exit_y] = 2;
			break;
		}
	case 4:
		{
			init_fun2();

			break;
		}
	}
}

void initgameover()
{
	mciSendString("close all", NULL, 0, NULL);
	_fun_2 = 0;
	_fun1 = 0;
	_fun2 = 0;
	_fun3 = 0;
	menu = 0;
	_fun = 0;
	_fun_2 = 0;
	gameover_choices = 2;
	m_gameoverStrings[0].assign("返回菜单");
	m_gameoverStrings[1].assign("退出游戏");
	
	gameover_choice = 0;
	_gameover = 1;
}


void fun_gameover()
{
	SelectObject(bufdc, bg_gameover);
	TransparentBlt(mdc, 0, 0, fun_x, fun_y,   
		bufdc, 0, 0, 
		bg_gameover_width, bg_gameover_height, NULL);

	int textY = 300;
	COLORREF oldColor;

	SetBkMode(mdc, TRANSPARENT);

	for (int i=0; i<gameover_choices; i++)
	{
		SelectObject(bufdc, gamewin_bmp[i]);
		if (i == gameover_choice)
		{
			TransparentBlt(mdc, 145, textY - 5, 133, 37,   
				bufdc, 0, 0, 
				128, 32, RGB(255, 255, 255));

			textY += 30;
		}
		else
		{
			TransparentBlt(mdc, 150, textY, 128, 32,   
				bufdc, 128, 0, 
				128, 32, RGB(255, 255, 255));

			textY += 30;
		}
	}
		
}


