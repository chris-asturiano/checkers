#include <stdio.h>
#define MAX_X 7
#define MAX_Y 5
#define ALPHA 'A'
#define BETA 'B'
#define FREE ' '

struct countType
{
    int B;  // count beta of pieces
    int A;  // count alpha of pieces
    int aY;  // count Alphas in Y spaces
    int bE;  // count Betas in E spaces
};

struct gameState
{
    int over; // boolean for the game state (over or ongoing)
    int ok; // boolean used for move validity
    int aTurn; // boolean for the current turn (Alpha or Beta)
    struct countType pieces;
};

void printRules(void);
int isFreeTile(char tile);
int isGreyTile(int x, int y);
int isValidPiece(char board[][MAX_Y], int a, int b, struct gameState *gameState);
int isValidChoice(char board[][MAX_Y], int a, int b, int c, int d, struct gameState *gameState);
int isEnemyTile(char next, struct gameState *gameState);
void movePiece(char board[][MAX_Y], int a, int b, int c, int d, struct gameState *gameState);
void countPieces(char board[][MAX_Y], struct gameState *gameState);
void NextPlayerMove(char board[][MAX_Y], struct gameState *gameState);
int gameOver (char board[][MAX_Y], struct gameState* gameState);
void printBoard(char board[][MAX_Y]);