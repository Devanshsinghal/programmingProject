#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define MAX_HEIGHT 100
#define MIN_HEIGHT 5
#define MAX_WIDTH 100
#define MIN_WIDTH 5
#define MAX_WALLS 25  // Maximum percentage of walls in the maze to avoid over crowding
#define MIN_EXIT_DISTANCE 3     // Minimum distance around exit point
#define MIN_START_DISTANCE 3    // Minimum distance around starting point

void printMaze(char maze[MAX_HEIGHT][MAX_WIDTH], int height, int width, int playerRow, int playerCol, int startRow, int startCol, int exitRow, int exitCol) 
{
    system("clear");

    for (int i = 0; i < height; ++i) 
    {
        for (int j = 0; j < width; ++j) 
        {
            if (i == playerRow && j == playerCol) 
            {
                printf("X ");
            } 
            else if (i == startRow && j == startCol)
            {
                printf("S ");
            }
            else if (i == exitRow && j == exitCol)
            {
                printf("E ");
            }
            else 
            {
                printf("%c ", maze[i][j]);
            }
        }
        printf("\n");
    }
}

void initializeMaze(char maze[MAX_HEIGHT][MAX_WIDTH], int height, int width, int *startRow, int *startCol, int *exitRow, int *exitCol) 
{
    // Initialize maze
    for (int i = 0; i < height; ++i) 
    {
        for (int j = 0; j < width; ++j) 
        {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) 
            {
                maze[i][j] = '#';  // Add a boundary of walls for clean look
            } 
            else 
            {
                maze[i][j] = ' ';
            }
        }
    }

    // Set starting point
    do {
        *startRow = rand() % (height - 2) + 1;  // Avoid the boundary
        *startCol = rand() % (width - 2) + 1;   // Avoid the boundary
    } while (maze[*startRow][*startCol] != ' ');

    maze[*startRow][*startCol] = 'S';

    // Set exit point
    do {
        *exitRow = rand() % (height - 2) + 1;  // Avoid the boundary
        *exitCol = rand() % (width - 2) + 1;   // Avoid the boundary
    } while (maze[*exitRow][*exitCol] != ' ');

    maze[*exitRow][*exitCol] = 'E';

    // Set random walls
    srand(time(NULL));

    int maxWalls = (height - 2) * (width - 2) * MAX_WALLS / 100;
    int numWalls = rand() % maxWalls + 1;

    for (int i = 0; i < numWalls; ++i) 
    {
        int wallRow;
        int wallCol;

        // random walls don't block the player from moving at all and give space to the starting point
        do {
            wallRow = rand() % (height - 2) + 1;  // Avoid the boundary
            wallCol = rand() % (width - 2) + 1;   // Avoid the boundary
        } while (maze[wallRow][wallCol] != ' ' &&
                 (wallRow == *startRow || wallRow == *exitRow || wallCol == *startCol || wallCol == *exitCol ||
                  abs(wallRow - *startRow) < MIN_START_DISTANCE || abs(wallCol - *startCol) < MIN_START_DISTANCE));

        maze[wallRow][wallCol] = '#';
    }
}


int main() {
    int height;
    int width;

    printf("Enter the height of the maze (between %d and %d): ", MIN_HEIGHT, MAX_HEIGHT);
    scanf("%d", &height);

    printf("Enter the width of the maze (between %d and %d): ", MIN_WIDTH, MAX_WIDTH);
    scanf("%d", &width);

    if (height < MIN_HEIGHT || height > MAX_HEIGHT || width < MIN_WIDTH || width > MAX_WIDTH) 
    {
        printf("Invalid maze dimensions! Exit! \n");
        return 1;
    }

    char maze[MAX_HEIGHT][MAX_WIDTH];

    int startRow, startCol, exitRow, exitCol;
    initializeMaze(maze, height, width, &startRow, &startCol, &exitRow, &exitCol);
    
    int playerRow = startRow;
    int playerCol = startCol;

    char move;

    while (1) 
    {
        //printMaze(maze, height, width, playerRow, playerCol, startRow, startCol, exitRow, exitCol);

        printf("Enter your move (W/A/S/D/M to view map): ");
        scanf(" %c", &move);

        move = toupper(move);

        switch (move) 
        {
            case 'W':
                if (playerRow > 1 && maze[playerRow - 1][playerCol] != '#') 
                {
                    maze[playerRow][playerCol] = ' ';
                    playerRow--;
                } 
                else 
                {
                    printf("Cannot move there!\n");
                }
                break;
            case 'A':
                if (playerCol > 1 && maze[playerRow][playerCol - 1] != '#') 
                {
                    maze[playerRow][playerCol] = ' ';
                    playerCol--;
                } 
                else 
                {
                    printf("Cannot move there!\n");
                }
                break;
            case 'S':
                if (playerRow < height - 2 && maze[playerRow + 1][playerCol] != '#') 
                {
                    maze[playerRow][playerCol] = ' ';
                    playerRow++;
                } 
                else 
                {
                    printf("Cannot move there!\n");
                }
                break;
            case 'D':
                if (playerCol < width - 2 && maze[playerRow][playerCol + 1] != '#') 
                {
                    maze[playerRow][playerCol] = ' ';
                    playerCol++;
                } 
                else 
                {
                    printf("Cannot move there!\n");
                }
                break;
            case 'M':
                printMaze(maze, height, width, playerRow, playerCol, startRow, startCol, exitRow, exitCol);
                break;
            default:
                printf("Invalid move!\n");
                break;
        }

        if (playerRow == exitRow && playerCol == exitCol) 
        {
            printf("Congratulations! You have reached the exit. You won!\n");
            break;
        }
    }

    return 0;
}