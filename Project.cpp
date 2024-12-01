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
    srand(time(NULL));
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
   char input = myGM -> getInput();
   if (input == 'p'){
        myFood;
        myFood -> generateFood(myPlayer->getPlayerPos());
   }
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

    // implement copy assignment operator to work
    objPosArrayList* playerPos = myPlayer -> getPlayerPos();
    int playerSize = playerPos->getSize();
    bool isPlayer;

    objPos foodPos = myFood -> getFoodPos();

    int boardX = myGM -> getBoardSizeX();
    int boardY = myGM -> getBoardSizeY();


    for (int i = 0; i < boardY; i++){
        for (int j = 0; j < boardX; j++){
            // assume element j i is not the player every loop
            isPlayer = false;

            for (int k = 0; k < playerSize; k++){
                objPos thisSeg = playerPos->getElement(k);

                // compare positions of element ji to seg j of playerArrayList
                if (objPos(j,i,' ').isPosEqual(&thisSeg)){
                    MacUILib_printf("%c", myPlayer->getPlayerSymbol());
                    // element j i is the player, skip the rest of conditionals after this loop
                    isPlayer = true;
                }
            }

            // if the player is not element ji perform remaining conditionals 
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
    MacUILib_printf("space key to quit\n");

    // MacUILib_printf("Player[x, y] = [%d, %d], %c\n",
    //                 playerPos.pos->x, playerPos.pos->y, playerPos.getSymbol());

    MacUILib_printf("Food[x,y] = [%d,%d], %c\n",
                    foodPos.pos->x, foodPos.pos->y, foodPos.symbol);
}    

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    delete myPlayer;
    delete myGM;
    delete myFood;

    MacUILib_uninit();
}
