#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    mainGameFoodRef = thisFoodRef;
    myDir = STOP;
    myPrevDir = STOP;
    symbol = '*';
    // instantiate objPosArrayList on heap
    playerPosList = new objPosArrayList();

    // set player initial conditions, start in middle of board
    objPos headPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, symbol);
    playerPosList->insertHead(headPos);


    // listHead.pos->x = mainGameMechsRef->getBoardSizeX() / 2;
    // listHead.pos->y = mainGameMechsRef->getBoardSizeY() / 2;
    // listHead.symbol = '*';
}


Player::~Player()
{ 
    // delete any heap members here
    delete playerPosList;
    playerPosList = nullptr;
}

// ease of access addition
char Player::getPlayerSymbol(){
    return symbol;
}

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the listHead array list
    return playerPosList;
}

void Player::increasePlayerLength(){
    mainGameMechsRef->incrementScore();
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
        // temp objPos to use when moving
        objPos listHead = playerPosList->getHeadElement();

        switch (myDir){
            case LEFT: 
                listHead.pos->x--;
                // wraps around
                if(listHead.pos->x <= 0){
                    // boardW-1 is #, boardW-2 is other side of board
                    listHead.pos->x = boardW - 2; 
                }
                break;

            case RIGHT: 
                listHead.pos->x++;
                // wraps around
                if(listHead.pos->x >= (boardW - 1)){
                    listHead.pos->x = 1;
                }
                break;

            case UP: 
                listHead.pos->y--;
                // wraps around
                if(listHead.pos->y <= 0){
                    listHead.pos->y = boardH - 2;
                }
                break;

            case DOWN: //down
                listHead.pos->y++;
                // wraps around
                if(listHead.pos->y >= (boardH - 1)){
                    listHead.pos->y = 1;
                }
                break;
        }

        // moves player forward
        playerPosList->insertHead(listHead);

        // checks if head will overlap food
        objPos foodPos = mainGameFoodRef->getFoodPos();
        // if head catches food don't remove tail to make 
        // length increase by 1 (since food eaten)
        if (listHead.isPosEqual(&foodPos)){
            increasePlayerLength();
            //change foodpos location after being eaten
            mainGameFoodRef->generateFood(playerPosList);
        } else {
            // removes tail to maintain length while moving
            playerPosList->removeTail();
        }
    }
}

// More methods to be added