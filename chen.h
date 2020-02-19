#include <graphics.h>
#include <conio.h>
#include <time.h>
#include<windows.h>
#include <stdio.h>


#define WIN_WID 480 
#define WIN_HIG 680

#define WID_NUM WIN_WID/SIZE
#define HIG_NUM WIN_HIG/SIZE

#define SIZE 40

typedef int TYPE;
typedef int SIMILAR;

typedef struct Point
{
	int x;
	int y;
};

typedef struct Shape
{
	Point point[4];
	TYPE type;
	SIMILAR similar;
	int color;
};

void draw();
void drawBackground();
void drawLine();
void drawShape(Shape s);
void refreshOtherThreeByXY(Shape &shape, int x, int y);

void getData_1_1(int x, int y, Shape &shape);
void getData_1_2(int x, int y, Shape &shape);
void getData_1_3(int x, int y, Shape &shape);
void getData_1_4(int x, int y, Shape &shape);

void getData_2_1(int x, int y, Shape &shape);
void getData_2_2(int x, int y, Shape &shape);
void getData_2_3(int x, int y, Shape &shape);
void getData_2_4(int x, int y, Shape &shape);

void getData_3_1(int x, int y, Shape &shape);
void getData_3_2(int x, int y, Shape &shape);
void getData_3_3(int x, int y, Shape &shape);
void getData_3_4(int x, int y, Shape &shape);

void getData_4_1(int x, int y, Shape &shape);
void getData_4_2(int x, int y, Shape &shape);

void getData_5_1(int x, int y, Shape &shape);
void getData_5_2(int x, int y, Shape &shape);

void getData_6_1(int x, int y, Shape &shape);
void getData_6_2(int x, int y, Shape &shape);

void getData_7_1(int x, int y, Shape &shape);


void initShape(Shape &shape, int x, int y);

void tauchXYchange(Shape &shape, char hit, int &x, int &y);
int leftOver(Shape s);
int rightOver(Shape s);
void drawStopedShape();
int searchStop(Shape s);
void clearRecord();
void recordMoveShape(Shape s);
void recordStopShape(Shape s);
int changedOver(Shape s);
void initClearLines();   //��¼������������ ���ã�
void searchCanClear();  //��¼��������������
void clearFullLine();  //������

int recordAll[HIG_NUM][WID_NUM];   //0��ʾ�գ� 1��ʾ�˶���ͼ�Σ�2��ʾ�Ѿ���ֹ��ͼ��
int clearLines[5];  //��0����¼β��
int bottom = 0;  //0��ʾû�е��ף�1��ʾ����, 2��ʾ������������ͼ��


int gameOver()   //0�� 1 ��
{
	for(int i = 0; i < WID_NUM; i++)
	{
		if(recordAll[0][i] == 2)
		{
			return 1;
		}
	}
	return 0;
}

void initClearLines()   //��¼������������ ���ã�
{
	clearLines[0] = 1;
	for(int i = 1; i < 5; i++)
	{
		clearLines[i] = 0;
	}
}

void searchCanClear()  //��¼��������������
{
	for(int i = 0; i < HIG_NUM; i++)
	{
		int clear = 0;
		for(int j = 0; j < WID_NUM; j++)
		{
			if(	recordAll[i][j] == 0)
			{
				break;
			}
			if(j == WID_NUM - 1)
			{
				clearLines[clearLines[0]] = i;
				clearLines[0] += 1;
			}
		}
	}
}

void clearFullLine()  //������
{
	for(int i = 1; i < clearLines[0]; i++)
	{
		for(int j = 0; j < WID_NUM; j++)
		{
			recordAll[clearLines[i]][j] = 0;
		}
		for(int k = clearLines[i]; k > 0; k--)
		{
			for(int m = 0; m < WID_NUM; m++)
			{
				recordAll[k][m] = recordAll[k - 1][m];
			}
		}
		for(int n = 0; n < WID_NUM; n++)
		{
			recordAll[0][n] = 0;
		}
	}
}


void recordStopShape(Shape s)
{
	for(int i = 0; i < 4; i++)
	{
		recordAll[s.point[i].y][s.point[i].x] = 2;
	}
}

void clearRecord()
{
	for(int i = 0; i < HIG_NUM; i++)
	{
		for(int j = 0; j < WID_NUM; j++)
		{
			if(recordAll[i][j] == 1)
			{
				recordAll[i][j] = 0;
			}
		}
	}
}

void recordMoveShape(Shape s)
{
	for(int i = 0; i < 4; i++)
	{
		recordAll[s.point[i].y][s.point[i].x] = 1;
	}
}

void draw(Shape shape)
{
	drawBackground();
	drawShape(shape);
	drawStopedShape();  //��ֹͣ��ҲҪ����
	drawLine();
}

