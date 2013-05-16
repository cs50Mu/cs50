/****************************************************************************
 * sudoku.h
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Compile-time options for the game of Sudoku.
 ***************************************************************************/

// game's author
#define AUTHOR "Linuxfish"

// game's title
#define TITLE "Sudoku"

// banner's colors
#define FG_BANNER COLOR_CYAN
#define BG_BANNER COLOR_BLACK

// grid's colors
#define FG_GRID COLOR_WHITE
#define BG_GRID COLOR_BLACK

// border's colors
#define FG_BORDER COLOR_WHITE
#define BG_BORDER COLOR_RED

// logo's colors
#define FG_LOGO COLOR_WHITE
#define BG_LOGO COLOR_BLACK

// winner's colors
#define FG_WIN COLOR_GREEN
#define BG_WIN COLOR_BLACK

// nicknames for pairs of colors
enum { PAIR_BANNER = 1, PAIR_GRID, PAIR_BORDER, PAIR_LOGO, PAIR_WIN };
