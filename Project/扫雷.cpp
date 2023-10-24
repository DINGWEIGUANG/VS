#include "Init_Map.h"

int main()
{
	IMAGE img[12];									// 定义图片数组
	int map[ROW][COL] = { 0 };						// 定义游戏的地图
 
	initgraph(COL*IMGW, ROW*IMGW, EW_SHOWCONSOLE);	// 创建图形窗口
	srand((unsigned)time(NULL));					// 设置随机数种子
	initMap(map);									// 初始化地图
	
	for (int i = 0; i < 12; i++)					// 加载图片
	{
		char fileName[50] = { 0 };
		sprintf_s(fileName,"./images/%d.png", i);
		loadimage(img + i, fileName, IMGW, IMGW);
	}
 
	while (1)
	{
		mouseEvent(map);							//鼠标操作
		drawMap(map, img);							//绘制地图
		judge_game(map);							//判断游戏是否结束、胜利
	}
 
	return 0;
}