void drawBackground()
{
	setfillcolor(RGB(205, 255, 236));
	solidrectangle(0, 0, WIN_WID, WIN_HIG);
}

void drawLine()
{
	setlinecolor(BLACK);
	for(int i = 0; i < WIN_WID/SIZE; i++)
	{
		line(i * SIZE, 0, i * SIZE, WIN_HIG);
	}
	for(int j = 0; j < WIN_HIG/SIZE; j++)
	{
		line(0, j * SIZE, WIN_HIG, j * SIZE);
	}
}

//��Ϊ2�Ļ���Ҫ����
void drawStopedShape()
{
	for(int i = 0; i < HIG_NUM; i++)
	{
		for(int j = 0; j < WID_NUM; j++)
		{
			if(recordAll[i][j] == 2)
			{
				setfillcolor(LIGHTGRAY);
				solidrectangle(j * SIZE, i * SIZE, (j + 1) * SIZE, (i + 1) * SIZE);
			}
		}
	}
}

void drawShape(Shape s)
{
	switch(s.color)
	{
		case 1:
		{
			setfillcolor(YELLOW);
		}break;
		case 2:
		{
			setfillcolor(LIGHTMAGENTA);
		}break;
		case 3:
		{
			setfillcolor(LIGHTRED);
		}break;
		case 4:
		{
			setfillcolor(LIGHTCYAN);
		}break;
		case 5:
		{
			setfillcolor(LIGHTGREEN);
		}break;
		case 6:
		{
			setfillcolor(LIGHTBLUE);
		}break;
		case 7:
		{
			setfillcolor(BROWN);
		}break;
		default:
			break;
	}

	for(int i = 0; i < 4; i++)
	{
		solidrectangle(s.point[i].x * SIZE, s.point[i].y * SIZE, (s.point[i].x + 1) * SIZE, (s.point[i].y + 1) * SIZE);
	}
}

void refreshOtherThreeByXY(Shape &shape, int x, int y)                                                      //��������
{
	switch(shape.type)    //ͨ���Ѿ����µ�xy����ˢ����������������
	{
		case 1:
		{
			switch(shape.similar)
			{
				case 1:
				{
					getData_1_1(x, y, shape);
				}break;
				case 2:
				{
					getData_1_2(x, y, shape);
				}break;
				case 3:
				{
					getData_1_3(x, y, shape);
				}break;
				case 4:
				{
					getData_1_4(x, y, shape);
				}break;
				default:
					break;
			}
		}break;

		case 2:
		{
			switch(shape.similar)
			{
				case 1:
				{
					getData_2_1(x, y, shape);
				}break;
				case 2:
				{
					getData_2_2(x, y, shape);
				}break;
				case 3:
				{
					getData_2_3(x, y, shape);
				}break;
				case 4:
				{
					getData_2_4(x, y, shape);
				}break;
				default:
					break;
			}
		}break;

		case 3:
		{
			switch(shape.similar)
			{
				case 1:
				{
					getData_3_1(x, y, shape);
				}break;
				case 2:
				{
					getData_3_2(x, y, shape);
				}break;
				case 3:
				{
					getData_3_3(x, y, shape);
				}break;
				case 4:
				{
					getData_3_4(x, y, shape);
				}break;
				default:
					break;
			}
		}break;
		case 4:
		{
			switch(shape.similar)
			{
				case 1:
				{
					getData_4_1(x, y, shape);
				}break;
				case 2:
				{
					getData_4_2(x, y, shape);
				}break;
				default:
					break;
			}
		}break;

		case 5:
		{
			switch(shape.similar)
			{
				case 1:
				{
					getData_5_1(x, y, shape);
				}break;
				case 2:
				{
					getData_5_2(x, y, shape);
				}break;
				default:
					break;
			}
		}break;

		case 6:
		{
			switch(shape.similar)
			{
				case 1:
				{
					getData_6_1(x, y, shape);
				}break;
				case 2:
				{
					getData_6_2(x, y, shape);
				}break;
				default:
					break;
			}
		}break;

		case 7:
		{
			getData_7_1(x, y, shape);
		}break;

		default:
			break;
	}
}

int changedOver(Shape s)
{
	for(int i = 0; i < 4; i++)
	{
		if(s.point[i].x < 1 || s.point[i].x > WID_NUM - 2)
		{
			return 1;
		}
	}
	return 0;
}

