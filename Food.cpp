#include "Food.h"
#include "MacUILib.h"
#include "GameMechs.h"

Food::Food(){
    foodPos.setObjPos(-10, -10, 'o'); // Place initial food outside of board
}

Food::~Food(){
    // Unneeded
}

void Food::generateFood(objPos blockOff){
    bool isValid;
    GameMechs genFoodGM; // Need an instance of a GameMechs for generateFood purposes

    // Current issue, but unspecified by iterative workflow is that food can spawn
    // in borders and on character
    do {
        isValid = true;
        int randX = rand() % genFoodGM.getBoardSizeX();
        int randY = rand() % genFoodGM.getBoardSizeY();
        foodPos.setObjPos(randX, randY, 'o');

        if (foodPos.isPosEqual(&blockOff)){
            isValid = false;
        }
        
    } while (!isValid); 
}

objPos Food::getFoodPos() const{
    return foodPos;
}