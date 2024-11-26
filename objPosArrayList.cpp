// ! needed for cout
// #include <iostream>
#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    int defaultSize = 200; // can change here easily if necessary
    aList = new objPos[defaultSize];
    listSize = 0;
    arrayCapacity = defaultSize;
}

objPosArrayList::~objPosArrayList()
{
    delete [] aList;
    aList = nullptr;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        // //cout << "WARNING: full list." << endl;
        return;
    }

    // shift all list elements towards the tail
    for(int i = listSize; i > 0; i--)   
        aList[i] = aList[i - 1];  

    aList[0] = thisPos; // 'head' is the 1st element
    listSize++; // list size increased
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        // //cout << "WARNING: full list." << endl;
        return;
    }

    aList[listSize++] = thisPos; //increments listSize after setting current element to thisPos
}

void objPosArrayList::removeHead()
{
    if(listSize == 0)
    {
        // //cout << "WARNING: empty list" << endl;
        return;
    }

    // shift all elements towards the head
    for(int i = 0; i < listSize - 1; i++)   
        aList[i] = aList[i + 1];  

    listSize--;
}

void objPosArrayList::removeTail()
{
    if(listSize == 0)
    {
        // //cout << "WARNING: empty list" << endl;
        return;
    }

    listSize--; 
}

objPos objPosArrayList::getHeadElement() const
{
    if(listSize == 0)
    {
        // //cout << "WARNING: empty list" << endl;
        objPos emptyObjPos = objPos(0,0,'_');
        return emptyObjPos;
    }
    
    //1st element in list is head
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    if(listSize == 0)
    {
        // //cout << "WARNING: empty list" << endl;
        objPos emptyObjPos = objPos(0,0,'_');
        return emptyObjPos;
    }
    
    //last element in list is tail
    return aList[listSize - 1];
}

objPos objPosArrayList::getElement(int index) const
{
    if(listSize == 0 || index < 0 || index >= listSize)
    {
        // //cout << "WARNING: out of bounds" << endl;
        objPos emptyObjPos = objPos(0,0,'_');
        return emptyObjPos;
    }

    // gets index'th element in list
    return aList[index];
}