#include<graphics.h>//使用EasyX库里的graphics.h创建图形界面
#include <iostream>//标准C++头文件
#include<conio.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

//原图34张 掩码图34张 背景图1张
IMAGE img_x[34], img_y[34], bg;
int x = 0, y = 200;
int MoveNum = 0;

//加载图片
void InitImg()
{
	//加载34张图片

	//用来转换图片的路径
	char buff_x[128], buff_y[128];

	for (int i = 0; i < 34; i++)
	{
    //格式转换  0-33    1-34
		sprintf_s(buff_x, "images\\%dx.png", i + 1);
		sprintf_s(buff_y, "images\\%dy.png", i + 1);
		//0-33 数组下标也是0-33
		loadimage(&img_x[i], buff_x);
		loadimage(&img_y[i], buff_y);
	}
	//加载背景图
	loadimage(&bg, "images\\br.jpg", 535, 300);


}

//绘制人物
void Draw()
{
	//掩码图
	putimage(x, y, &img_y[MoveNum], SRCAND);
	//原图
	putimage(x, y, &img_x[MoveNum], SRCPAINT);
	//反复的贴图
	MoveNum++;//就是图片移动
	Sleep(50);
	//还原图片 如果超出了变化范围 还原
	if (MoveNum == 24)
		MoveNum = 0;

}

//向右移动
void RightMove()
{
	MoveNum = 24;//从第25张图片开始
	while (MoveNum < 34)//贴图
	{
		BeginBatchDraw();
		putimage(0, 0, &bg);//背景图
		Draw();//画人物
		MoveNum++;
		Sleep(100);
		EndBatchDraw();
	}
	MoveNum = 0;
}

//技能的释放
void KeyPlay()
{

}

int main()
{
	//1.创建窗口     宽 高 单位:px像素
	initgraph(535, 300);
#if 0
	IMAGE img;//定义变量

	//1.图片存储的位置
	//2.图片所在的位置
	//3.图片的宽
	//4.图片的高
	loadimage(&img, "images\\br.jpg", 535, 300);

	//显示图片
	//操作系统中的y往下是加，x往右是加，坐标原点在左上角
	//1|2 x,y表示图片在窗口显示的位置
	//3.显示的图片变量
	putimage(0, 0, &img);
#endif

	//播放音频
	mciSendString("play a.mp3 repeat", 0, 0, 0);

	InitImg();

	while (1)
	{
		BeginBatchDraw();
		putimage(0, 0, &bg);
		Draw();
		//通过键盘按键 改变图片位置及人物移动
		if (_kbhit()) {
			//从键盘获取一个字符
			switch (_getch()) {
				//人物向上
			case 'W':
			case 'w':
			case 72:
				y = y - 10;//向上移动10px
				break;
			case 'S':
			case 's':
			case 80:
				y = y + 10;//向下移动10px
				break;
			case 'A':
			case 'a':
			case 75:
				x = x - 10;//向左移动10px
				break;
			case 'D':
			case 'd':
			case 77:
				RightMove();
				x = x + 10;
				break;
			case 'J':
			case 'j':
				//释放游戏技能
				break;
			}
		}

		EndBatchDraw();

	}

	system("pause");//悬停窗口

	return 0;
}
