#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
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
    myPlayer = new Player(myGM);
    myFood = new Food();

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
    objPos playerPos = myPlayer -> getPlayerPos();
    objPos foodPos = myFood -> getFoodPos();

    int boardX = myGM -> getBoardSizeX();
    int boardY = myGM -> getBoardSizeY();

    // MacUILib_printf("Player[x, y] = [%d, %d], %c\n",
    //                 playerPos.pos->x, playerPos.pos->y, playerPos.getSymbol());

    MacUILib_printf("Food[x,y] = [%d,%d], %c\n",
                    foodPos.pos->x, foodPos.pos->y, foodPos.symbol);


    for (int i = 0; i < boardY; i++){
        for (int j = 0; j < boardX; j++){
            if (i == 0 || i == (boardY - 1) || j == 0 || j == (boardX - 1)){
                MacUILib_printf("#");
            }
            else if ((i == playerPos.pos -> y) && (j == playerPos.pos -> x)){
                MacUILib_printf("%c", playerPos.symbol);
            }
            else if ((j == foodPos.pos -> x) && (i == foodPos.pos -> y)){
                MacUILib_printf("%c", foodPos.symbol);
            }
            else {

                MacUILib_printf("%c", ' ');
            }
        }
        MacUILib_printf("\n");
    }
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
