#include <stdio.h>
#include <stdlib.h>
int bomb , size ;

#define SIZE 20
#define MINES bomb



void Menu()
{
	printf("\n0.EXIT\n1.EASY\n2.MEDIUM\n3.HARD\n4.COSTUM\nEnter your choice: \n");
}

void initializeBoard(char board[][SIZE], char revealedBoard[][SIZE] , int size )
{
    int i, j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            board[i][j] = '#';
            revealedBoard[i][j] = '#';
        }
    }
}

void placeMines(char board[][SIZE] , int size)
{
    int i, j, count = 0;
    while (count < MINES)
    {
        i = rand() % size;
        j = rand() % size;
        if (board[i][j] != '*')
        {
            board[i][j] = '*';
            count++;
        }
    }
}

void printBoard(char board[][SIZE] , int size)
{
    int i, j;
    printf("    ");
    for (i = 0; i < size; i++)
        printf("%2d ", i);
    printf("\n");
    for (i = 0; i < size; i++)
    {
        printf("%2d: ", i);
        for (j = 0; j < size ; j++)
        	if(board[i][j] == '0')
        	{
        		printf("   ");
			}
			else
			{
				printf("%2c ", board[i][j]);
			}
        printf("\n");
    }
}

int isValidCell(int row, int col, int size)
{
    return (row >= 0 && row < size && col >= 0 && col < size);
}

int countMines(char board[][SIZE], int row, int col, int size)
{
    int count = 0, i, j;
    int rowOffsets[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int colOffsets[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    for (i = 0; i < 8; i++)
    {
        int newRow = row + rowOffsets[i];
        int newCol = col + colOffsets[i];
        if (isValidCell(newRow, newCol, size) && board[newRow][newCol] == '*')
            count++;
    }
    return count;
}

void revealCell(char board[][SIZE], char revealedBoard[][SIZE], int row, int col)
{
    if (isValidCell(row, col, size) && revealedBoard[row][col] == '#')
    {
        revealedBoard[row][col] = '0' + countMines(board, row, col, size);
        if (board[row][col] == '*')
        {
            printf("Game Over! You stepped on a mine.\n");
            exit(0);
        }
        
        if (revealedBoard[row][col] == '0')
        {
            int i, j;
            int rowOffsets[] = {-1, -1, -1, 0, 0, 1, 1, 1};
            int colOffsets[] = {-1, 0, 1, -1, 1, -1, 0, 1};
            for (i = 0; i < 8; i++)
            {
                int newRow = row + rowOffsets[i];
                int newCol = col + colOffsets[i];
                revealCell(board, revealedBoard, newRow, newCol);
            }
        }
    }
}
void CheckWin( char revealedBoard[][SIZE])
{
	int count = 0 ;
	for(int i = 0 ; i < size ; i++)
	{
		for(int j = 0 ; j < size ; j++)
		{
			if(revealedBoard[i][j] == '#')
			{
				count++;
			}
		}
	}
	if(count == MINES)
	{
		printf("YOU WIN!!!");
		exit(0);
	}
}

//  0 = Black       8 = Gray
//    1 = Blue        9 = Light Blue
//    2 = Green       A = Light Green
//    3 = Aqua        B = Light Aqua
//    4 = Red         C = Light Red
//    5 = Purple      D = Light Purple
//    6 = Yellow      E = Light Yellow
//    7 = White       F = Bright White

int main()
{	
	char backgroundColor='3',textColor='0';
    char sysmes[] = "color BF";

    sysmes[6] = backgroundColor;
    sysmes[7] = textColor;
    system(sysmes);
    char board[SIZE][SIZE];
    char revealedBoard[SIZE][SIZE];
    int row, col;
    int choice ; 
    Menu();
    scanf("%d" , & choice);
    while(choice < 0 || choice > 4)
    {
    	Menu();
    	scanf("%d" , &choice);
	}
    while(choice != 0 )
    {
    	switch(choice)
    	{
    		case 1:
    			{
					size = 8 ;
					bomb = 8 ;
					
				    initializeBoard(board, revealedBoard, size);
				    placeMines(board, size);
				
				    while (1)
				    {
				        printBoard(revealedBoard, size);
				
				        printf("MINES:%d\nEnter row and column (separated by a space): " , bomb);
				        scanf("%d %d", &row, &col);
				
				        revealCell(board, revealedBoard, row, col);
				        CheckWin(revealedBoard);
				    }
				    break ;
				}
			case 2:
				{
					size = 13 ; 
					bomb = 20 ; 
					
				    initializeBoard(board, revealedBoard, size);
				    placeMines(board, size);
				
				    while (1)
				    {
				        printBoard(revealedBoard, size);
				
				        printf("MINES:%d\nEnter row and column (separated by a space): " , bomb);
				        scanf("%d %d", &row, &col);
				
				        revealCell(board, revealedBoard, row, col);
				        CheckWin(revealedBoard);
				    }
				    break ;	
				}
				case 3:
					{
						scanf("%d", &size);
						scanf("%d", &bomb);
						
					    initializeBoard(board, revealedBoard, size);
					    placeMines(board, size);
					
					    while (1)
					    {
					        printBoard(revealedBoard, size);
					
					        printf("MINES:%d\nEnter row and column (separated by a space): " , bomb);
					        scanf("%d %d", &row, &col);
					
					        revealCell(board, revealedBoard, row, col);
					        CheckWin(revealedBoard);
					    }
					    break ;
					}
				case 4:
					{
						printf("Enter SIZE , MINES : \n");
						scanf("%d", &size);
						scanf("%d", &bomb);
						
					    initializeBoard(board, revealedBoard, size);
					    placeMines(board, size);
					
					    while (1)
					    {
					        printBoard(revealedBoard, size);
					
					        printf("MINES:%d\nEnter row and column (separated by a space): " , bomb);
					        scanf("%d %d", &row, &col);
					
					        revealCell(board, revealedBoard, row, col);
					        CheckWin(revealedBoard);
					    }
					    break ;
				}
		}
	}

    return 0;
}