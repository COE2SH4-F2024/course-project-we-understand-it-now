#include "objPos.h"

class Food
{
    private:
        objPos foodPos;
    
    public:
        Food();
        ~Food();

        void generateFood(objPos blockOff);
        objPos getFoodPos() const;
};