void tauchXYchange(Shape &shape, char hit, int &x, int &y)
{
	if(hit == 'w' && !changedOver(shape))   //�����ж�
	{
		switch(shape.type)
		{
			case 1:{}
			case 2:{}
			case 3:
			{
				shape.similar += 1;
				if(shape.similar > 4)
				{
					shape.similar = 1;
				}
			}break;
			case 4:{}
			case 5:{}
			case 6:
			{
				if(shape.similar == 1)
				{
					shape.similar = 2; 
				}
				else
				{
					shape.similar = 1;
				}
			}break;
			case 7:
			{
			}break;
			default:
				break;
		}
	}
	else if(hit == 'a')
	{
		if(!leftOver(shape))  //������߽߱�
		{
			//�ж�������Ƿ�Ϊ2
			for(int i = 0; i < 4; i++)
			{
				 if(recordAll[shape.point[i].y][shape.point[i].x - 1] == 2)
				 {
					 break;
				 }
				 if(i == 3)
				 {
					x -= 1;
				 }
			}
		}
	}
	else if(hit == 'd')
	{
		if(!rightOver(shape))
		{
			//�ж�������Ƿ�Ϊ2
			for(int i = 0; i < 4; i++)
			{
				 if(recordAll[shape.point[i].y][shape.point[i].x + 1] == 2)
				 {
					 break;
				 }
				 if(i == 3)
				 {
					x += 1;
				 }
			}
		}
	}
}

//�ж��Ƿ����������ұ߽�,0�� 1 ��
int leftOver(Shape s)
{
	for(int i = 0; i < 4; i++)
	{
		if(s.point[i].x <= 0)
		{
			return 1;
		}
	}
	return 0;
}

//�ж��Ƿ����������ұ߽�,0�� 1 ��
int rightOver(Shape s)
{
	for(int i = 0; i < 4; i++)
	{
		if(s.point[i].x + 1>= WID_NUM)
		{
			return 1;
		}
	}
	return 0;
}

void initShape(Shape &shape, int x, int y)                                     //������Ҫ�޸Ļ�ȡ����
{
	int similar = 1;
	int type = rand()%7 + 1;
	if(type < 4)
	{
		similar = rand()%4 + 1;
	}
	else if(type != 7)
	{
		similar = rand()%2 + 1;
	}
	int color = rand()%7 + 1;
	shape.color = color;
	shape.similar = similar;
	shape.type = type;
	refreshOtherThreeByXY(shape, x, y);  
}

//�ж�ֹͣ���߼� ,1�ǣ�0��
int searchStop(Shape s)
{
	//һ���Ǵ����ײ�
	for(int i = 0; i < WID_NUM; i++)
	{
		if(recordAll[HIG_NUM - 1][i] == 1)
		{
			return 1;
		}
	}
	//һ�����������Ѿ����ڵģ�Ҳ����2
	for(int j = 0; j < 4; j++)
	{
		if(recordAll[s.point[j].y + 1][s.point[j].x] == 2)
		{
			return 1;
		}
	}

	return 0;
}

void getData_3_1(int x, int y, Shape &shape)
{
	shape.point[0].x = x;
	shape.point[0].y = y;

	shape.point[1].x = x;
	shape.point[1].y = y - 1;

	shape.point[2].x = x;
	shape.point[2].y = y + 1;

	shape.point[3].x = x + 1;
	shape.point[3].y = y + 1;
}

void getData_3_2(int x, int y, Shape &shape)
{
	shape.point[0].x = x;
	shape.point[0].y = y;

	shape.point[1].x = x - 1;
	shape.point[1].y = y;

	shape.point[2].x = x + 1;
	shape.point[2].y = y;

	shape.point[3].x = x - 1;
	shape.point[3].y = y + 1;
}

void getData_3_3(int x, int y, Shape &shape)
{
	shape.point[0].x = x;
	shape.point[0].y = y;

	shape.point[1].x = x;
	shape.point[1].y = y - 1;

	shape.point[2].x = x;
	shape.point[2].y = y + 1;

	shape.point[3].x = x - 1;
	shape.point[3].y = y - 1;
}

void getData_3_4(int x, int y, Shape &shape)
{
	shape.point[0].x = x;
	shape.point[0].y = y;

	shape.point[1].x = x - 1;
	shape.point[1].y = y;

	shape.point[2].x = x + 1;
	shape.point[2].y = y;

	shape.point[3].x = x + 1;
	shape.point[3].y = y - 1;
}

void getData_1_1(int x, int y, Shape &shape)
{
	shape.point[0].x = x;
	shape.point[0].y = y;

	shape.point[1].x = x - 1;
	shape.point[1].y = y;

	shape.point[2].x = x + 1;
	shape.point[2].y = y;

	shape.point[3].x = x;
	shape.point[3].y = y - 1;
}

void getData_1_2(int x, int y, Shape &shape)
{
	shape.point[0].x = x;
	shape.point[0].y = y;

	shape.point[1].x = x;
	shape.point[1].y = y - 1;

	shape.point[2].x = x;
	shape.point[2].y = y + 1;

	shape.point[3].x = x + 1;
	shape.point[3].y = y;
}

