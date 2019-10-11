#include "Items.h"

Items::Items()
{
    //ctor
}

Items::~Items()
{
    //dtor
}


bool Items::GetItemsPodnies()
{
	if(!przPodnies)
	return true;
	else
	return false;
}

int GetItemsPosX()
{
	return 0;
}
int GetItemsPosY()
{
	return 0;
}
void SetItemsPosX(int posx)
{
}
void SetItemsPosY(int posy)
{
}
unsigned int Items::GetItemsID()
{
	return przID;
}
unsigned int Items::GetItemsWaga()
{
	return przWaga;
}
