#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    mainGameFoodRef = thisFoodRef;
    myDir = STOP;
    symbol = '*';
    // Instantiate objPosArrayList on heap
    playerPosList = new objPosArrayList();

    // Setting player initial conditions, start in middle of board
    objPos headPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, symbol);
    playerPosList->insertHead(headPos);

}

Player::~Player()
{ 
    // Delete any heap members here
    delete playerPosList;
    playerPosList = nullptr;
}

objPosArrayList* Player::getPlayerPos() const
{
    // Return the reference to the listHead array list
    return playerPosList;
}

void Player::increasePlayerLength(){
    mainGameMechsRef->incrementScore();
}

bool Player::checkSelfCollision(){
    objPos listHead = playerPosList->getHeadElement();

    // Loops through playerPosList (after its head)
    for (int h = 1; h < playerPosList->getSize(); h++) {
        // gets element h to compare to in this iteration
        objPos listComp = playerPosList->getElement(h);

        // Check if the position of the listHead aligns with list elements
        if (listHead.isPosEqual(&listComp)){
            return true;
        }
    }

    // If no collision detected above,
    return false;
}

bool Player::checkFoodConsumption(){
    objPos foodPos = mainGameFoodRef->getFoodPos();
    // New position after snake movement 
    objPos listHead = playerPosList->getHeadElement();

    // If the new movement made the snake collide with the head
    if (listHead.isPosEqual(&foodPos)){
        return true;

    // No food collision
    } else{
        return false;
    }
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic  

    char input = mainGameMechsRef->getInput();
    
    // If not null (i.e. has an input)
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

    // Get width and height for wraparound
    int boardW = mainGameMechsRef->getBoardSizeX();
    int boardH = mainGameMechsRef->getBoardSizeY();

    
    if (myDir != STOP){
        // Temporary current head position to use when updating movement
        objPos listHead = playerPosList->getHeadElement();

        switch (myDir){
            case LEFT: 
                listHead.pos->x--;
                // Wraps around
                if(listHead.pos->x <= 0){
                    // boardW-1 is #, boardW-2 is other side of board
                    listHead.pos->x = boardW - 2; 
                }
                break;

            case RIGHT: 
                listHead.pos->x++;
                // Wraps around
                if(listHead.pos->x >= (boardW - 1)){
                    listHead.pos->x = 1;
                }
                break;

            case UP: 
                listHead.pos->y--;
                // Wraps around
                if(listHead.pos->y <= 0){
                    listHead.pos->y = boardH - 2;
                }
                break;

            case DOWN: 
                listHead.pos->y++;
                // Wraps around
                if(listHead.pos->y >= (boardH - 1)){
                    listHead.pos->y = 1;
                }
                break;
        }

        // Moves player based on above movement direction
        playerPosList->insertHead(listHead);

        // Check if the position of the listHead collides with snake body
        if (checkSelfCollision()){
            // If so, activate exit and lose flag
            mainGameMechsRef -> setExitTrue();
            mainGameMechsRef -> setLoseFlag();

            // Undoes head move on collision
            playerPosList->removeHead();
            // Don't continue to food collision since self collision detected
            return;
        }

        // If head catches food don't remove tail to make 
        // Length increase by 1 (since food eaten)
        if (checkFoodConsumption()){
            increasePlayerLength();
            
            // Change foodpos location after being eaten
            mainGameFoodRef->generateFood(playerPosList);
        } else {
            // Removes tail to maintain length while moving
            playerPosList->removeTail();
        }
    }
}

// More methods to be added

// Ease of access addition
char Player::getPlayerSymbol(){
    return symbol;
}
