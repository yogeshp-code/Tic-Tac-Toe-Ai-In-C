#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include <windows.h>

#define computermove 'X'
#define humanmove 'O'
#define computer 0
#define human 1
#define SIDE 3

char board[3][3];
char winner;
int flagover=0;

int equals3(char a, char b, char c)
{
	if(a==b && b==c && a!=' ')
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
void initialize()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			board[i][j]=' ';
		}
	}
}
void printboard()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(j==1 || j==2)
			{
				printf("|");
			}
			printf(" %c ",board[i][j]);
		}
		if(i==0 || i==1)
		{
			printf("\n---------");
		}
		printf("\n");
	}

}
char checkwinner()
{
	 char winner = 's';

	  // horizontal
	  for (int i = 0; i < 3; i++) {
	    if (equals3(board[i][0], board[i][1], board[i][2])==0) {
	      winner = board[i][0];
	    }
	  }

	  // Vertical
	  for (int i = 0; i < 3; i++) {
	    if (equals3(board[0][i], board[1][i], board[2][i])==0) {
	      winner = board[0][i];
	    }
	  }

	  // Diagonal
	  if (equals3(board[0][0], board[1][1], board[2][2])==0) {
	    winner = board[0][0];
	  }
	  if (equals3(board[2][0], board[1][1], board[0][2])==0) {
	    winner = board[2][0];
	  }

	  int openSpots = 0;
	  for (int i = 0; i < 3; i++) {
	    for (int j = 0; j < 3; j++) {
	      if (board[i][j] == ' ') {
	        openSpots++;
	      }
	    }
	  }

	  if (winner == 's' && openSpots == 0) {
		  return 't';
	  } else {
	    return winner;
	  }
}

void humanturn()
{
	int choice,x,y;
	printf("\n Human Turn");
	do{

		printf("\n Enter From 1 to 9 to play your turn :");
			fflush(stdout);
	scanf("%d", &choice);

	choice=choice-1;
	 x=choice/SIDE;
	 y=choice%SIDE;
	}while(board[x][y]!=' ');
	board[x][y] = humanmove;
	printboard();
	fflush(stdout);

}
char gamewinner='s';
void gameover()
{
	for(int i=0;i<3;i++)
	{
		if(board[i][0]==board[i][1] && board[i][2]==board[i][1] && board[i][0]!=' ')
		{
			flagover=1;
			gamewinner=board[i][0];
		}
		if(board[0][i]==board[1][i] && board[1][i]==board[2][i] && board[0][i]!=' ')
		{
			flagover=1;
			gamewinner=board[0][i];
		}
	}
	if((board[0][0]==board[1][1] && board[1][1]==board[2][2] && board[1][1]!=' ')||(board[0][2]==board[1][1] && board[1][1]==board[2][0] && board[1][1]!=' '))
	{
		flagover=1;
		gamewinner=board[1][1];
	}

	int flag=0;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(board[i][j]==' ')
			{
				flag++;
			}
		}
	}
	if(flag==0)
	{
		flagover=1;
		gamewinner='t';
	}
}
char result;
int  minimax(char board[3][3],int  depth,int isMaximizing) {
	  char result = checkwinner();
	  if (result != 's') {
		  if(result == 'X')
		  {
			  return 1;
		  }
		  else if(result == 'O')
		  {
			  return -1;
		  }
		  else
		  {
			  return 0;
		  }
	  }

	  if (isMaximizing==0) {
	    int bestScore = -100;
	    for (int  i = 0; i < 3; i++) {
	      for (int  j = 0; j < 3; j++) {
	        if (board[i][j] == ' ') {
	          board[i][j] = computermove;
	          int  score = minimax(board, depth + 1, 1);
	          board[i][j] = ' ';
	          bestScore = fmax(score, bestScore);
	        }
	      }
	    }
	    return bestScore;
	  } else {
	    int  bestScore = 100;
	    for (int  i = 0; i < 3; i++) {
	      for (int j = 0; j < 3; j++) {
	        // Is the spot available?
	        if (board[i][j] == ' ') {
	          board[i][j] = humanmove;
	          int score = minimax(board, depth + 1, 0);
	          board[i][j] = ' ';
	          bestScore = fmin(score, bestScore);
	          //printf("%d",bestScore);
	        }
	      }
	    }
	    return bestScore;
	  }
	}
int besti,bestj;
void computerturn()
{
	int bestscore=-1000;
	printf("\n Computer turn :\n");
	fflush(stdout);
	//equal(board,boardt);
	for(int i=0;i<SIDE;i++)
	{
		for (int  j = 0; j < SIDE; j++)
		{
			if(board[i][j] == ' ')
			{
				board[i][j] = computermove;
				int scoreee=minimax(board,0,1);//depth,true
				board[i][j]=' ';
				if(scoreee>bestscore)
				{
					bestscore=scoreee;
					besti=i;
					bestj=j;
				}

			}
		}		
	}
	board[besti][bestj]=computermove;
	printboard();
	fflush(stdout);
}
void play(int turn)
{
	int choice=0;
	do{
			flagover=0;
			initialize();
			do{
				if(turn == human)
				{
					humanturn();
					turn = computer;
					gameover();
				}
				else
				{
					printf("Computer turn");
					computerturn();
					turn = human;
					gameover();
				}
			}while(flagover==0);
				if(gamewinner=='X')
				{
					printf("Computer Win\a\n");
					fflush(stdout);
				}
				else if(gamewinner=='O')
				{
					printf("Player Win\a\n");
					fflush(stdout);
				}
				else
				{
					printf("Math Tied\a\n");
					fflush(stdout);
				}

	printf("\nDo You Want To restart [0-yes,1-no] :");
	fflush(stdout);
	scanf("%d",&choice);
	}while(choice==0);
}

int main()
{
	play(computer);
	return 0;
}

