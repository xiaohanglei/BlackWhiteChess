#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXSIZE 8//  �����������ߴ�
//��������
int Exa(char board[][MAXSIZE], int arrput[][MAXSIZE], char );//���㲽��
void Print(char board[][MAXSIZE], int , int , char );//
int CalSore(char board[][MAXSIZE], char );
int Hint(char board[][MAXSIZE], int arrput[][MAXSIZE], char );//����㷨
void Foeplay(char board[][MAXSIZE], int arrput[][MAXSIZE], char );
void Show(char board[][MAXSIZE]);//��ʾ����
int main()
{
	char board[MAXSIZE][MAXSIZE];
	int arrput[MAXSIZE][MAXSIZE] = { 0 };
	int row, col, x, y;
	int count = 0;
	int level = 0;		
	int cross = 0;
	int score[2];
	char ok;
	char input[100];
	int order = 0;
	printf("=============================��ת��=============================\n");
	printf("REVERSI\n");
	printf("You will be white - (O)\nI will be black - (X).\nok a square for your move by typing a digit for the row\nand a letter for the column with no spaces between.\nGood luck! Press Enter to start.\n");
	scanf("%c", &ok);
	printf("Go First? Press 1 to go first,and 0 to go second.");
	scanf("%d", &order);
	if (order == 0)
		level = 1;

	if (level == 0)
	{
		level = 1;
	}
	else
	{
		level = 0;
	}
	count = 4;
	for (row = 0; row < MAXSIZE; row++)//�������̵ĳ�ʼֵ
	{
		for (col = 0; col < MAXSIZE; col++)
		{
			board[row][col] = 0;
		}
	}
	board[MAXSIZE / 2 - 1][MAXSIZE / 2 - 1] = board[MAXSIZE / 2][MAXSIZE / 2] = -1;	//��ʼ������
	board[MAXSIZE / 2 - 1][MAXSIZE / 2] = board[MAXSIZE / 2][MAXSIZE / 2 - 1] = 1;	
	printf("\nInitial:\n");
	Show(board);//��ʾ����
	int i = 0;
	for (i = count; count < (MAXSIZE*MAXSIZE) && cross < 2;)
	{
		if (level == 1)
		{
			level = 0;
			if (Exa(board, arrput, 2))
			{
				while (1)
				{
					printf("Please enter your move (row column- no space):");
					scanf("%s", input);
					x = input[0] - '0';//�����û������λ�ý���ת���ɶ�ά������±�
					y = input[1];
					x--;
					if (y >= 'a')
					{
						y = y - 'a' + 1;
					}
					else
					{
						y = y - 'A' + 1;
					}
					y--;//���û�������б�ת���ɶ�ά��������±�
					if (x >= 0 && y >= 0 && x < MAXSIZE && y < MAXSIZE && arrput[x][y])//�ж������Ƿ���ȷ
					{
						Print(board, x, y, 2);
						count++;
						break;
					}
					else
					{
						printf("Not a valid move, try again.\n");
					}
				}
				Show(board);//�����û������λ�ý��и������̲���ʾ
			}
			else if (++cross < 2)
			{
				printf("NO MOVE,AI GO.\n");
			}
			else
			{
				printf("BOTH NO MOVE, GAME OVER.\n");
			}
		}
		else
		{
			level = 1;
			if (Exa(board, arrput, 1))
			{
				cross = 0;
				Foeplay(board, arrput, 1);
				count++;
				Show(board);
			}
			else
			{
				if (++cross < 2)
				{
					printf("NO MOVE, nowplay GO.\n");
				}
				else
				{
					printf("BOTH NO MOVE, GAME OVER.");
				}
			}
		}
	} 
	Show(board);
	score[0] = score[1] = 0;
	for (row = 0; row < MAXSIZE; row++)//��ʼ�������
	{
		for (col = 0; col < MAXSIZE; col++)
		{
			score[0] = score[0] + (board[row][col] == -1);
			score[1] = score[1] + (board[row][col] == 1);
		}
	}
	printf("Final score:\n");
	printf("AI:%d\nnowplay:%d\n", score[1], score[0]);
	scanf("%c", &ok);
	return 0;
}
void Show(char board[][MAXSIZE])
{
	int row, col;
	printf("\n   ");
	for (col = 0; col < MAXSIZE; col++)//��ʾ ���̺����ʶ
	{
		printf("%c  ", col + 'a');
	}
	for (row = 0; row < MAXSIZE; row++)
	{
		printf("\n ");
		for (col = 0; col < MAXSIZE; col++)
		{
			printf("+--");
			if (col == (MAXSIZE - 1))
				printf("+\n");
		}
		printf("%c", row + '1');
		for (col = 0; col < MAXSIZE; col++)
		{
			if (board[row][col] == 1)//���������е�ֵ��ʾ��Ӧ�ı��
				printf("|�w");
			else if (board[row][col] == -1)
				printf("|��");
			else
			{
				printf("|  ");
			}
			if (col == (MAXSIZE - 1))
				printf("|");
		}
		if (row == (MAXSIZE - 1))
		{
			printf("\n ");
			for (col = 0; col < MAXSIZE; col++)//��ʾ�ָ���
			{
				printf("+--");
				if (col == (MAXSIZE - 1))
					printf("+\n");
			}
		}
	}
}
int Exa(char board[][MAXSIZE], int arrput[][MAXSIZE], char level)
{
	int rowd, cold, row, col, x, y = 0;
	int step = 0;	
	char foe;
	if (level == 1)
		foe = -1;
	else
		foe = 1;
	char player = -1 * foe;
	for (row = 0; row < MAXSIZE; row++)
	{
		for (col = 0; col < MAXSIZE; col++)
		{
			arrput[row][col] = 0;
		}
	}
	for (row = 0; row < MAXSIZE; row++)
	{
		for (col = 0; col < MAXSIZE; col++)
		{
			if (board[row][col] != 0)//�ҵ���ά������ֵλ1��Ԫ��
				continue;
			for (rowd = -1; rowd <= 1; rowd++)
				for (cold = -1; cold <= 1; cold++)
				{
					//�ж��Ƿ�Խ��
					if (row + rowd < 0 || row + rowd >= MAXSIZE
						|| col + cold < 0 || col + cold >= MAXSIZE
						|| (rowd == 0 && cold == 0))
					{
						continue;
					}
					if (board[row + rowd][col + cold] == foe)
					{
						x = row + rowd;
						y = col + cold;
						while (1)
						{
							x += rowd;
							y += cold;
							if (x < 0 || x >= MAXSIZE || y < 0 || y >= MAXSIZE)
							{
								break;
							}
							if (board[x][y] == 0)
							{
								break;
							}
							if (board[x][y] == player)
							{
								arrput[row][col] = 1;
								step++;
								break;
							}
						}
					}
				}
			}
	}
	return step;
}
void Print(char board[][MAXSIZE], int row, int col, char level)
{
	int rowd = 0, cold = 0, x = 0, y = 0;
	char foe;
	if (level == 1)
		foe = -1;
	else
		foe = 1;
	char player = -1 * foe;
	board[row][col] = player;
	for (rowd = -1; rowd <= 1; rowd++)
	{
		for (cold = -1; cold <= 1; cold++)
		{
			if (row + rowd < 0 || row + rowd >= MAXSIZE || col + cold < 0
				|| col + cold >= MAXSIZE || (rowd == 0 && cold == 0))//�ж��Ƿ�Խ��
			{
				continue;
			}
			if (board[row + rowd][col + cold] == foe)
			{
				x = row + rowd;
				y = col + cold;
				while (1)
				{
					x += rowd;
					y += cold;
					if (x < 0 || x >= MAXSIZE || y < 0 || y >= MAXSIZE)//�ж�Խ��
					{
						break;
					}
					if (board[x][y] == 0)
					{
						break;
					}
					if (board[x][y] == player)
					{
						while (board[x -= rowd][y -= cold] == foe)//�ҵ���ǰ��λ��
						{
							board[x][y] = player;
						}
						break;
					}
				}
			}
		}
	}
}
int CalSore(char board[][MAXSIZE], char level)//����ɼ�
{
	int score = 0;
	int row, col;
	char foe ;
	if (level == 1)
		foe = -1;
	else
		foe = 1;
	char player = -1 * foe;
	for (row = 0; row < MAXSIZE; row++)
		for (col = 0; col < MAXSIZE; col++)
		{
			score = score - (board[row][col] == foe);
			score = score + (board[row][col] == player);
		}
	return score;
}
int Hint(char board[][MAXSIZE], int arrput[][MAXSIZE], char level)//��ʾ����߷�
{
	int row, col, i, j;
	char board1[MAXSIZE][MAXSIZE] = { 0 };
	int maxscore = 0;
	int score = 0;
	char foe;
	if (level == 1)
		foe = -1;
	else
		foe = 1;
	for (row = 0; row < MAXSIZE; row++)
		for (col = 0; col < MAXSIZE; col++)
		{
			if (!arrput[row][col])
				continue;
			for (i = 0; i < MAXSIZE; i++)
				for (j = 0; j < MAXSIZE; j++)
				{
					board1[i][j] = board[i][j];
				}
			Print(board1, row, col, level);
			score = CalSore(board1, level);
			if (maxscore < score)
				maxscore = score;
		}
	return maxscore;
}
void Foeplay(char board[][MAXSIZE], int arrput[][MAXSIZE], char level)
{
	int row, col, row1, col1, i, j;
	int score = 0, minscore = 100;
	char board1[MAXSIZE][MAXSIZE];
	int arrput1[MAXSIZE][MAXSIZE];
	char foe;
	if (level == 1)
		foe = -1;
	else
		foe = 1;
	for (row = 0; row < MAXSIZE; row++)
	{
		for (col = 0; col < MAXSIZE; col++)
		{
			if (arrput[row][col] == 0)
			{
				continue;
			}
			for (i = 0; i < MAXSIZE; i++)
			{
				for (j = 0; j < MAXSIZE; j++)
				{
					board1[i][j] = board[i][j];
				}
			}
			Print(board1, row, col, level);
			Exa(board1, arrput1, foe);
			score = Hint(board1, arrput1, foe);
			if ((row == 0 && col == 0) || (row == 0 && col == MAXSIZE - 1 || row == MAXSIZE - 1 && col == 0 || row == MAXSIZE - 1 && col == MAXSIZE - 1))
			{
				minscore = score;
				row1 = row;
				col1 = col;
			}
			else if (row == 0 || row == MAXSIZE - 1 || col == 0 || col == MAXSIZE - 1)
			{
				minscore = score;
				row1 = row;
				col1 = col;
			}
			else if (score < minscore)
			{
				minscore = score;
				row1 = row;
				col1 = col;
			}
		}
	}
	Print(board, row1, col1, level);
}