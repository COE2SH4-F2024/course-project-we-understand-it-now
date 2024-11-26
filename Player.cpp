#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;


    // set player initial conditions
    playerPos.setObjPos(9,5,'*');
}


Player::~Player()
{ 
    // delete any heap members here
}

objPos Player::getPlayerPos() const
{
    // ? return the reference to the playerPos arrray list
    // ^not sure what it means by array list
    return playerPos.getObjPos();
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic  

    char input = mainGameMechsRef->getInput();
    
    // if not null (has an input)
    if (input != 0){
        // ? should this also include the rest of the inputs used? (quit game, etc.)
        switch(input){
            //           0     1    2      3      4
            //    myDir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state
            case 'w': 
                if (myDir >= 2){ //if last horizontal/stopped: change dir
                    myDir = UP;
                }
                break;
            case 'a': 
                if (myDir <= 1 || myDir == 4){ //if last vertical/stopped: change dir
                    myDir = LEFT;
                }                
                break;
            case 's': 
                if (myDir >= 2){ //if last horizontal/stopped: change dir
                    myDir = DOWN;
                }                
                break;
            case 'd': 
                if (myDir <= 1 || myDir == 4){ //if last vertical/stopped: change dir
                    myDir = RIGHT;
                }                
                break;
            default:
                // don't need to do anything when a character unspecified is pressed
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
    switch (myDir){
        case 4: //stop (initial)
            // nothing happens, only default when nothing has been pressed at start
            break;
        case 2://left
            playerPos.pos->x--;
            // wraps around
            if(playerPos.pos->x <= 0){
                // boardW-1 is #, boardW-2 is other side of board
                playerPos.pos->x = boardW-2; 
            }
            break;
        case 3://right
            playerPos.pos->x++;
            // wraps around
            if(playerPos.pos->x >= (boardW-1)){
                playerPos.pos->x = 1;
            }
            break;
        case 0://up
            playerPos.pos->y--;
            // wraps around
            if(playerPos.pos->y <= 0){
                playerPos.pos->y = boardH-2;
            }
            break;
        case 1://down
            
            playerPos.pos->y++;
            // wraps around
            if(playerPos.pos->y >= (boardH-1)){
                playerPos.pos->y = 1;
            }
            break;
    }
}

// More methods to be added