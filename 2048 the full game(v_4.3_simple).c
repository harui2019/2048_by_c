#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#define size 4
#define table (size*size)

int M[size][size], total = 0;//Matrix&score5
int counting(int n){
	int a=0;
	while (n > 0)
		a++, n /= 10;
	return a;
}
int execute_l(int n) {
	if (n == 0) 
		return 1;
	else return counting(n);
}
int execute_laa(int n) {
	int lc = n + 1;
	if (lc % 2 == 0) 
		return 2;
	else return 3;
}
void PrintBoard(int board[size][size]){
	for (int i = 0; i < size; i++){
		for (int r = 0; r < size; r++)
			printf("*******");
		printf("*\n");
		for (int r = 0; r < size; r++)
			printf("*      ");
		printf("*\n");
		for (int j = 0; j < size; j++){
			int l = execute_l(board[i][j]);//log10()+1=���				
			int laa = execute_laa(l) - l / 2;
			int lbb = 3 - l / 2;
			printf("*");
			for (int la = 0; la < laa; la++) 
				printf(" ");
			if (board[i][j] != 0)
				printf("%d", board[i][j]);
			else
				printf(" ");
			for (int lb = 0; lb < lbb; lb++)
				printf(" ");
			if (j > size - 2)
				printf("*");
		}
		printf("\n");
		for (int r = 0; r < size; r++)
			printf("*      ");
		printf("*\n");
		if (i > size - 2){
			for (int r = 0; r < size; r++)
				printf("*******");
			printf("*\n");
		}
	}
	printf("\n\n");
}
void transMatrix(int A[size][size],int B[size][size]){
	int i, j;
	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++)
			A[i][j] = B[i][j];
	}
}
int dice(){
	if (rand() % 10 <= 9)
		return 2;
	else return 4;
}
void madeboard(int board[size][size]){
	int r;
	int i, j;
	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++)
			board[i][j] = 0;
	}
	total = 0;
	for (r = 1; r < 3; r++){
		unsigned seed;
		seed = (unsigned)time(NULL);
		srand(seed);
		i = rand() % size;
		j = rand() % size;
		if (board[i][j] == 0)
			board[i][j] = board[i][j] + dice();
		else
			r = 1;
	}
}
void addnumber(int board[size][size]){
	int i, j, f = 0;
	unsigned seed;
	seed = (unsigned)time(NULL);
	srand(seed);
	while (f == 0){
		i = rand() % size;
		j = rand() % size;
		if (board[i][j] == 0)
			f = 1;
		else
			f = 0;
	}
	if (f == 1)
		board[i][j] = dice(), f = 0;
}
int lastangle(int M[size][size]){
	int i, j, a = 0;
	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			if (M[i][j] != 0)
				a++;
		}
	}
		return a;
}
int last[size][size], lastscore;
void yester(int board[size][size], int score){
	int i, j;
	lastscore = score;
	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++)
			last[i][j] = board[i][j];
	}
}
void back(int board[size][size], int score){
	int i, j;
	score = lastscore;
	total = score;
	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++)
			board[i][j] = last[i][j];
	}
}
int move_up(int board[size][size]){
	int j, i, r, n = 0;
	for (j = 0; j < size; j++){
		for (r = 0; r < size; r++){
			for (i = 0; i < size - 1; i++)	{
				if (board[i][j] == 0 && board[i + 1][j] != 0){
					board[i][j] = board[i + 1][j];
					board[i + 1][j] = 0;
				}
			}
		}
		for (i = 0; i < size - 1; i++){
			if (board[i + 1][j] == board[i][j])	{
				board[i][j] = board[i + 1][j] + board[i][j];
				n = n + board[i][j];
				board[i + 1][j] = 0;
			}
		}
		for (i = 0; i < size - 1; i++){
			if (board[i][j] == 0 && board[i + 1][j] != 0)	{
				board[i][j] = board[i + 1][j];
				board[i + 1][j] = 0;
			}
		}
	}
	return n;
}
int move_down(int board[size][size]){
	int j, i, r, n = 0;
	for (j = 0; j < size; j++){
		for (r = 0; r < size; r++)	{
			for (i = size - 1; i >0; i--)	{
				if (board[i][j] == 0 && board[i - 1][j] != 0)				{
					board[i][j] = board[i - 1][j];
					board[i - 1][j] = 0;
				}
			}
		}
		for (i = size - 1; i > 0; i--)		{
			if (board[i - 1][j] == board[i][j])			{
				board[i][j] = board[i][j] + board[i - 1][j];
				n = n + board[i][j];
				board[i - 1][j] = 0;
			}
		}
		for (i = size - 1; i >0; i--)	{
			if (board[i][j] == 0 && board[i - 1][j] != 0)		{
				board[i][j] = board[i - 1][j];
				board[i - 1][j] = 0;
			}
		}
	}
	return n;
}
int move_left(int board[size][size]){
	int i, j, r, n = 0;
	for (i = 0; i < size; i++)	{
		for (r = 0; r < size; r++)	{
			for (j = 0; j < size - 1; j++)			{
				if (board[i][j] == 0 && board[i][j + 1] != 0)			{
					board[i][j] = board[i][j + 1];
					board[i][j + 1] = 0;
				}
			}
		}
		for (j = 0; j < size - 1; j++)		{
			if (board[i][j + 1] == board[i][j])			{
				board[i][j] = board[i][j + 1] + board[i][j];
				n = n + board[i][j];
				board[i][j + 1] = 0;
			}
		}
		for (j = 0; j < size - 1; j++)	{
			if (board[i][j] == 0 && board[i][j + 1] != 0)		{
				board[i][j] = board[i][j + 1];
				board[i][j + 1] = 0;
			}
		}
	}
	return n;
}
int move_right(int board[size][size]){
	int i, j, r, n = 0;
	for (i = 0; i < size; i++)	{
		for (r = 0; r < size; r++)	{
			for (j = size - 1; j >0; j--)			{
				if (board[i][j] == 0 && board[i][j - 1] != 0)			{
					board[i][j] = board[i][j - 1];
					board[i][j - 1] = 0;
				}
			}
		}
		for (j = size - 1; j > 0; j--)	{
			if (board[i][j - 1] == board[i][j])		{
				board[i][j] = board[i][j] + board[i][j - 1];
				n = n + board[i][j];
				board[i][j - 1] = 0;
			}
		}
		for (j = size - 1; j >0; j--)	{
			if (board[i][j] == 0 && board[i][j - 1] != 0)		{
				board[i][j] = board[i][j - 1];
				board[i][j - 1] = 0;
			}
		}
	}
	return n;
}
int move_YN(int C[size][size], int D[size][size])
{
	int i, j, m = 0;
	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++)	{
			if (C[i][j] == D[i][j])
				m++;
		}
	}
	if (m == table)
		return 0;
	else return 1;
}
int prophecy_W[size][size], message_W;
int prophecy_A[size][size], message_A;
int prophecy_S[size][size], message_S;
int prophecy_D[size][size], message_D;
void prophets(int board[size][size]){
	transMatrix(prophecy_W, board);
	message_W = move_up(prophecy_W);
	transMatrix(prophecy_A, board);
	message_A = move_left(prophecy_A);
	transMatrix(prophecy_S, board);
	message_S = move_down(prophecy_S);
	transMatrix(prophecy_D, board);
	message_D = move_right(prophecy_D);
}
int m = 0;
void afterexcess(){
	prophets(M);
	printf("\nscore:%d\n", total);
	PrintBoard(M);
	printf(">");
}
void impact(){
	int i, j, w = 0, a = 0, s = 0, d = 0;
	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			if (M[i][j] == prophecy_W[i][j])
				w++;
		}
	}
	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			if (M[i][j] == prophecy_A[i][j])
				a++;
		}
	}
	for (i = 0; i < size; i++)	{
		for (j = 0; j < size; j++)		{
			if (M[i][j] == prophecy_S[i][j])
				s++;
		}
	}
	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++)	{
			if (M[i][j] == prophecy_D[i][j])
				d++;
		}
	}
	if (w == table && a == table && s == table && s == table)	{		
		printf("\nThe game is over.");
		printf("\nPress y to restart.");
		printf("\nPress n to leave the game.");
		printf("\nscore:%d\n", total);
		PrintBoard(M);
		printf("\nPress y or n\n>");
		m = 1;
	}
}
void process(int M[size][size],int prophecy[size][size],int message){
	if (move_YN(M, prophecy) == 1){
		yester(M, total);
		total = total + message;
		transMatrix(M, prophecy);
		addnumber(M);
		afterexcess();
	}
	if (lastangle(M) >= (table - 1))
		impact();
}
void hint(){
	printf("press h to open the hint\n");
	printf("press b to go back last board\n");
	printf("press WASD or Arrow keys to move\n");
	printf("press r twice to reset the board\n");
	printf("press x twice to leave the game\n");
	if (m == 1){
		printf("\n");
		printf("\nThe game is over.");
		printf("\nPress y to restart.");
		printf("\nPress n to leave the game.");
		printf("\n");
	}
}
int main(){		
	int s = 0, l = 0;
	printf("Welcome to 2048\n");
	hint();
	printf("\nLoaing......\n\n");
	madeboard(M);
	afterexcess();
	while (1 == 1){
		char c;
		c=_getch();
		switch (c){
		case 'w':;case 'H':{
			if (move_YN(M, prophecy_W) == 1 && m == 0)	{
				printf("%c", c);
				s = 0, l = 0, m = 0;
				printf("\n______________________________\n\n");
				printf("move up\n");
				process(M, prophecy_W, message_W);
			}
		break;
		}
		case 's':;case 'P':{
			if (move_YN(M, prophecy_S) == 1 && m == 0){
				printf("%c", c);
				s = 0, l = 0, m = 0;
				printf("\n______________________________\n\n");
				printf("move down\n");
				process(M, prophecy_S, message_S);
			}
			break;
		}
		case 'a':;case 'K':{
			if (move_YN(M, prophecy_A) == 1 && m == 0){
				printf("%c", c);
				s = 0, l = 0, m = 0;
				printf("\n______________________________\n\n");
				printf("move left\n");
				process(M, prophecy_A, message_A);
			}
			break;
		}
		case 'd':;case 'M':{
			if (move_YN(M, prophecy_D) == 1 && m == 0){
				printf("%c", c);
				s = 0, l = 0, m = 0;
				printf("\n______________________________\n\n");
				printf("move right\n");
				process(M, prophecy_D, message_D);
			}
			break;
		}
		case 'h':{
			s = 0, l = 0;
			printf("\n______________________________\n\n");
			hint();
			afterexcess();
			break;
		}
		case 'b':{
			s = 0, l = 0, m = 0;
			back(M, total);
			printf("\n______________________________\n\n");
			printf("Now you already go back the last board.\n\n");
			afterexcess();
			break;
		}
		case 'r':{
			s++, l = 0;
			if (s < 2){
				printf("\n______________________________\n\n");
				printf("Do you want to reset the board?\n");
				printf("press r again-Yes,reset it.\n");
				printf("press other workable keys-No,I want to finish this game.\n");
				printf(">>");
			}
			afterexcess();
			break;
		}
		case 'z':{
			s = 0, l = 0;
			printf("\n______________________________\n\n");
			printf("Made by huai\n");
			printf("v4.3_simple(20180503 17:17)\n\n");
			afterexcess();
			break;
		}
		case 'x':{
			l++, s = 0;
			if (l < 2){
				printf("\n______________________________\n\n");
				printf("Do you want to leave the game?\n");
				printf("press x again-Yes,leave the game.\n");
				printf("press other workable keys-No,I want to finish this game.\n");
				printf(">>");
			}
			afterexcess();
			break;
		}
		case 'y':{
			if (m == 1){
				printf("%c", c);
				printf("\nLoaing......\n \n");
				madeboard(M);
				printf("\n______________________________\n\n");
				afterexcess();
				m = 0;
			}
			break;
		}
		case 'n':{
			if (m == 1)
			{
				printf("%c", c);
				printf("\n______________________________\n\n");
				afterexcess();
				m = 0, l = 2;
			}
			break;
		}
		default:
			break;
		}
		if (s == 2){
			printf("\nLoaing......\n \n");
			printf("\n______________________________\n\n");
			madeboard(M);
			afterexcess();
			s = 0, m = 0;
		}
		if (l == 2)
			break;
	}
}