void getData_1_3(int x, int y, Shape &shape)
{
	shape.point[0].x = x;
	shape.point[0].y = y;

	shape.point[1].x = x - 1;
	shape.point[1].y = y;

	shape.point[2].x = x + 1;
	shape.point[2].y = y;

	shape.point[3].x = x;
	shape.point[3].y = y + 1;
}

void getData_1_4(int x, int y, Shape &shape)
{
	shape.point[0].x = x;
	shape.point[0].y = y;

	shape.point[1].x = x;
	shape.point[1].y = y - 1;

	shape.point[2].x = x;
	shape.point[2].y = y + 1;

	shape.point[3].x = x - 1;
	shape.point[3].y = y;
}

void getData_2_1(int x, int y, Shape &shape)
{
	shape.point[0].x = x;
	shape.point[0].y = y;

	shape.point[1].x = x;
	shape.point[1].y = y - 1;

	shape.point[2].x = x;
	shape.point[2].y = y + 1;

	shape.point[3].x = x - 1;
	shape.point[3].y = y + 1;
}

void getData_2_2(int x, int y, Shape &shape)
{
	shape.point[0].x = x;
	shape.point[0].y = y;

	shape.point[1].x = x - 1;
	shape.point[1].y = y;

	shape.point[2].x = x + 1;
	shape.point[2].y = y;

	shape.point[3].x = x - 1;
	shape.point[3].y = y - 1;
}

void getData_2_3(int x, int y, Shape &shape)
{
	shape.point[0].x = x;
	shape.point[0].y = y;

	shape.point[1].x = x;
	shape.point[1].y = y - 1;

	shape.point[2].x = x;
	shape.point[2].y = y + 1;

	shape.point[3].x = x + 1;
	shape.point[3].y = y - 1;
}

void getData_2_4(int x, int y, Shape &shape)
{
	shape.point[0].x = x;
	shape.point[0].y = y;

	shape.point[1].x = x - 1;
	shape.point[1].y = y;

	shape.point[2].x = x + 1;
	shape.point[2].y = y;

	shape.point[3].x = x + 1;
	shape.point[3].y = y + 1;
}

void getData_4_1(int x, int y, Shape &shape)
{
	shape.point[0].x = x;
	shape.point[0].y = y;

	shape.point[1].x = x - 1;
	shape.point[1].y = y;

	shape.point[2].x = x;
	shape.point[2].y = y - 1;

	shape.point[3].x = x + 1;
	shape.point[3].y = y - 1;
}

void getData_4_2(int x, int y, Shape &shape)
{
	shape.point[0].x = x;
	shape.point[0].y = y;

	shape.point[1].x = x;
	shape.point[1].y = y - 1;

	shape.point[2].x = x + 1;
	shape.point[2].y = y;

	shape.point[3].x = x + 1;
	shape.point[3].y = y + 1;
}

void getData_5_1(int x, int y, Shape &shape)
{
	shape.point[0].x = x;
	shape.point[0].y = y;

	shape.point[1].x = x + 1;
	shape.point[1].y = y;

	shape.point[2].x = x;
	shape.point[2].y = y - 1;

	shape.point[3].x = x - 1;
	shape.point[3].y = y - 1;
}

void getData_5_2(int x, int y, Shape &shape)
{
	shape.point[0].x = x;
	shape.point[0].y = y;

	shape.point[1].x = x;
	shape.point[1].y = y + 1;

	shape.point[2].x = x + 1;
	shape.point[2].y = y;

	shape.point[3].x = x + 1;
	shape.point[3].y = y - 1;
}

void getData_6_1(int x, int y, Shape &shape)
{
	shape.point[0].x = x;
	shape.point[0].y = y;

	shape.point[1].x = x - 1;
	shape.point[1].y = y;

	shape.point[2].x = x + 1;
	shape.point[2].y = y;

	shape.point[3].x = x + 2;
	shape.point[3].y = y;
}

void getData_6_2(int x, int y, Shape &shape)
{
	shape.point[0].x = x;
	shape.point[0].y = y;

	shape.point[1].x = x;
	shape.point[1].y = y - 1;

	shape.point[2].x = x;
	shape.point[2].y = y - 2;

	shape.point[3].x = x;
	shape.point[3].y = y + 1;
}

void getData_7_1(int x, int y, Shape &shape)
{
	shape.point[0].x = x;
	shape.point[0].y = y;

	shape.point[1].x = x - 1;
	shape.point[1].y = y;

	shape.point[2].x = x;
	shape.point[2].y = y - 1;

	shape.point[3].x = x - 1;
	shape.point[3].y = y - 1;
}
