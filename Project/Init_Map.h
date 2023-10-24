#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <easyx.h>
#include <graphics.h>

using namespace std;

#define		ROW		10		// 地图的行数
#define		COL		10		// 地图的列数
#define		BOOM	10		// 雷的个数
#define		IMGW	40		// 图片的宽度

void showMap(int map[ROW][COL]);						// 打印地图数据
void initMap(int map[ROW][COL]);						// 初始化地图
void mouseEvent(int map[ROW][COL]);						// 鼠标操作
void drawMap(int map[ROW][COL], IMAGE img[]);			// 绘制地图
void openNull(int map[ROW][COL], int row, int col);		// 炸开空白格子周围的非雷格子
void judge(int map[ROW][COL], int row, int col);		// 判断是否点到雷
void judge_game(int map[ROW][COL]);						// 判断游戏是否结束、胜利