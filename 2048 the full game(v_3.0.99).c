#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#define size 4

/*int M[size][size] =
{
	{ 1,2,3,4 },
	{ 8,7,6,5 },
	{ 9,10,11,12 },
	{ 13,14,15,0 }
};*/
int M[size][size] =
{
	{ 0,0,0,0 },
	{ 0,0,0,0 },
	{ 0,0,0,0 },
	{ 0,0,0,0 }
};
/*
int M[size][size] =
{
	{ 8,8,4,2 },
	{ 0,8,2,2 },
	{ 2,0,0,2 },
	{ 2,0,2,0 }
};*///working test

//PrintBoard_nxn
int execute_l(int n) {
	if (n == 0) {
		return 1;
	}
	if (n != 0) {
		return(log10(n) + 1);
	}
	return 0;
}
int execute_laa(int n) {
	int lc = n + 1;
	if (lc % 2 == 0) {
		return 2;
	}
	if (lc % 2 == 1) {
		return 3;
	}
	return 0;
}
void PrintBoard(int board[size][size])
{
	for (int i = 0; i < size; i++)
	{
		for (int r = 0; r < size; r++)
		{
			printf("*******");
		}
		printf("*\n");
		for (int r = 0; r < size; r++)
		{
			printf("*      ");
		}
		printf("*\n");
		for (int j = 0; j < size; j++)
		{
			int l = execute_l(board[i][j]);//log10()+1=¦ì¼Æ				
			int laa = execute_laa(l) - l / 2;
			int lbb = 3 - l / 2;
			//printf("  laa=%d,lbb=%d  ", laa, lbb);
			printf("*");
			for (int la = 0; la < laa; la++) {
				printf(" ");
			}
			if (board[i][j] != 0)
				printf("%d", board[i][j]);
			else
				printf(" ");
			for (int lb = 0; lb < lbb; lb++) {
				printf(" ");
			}
			if (j > size - 2)
			{
				printf("*");
			}
		}
		printf("\n");
		for (int r = 0; r < size; r++)
		{
			printf("*      ");
		}
		printf("*\n");
		if (i > size - 2)
		{
			for (int r = 0; r < size; r++)
			{
				printf("*******");
			}
			printf("*\n");
		}
	}
	printf("\n\n");
}//PrintBoard(board[i][j])_v2.9.1(zero-space-revealing) by huai
 //content: main: PrintBoard(board[size][size]); sub: execute_l(int n); execute_laa(int n)

int dice()
{
	if (rand() % 10 <= 9)
		return 2;
	else return 4;
}
//choose the next number.

//score
int total = 0;
int scorecounting(int n)
{
	total = total + n;
	return 0;
}
//content: main:total=(score); scorecounting(n)

//madeboard
void madeboard(int board[size][size])
{
	int r;
	int i, j;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			board[i][j] = 0;
		}
	}
	total = 0;
	for (r = 1; r < 3; r++)
	{
		unsigned seed;
		seed = (unsigned)time(NULL);
		srand(seed);
		i = rand() % size;
		j = rand() % size;
		//printf("%d %d", i, j);
		if (board[i][j] == 0)
		{
			board[i][j] = board[i][j] + dice();
		}
		else
		{
			r = 1;
		}
	}
}
//content: madeboard(board[size][size])


void addnumber(int board[size][size])
{
	char d;
	int i, j,e=0,f=0;
	unsigned seed;
	seed = (unsigned)time(NULL);
	srand(seed);
	i = rand() % size;
	j = rand() % size;
	for (f = 0; f < 1; f++)
	{
		if (board[i][j] == 0)
		{
			board[i][j] = board[i][j] + dice();
			e = 0;
			printf("\n%d %d\n", i, j);
		}
		else
		{
			f = 0;
			printf("reset f=0");
			printf("\n%d %d\n", i, j);
		}
	}
	/*for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if(board[i][j]!=0)
				e++;
		}
	}
	if (e == 16)
	{
		printf("\n______________________________\n\n");
		printf("you can't move the numbers anymore.\n");
		PrintBoard(M);
		printf("press enter to countinues\n");
		getchar();
		printf("Do you wanna play again?\ny-yes,reset the board\nn-no,back the board\n>>");
		d=_getch();
		switch (d)
		{
		case'y':
			madeboard(M);
			break;
		case'n':
			break;
		}
	}*/
}

