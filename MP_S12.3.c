/*

    CCDSTRU Machine Project
    Term 2 AY 2021-2022
    S12B

    GROUP S12.3
    Asturiano, Christian
    Cheng, Samuel
    Jardenil, Aaron
    Rebano, Jaeme

*/
#include "functions.c"

int 
main(void) {

    struct gameState gameState;
    char board[MAX_X][MAX_Y];
    int i, j;

    // initialize variables
    gameState.over = 0;        // if game is ongoing or not
    gameState.ok = 0;          // move validity
    gameState.aTurn = 1;       // Alpha has the first turn

  
    // board initialization
    for (i = 0; i < MAX_X; i++) // initialize pieces
    {
        for (j = MAX_Y - 1; j >= 0; j--)
        {
            board[i][j] = FREE; // initialize empty space first
            if (isGreyTile(i, j)) // pieces are initialized onto grey tiles
            {      
                if (i >= 5) // Alpha pieces
                    board[i][j] = ALPHA;

                else if (i <= 1) // Beta pieces
                    board[i][j] = BETA;
            }
        }
    }

    printRules();

    while (!gameState.over)
    {
        printBoard(board);
        NextPlayerMove(board, &gameState);
        countPieces(board, &gameState);
        gameState.over = gameOver(board, &gameState);             
    }

    printBoard(board);
    
    if (gameState.over == 1)
        printf("Alpha Wins! Thank you for playing.");
    else if (gameState.over == -1)
        printf("Beta Wins! Thank you for playing.");
    else
        printf("The game is a Tie! Nobody Wins. Thank you for playing.");
  
    return 0;
}