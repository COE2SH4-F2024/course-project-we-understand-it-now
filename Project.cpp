#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"

using namespace std;

#define DELAY_CONST 100000
// may need to store somewhere later; temp def for drawscreen
#define M 10
#define N 20

bool exitFlag;


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(exitFlag == false)  
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

    exitFlag = false;
}

void GetInput(void)
{
   
}

void RunLogic(void)
{
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    
    //! not sure abt below
    // int i, j;
    // for(i = 0; i < M; i++) {     
    //     for(j = 0; j < N; j++) {
    //         // if on border place border char
    //         if (i = 0  || i == (M-1) || j == 0 || j == (N-1)){
    //             cout << "#";
    //         } else {
    //             cout << " ";
    //         }
    //     }
    //     cout << endl;
    // }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    MacUILib_uninit();
}
