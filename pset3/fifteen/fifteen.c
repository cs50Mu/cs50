/***************************************************************************
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements The Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 ***************************************************************************/
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


// constants
#define DIM_MIN 3
#define DIM_MAX 9
#define BLANK 0   // define BLANK to be a number that can't be used in the board.


// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// position of BLANK tile
int zeroRow;
int zeroVol;


// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void swap(int *a,int *b);


int
main(int argc, char *argv[])
{
    // greet user with instructions
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %d x %d and %d x %d, inclusive.\n",
         DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // initialize the board
    init();

    zeroRow = d - 1;
    zeroVol = d - 1;

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // that's all folks
    return 0;
}


/*
 * Clears screen using ANSI escape sequences.
 */

void
clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}


/*
 * Greets player.
 */

void
greet(void)
{
    clear();
    printf("WELCOME TO THE GAME OF FIFTEEN\n");
    usleep(2000000);
}


/*
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */

void
init(void)
{  int num = d*d - 1;
   for (int i=0;i<d;i++)
   {
        for (int j=0;j<d;j++)
        {
            board[i][j] = num;
            num--;
        }
   }
   if ((d*d-1)%2 != 0)
   {
        board[d-1][d-3] = 1;
        board[d-1][d-2] = 2;
   }
//   board[d-1][d-1] = '_';

}


/* 
 * Prints the board in its current state.
 */

void
draw(void)
{
    printf("\n\n");
    for (int i=0;i<d;i++)
    {
        printf("\t");
        for (int j=0;j<d;j++)
        {
            if (board[i][j] == BLANK)
            {
                printf("%c\t",'_');
            }
            else
                printf("%d\t",board[i][j]);
        }
        printf("\n\n\n");
    }
}


/* 
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */

bool
move(int tile)
{
    int row,vol;
    if (tile < 1 || tile > d * d - 1)
        return false;
    for (int i=0;i<d;i++)
    {
        for (int j=0;j<d;j++)
        {
            if (tile == board[i][j])
            {
                row = i;
                vol = j;
                break;
            }
        }
    }
    if ((row - zeroRow) == 0 && abs(vol -zeroVol) == 1)
    {
        swap(&board[row][vol],&board[zeroRow][zeroVol]);
        zeroRow = row;
        zeroVol = vol;
        return true;
    }
    else if ((vol - zeroVol) == 0 && abs(row - zeroRow) == 1)
    {
        swap(&board[row][vol],&board[zeroRow][zeroVol]);
        zeroRow = row;
        zeroVol = vol;
        return true;
    }
    else
        return false;
}

void
swap(int *a,int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

/*
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */



bool
won(void)
{
    int num = 0;
    for (int i=0;i<d;i++)
    {
        for (int j=0;j<d;j++)
        {
            num++;
            if ((i == d - 1) && (j == d - 1))
                num = 0;
            if (board[i][j] != num)
                return false;
        }
    }

    return true;
}
