#include "Init_Map.h"

bool	isOver = false;									// 游戏结束标志位
int		flag = 0;										// 已经点开的非雷格子数，如果格子数达到（ROW*COL-BOOM）（这里是90），就胜利

//打印游戏的数据
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
	//给地图埋10个雷，雷用-1表示
	for (int i = 0; i < BOOM; )
	{

		int r = rand() % ROW;
		int c = rand() % COL;
		if (map[r][c] == 0)
		{
			map[r][c] = -1;
			i++;		//只有成功设置了雷，才自增
		}
	}
	//雷所在的九宫格所有的格子的数值都+1，雷除外
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (map[i][j] == -1)
			{
				//遍历雷所在的九宫格
				for (int r = i - 1; r <= i + 1; r++)
				{
					for (int c = j - 1; c <= j + 1; c++)
					{
						//除了雷之外的格子，数值都+1
						if ((r >= 0 && r < ROW && c >= 0 && c < COL) && map[r][c] != -1)
						{
							map[r][c]++;
						}
					}
				}
			}
		}
	}
	//把所有的格子都用遮图盖起来，给每个格子都加密，比如都加上20
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
	//把数组里的数据转换成对应的图片，贴图贴到图形窗口上面
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < ROW; j++)
		{
			//空白格子和数字
			if (map[i][j] >= 0 && map[i][j] <= 8)
			{
				putimage(j * IMGW, i * IMGW, img + map[i][j]);
			}
			//雷，贴上雷图
			else if (map[i][j] == -1)
			{
				putimage(j * IMGW, i * IMGW, img + 9);
			}
			//没被点开的格子，贴上遮盖图
			else if (map[i][j] >= 19 && map[i][j] <= 28)
			{
				putimage(j * IMGW, i * IMGW, img + 10);
			}
			//右键标记，贴上标记图
			else if (map[i][j] == -2)
			{
				putimage(j * IMGW, i * IMGW, img + 11);
			}
		}
	}
}

void mouseEvent(int map[ROW][COL])
{
	//定义消息结构体（鼠标、按键、字符消息）
	ExMessage msg;
	//如果有消息，会返回真，并且会给msg设置值
	if (peekmessage(&msg, EM_MOUSE))
	{
		//把鼠标的坐标转换成下标
		int c = msg.x / IMGW;
		int r = msg.y / IMGW;
		if (msg.message == WM_LBUTTONDOWN)	//如果鼠标左击，
		{
			if (map[r][c] >= 19 && map[r][c] <= 28)	//	如果该格子没有点开，则允许点开格子
			{
				flag++;
				map[r][c] -= 20;
				openNull(map, r, c);
				judge(map, r, c);
				showMap(map);
			}
			else if (map[r][c] == -2)	//如果已经被标记为雷，还左击则游戏结束
			{
				flag++;
				map[r][c] = -1;
				judge(map, r, c);
				showMap(map);
			}
		}
		else if (msg.message == WM_RBUTTONDOWN)	//如果鼠标右击，则显示标记图
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
	//判断当前点击的是否为空白
	if (map[row][col] == 0)
	{
		//遍历周围九宫格
		for (int i = row - 1; i <= row + 1; i++)
		{
			for (int j = col - 1; j <= col + 1; j++)
			{
				//如果有没点开的非雷格子，就把它炸开（显示出来）
				if ((i >= 0 && i < ROW && j >= 0 && j < COL) && map[i][j] >= 19 && map[i][j] <= 28)
				{
					map[i][j] -= 20;
					flag++;
					openNull(map, i, j);	//如果炸开的是空白格子，递归实现连续炸开
				}
			}
		}
	}
}

void judge(int map[ROW][COL], int row, int col)
{
	//如果点到雷，就game over ，点一个雷其他的雷都显示出来
	if (map[row][col] == -1)
	{
		//遍历显示地图中的所有的雷
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
	//输了，点到雷
	if (isOver)
	{
		int ret = MessageBox(GetHWnd(), "你已经输了，是否继续游戏？", "hit", MB_OKCANCEL);	//显示提示窗口：已经输了，是否继续游戏
		if (ret == IDOK)					//如果左击确定，重新初始化地图
		{
			//把map清零
			memset(map, 0, ROW * COL * sizeof(int));
			initMap(map);
			showMap(map);
			isOver = false;
		}
		else if (ret == IDCANCEL)			//如果左击退出，退出程序
		{
			exit(666);
		}
	}
	//赢了，点了所有非雷的点就赢了
	if (flag == (ROW * COL - BOOM))
	{
		int ret = MessageBox(GetHWnd(), "你已经赢了，是否继续游戏？", "666", MB_OKCANCEL);	//显示提示窗口：已经赢了，是否继续游戏
		if (ret == IDOK)					//如果左击确定，重新初始化地图
		{
			//把map清零
			flag = 0;
			memset(map, 0, ROW * COL * sizeof(int));
			initMap(map);
			showMap(map);
			isOver = false;
		}
		else if (ret == IDCANCEL)			//如果左击退出，退出程序
		{
			exit(666);
		}
	}
}