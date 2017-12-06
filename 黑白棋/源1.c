#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 8
void Myprint(char chessboard[][SIZE])
{
	int row, col;
	printf("\n   ");
	for (col = 0; col < SIZE; col++)
	{
		printf("%c   ", col + 'a');
	}
	for (row = 0; row < SIZE; row++)
	{
		printf("\n ");
		for (col = 0; col < SIZE; col++)
		{
			printf("+---"); if (col == (SIZE - 1))printf("+\n");
		}
		printf("%c", row + '1');
		for (col = 0; col < SIZE; col++)
		{
			if (chessboard[row][col] == 1) printf("| X ");
			else if (chessboard[row][col] == -1) printf("| O ");
			else { printf("|   "); }
			if (col == (SIZE - 1))printf("|");
		}
		if (row == (SIZE - 1))
		{
			printf("\n ");
			for (col = 0; col < SIZE; col++)
			{
				printf("+---"); if (col == (SIZE - 1))printf("+\n");
			}
		}
	}

}
int Check(char chessboard[][SIZE], int can_put[][SIZE], char nowplay)
{
	int rowdelta, coldelta, row, col, x, y = 0;
	int iStep = 0;
	char opponent = (nowplay == 1) ? -1 : 1;
	char mynowplay = -1 * opponent;
	for (row = 0; row < SIZE; row++)
	{
		for (col = 0; col < SIZE; col++)
		{
			can_put[row][col] = 0;
		}
	}
	for (row = 0; row < SIZE; row++)
	{
		for (col = 0; col < SIZE; col++)
		{
			if (chessboard[row][col] != 0)
			{
				continue;
			}
			for (rowdelta = -1; rowdelta <= 1; rowdelta++)
			{
				for (coldelta = -1; coldelta <= 1; coldelta++)
				{
					if (row + rowdelta < 0 || row + rowdelta >= SIZE
						|| col + coldelta < 0 || col + coldelta >= SIZE
						|| (rowdelta == 0 && coldelta == 0))
					{
						continue;
					}
					if (chessboard[row + rowdelta][col + coldelta] == opponent)
					{
						x = row + rowdelta;
						y = col + coldelta;
						while (1)
						{
							x += rowdelta;
							y += coldelta;
							if (x < 0 || x >= SIZE || y < 0 || y >= SIZE)
							{
								break;
							}
							if (chessboard[x][y] == 0)
							{
								break;
							}
							if (chessboard[x][y] == mynowplay)
							{
								can_put[row][col] = 1;
								iStep++;
								break;
							}
						}
					}
				}
			}
		}
	}
	return iStep;
}
void Put(char chessboard[][SIZE], int row, int col, char nowplay)
{
	int rowdelta = 0, coldelta = 0, x = 0, y = 0;
	char opponent = (nowplay == 1) ? -1 : 1;
	char mynowplay = -1 * opponent;
	chessboard[row][col] = mynowplay;
	for (rowdelta = -1; rowdelta <= 1; rowdelta++)
	{
		for (coldelta = -1; coldelta <= 1; coldelta++)
		{
			if (row + rowdelta < 0 || row + rowdelta >= SIZE || col + coldelta < 0
				|| col + coldelta >= SIZE || (rowdelta == 0 && coldelta == 0))
			{
				continue;
			}
			if (chessboard[row + rowdelta][col + coldelta] == opponent)
			{
				x = row + rowdelta;
				y = col + coldelta;
				while (1)
				{
					x += rowdelta;
					y += coldelta;
					if (x < 0 || x >= SIZE || y < 0 || y >= SIZE)
					{
						break;
					}
					if (chessboard[x][y] == 0)
					{
						break;
					}
					if (chessboard[x][y] == mynowplay)
					{
						while (chessboard[x -= rowdelta][y -= coldelta] == opponent)
						{
							chessboard[x][y] = mynowplay;
						}
						break;
					}
				}
			}
		}
	}
}
int PlayScore(char chessboard[][SIZE], char nowplay)
{
	int Score = 0, row, col;
	char opponent = (nowplay == 1) ? -1 : 1;
	char mynowplay = -1 * opponent;
	for (row = 0; row < SIZE; row++)
	{
		for (col = 0; col < SIZE; col++)
		{
			Score = Score - (chessboard[row][col] == opponent);
			Score = Score + (chessboard[row][col] == mynowplay);
		}
	}
	return Score;
}
int AIchoose(char chessboard[][SIZE], int can_put[][SIZE], char nowplay)
{
	int row, col, i, j;
	char chessboard1[SIZE][SIZE] = { 0 };
	int MaxScore = 0;
	int Score = 0;
	char opponent = (nowplay == 1) ? -1 : 1;
	for (row = 0; row < SIZE; row++)
	{
		for (col = 0; col < SIZE; col++)
		{
			if (!can_put[row][col])
			{
				continue;
			}
			for (i = 0; i < SIZE; i++)
			{
				for (j = 0; j < SIZE; j++)
				{
					chessboard1[i][j] = chessboard[i][j];
				}
			}
			Put(chessboard1, row, col, nowplay);
			Score = PlayScore(chessboard1, nowplay);
			if (MaxScore < Score)
			{
				MaxScore = Score;
			}
		}
	}
	return MaxScore;
}
void AIplay(char chessboard[][SIZE], int can_put[][SIZE], char nowplay)
{
	int row, col, row1, col1, i, j;
	int Score = 0, MinScore = 100;
	char chessboard1[SIZE][SIZE];
	int can_put1[SIZE][SIZE];
	char opponent = (nowplay == 1) ? -1 : 1;
	for (row = 0; row < SIZE; row++)
	{
		for (col = 0; col < SIZE; col++)
		{
			if (can_put[row][col] == 0)
			{
				continue;
			}
			for (i = 0; i < SIZE; i++)
			{
				for (j = 0; j < SIZE; j++)
				{
					chessboard1[i][j] = chessboard[i][j];
				}
			}
			Put(chessboard1, row, col, nowplay);
			Check(chessboard1, can_put1, opponent);
			Score = AIchoose(chessboard1, can_put1, opponent);
			if ((row == 0 && col == 0) || (row == 0 && col == SIZE - 1 || row == SIZE - 1 && col == 0 || row == SIZE - 1 && col == SIZE - 1))
			{
				MinScore = Score;
				row1 = row;
				col1 = col;
			}
			else if(row == 0 || row == SIZE - 1 || col == 0 || col == SIZE - 1)
			{
				MinScore = Score;
				row1 = row;
				col1 = col;
			}
			else if (Score < MinScore)
			{
				//if(row == 1&&col==0||row==1&&col==1||row==0&&col==1||row==SIZE-2&&col==0||row==SIZE-2&&col==1||row==SIZE-1&&col==1||)
				MinScore = Score;
				row1 = row;
				col1 = col;
			}
		}
	}
	Put(chessboard, row1, col1, nowplay);
}
int main()
{
	char chessboard[SIZE][SIZE];
	int can_put[SIZE][SIZE] = { 0 };
	int row, col, x, y;
	int count = 0;
	int nowplay = 0;			//nowplay:0  AI:1
	int skip = 0;
	int Score[2];
	char ok;
	char input[100];
	int order = 0;
	printf("REVERSI\n");
	printf("You will be white - (O)\nI will be black - (X).\nok a square for your move by typing a digit for the row\nand a letter for the column with no spaces between.\nGood luck! Press Enter to start.\n");
	scanf("%c", &ok);
	printf("Go First? Press 1 to go first,and 0 to go second.");
	scanf("%d", &order);
	if (order == 0) { nowplay = 1; }
	if (nowplay == 0)
	{
		nowplay = 1;
	}
	else
	{
		nowplay = 0;
	}
	count = 4;
	for (row = 0; row < SIZE; row++)
	{
		for (col = 0; col < SIZE; col++)
		{
			chessboard[row][col] = 0;
		}
	}
	chessboard[SIZE / 2 - 1][SIZE / 2 - 1] = chessboard[SIZE / 2][SIZE / 2] = -1;	//put O
	chessboard[SIZE / 2 - 1][SIZE / 2] = chessboard[SIZE / 2][SIZE / 2 - 1] = 1;	//put X
	printf("\nInitial:\n");
	Myprint(chessboard);
	do
	{
		if (nowplay == 1)
		{
			nowplay = 0;
			if (Check(chessboard, can_put, 2))
			{
				while (1)
				{
					printf("Please enter your move (row column- no space):");
					scanf("%s", input);
					x = input[0] - '0';
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
					y--;
					if (x >= 0 && y >= 0 && x < SIZE && y < SIZE && can_put[x][y])
					{
						Put(chessboard, x, y, 2);
						count++;
						break;
					}
					else
					{
						printf("Not a valid move, try again.\n");
					}
				}
				Myprint(chessboard);
			}
			else if (++skip < 2)
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
			nowplay = 1;
			if (Check(chessboard, can_put, 1))
			{
				skip = 0;
				AIplay(chessboard, can_put, 1);
				count++;
				Myprint(chessboard);
			}
			else
			{
				if (++skip < 2)
				{
					printf("NO MOVE, nowplay GO.\n");
				}
				else
				{
					printf("BOTH NO MOVE, GAME OVER.");
				}
			}
		}
	} while (count < (SIZE*SIZE) && skip < 2);
	Myprint(chessboard);
	Score[0] = Score[1] = 0;
	for (row = 0; row < SIZE; row++)
	{
		for (col = 0; col < SIZE; col++)
		{
			Score[0] = Score[0] + (chessboard[row][col] == -1);
			Score[1] = Score[1] + (chessboard[row][col] == 1);
		}
	}
	printf("Final Score:\n");
	printf("AI:%d\nnowplay:%d\n", Score[1], Score[0]);
	scanf("%c", &ok);
	return 0;
}
