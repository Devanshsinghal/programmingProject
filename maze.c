#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define Max_height 100
#define Min_height 5
#define Max_witdh 100
#define Min_width 5

void printMaze(char **maze, int height, int *width, int playerRow, int playerCol, int startRow, int startCol, int exitRow, int exitCol) 
{
    system("clear");

    for (int i = 0; i < height; ++i) 
    {
        for (int j = 0; j < width[i]; ++j) 
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

void ValidateMaze(char **maze, int height, int *width) 
{
    int expectedWidth = width[0];

    for (int i = 1; i < height; ++i) 
    {
        if (width[i] != expectedWidth) 
        {
            fprintf(stderr, "Invalid maze! Rows have different lengths.\n");
            //fprintf(stderr, "Expected width: %d, Actual width in row %d: %d\n", expectedWidth, i, width[i]);
            exit(1);
        }
    }

    for (int i = 0; i < height; ++i) 
    {
        for (int j = 0; j < width[i]; ++j) 
        {
            if (maze[i][j] != '#' && maze[i][j] != 'S' && maze[i][j] != 'E' && maze[i][j] != ' ') 
            {
                fprintf(stderr, "Invalid maze! Invalid character detected: %c\n", maze[i][j]);
                exit(1);
            }
        }
    }
}



void initializeMaze(char ***maze, int *height, int **width, int *startRow, int *startCol, int *exitRow, int *exitCol, const char *filename) 
{
    FILE *file = fopen(filename, "r");
    
    if (!file) 
    {
        fprintf(stderr, "Error opening file!\n");
        exit(1);
    }
    else
    {
        fprintf(stderr, "file opened successfully!");
    }

    *height = 0;
    *maze = NULL;
    *width = NULL;

    char line[Max_witdh];
    while (fgets(line, sizeof(line), file) != NULL) 
    {
        int lineLength = strlen(line);

        // Skip empty lines
        if (lineLength == 1 && line[0] == '\n') 
        {
            continue;
        }

        // Reallocate memory for maze
        *maze = (char **)realloc(*maze, (*height + 1) * sizeof(char *));
        (*maze)[*height] = (char *)malloc((lineLength + 1) * sizeof(char));

        // Copy the line to the maze
        strcpy((*maze)[*height], line);

        // Reallocate memory for widths
        *width = (int *)realloc(*width, (*height + 1) * sizeof(int));
        (*width)[*height] = lineLength;

        if (lineLength > 0 && line[lineLength - 1] == '\n') 
        {
            (*maze)[*height][lineLength - 1] = '\0'; // Remove newline character
            (*width)[*height]--;
        }

        (*height)++;
    }

    fclose(file);

    // Check if the maze is a valid rectangle within the accepted range
    if (*height < Min_height || *height > Max_height) 
    {
        fprintf(stderr, "Invalid maze dimensions! Height must be within the range [%d, %d].\n", Min_height, Max_height);
        exit(1);
    }

    ValidateMaze(*maze, *height, *width);

    // Find the start and exit positions
    for (int i = 0; i < *height; ++i) 
    {
        for (int j = 0; j < (*width)[i]; ++j) 
        {
            if ((*maze)[i][j] == 'S') 
            {
                *startRow = i;
                *startCol = j;
            } 
            else if ((*maze)[i][j] == 'E') 
            {
                *exitRow = i;
                *exitCol = j;
            }
        }
    }
}



void freeMaze(char ***maze, int height) 
{
    for (int i = 0; i < height; ++i) 
    {
        free((*maze)[i]);
    }
    free(*maze);
}

int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    int height;
    char **maze = NULL;
    int *width = NULL;

    int startRow, startCol, exitRow, exitCol;
    initializeMaze(&maze, &height, &width, &startRow, &startCol, &exitRow, &exitCol, argv[1]);
    
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
                printf("You moved up!\n");
                if (playerRow > 0 && maze[playerRow - 1][playerCol] != '#') 
                {
                    playerRow--;
                } 
                else 
                {
                    printf("Cannot move there!\n");
                }
                break;
            case 'A':
                printf("You moved left!\n");
                if (playerCol > 0 && maze[playerRow][playerCol - 1] != '#') 
                {
                    playerCol--;
                } 
                else 
                {
                    printf("Cannot move there!\n");
                }
                break;
            case 'S':
                printf("You moved down!\n");
                if (playerRow < height - 1 && maze[playerRow + 1][playerCol] != '#') 
                {
                    playerRow++;
                } 
                else 
                {
                    printf("Cannot move there!\n");
                }
                break;
            case 'D':
                printf("You moved right!\n");
                if (playerCol < width[playerRow] - 1 && maze[playerRow][playerCol + 1] != '#') 
                {
                    playerCol++;
                } 
                else 
                {
                    printf("Cannot move there!\n");
                }
                break;
            case 'M':
                printf("This is your current location!\n");
                printMaze(maze, height, width, playerRow, playerCol, startRow, startCol, exitRow, exitCol);
                break;
            default:
                printf("Invalid move!\n");
                break;
        }


        if (playerRow == exitRow && playerCol == exitCol) 
        {
            printMaze(maze, height, width, playerRow, playerCol, startRow, startCol, exitRow, exitCol);
            printf("Congratulations! You have reached the exit. You won!\n");
            break;
        }
    }

    // Free allocated memory for maze
    freeMaze(&maze, height);
    free(width);

    return 0;
}
