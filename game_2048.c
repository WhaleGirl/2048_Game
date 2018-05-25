#include"game_2048.h"

void init()
{
	int x,y;
	initscr();//初始化curses包
	cbreak();//禁止行缓冲
	noecho();//关闭回显模式，通过按键控制屏幕
	curs_set(0);//光标设置，参数为0表示隐藏光标

	//随机生成两个位置，将这个位置填上2
	empty = 15;
	srand(time(0));
	x = rand()%4;
	y = rand()%4;
	a[y][x] = 2;
	Draw();//自定义函数，画出整个框架
}
void Draw()
{
	int n,m,x,y;
	char c[4] = {'0','0','0','0'};

	clear();
	//绘制横线，n代表行，m代表列
	for(n = 0;n<9;n+=2)
	{
		for(m = 0;m<21;m++)
		{
			move(n,m);//移动光标到n,m
			addch('-');//添加字符到n,m
			refresh();//更新默认窗口
		}
	}
	//绘制竖线
	for(m = 0;m<22;m+=5)
	{
		for(n=1;n<8;n++)
		{
			move(n,m);
			addch('|');
			refresh();
		}
	}
	for(y = 0;y<4;y++)
	{
		for(x=0;x<4;x++)
			draw_one(y,x);
	}
}

void draw_one(int y,int x)
{
	int i,m,k,j;
	char c[5] = {0x00};
	i = a[y][x];
	m = 0;
	while(i>0)
	{
		j = i%10;
		c[m++]  = j+'0';
		i  =i/10;
	}
	m =0;
	k = (x+1)*5-1;
	while(c[m]!=0x00)
	{
		move(2*y+1,k);
		addch(c[m++]);
		k--;
	}
}
void play()
{
	int x,y,i,new_x,new_y,tmp;
	int old_empty,move;
	char ch;
	while(1)
	{
		move = 0;
		old_empty = empty;
		ch = getch();
		switch(ch)
		{
			//左
			case 97:	//左移：a
			case 104:	//h
			case 68:	//左移方向键
				for(y=0;y<4;y++)
				{
					for(x= 0;x<4;)
					{
						if(a[y][x]==0)
						{
							x++;
							continue;
						}
						else
						{
							for(i = x+1;i<4;i++)
							{
								if(a[y][i] == 0)
									continue;
								else
								{
									if(a[y][x]==a[y][i])
									{
										a[y][x]+=a[y][i];
										a[y][i] = 0;
										empty++;
										break;
									}
									else
										break;
								}
							}
					x = i;
						}
					}
				}
		
		for(y= 0;y<4;y++)
		{
			for(x = 0;x<4;x++)
			{
				if(a[y][x] == 0)
					continue;
				else
				{
					for(i = x;(i>0)&&(a[y][i-1]==0);i--)
					{
						a[y][i-1]=a[y][i];
						a[y][i] =0;
						move = 1;
					}		
				}
			}
		}
		break;
		//
		case 100:	//右移：d
		case 108:   //l
		case 67:    //右移方向键
		for(y= 0;y<4;y++)
		{
			for(x =3;x>=0;)
			{
				if(a[y][x] == 0)
				{
					x--;
					continue;
				}
				else
				{
					for(i =x-1;i>=0;i--)
					{
						if(a[y][i]==0)
							continue;
						else if(a[y][x] == a[y][i])
								{
									a[y][x] += a[y][i];
									a[y][i]=0;
									empty++;
									break;
								}
						else
							break;
					}
					x = i;
				}
			}
		}
		for(y= 0;y<4;y++)
		{
			for(x= 3;x>=0;x--)
			{
				if(a[y][x] ==0 )
					continue;
				else
				{
					for(i = x;(i<3)&&(a[y][i+1]==0);i++)
					{
						a[y][i+1] = a[y][i];
						a[y][i] = 0 ;
						move = 1;
					}
				}
			}
		}
		break;
		case 119:	//上移：w
		case 107:   //k
		case 65:    //上移方向键
		for(x =0;x<4;x++)
		{
			for(y = 0;y<4;)
			{
				if(a[y][x] ==0)
				{
					y++;
					continue;
				}
				else
				{
					for(i = y+1;i<4;i++)
					{
						if(a[i][x] == 0)
							continue;
						else if(a[y][x] == a[i][x])
						{
							a[y][x] += a[i][x];
							a[i][x]=0;
							empty++;
							break;
						}
						else 
							break;
					}
					y=i;
				}
			}
		}
		for(x =0;x<4;x++)
		{

			for(y= 0;y<4;y++)
			{
				if(a[y][x] ==0 )
					continue;
				else
				{
					for(i = y;(i>0)&&(a[i-1][x]==0);i--)
					{
						a[i-1][x]= a[i][x];
						 a[i][x]= 0 ;
						move = 1;
					}
				}
			}
		}
		break;
		case 115:	//下移：s
		case 106:   //j
		case 66:    //下移方向键
		for(x= 0;x<4;x++)
		{
			for(y =3;y>=0;)
			{
				if(a[y][x] == 0)
				{
					y--;
					continue;
				}
				else
				{
					for(i =y-1;i>=0;i--)
					{
						if(a[i][x]==0)
							continue;
						else if(a[y][x] == a[i][x])
								{
									a[y][x] += a[i][x];
									a[i][x]=0;
									empty++;
									break;
								}
						else
							break;
					}
					y = i;
				}
			}
		}
		for(x =0;x<4;x++)
		{

			for(y= 3;y>=0;y--)
			{
				if(a[y][x] ==0 )
					continue;
				else
				{
					for(i = y;(i<3)&&(a[i+1][x]==0);i++)
					{
						a[i+1][x]= a[i][x];
						 a[i][x]= 0 ;
						move = 1;
					}
				}
			}
		}
		break;
		case 'Q':	//退出
		case 'q':
			game_over();
			break;
		default:
			continue;
			break;
	}

		if(empty<=0)
			game_over();
		if((empty!=old_empty)||(move==1))
				{
					do{
						new_x = rand()%4;
						new_y = rand()%4;
					}while(a[new_y][new_x] != 0);

					cnt_value(&new_y,&new_x);
						
					do{
						tmp = rand()%4;
					}while(tmp==0||tmp==2);
					a[new_y][new_x] = tmp+1;
					empty--;
				}
		draw();

	}
}

