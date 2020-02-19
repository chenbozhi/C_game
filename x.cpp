#include "chen.h"

int main()
{
	initgraph(WIN_WID, WIN_HIG);
	srand( (unsigned)time( NULL ) ); 

	
	int refreshNewShape = 0;  //�Ƿ���Ҫ����һ����״
	Shape shape;
	int x = rand()%(WID_NUM - 6) + 3;
	int y = -2;
	initShape(shape, x, y);   //��ʼ��

	BeginBatchDraw(); 
	while(true)
	{
		if(_kbhit())   //�Ƿ��е���¼�
		{
			char hit = _getch();
			tauchXYchange(shape, hit, x, y);   //���� �����жϲ��޸�����

			hit = ' ';
			fflush(stdin); 
		}
		y += 1;
		refreshOtherThreeByXY(shape, x, y);   //ͨ���Ѿ����µ�xy���������������������

		clearRecord();  //�������һ�¼�¼
		recordMoveShape(shape);  //�����º�ĵ��¼
		if(searchStop(shape))
		{
			refreshNewShape = 1;
		}

		//�������ж��Ƿ���Ҫ������״
		if(refreshNewShape)
		{
			recordStopShape(shape);    //��Ҫ��ͣ�µ���״����¼Ϊ2

			if(gameOver())    //�����ж��Ƿ���Ϸ����
			{
				break;
			}

			refreshNewShape = 0;  //����Ϊ0
			//����Ҫ�ж��Ƿ��п�������
			initClearLines();  //��¼�е�����������
			searchCanClear();  //��¼
			clearFullLine();

			x = rand()%(WID_NUM - 6) + 3;
			y = -2;
			initShape(shape, x, y);   //��ʼ��
		}
		draw(shape);   //����������ͼ������, ��2��״
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