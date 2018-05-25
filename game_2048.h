#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include<unistd.h>
#include<signal.h>
#include<time.h>

int a[4][4] = {0};

int empty;
int old_x,old_y;

void draw();//绘制游戏界面
void init();//完成一些初始化操作
void play();//游戏主要逻辑
void draw_one(int y,int x);//绘制单个数字
void cnt_value(int* new_y,int* new_x);//相加之后的生成新的数字
int game_over();//游戏结束
int cnt_one(int y,int x);
