#include "header.h"

/*
This function prints the rules of the game.
*/
void
printRules(void)
{
    printf("----------------------- GAME RULES -----------------------\n");
    printf("The players take turns moving 1 piece, starting with Alpha\n\n");
    printf("Move Restrictions:\n");
    printf("Players cannot move pieces anywhere outside the board\n");
    printf("A player cannot move a piece to a tile that already has a piece of theirs on it, or a white tile with an opposing piece on it.\n\n");
    printf("Valid Moves:\n");
    printf("Alpha can move any of their pieces 1 tile towards the left, horizontally or diagonally. \n");
    printf("Beta can move any of their pieces 1 tile towards the right, horizontally or diagonally. \n\n");
    printf("If a piece moves to a | | tile with an opposing piece, it eats the piece, which is removed from the board.\n");
    printf("A player wins if their opponent has no more pieces or if they still have pieces and all of them are on starting squares of the opponent.\n");
    printf("-----------------------------------------------------------\n\n");
}

/*
This function checks if tile is part of the Free set ( ).

@param tile - chosen tile 
@return 1 if it is part of the Free set.
@return 0 if it is not part of the Free set.
*/
int 
isFreeTile(char tile)
{
  if (tile == FREE)
      return 1;

  return 0;
}

/*
This function checks if tile is part of the S set (| |).

@param x - x coordinate of the tile
@param y - y coordinate of the tile
@return 1 if it is part of the S set.
@return 0 if it is not part of the S set.
*/
int 
isGreyTile(int x, int y)
{
    if (x % 2 == y % 2)
        return 1;

    return 0;
}

/* 
This function checks if selected tile is on the board,
current player has a piece on the selected tile, and
the piece is not on the edge of the board. 

@param board[][MAXY_Y] - array containing all the board pieces
@param a - x coordinate of the piece
@param b - y coordinate of the piece
@return 1 if all conditions are met.
@return 0 if not all conditions are met.
*/
int 
isValidPiece(char board[][MAX_Y], int a, int b, struct gameState *gameState)
{
    // check if its within the board range
    if (a >= 0 && a <= 6 && b >= 0 && b <= 4)
    {
        if (gameState->aTurn && board[a][b] == ALPHA && a != 0)  // alpha's turn
            return 1;
        else if (!gameState->aTurn && board[a][b] == BETA && a != 6) // beta's turn
            return 1;    
    }

    return 0;
}

/*
This function checks if the destination tile is valid.

@param board[][MAX_Y] array containing all the board pieces
@param a - x coordinate of the chosen piece
@param b - y coordinate of the chosen piece
@param c - x coordinate of the chosen destination tile
@param d - y coordinate of the chosen destination tile
@param gameState - struct of all the game state variables
@return 1 if valid move (all conditions are met).
@return 0 if not valid move (not all conditions are met).
*/
int 
isValidMove(char board[][MAX_Y], int a, int b, int c, int d, struct gameState *gameState)
{
    // check if its within the board range
    if (c <= 6 && c >= 0 && d <= 4 && d >= 0)
    {
        if (d == b || d == b + 1 || b == d + 1)
        {
            if (gameState->aTurn && a == c + 1 && board[c][d] != ALPHA) // alpha's turn
                return 1;
            else if(!gameState->aTurn && c == a + 1 && board[c][d] != BETA) // beta's turn
                return 1;
        }
    }
    
    return 0;
}

/*
This function checks if there is an opponent piece
on the destination tile.

@param next - the piece on the tile
@param gameState - struct of all the game state variables
@return 1 if there is an opponent piece on the tile.
@return 0 if there is no opponent piece on the tile.
*/
int 
isEnemyTile(char next, struct gameState *gameState)
{
    if (!gameState->aTurn && next == ALPHA)
        return 1;
    else if (gameState->aTurn && next == BETA)
        return 1;

    return 0;
}

/*
This function moves chosen piece to destination
tile ("prev" to "next").

@param board - array containing all the board pieces
@param a - x coordinate of the chosen piece
@param b - y coordinate of the chosen piece
@param c - x coordinate of the destination tile
@param d - y coordinate of the desintation tile
@param gameState - struct of all the game state variables
*/
void 
movePiece(char board[][MAX_Y], int a, int b, int c, int d, struct gameState *gameState) 
{
    if (gameState->aTurn)
        board[c][d] = ALPHA;
    else
        board[c][d] = BETA;

    // prev becomes a free tile
    board[a][b] = FREE;
} 

/*
This function counts the current pieces on the board and
updates all the count variables in gameState.pieces.

@param board - array containing all the board pieces
@param gameState - struct of all the game state variables
*/
void 
countPieces(char board[][MAX_Y], struct gameState *gameState)
{
    // initialization
    gameState->pieces.A = 0;
    gameState->pieces.B = 0;
    gameState->pieces.aY = 0;
    gameState->pieces.bE = 0;
    
    for (int i = 0; i < MAX_X; i++)
    {
        for (int j = 0; j < MAX_Y; j++)
        {
            // counts number of Alpha pieces
            if (board[i][j] == ALPHA)
            {
                gameState->pieces.A++;

                // counts number of Alpha pieces in Beta territory
                if (i <= 1 && isGreyTile(i, j))
                    gameState->pieces.aY++;
            }
            // counts number of Beta pieces
            else if (board[i][j] == BETA)
            {
                gameState->pieces.B++;

                // counts number of Beta pieces in Alpha territory
                if (i >= 5 && isGreyTile(i, j))
                    gameState->pieces.bE++;
            }
        }
    }
}

