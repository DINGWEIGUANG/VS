#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <easyx.h>
#include <graphics.h>

using namespace std;

#define		ROW		10		// ��ͼ������
#define		COL		10		// ��ͼ������
#define		BOOM	10		// �׵ĸ���
#define		IMGW	40		// ͼƬ�Ŀ��

void showMap(int map[ROW][COL]);						// ��ӡ��ͼ����
void initMap(int map[ROW][COL]);						// ��ʼ����ͼ
void mouseEvent(int map[ROW][COL]);						// ������
void drawMap(int map[ROW][COL], IMAGE img[]);			// ���Ƶ�ͼ
void openNull(int map[ROW][COL], int row, int col);		// ը���հ׸�����Χ�ķ��׸���
void judge(int map[ROW][COL], int row, int col);		// �ж��Ƿ�㵽��
void judge_game(int map[ROW][COL]);						// �ж���Ϸ�Ƿ������ʤ��