#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer;
GameMechs *myGM;
Food *myFood;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{
    srand(time(NULL)); // Creating a new seed for the rand() function upon every frame
    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGM = new GameMechs();
    myFood = new Food();
    myPlayer = new Player(myGM, myFood);

    myFood -> generateFood(myPlayer->getPlayerPos());
}

void GetInput(void)
{
   myGM -> collectAsyncInput();

   // Debug-Use Key:
//    char input = myGM -> getInput();
//    if (input == 'p'){
//         myFood;
//         myFood -> generateFood(myPlayer->getPlayerPos());
//    }
}

void RunLogic(void)
{
    myPlayer -> updatePlayerDir();
    myPlayer -> movePlayer();

    myGM -> clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    

    // Implement copy assignment operator to work
    objPosArrayList* playerPos = myPlayer -> getPlayerPos();
    int playerSize = playerPos->getSize();
    bool isPlayer;

    objPos foodPos = myFood -> getFoodPos();
    int boardX = myGM -> getBoardSizeX();
    int boardY = myGM -> getBoardSizeY();


    for (int i = 0; i < boardY; i++){
        for (int j = 0; j < boardX; j++){
            // Assume element j i is not the player every loop
            isPlayer = false;

            for (int k = 0; k < playerSize; k++){
                objPos thisSeg = playerPos->getElement(k);

                // Compare positions of element ji to seg j of playerArrayList
                if (objPos(j,i,' ').isPosEqual(&thisSeg)){
                    MacUILib_printf("%c", myPlayer->getPlayerSymbol());
                    // Element j i is the player, skip the rest of conditionals after this loop
                    isPlayer = true;
                }
            }

            // If the player is not element ji perform remaining conditionals 
            if (!isPlayer){
                if (i == 0 || i == (boardY - 1) || j == 0 || j == (boardX - 1)){
                MacUILib_printf("#");
                }
                else if ((j == foodPos.pos -> x) && (i == foodPos.pos -> y)){
                    MacUILib_printf("%c", foodPos.symbol);
                }
                else {
                    MacUILib_printf("%c", ' ');
                }
            }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("Score: %d\n", myGM->getScore());
    MacUILib_printf("Press SPACE To Quit.\n");
    MacUILib_printf("Food[x,y] = [%d,%d], %c\n",
                    foodPos.pos->x, foodPos.pos->y, foodPos.symbol);

    // Establish different game-ending messages based on forced exit or losing exit
    if (myGM -> getLoseFlagStatus() == true){
        MacUILib_printf("You Have Lost The Game\n");
    } else if (myGM -> getExitFlagStatus() == true){
        MacUILib_printf("Game Exited by Player\n");
    }

}    

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    // MacUILib_clearScreen();    

    // Free heap members
    delete myPlayer;
    delete myGM;
    delete myFood;

    MacUILib_uninit();
}
