/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Constants
#define DIM_MIN 3
#define DIM_MAX 9

// Board
int board[DIM_MAX][DIM_MAX];

// Converted 2D array to 1D array
int convertBoard[DIM_MAX * DIM_MAX];

// Dimensions (d x d 2D Array)
int d;

// Positions of "_" that user controls
int holderRow;
int holderCol;

// Positions of tile to be swapped
int tileRow;
int tileCol;

// Prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // Ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // Open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // Greet user with instructions
    greet();

    // Initialize the board
    init();

    // Accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // Draw the current state of the board
        draw();

        // Log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // Prompt user for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // Quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // Log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // Move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move. You can only move up, down, left, or right.\n");
            usleep(1200000);
        }

        // Sleep thread for animation's sake
        usleep(150000);
    }
    
    // Close log
    fclose(file);

    // Success!
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    printf("(Type 0 to quit)\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    
    // DEBUG: verify dimensions and initialized array.
    printf("Inputted 2D Array Dimensions: %d x %d\n\n", d, d);
    int boardValue = (d * d) - 1;
    printf("Initialized Array: \n");
    
    for (int i = 0; i < d; i++)
    {
        
        for (int j = 0; j < d; j++)
        {
            board[i][j] = boardValue;
            boardValue--;
        }
        
    }
    
    if ((d % 2) == 0)
    {
        board[d-1][d-2] = 2;
        board[d-1][d-3] = 1;
    }
    
    // DEBUG: See if 1 and 2 have swapped if # tiles is odd
    // printf("board[d-1][d-2] = %d\n", board[d-1][d-2]);
    // printf("board[d-1][d-3] = %d\n", board[d-1][d-2]);
    
    // printf("d modulo 2 - 1 is %d\n", (d % 2) - 1);
    
    // Setting bottom-right tile as a "blank" where 0 will
    // be replaced with a "-" in the draw function.
    board [d-1][d-1] = 0;
    
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int i = 0; i < (d); i++)
    {
        
        // Each row of the array will be printed every "i" loop.
        for (int j = 0; j < d; j++)
        {
            printf("%4d", board[i][j]);
            
            // Print out the movable tile.
            if (board[i][j] == 0)
            printf("\b_");
            
            // Continuously track location of "_" character.
            if (board[i][j] == 0)
            {
                holderRow = i;
                holderCol = j;
            }
            
        }
        
        printf ("\n\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    
    // DEBUG: Location of "_" character
    // printf("_ coordinates: %d, %d\n", holderRow, holderCol);
    
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            // If the tile to swap with is in the 2D array,
            // record the tile's row and column. 
            if (board[i][j] == tile)
            {
                tileRow = i;
                tileCol = j;
                
                //If the tile to be swapped is above, below, to the left, or right
                // of the "_" character, swap them.
                if ((((tileRow == holderRow + 1) || (tileRow == holderRow - 1)) && (tileCol == holderCol)) || ((tileRow == holderRow) && ((tileCol == holderCol + 1) || (tileCol == holderCol - 1))))
                {
                    // Replace "_" with tile that user specified.
                    board[holderRow][holderCol] = tile;
                    
                    // Replace tile with "_" character.
                    board[i][j] = 0;
                    return true;
                }
                else
                {
                    return false;
                }
                
            }
        }  // Inner for loop
    } // Outer for loop
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int counter = 0;
    
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            convertBoard[counter++] = board[i][j];
        }
    }
    
    bool winning = true;
    
    // Keep looping through array until all numbers are sorted.
    for (int a = 0; a < counter - 1; a++)
    {
        // Loop through the array and swap numbers to make
        // larger numbers "bubble" to the top.
        for (int b = 0; b < (counter - 2 - a); b++)
        {
            if (convertBoard[b] >= convertBoard[b+1])
            {
                winning = false;
                break;
            }
        }
        if (winning == false)
        {
            break;
        }
    }
    return winning;
}