//goback
int last[size][size];
int lastscore;
int yester(int board[size][size], int score)
{
	int i, j;
	lastscore = score;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			last[i][j] = board[i][j];
		}
	}
	return 0;
}
int back(int board[size][size], int score)
{
	int i, j;
	score = lastscore;
	total = score;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			board[i][j] = last[i][j];
		}
	}
	return 0;
}
//content: last[size][size]; lastscore;
//             yester(board[size][size], (score)); back(board[size][size], (score))

int shalladdnewnumber(int board[size][size])
{
	int i, j,y=0;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (last[i][j] == board[i][j])
				y++;
		}
	}
	//printf("---%d---", y);
	if (y == 16)
	{
		printf("no add\n");
		y = 0;
	}
	else
	{
		addnumber(M);
		printf("add\n");
		y = 0;
	}
	return 0;
}

void prophet(int board[size][size])
{
	int i,j;
	int prophecy_W[size][size];
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			prophecy_W[i][j] = board[i][j];
		}
	}
	move_up(prophecy_W);
	
	int prophecy_A[size][size];
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			prophecy_A[i][j] = board[i][j];
		}
	}
	move_left(prophecy_A);

	int prophecy_S[size][size];
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			prophecy_S[i][j] = board[i][j];
		}
	}
	move_down(prophecy_S);

	int prophecy_D[size][size];
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			prophecy_D[i][j] = board[i][j];
		}
	}
	move_right(prophecy_D);
}

//movenumber
int move_up(int board[size][size])
{
	int j, i,r;
	for (j = 0; j < size; j++)
	{
		for (r = 0; r < size; r++)
		{
			for (i = 0; i < size-1; i++)
			{	
				if (board[i][j] == 0 && board[i + 1][j] != 0)
				{
					board[i][j] = board[i + 1][j];
					board[i + 1][j] = 0;
				}
			}
		}
		for (i = 0; i < size-1; i++)
		{
			if (board[i + 1][j] == board[i][j])
			{
				board[i][j] = board[i + 1][j] + board[i][j];
				scorecounting(board[i][j]);
				board[i + 1][j] = 0;
			}
		}
		for (i = 0; i < size-1; i++)
		{
			if (board[i][j] == 0 && board[i + 1][j] != 0)
			{
				board[i][j] = board[i + 1][j];
				board[i + 1][j] = 0;
			}
		}
	}
	return 0;
}
int move_down(int board[size][size])
{
	int j, i, r;
	for (j = 0; j < size; j++)
	{
		for (r = 0; r < size; r++)
		{
			for (i = size-1; i >0 ; i--)
			{
				if (board[i][j] == 0 && board[i-1][j] != 0)
				{
					board[i][j] = board[i-1][j];
					board[i-1][j] = 0;
				}
			}
		}
		for (i = size - 1; i > 0; i--)
		{
			if (board[i - 1][j] == board[i][j])
			{
				board[i][j] = board[i][j] + board[i - 1][j];
				scorecounting(board[i][j]);
				board[i - 1][j] = 0;
			}
		}
		for (i = size - 1; i >0; i--)
		{
			if (board[i][j] == 0 && board[i - 1][j] != 0)
			{
				board[i][j] = board[i - 1][j];
				board[i - 1][j] = 0;
			}
		}
	}
	return 0;
}
int move_left(int board[size][size])
{
	int i, j, r;
	for (i = 0; i < size; i++)
	{
		for (r = 0; r < size; r++)
		{
			for (j = 0; j < size-1; j++)
			{
				if (board[i][j] == 0 && board[i][j + 1] != 0)
				{
					board[i][j] = board[i][j + 1];
					board[i][j + 1] = 0;
				}
			}
		}
		for (j = 0; j < size-1; j++)
		{
			if (board[i][j + 1] == board[i][j])
			{
				board[i][j] = board[i][j + 1] + board[i][j];
				scorecounting(board[i][j]);
				board[i][j + 1] = 0;
			}
		}
		for (j = 0; j < size-1; j++)
		{
			if (board[i][j] == 0 && board[i][j + 1] != 0)
			{
				board[i][j] = board[i][j + 1];
				board[i][j + 1] = 0;
			}
		}
	}
	return 0;
}
int move_right(int board[size][size])
{
	int i, j, r;
	for (i = 0; i < size; i++)
	{
		for (r = 0; r < size; r++)
		{
			for (j = size - 1; j >0; j--)
			{
				if (board[i][j] == 0 && board[i][j - 1] != 0)
				{
					board[i][j] = board[i][j - 1];
					board[i][j - 1] = 0;
				}
			}
		}
		for (j = size - 1; j > 0; j--)
		{
			if (board[i][j - 1] == board[i][j])
			{
				board[i][j] = board[i][j] + board[i][j - 1];
				scorecounting(board[i][j]);
				board[i][j - 1] = 0;
			}
		}
		for (j = size - 1; j >0; j--)
		{
			if (board[i][j] == 0 && board[i][j - 1] != 0)
			{
				board[i][j] = board[i][j - 1];
				board[i][j - 1] = 0;
			}
		}
	}
	return 0;
}

