#include "Tiles.h"

Tiles::Tiles()
{
	blockId = 0;
	ParentKwadrat = nullptr;
}

Tiles::~Tiles()
{
    //dtor
}


void Tiles::WyczyscKwadrat()
{
	itemy.clear();
	//itemy.clear();
}

	bool Tiles::GetPrz(Tiles *KWADRAT)
	{
		if(!KWADRAT->itemy.empty())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Tiles::StworzPrz(int przId, std::string stringPrz)
	{
	//	itemy.push_back(Przedmiot(przId,przId,stringPrz);
		//Pprzedmiot = new Items( przId, przId, stringPrz);
		//std::cout << Pprzedmiot.GetItemsID();
		itemy.push_back(Pprzedmiot);
		//delete Pprzedmiot; //
	}

	void Tiles::DrukujPrzedmioty()
	{
		for(iter_itemy = itemy.begin(); iter_itemy!= itemy.end(); iter_itemy++)
		{
			std::cout << "ID: " << iter_itemy->GetItemsID() << std::endl;
		}
	}

	int Tiles::GetBlockId()
	{
		return blockId;
	}

	void Tiles::SetBlockId(int BLOCKID)
	{
		blockId = BLOCKID;
	}

	void Tiles::SetSprite(char SPRITE)
	{
		Sprite = SPRITE;
	}

	void Tiles::SetCollidable(bool COLLIDABLE)
	{
		collidable = COLLIDABLE;
	}

	void Tiles::SetPosX(int TPOSX)
	{
		tposx = TPOSX;
	}

	void Tiles::SetPosY(int TPOSY)
	{
		tposy = TPOSY;
	}

	char Tiles::GetSprite()
	{
		return Sprite;
	}

	bool Tiles::GetCollidable()
	{
		return collidable;
	}

	int Tiles::GetKwadratPosX()
	{
		return tposx;
	}

	int Tiles::GetKwadratPosY()
	{
		return tposy;
	}

	void Tiles::PrintKwadrats()
	{
		std::cout << tposx << " ";
		std::cout << tposy <<std::endl;
	}

	void Tiles::CreateKwadrat(int BLOCKID ,char SPRITE, bool COLLIDABLE, int TPOSX, int TPOSY)
	{
		blockId = BLOCKID;
		Sprite = SPRITE;
	//	color = COLOR;
		collidable = COLLIDABLE;
		tposx = TPOSX;
		tposy = TPOSY;
	}


	bool Tiles::operator<(const Tiles& L  ) const
	{
        return L.funkcheu < funkcheu;
	}

	bool Tiles::operator==(const Tiles& S) const
	{
		if(S.tposx == tposx && S.tposy == tposy)
		{
			return true;
		}
		else
			return false;
	}