int cnt_one(int y,int x)
{
	int value = 0;
	if(y-1>0)
		a[y-1][x] ?0 : value++;
	if(y+1<4)
		a[y+1][x] ? 0: value++;
	if(x-1>=0)
		a[y][x-1] ? 0: value++;
	if(x+1<4)
		a[y][x+1] ? 0: value++;
	if(y-1>=0 && x-1>=0)
		a[y-1][x-1] ? 0: value++;
	if(y-1>=0 && x+1<4)
		a[y-1][x+1] ? 0: value++;
	if(y+1<4 && x-1>=0)
		a[y+1][x-1] ? 0: value++;
	if(y+1<4 && x+1<4)
		a[y+1][x+1] ? 0: value++;
	return value;
}

void cnt_value(int* new_y,int* new_x)
{
	int max_x,max_y,x,y,value;
	int max =0;
	max = cnt_one(*new_y,*new_x);
	for(y =0;y<<4;y++)
	{
		for(x = 0;x<4;x++)
		{
			//如果（y,x)对应的空格为空
			if(!a[y][x])
			{
				value = cnt_one(y,x);//优先选取周围空格多的空格展示新数字
				if(value>max&& old_y!=y&&old_x!=x)
				{
					*new_x = x;
					*new_y =y;
					old_x = x;
					old_y = y;
					break;
				}
			}
		}
	}

}



int game_over()
{
	sleep(1);
	endwin();
	exit(0);
}

int main()
{

	printf("··················游戏马上开始了哦············\n");
	printf("游戏手册:\n");
	printf("------W-----上移-----\n");
	printf("------S-----下移-----\n");
	printf("------A-----左移-----\n");
	printf("------D-----右移-----\n");
	printf("------Q-----退出游戏-----\n");
	printf("10秒后游戏开始\n");
	printf("祝您游戏愉快\n");
	sleep(10);
	init();
	play();
	endwin();
	return 0;
}