int main()
{		
	int s = 0, l = 0, b = 1;
	printf("Welcome to 2048\n");
	printf("press h to open the hint\n");
	printf("press b to go back last board\n");
	printf("press WASD or Arrow keys to move\n");
	printf("press r twice to reset the board\n");
	printf("press x twice to leave the game\n");
	printf("\nLoaing......\n\n");
	madeboard(M);
	printf("score:%d\n", total);
	PrintBoard(M);
	printf(">");
	while (1 == 1)
	{
		char c;
		c=_getch();
		printf("%c",c);
		printf("\n______________________________\n\n");
		switch (c)
		{
		case 'w':;case'H':
		{
			s = 0, l = 0, b = 0;
			printf("move up\n");
			yester(M, total);
			move_up(M);
			shalladdnewnumber(M);
			break;
		}
		case 's':;case 'P':
		{
			s = 0, l = 0, b = 0;
			printf("move down\n");
			yester(M, total);
			move_down(M);
			shalladdnewnumber(M);
			break;
		}
		case 'a':;case 'K':
		{
			s = 0, l = 0, b = 0;
			printf("move left\n");
			yester(M, total);
			move_left(M);
			shalladdnewnumber(M);
			break;
		}
		case 'd':;case 'M':
		{
			s = 0, l = 0, b = 0;
			printf("move right\n");
			yester(M, total);
			move_right(M);
			shalladdnewnumber(M);
			break;
		}
		case 'h':
		{
			s = 0, l = 0;
			printf("Now you call the hint\n\n");
			printf("press h to open the help\n");
			printf("press b to go back last board\n");
			printf("press WASD or Arrow keys to move\n");
			printf("press r twice to reset the board\n");
			printf("press x twice to leave the game\n");
			printf("\n");
			break;
		}
		case 'b':
		{
			s = 0, l = 0;
			if(b==0)
			printf("Now you already go back the last board.\n\n");
			back(M, total);
			break;
		}
		case 'r':
		{
			s++;
			l = 0;
			if (s < 2)
			{
				printf("Do you want to reset the board?\n");
				printf("press r again-Yes,reset it.\n");
				printf("press other workable keys-No,I want to finish this game.\n");
				printf(">>");
			}
			break;
		}
		case 'z':
		{
			s = 0, l = 0;
			printf("Made by huai\n");
			printf("v3.0.99_(20180429 23:44)(expect_to_prophecy)\n\n");
			break;
		}
		case 'x':
		{
			l++;
			s = 0;
			if (l < 2)
			{
				printf("\n______________________________\n\n");
				printf("Do you want to leave the game?\n");
				printf("press x again-Yes,leave the game.\n");
				printf("press other workable keys-No,I want to finish this game.\n");
				printf(">>");
			}
			break;
		}
		default:
		{
			s = 0, l = 0;
			printf("This key dosn't set any fuction\n");
			break;
		}
		}
		printf("score:%d\n", total);
		PrintBoard(M);
		printf(">");
		if (s == 2)
		{
			printf("\nLoaing......\n \n");
			madeboard(M);
			printf("score:%d\n", total);
			PrintBoard(M);
			printf(">");
			s = 0;
		}
		if (l == 2)
		{
			break;
		}
	}
}