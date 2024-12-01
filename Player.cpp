#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    myPrevDir = STOP;


    // set player initial conditions
    playerPos.pos->x = mainGameMechsRef->getBoardSizeX() / 2;
    playerPos.pos->y = mainGameMechsRef->getBoardSizeY() / 2;
    playerPos.symbol = '*';
}


Player::~Player()
{ 
    // delete any heap members here
    // no heap members :p -- can leave destructor alone for now
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic  

    char input = mainGameMechsRef->getInput();
    
    // if not null (has an input)
    if (input != 0){
        switch(input){
            //           0     1    2      3      4
            //    myDir {UP, DOWN, LEFT, RIGHT, STOP};  -- This is the direction state
            case 'w': 
                if (myPrevDir != UP & myPrevDir != DOWN){ // If the direction wasn't vertical, then you can go up
                    myDir = UP;
                    myPrevDir = myDir;
                }
                break;
            case 'a': 
                if (myPrevDir != LEFT && myPrevDir != RIGHT){ // If the direction wasn't horizontal, then you can go left
                    myDir = LEFT;
                    myPrevDir = myDir;
                }                
                break;
            case 's': 
                if (myPrevDir != UP & myPrevDir != DOWN){ // If the direction wasn't vertical, then you can go down
                    myDir = DOWN;
                    myPrevDir = myDir;
                }                
                break;
            case 'd': 
                if (myPrevDir != LEFT && myPrevDir != RIGHT){ // If the direction wasn't horizontal, then you can go right
                    myDir = RIGHT;
                    myPrevDir = myDir;
                }                
                break;

            default:
                // Don't need to do anything when a character unspecified is pressed
                break;
        }
        mainGameMechsRef->clearInput();
    }
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    // get w and h for wraparound
    int boardW = mainGameMechsRef->getBoardSizeX();
    int boardH = mainGameMechsRef->getBoardSizeY();
    if (myDir != STOP){
        switch (myDir){
            case LEFT: 
                playerPos.pos->x--;
                // wraps around
                if(playerPos.pos->x <= 0){
                    // boardW-1 is #, boardW-2 is other side of board
                    playerPos.pos->x = boardW - 2; 
                }
                break;

            case RIGHT: 
                playerPos.pos->x++;
                // wraps around
                if(playerPos.pos->x >= (boardW - 1)){
                    playerPos.pos->x = 1;
                }
                break;

            case UP: 
                playerPos.pos->y--;
                // wraps around
                if(playerPos.pos->y <= 0){
                    playerPos.pos->y = boardH - 2;
                }
                break;

            case DOWN: //down
                playerPos.pos->y++;
                // wraps around
                if(playerPos.pos->y >= (boardH - 1)){
                    playerPos.pos->y = 1;
                }
                break;
        }
    }
}

// More methods to be added