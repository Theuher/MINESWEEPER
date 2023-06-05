#include <stdio.h>
#include <stdlib.h>
int bomb, size;
#define SIZE 20
#define MINES bomb

// color codes
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN "\x1b[36m"
#define COLOR_RESET "\x1b[0m"

void Menu()
{
    printf(COLOR_YELLOW "\n0.EXIT\n1.EASY\n2.MEDIUM\n3.HARD\n4.CUSTOM\nEnter your choice: \n" COLOR_RESET);
}

void initializeBoard(char board[][SIZE], char revealedBoard[][SIZE], int size)
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

void placeMines(char board[][SIZE], int size)
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

void printBoard(char board[][SIZE], int size)
{
    int i, j;
    printf("    ");
    for (i = 0; i < size; i++)
        printf(COLOR_CYAN "%2d " COLOR_RESET, i);
    printf("\n");
    for (i = 0; i < size; i++)
    {
        printf(COLOR_CYAN "%2d: " COLOR_RESET, i);
        for (j = 0; j < size; j++)
        {
            if (board[i][j] == '0')
            {
                printf("   ");
            }
            else if (board[i][j] == '*')
            {
                printf(COLOR_RED "%2c " COLOR_RESET, board[i][j]);
            }
            else if(board[i][j] == '1')
            {
                printf(COLOR_BLUE "%2c " COLOR_RESET, board[i][j]);
            }
            else if(board[i][j] == '2')
            {
                printf(COLOR_GREEN "%2c " COLOR_RESET, board[i][j]);
            }
            else 
            {
                printf(COLOR_YELLOW "%2c " COLOR_RESET, board[i][j]);
            }
        }

        printf("\n");
    }
}

int isValidCell(int row, int col, int size)
{
    return (row >= 0 && row < size && col >= 0 && col < size);
}

int countSurroundingMines(char board[][SIZE], int row, int col, int size)
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

void printBoardAfter (char board[][SIZE] , int size) {

			int i, j;	
			for (i = 0; i < size; i++)
			        		printf(COLOR_CYAN "%2d " COLOR_RESET, i);
			    		printf("\n");
						for (i = 0; i < size; i++) {
							printf(COLOR_CYAN "%2d: " COLOR_RESET, i);
							for (j = 0; j < size ; j++) {
								if(board[i][j] == '*' ) {
									printf(COLOR_RED" * "COLOR_RESET);
								} else {
									printf("   ", board[i][j]);
								}	
			    			}
						printf("\n");
			    		}
}

void revealCell(char board[][SIZE], char revealedBoard[][SIZE], int row, int col)
{	int i , j ;
    if (isValidCell(row, col, size) && revealedBoard[row][col] == '#')
    {
        revealedBoard[row][col] = '0' + countSurroundingMines(board, row, col, size);
        if (board[row][col] == '*')
        {
            printf(COLOR_RED "Game Over! You stepped on a mine.\n" COLOR_RESET);
            printBoardAfter(board , size);
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

void CheckWin(char revealedBoard[][SIZE])
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (revealedBoard[i][j] == '#')
            {
                count++;
            }
        }
    }
    if (count == MINES)
    {
        printf(COLOR_GREEN "CONGRATULATIONS. YOU WON!!!" COLOR_RESET);
        exit(0);
    }
}

int main()
{
    char board[SIZE][SIZE];
    char revealedBoard[SIZE][SIZE];
    int row, col;
    int choice;
    Menu();
    scanf("%d", &choice);
    while (choice < 0 || choice > 4)
    {
        Menu();
        scanf("%d", &choice);
    }
    while (choice != 0)
    {
        switch (choice)
        {
        case 1:
        {
            size = 8;
            bomb = 8;

            initializeBoard(board, revealedBoard, size);
            placeMines(board, size);

            while (1)
            {
                printBoard(revealedBoard, size);

                printf("MINES:%d\nEnter row and column (separated by a space): ", bomb);
                scanf("%d %d", &row, &col);

                revealCell(board, revealedBoard, row, col);
                CheckWin(revealedBoard);
            }
            break;
        }
        case 2:
        {
            size = 13;
            bomb = 20;

            initializeBoard(board, revealedBoard, size);
            placeMines(board, size);

            while (1)
            {
                printBoard(revealedBoard, size);

                printf("MINES:%d\nEnter row and column (separated by a space): ", bomb);
                scanf("%d %d", &row, &col);

                revealCell(board, revealedBoard, row, col);
                CheckWin(revealedBoard);
            }
            break;
        }
        case 3:
        {
            size = 20;
            bomb = 40;

            initializeBoard(board, revealedBoard, size);
            placeMines(board, size);

            while (1)
            {
                printBoard(revealedBoard, size);

                printf("MINES:%d\nEnter row and column (separated by a space): ", bomb);
                scanf("%d %d", &row, &col);

                revealCell(board, revealedBoard, row, col);
                CheckWin(revealedBoard);
            }
            break;
        }
        case 4:
        {
            printf("Enter SIZE, MINES: \n");
            scanf("%d", &size);
            scanf("%d", &bomb);

            initializeBoard(board, revealedBoard, size);
            placeMines(board, size);

            while (1)
            {
                printBoard(revealedBoard, size);

                printf("MINES:%d\nEnter row and column (separated by a space): ", bomb);
                scanf("%d %d", &row, &col);

                revealCell(board, revealedBoard, row, col);
                CheckWin(revealedBoard);
            }
            break;
        }
        }
    }

    return 0;
}