/*
This function allows the player to do their turn. Updates the
board once chosen piece and destination tile meets all necessary
conditions.

@param board - array containing all the board pieces
@param gameState - struct of all the game state variables
*/
void 
NextPlayerMove(char board[][MAX_Y], struct gameState *gameState)
{
    int a, b; // x and y coordinates of the chosen piece 
    int c, d; // x and y coordinates of the next desired tile
    
    // loops until player makes a valid move
    do
    {    
        // loops until the player chooses a tile with one of their pieces on it
        if (gameState->aTurn)
            printf("Alpha, ");
        else
            printf("Beta, ");
                
        printf("Type the location of your chosen piece (x y):\t");
        scanf("%d %d", &a, &b);

        // subtract -1 to follow indices of board
        a--;
        b--;

        if (isValidPiece(board, a, b, gameState))
        {
            // loops until the player chooses a valid move location
            printf("Type the location you would like to move it to (x y):\t");
            scanf("%d %d", &c, &d);
                
            // subtract -1 to follow indices of board
            c--;
            d--;

            if (isValidMove(board, a, b, c, d, gameState)) 
            {
                // if opponent is on that tile and it is not a grey tile (S set)
                if (isEnemyTile(board[c][d], gameState) && !isGreyTile(c, d)) 
                    printf("There is an enemy piece on that tile but unable to eat their piece. Restarting Turn...\n");       
                else
                    gameState->ok = !gameState->ok;
            }
            else
                printf("Invalid Move. Restarting Turn...\n\n");
        }
        else
            printf("Invalid piece. Restarting Turn...\n\n");
        
    } while (!gameState->ok);

    if (isFreeTile(board[c][d]))
        printf("Chose a Free Tile. Moving your piece...\n");
    else if (isEnemyTile(board[c][d], gameState))
        printf("There is an enemy piece on that tile. You ate it. Moving your piece...\n");
    
    printf("\n");
    
    movePiece(board, a, b, c, d, gameState);

    // change turn to next player
    gameState->aTurn = !gameState->aTurn;
    gameState->ok = !gameState->ok;
}


/* 
This function checks if the game is over

@param board - array containing all the board pieces
@param gameState - struct of all the game state variables
@return 0 if game is not yet over
@return 1 if Alpha won
@return -1 if Beta won
@return 2 if the game is a draw
*/
int 
gameOver(char board[][MAX_Y], struct gameState* gameState) 
{
    int aWin = 0; // if alpha meets win conditions
    int bWin = 0; // if beta meets win conditions
    int a = 0; // number of alphas on the opposite side of the board on white squares
    int b = 0; // number of betas on the opposite side of the board on white squares

    // checks if alpha or beta meets win conditions
    if (gameState->pieces.B == 0 || (gameState->pieces.A > 0 && gameState->pieces.A == gameState->pieces.aY) ) 
    {
        // ALPHA ate all beta pieces OR all alive alpha pieces are on beta's territory
        gameState->over = 1;
        aWin = 1;
    }
    
    if (gameState->pieces.A == 0 || (gameState->pieces.B > 0 && gameState->pieces.B == gameState->pieces.bE) ) 
    {       
        // BETA ate all alpha pieces OR all alive beta pieces are on alpha's territory
        gameState->over = 1;
        bWin = 1;
    }

    // if none met the win conditions
    if (!gameState->over)
    {
        // each side has at least one piece that is at the edge but not on a starting square of an enemy piece
        if (board[0][1] == ALPHA || board[0][3] == ALPHA)
            a++;
        if (board[6][1] == BETA || board[6][3] == BETA)
            b++;

        // at least one piece of EACH team is on a non-grey tile at the edges (not Y or E)
        if (a > 0 && b > 0) 
        {
            // game is a draw
            gameState->over = 1;
            return 2;
        }
    }
    
    if (aWin && bWin) // both meet win conditions simultaneously, game is draw
        return 2;
    else if (aWin) // alpha win
        return 1;
    else if (bWin) // beta win
        return -1;
    
    return 0; // game is not over
}

/*
This function prints the current state of the board.
*/
void 
printBoard(char board[][MAX_Y])
{
    int i, j;
    
    printf("X -> 1 to 7 Left to Right\nY -> 1 to 5 bottom to top\n\n");
    printf("Y\n ---------------------------\n");
    
    for (j = MAX_Y - 1; j >= 0; j--)
    {
        printf("%d ", j + 1);
        for (i = 0; i < MAX_X; i++)
        {   
            if (isGreyTile(i, j))
                printf("|%c| ", board[i][j]);
            else
                printf(" %c  ", board[i][j]);
        }

        if (j == 0)
            printf("\n");
        else 
            printf("\n\n");
    }
    
    printf("  ---------------------------\n");
    printf("X  1   2   3   4   5   6   7\n\n");
}