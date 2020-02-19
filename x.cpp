#include "chen.h"

int main()
{
	initgraph(WIN_WID, WIN_HIG);
	srand( (unsigned)time( NULL ) ); 

	
	int refreshNewShape = 0;  //是否需要更新一个形状
	Shape shape;
	int x = rand()%(WID_NUM - 6) + 3;
	int y = -2;
	initShape(shape, x, y);   //初始化

	BeginBatchDraw(); 
	while(true)
	{
		if(_kbhit())   //是否有点击事件
		{
			char hit = _getch();
			tauchXYchange(shape, hit, x, y);   //左右 变形判断并修改坐标

			hit = ' ';
			fflush(stdin); 
		}
		y += 1;
		refreshOtherThreeByXY(shape, x, y);   //通过已经更新的xy坐标更新其他三个点坐标

		clearRecord();  //首先清空一下记录
		recordMoveShape(shape);  //将更新后的点记录
		if(searchStop(shape))
		{
			refreshNewShape = 1;
		}

		//在这里判断是否需要更新形状
		if(refreshNewShape)
		{
			recordStopShape(shape);    //先要将停下的形状，记录为2

			if(gameOver())    //插入判断是否游戏结束
			{
				break;
			}

			refreshNewShape = 0;  //重置为0
			//接着要判断是否有可以消除
			initClearLines();  //记录行的数组先重置
			searchCanClear();  //记录
			clearFullLine();

			x = rand()%(WID_NUM - 6) + 3;
			y = -2;
			initShape(shape, x, y);   //初始化
		}
		draw(shape);   //画背景，画图，画线, 画2形状
		FlushBatchDraw();  
		Sleep(400);
	}
	draw(shape); 
	setfillcolor(RED);
	solidrectangle(WIN_WID / 2 - 80, WIN_HIG/2 - 40, WIN_WID/2 + 80, WIN_HIG/2 + 40);
	char over[] = "GAME OVER!";
	outtextxy(WIN_WID / 2 - 45, WIN_HIG/2 - 8, over);
	EndBatchDraw();
	_getch();		
	closegraph();			
	return 0;
}