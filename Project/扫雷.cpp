#include "Init_Map.h"

int main()
{
	IMAGE img[12];									// ����ͼƬ����
	int map[ROW][COL] = { 0 };						// ������Ϸ�ĵ�ͼ
 
	initgraph(COL*IMGW, ROW*IMGW, EW_SHOWCONSOLE);	// ����ͼ�δ���
	srand((unsigned)time(NULL));					// �������������
	initMap(map);									// ��ʼ����ͼ
	
	for (int i = 0; i < 12; i++)					// ����ͼƬ
	{
		char fileName[50] = { 0 };
		sprintf_s(fileName,"./images/%d.png", i);
		loadimage(img + i, fileName, IMGW, IMGW);
	}
 
	while (1)
	{
		mouseEvent(map);							//������
		drawMap(map, img);							//���Ƶ�ͼ
		judge_game(map);							//�ж���Ϸ�Ƿ������ʤ��
	}
 
	return 0;
}
