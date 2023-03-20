
#include "acllib.h"
#include <time.h>
#include <string>
using namespace std;
typedef struct rect
{
	int x;
	int y;
	int width;
	int  height;
}rect;
ACL_Image tomimg, jerryimg,heartimg;//变量
ACL_Color red = RED;
void timerEvent(int id);
void keyEvent(int key, int e);
int winWidth = 700, winHeight = 480;
int moveid = 0, movetime = 60;
int creatid = 1, creattime = 6000;
const int maxnum = 5;
const char* tomm = "tom.bmp";
const char* jerryy = "jerry.bmp";
const char* heartt = "heart.bmp";
void paint();
int score=0;//分数
int collision(rect r1, rect r2);
 
struct sprite {
	char const* name;
	int x, y;
	int distx, disty;
	int width, height;
};
struct sprite tom[maxnum], jerry , heart[maxnum];
int num = 0;
 
 
int Setup()
{
	srand((unsigned)time(NULL));
	initWindow("happy game", DEFAULT, DEFAULT, winWidth, winHeight);
	loadImage(tomm, &tomimg);
	loadImage(jerryy, &jerryimg);//
	loadImage(heartt, &heartimg);//
 
	tom[0].width = 100;
	tom[0].height = 100;
	tom[0].x = rand() % (winWidth - tom[0].width);
	tom[0].y = rand() % (winHeight - tom[0].height);
	tom[0].distx = tom[0].disty = 3;
 
	//tom[num] = (struct sprite*)malloc(sizeof(struct sprite));//?
 
 
	jerry.x = 40;
	jerry.y = 50;
 
 
	registerTimerEvent(timerEvent);
	startTimer(moveid, movetime);
	startTimer(creatid, creattime);
	//paint();
 
	registerKeyboardEvent(keyEvent);
	//paint();
	return 0;
}//windows编程   消息处理机制
void timerEvent(int id)
{
	
	if (id == 0)
	{
		for (int i = 0; i < maxnum; i++)
		{
			tom[i].x += tom[i].distx;
			tom[i].y += tom[i].disty;
			if (tom[i].x > (winWidth - tom[i].width) || tom[i].x <= 0) tom[i].distx = tom[i].distx * -1;
			if (tom[i].y > (winHeight - tom[i].height) || tom[i].y <= 0) tom[i].disty = tom[i].disty * -1;
		}
		for (int i = 0; i < num; ++i)
		{
			rect r1, r2;
			r1.x = jerry.x;
			r1.y = jerry.y;
			r1.width = 80;
			r1.height = 70;
 
			r2.x = tom[i].x;
			r2.y = tom[i].y;
			r2.width = tom[i].width;
			r2.height = tom[i].height;
			int c = collision(r1, r2);
			if (c == 1) score--;
 
		}//判断于tom是否主动碰撞jerry
 
	}
	if (id == 1)
	{
		
		 if (num < maxnum-1)
		 {
			 num++;
			 tom[num].width = 100;
			 tom[num].height = 100;
			 tom[num].x = rand() % (winWidth - tom[num].width);
			 tom[num].y = rand() % (winHeight - tom[num].height);
			 tom[num].distx = tom[num].disty = 3;
			 
			 
 
 
		 }
		 heart[num].width = 40;
		 heart[num].height = 40;
		 heart[num].x = rand() % (winWidth - tom[num].width);
		 heart[num].y = rand() % (winHeight - tom[num].height);
		 heart[num].distx = heart[num].disty = 0;
		
 
	}
	paint();
 
}
 
void paint()
{
	beginPaint();
	//putImage(&img,0,0);//把图片数据绘制到指定位置
	clearDevice();
	setTextSize(40);
	setTextColor(BLACK);
	paintText(1, 1, "分数：");
	char score1[20];
	sprintf_s(score1, "%d", score);
	paintText(99, 1, score1);
	setTextSize(20);
	setTextColor(BLUE);
	paintText(490, 450, "使用键盘控制jerry");
	putImageScale(&jerryimg, jerry.x, jerry.y, 80, 70);
	for (int i = 0; i <= num; i++)
	{
		putImageScale(&tomimg, tom[i].x, tom[i].y, tom[i].width, tom[i].height);
		putImageScale(&heartimg, heart[i].x, heart[i].y, heart[i].width, heart[i].height);
	}
	
 
	endPaint();
}
 
 
void keyEvent(int key, int e)
{
	if (e != KEY_DOWN) return;
	switch (key)
	{
	case VK_UP:
		jerry.y = jerry.y - 11;
		break;
	case VK_DOWN:
		jerry.y = jerry.y + 11;
		break;
	case VK_LEFT:
		jerry.x = jerry.x - 11;
		break;
	case VK_RIGHT:
		jerry.x = jerry.x + 11;
		break;
 
	}
	for (int i = 0; i < num; ++i) 
	{
		rect r1, r2;
		r1.x = jerry.x;
		r1.y = jerry.y;
		r1.width =  80;
		r1.height = 70;
		
			r2.x = tom[i].x;
			r2.y = tom[i].y;
			r2.width = tom[i].width;
			r2.height = tom[i].height;
			int c = collision(r1, r2);
			if (c ==1) score--;
 
	}//判断于tom是否碰撞
	for (int i = 1; i <=num; ++i)
	{
		rect r1, r2;
		r1.x = jerry.x;
		r1.y = jerry.y;
		r1.width = 80;
		r1.height = 70;
 
		r2.x = heart[i].x;
		r2.y = heart[i].y;
		r2.width = heart[i].width;
		r2.height = heart[i].height;
		int c = collision(r1, r2);
		if (c == 1) { score = score + 5; heart[i].width = 0; heart[i].height = 0; heart[i].x = winWidth + 10000;  }
	}//判断是否与heart碰撞
	paint();
}
int collision(rect r1, rect r2)
{
	int c = 1;
if (r1.x<r2.x && r1.x + r1.width>r2.x) {
	if (r1.y > r2.y && r1.y < r2.y + r2.height) return c;
	if (r1.y<r2.y && r1.y + r1.height>r2.y)return c;
	else {
		if (r1.x > r2.x && r2.x + r2.width > r1.x) 
		{
			if (r1.y > r2.y && r1.y < r2.y + r2.height) return c;
			if (r1.y<  r2.y && r1.y + r1.height > r2.y)return c;
 
		}
		c = 0; return c;
 
 
 
	}
 
}
 
}
