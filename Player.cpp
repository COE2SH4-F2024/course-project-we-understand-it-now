#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    mainGameFoodRef = thisFoodRef;
    myDir = STOP;
    symbol = '*';
    // instantiate objPosArrayList on heap
    playerPosList = new objPosArrayList();

    // set player initial conditions, start in middle of board
    objPos headPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, symbol);
    playerPosList->insertHead(headPos);

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

bool Player::checkSelfCollision(){

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
                if (myDir != UP & myDir != DOWN){ // If the direction wasn't vertical, then you can go up
                    myDir = UP;
                }
                break;
            case 'a': 
                if (myDir != LEFT && myDir != RIGHT){ // If the direction wasn't horizontal, then you can go left
                    myDir = LEFT;
                }                
                break;
            case 's': 
                if (myDir != UP & myDir != DOWN){ // If the direction wasn't vertical, then you can go down
                    myDir = DOWN;
                }                
                break;
            case 'd': 
                if (myDir != LEFT && myDir != RIGHT){ // If the direction wasn't horizontal, then you can go right
                    myDir = RIGHT;
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

            case DOWN: 
                listHead.pos->y++;
                // wraps around
                if(listHead.pos->y >= (boardH - 1)){
                    listHead.pos->y = 1;
                }
                break;
        }

        // loops through playerPosList
        for (int h = 0; h < playerPosList->getSize(); h++) {
            // gets element h to compare to in this iteration
            objPos listComp = playerPosList->getElement(h);

            // Check if the position of the listHead aligns with list elements
            if (listHead.isPosEqual(&listComp)){
                
                // If so, activate exit and lose flag
                mainGameMechsRef -> setExitTrue();
                mainGameMechsRef -> setLoseFlag();
                
            }
        }
        
        // only move the characters if exit flag or lose flag aren't triggered above 
        // (prevents display misorientation)
        if (!mainGameMechsRef->getExitFlagStatus() || !mainGameMechsRef->getLoseFlagStatus()){
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
}

// More methods to be added