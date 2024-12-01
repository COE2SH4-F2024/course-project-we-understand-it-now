#include "Food.h"
#include "MacUILib.h"
#include "GameMechs.h"
#include "objPosArrayList.h"

Food::Food(){
    foodPos.setObjPos(-10, -10, 'o'); // Place initial food outside of board
}

Food::~Food(){
    // Unneeded
}

void Food::generateFood(objPosArrayList* blockOff){
    bool isValid;
    GameMechs genFoodGM; // Need an instance of a GameMechs for generateFood purposes

    // Current issue, but unspecified by iterative workflow is that food can spawn
    // in borders and on character
    do {
        isValid = true;
        int randX = 1 + rand() % (genFoodGM.getBoardSizeX() - 2);
        int randY = 1 + rand() % (genFoodGM.getBoardSizeY() - 2);
        foodPos.setObjPos(randX, randY, 'o');

        // loops through all of player positions, making sure none match new food
        for (int i = 0; i < blockOff->getSize(); i++){
            if (blockOff->getElement(i).isPosEqual(&foodPos)){
                isValid = false;
            }
        }
        
    } while (!isValid); 
}

objPos Food::getFoodPos() const{
    return foodPos;
}