#include "Init_Map.h"

bool	isOver = false;									// ��Ϸ������־λ
int		flag = 0;										// �Ѿ��㿪�ķ��׸�����������������ﵽ��ROW*COL-BOOM����������90������ʤ��

//��ӡ��Ϸ������
void showMap(int map[ROW][COL])
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			printf("%2d ", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void initMap(int map[ROW][COL])
{
	//����ͼ��10���ף�����-1��ʾ
	for (int i = 0; i < BOOM; )
	{

		int r = rand() % ROW;
		int c = rand() % COL;
		if (map[r][c] == 0)
		{
			map[r][c] = -1;
			i++;		//ֻ�гɹ��������ף�������
		}
	}
	//�����ڵľŹ������еĸ��ӵ���ֵ��+1���׳���
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (map[i][j] == -1)
			{
				//���������ڵľŹ���
				for (int r = i - 1; r <= i + 1; r++)
				{
					for (int c = j - 1; c <= j + 1; c++)
					{
						//������֮��ĸ��ӣ���ֵ��+1
						if ((r >= 0 && r < ROW && c >= 0 && c < COL) && map[r][c] != -1)
						{
							map[r][c]++;
						}
					}
				}
			}
		}
	}
	//�����еĸ��Ӷ�����ͼ����������ÿ�����Ӷ����ܣ����綼����20
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < ROW; j++)
		{
			map[i][j] += 20;
		}
	}
}

void drawMap(int map[ROW][COL], IMAGE img[])
{
	//�������������ת���ɶ�Ӧ��ͼƬ����ͼ����ͼ�δ�������
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < ROW; j++)
		{
			//�հ׸��Ӻ�����
			if (map[i][j] >= 0 && map[i][j] <= 8)
			{
				putimage(j * IMGW, i * IMGW, img + map[i][j]);
			}
			//�ף�������ͼ
			else if (map[i][j] == -1)
			{
				putimage(j * IMGW, i * IMGW, img + 9);
			}
			//û���㿪�ĸ��ӣ������ڸ�ͼ
			else if (map[i][j] >= 19 && map[i][j] <= 28)
			{
				putimage(j * IMGW, i * IMGW, img + 10);
			}
			//�Ҽ���ǣ����ϱ��ͼ
			else if (map[i][j] == -2)
			{
				putimage(j * IMGW, i * IMGW, img + 11);
			}
		}
	}
}

void mouseEvent(int map[ROW][COL])
{
	//������Ϣ�ṹ�壨��ꡢ�������ַ���Ϣ��
	ExMessage msg;
	//�������Ϣ���᷵���棬���һ��msg����ֵ
	if (peekmessage(&msg, EM_MOUSE))
	{
		//����������ת�����±�
		int c = msg.x / IMGW;
		int r = msg.y / IMGW;
		if (msg.message == WM_LBUTTONDOWN)	//�����������
		{
			if (map[r][c] >= 19 && map[r][c] <= 28)	//	����ø���û�е㿪��������㿪����
			{
				flag++;
				map[r][c] -= 20;
				openNull(map, r, c);
				judge(map, r, c);
				showMap(map);
			}
			else if (map[r][c] == -2)	//����Ѿ������Ϊ�ף����������Ϸ����
			{
				flag++;
				map[r][c] = -1;
				judge(map, r, c);
				showMap(map);
			}
		}
		else if (msg.message == WM_RBUTTONDOWN)	//�������һ�������ʾ���ͼ
		{
			if (map[r][c] >= 19 && map[r][c] <= 28)
			{
				map[r][c] = -2;
				showMap(map);
			}
		}
	}
}

void openNull(int map[ROW][COL], int row, int col)
{
	//�жϵ�ǰ������Ƿ�Ϊ�հ�
	if (map[row][col] == 0)
	{
		//������Χ�Ź���
		for (int i = row - 1; i <= row + 1; i++)
		{
			for (int j = col - 1; j <= col + 1; j++)
			{
				//�����û�㿪�ķ��׸��ӣ��Ͱ���ը������ʾ������
				if ((i >= 0 && i < ROW && j >= 0 && j < COL) && map[i][j] >= 19 && map[i][j] <= 28)
				{
					map[i][j] -= 20;
					flag++;
					openNull(map, i, j);	//���ը�����ǿհ׸��ӣ��ݹ�ʵ������ը��
				}
			}
		}
	}
}

void judge(int map[ROW][COL], int row, int col)
{
	//����㵽�ף���game over ����һ�����������׶���ʾ����
	if (map[row][col] == -1)
	{
		//������ʾ��ͼ�е����е���
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				if (map[i][j] == 19)
				{
					map[i][j] -= 20;
					flag = 0;
				}

			}
		}
		isOver = true;
	}
}

void judge_game(int map[ROW][COL])
{
	//���ˣ��㵽��
	if (isOver)
	{
		int ret = MessageBox(GetHWnd(), "���Ѿ����ˣ��Ƿ������Ϸ��", "hit", MB_OKCANCEL);	//��ʾ��ʾ���ڣ��Ѿ����ˣ��Ƿ������Ϸ
		if (ret == IDOK)					//������ȷ�������³�ʼ����ͼ
		{
			//��map����
			memset(map, 0, ROW * COL * sizeof(int));
			initMap(map);
			showMap(map);
			isOver = false;
		}
		else if (ret == IDCANCEL)			//�������˳����˳�����
		{
			exit(666);
		}
	}
	//Ӯ�ˣ��������з��׵ĵ��Ӯ��
	if (flag == (ROW * COL - BOOM))
	{
		int ret = MessageBox(GetHWnd(), "���Ѿ�Ӯ�ˣ��Ƿ������Ϸ��", "666", MB_OKCANCEL);	//��ʾ��ʾ���ڣ��Ѿ�Ӯ�ˣ��Ƿ������Ϸ
		if (ret == IDOK)					//������ȷ�������³�ʼ����ͼ
		{
			//��map����
			flag = 0;
			memset(map, 0, ROW * COL * sizeof(int));
			initMap(map);
			showMap(map);
			isOver = false;
		}
		else if (ret == IDCANCEL)			//�������˳����˳�����
		{
			exit(666);
		}
	}
}