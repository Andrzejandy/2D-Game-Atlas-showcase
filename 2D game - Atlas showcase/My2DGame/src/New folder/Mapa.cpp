//#include "stdafx.h"
#include "Mapa.h"
#include <math.h>

#define M_PI 3.141/*59265358979323846*/

int modulo(int a, int b)
{ return (a%b+b)%b; }

Mapa::Mapa(int maxx, int maxy)
{
	player,pMonster,pGUI = nullptr;
	player = new Player();
//	pMonster = new Enemies();
	pGUI = new GUI();
	Resolution = 8; // parzyste!
	Mapa_size_X = maxx;
	Mapa_size_Y = maxy;
	//docelowa = false;
	RectSizeX = sf::VideoMode::getDesktopMode().width / Resolution;
	RectSizeY = sf::VideoMode::getDesktopMode().height / Resolution;

	player->SetShapeRes(Resolution);
	pMonster.SetShapeRes(Resolution);

	rect.setSize(sf::Vector2f(	RectSizeX,	RectSizeY));  // +1 bez bugów
	rectPrz.setSize(sf::Vector2f( RectSizeX/1.5,	RectSizeY/1.5)); // -//-

	pociskShape.setRadius(RectSizeY/5);
	pociskShape.setOrigin(RectSizeX/9,RectSizeY/9);


	map_size[Mapa_size_X][Mapa_size_Y];
	//	CreateMap();
	//	CreateMapKwadrats

	if(!drzewo.loadFromFile("Resources//sprites//drzewo.png"))
		drzewo.loadFromFile("drzewo.png");
	if(!trawa.loadFromFile("Resources//sprites//trawa.png"))
		trawa.loadFromFile("trawa.png");
	if(!kamien.loadFromFile("Resources//sprites//kamien.png"))
		kamien.loadFromFile("kamien.png");
	if(!woda.loadFromFile("Resources//sprites//woda.png"))
		woda.loadFromFile("woda.png");
	if(!przedmiot.loadFromFile("Resources//sprites//przedmiot.png"))
		przedmiot.loadFromFile("przedmiot.png");
	if(!pocisk.loadFromFile("Resources//sprites//pocisk.png"))
		pocisk.loadFromFile("pocisk.png");
	if(!statek.loadFromFile("Resources//sprites//statek.png"))
		statek.loadFromFile("statek.png");
	if(!statek01.loadFromFile("Resources//sprites//statek01.png"))
		statek01.loadFromFile("statek01.png");
	if(!statek02.loadFromFile("Resources//sprites//statek02.png"))
		statek02.loadFromFile("statek02.png");
	if(!statek03.loadFromFile("Resources//sprites//statek03.png"))
		statek03.loadFromFile("statek03.png");
	if(!statek04.loadFromFile("Resources//sprites//statek04.png"))
		statek04.loadFromFile("statek04.png");


	if(!rectPrz.getTexture())
	{		rectPrz.setTexture(&przedmiot);	}
	if(!pociskShape.getTexture())
	{		pociskShape.setTexture(&pocisk);}
};

Mapa::~Mapa(void)
{
//	if(pMonster!=nullptr){delete pMonster; pMonster=nullptr;}
//	if(pKwadrat!=nullptr){delete pKwadrat; pKwadrat=nullptr;}

	if(player!=nullptr)
	{
		delete player;
		player=nullptr;
	}
	if(pGUI!=nullptr){delete pGUI; pGUI=nullptr;}
	MonsterList.clear();

	while(!vec_Tiles.empty())
	{
		std::vector<Tiles>::iterator terIter;
		for(terIter = vec_Tiles.begin(); terIter != vec_Tiles.end(); ++terIter)
		{
			terIter->WyczyscKwadrat();

			terIter->itemy.clear();
		}
		std::vector<Tiles>().swap(vec_Tiles);
	}
	vec_Tiles.clear();

	while(!MonsterList.empty())
	{
		std::list<Enemies>::iterator MonsterList_it; // iterator na potwory
		MonsterList.clear();
		std::list<Enemies>().swap(MonsterList);
	}
//	itemy.clear();
}

Player* Mapa::GetGracz()
{
	return player;
}

Enemies Mapa::GetMonster()
{
	return pMonster;
}

unsigned int Mapa::GetMapSizeX()
{
    return Mapa_size_X;
}

unsigned int Mapa::GetMapSizeY()
{
    return Mapa_size_Y;
}

int Mapa::GetDistance(int x1, int y1, int x2, int y2)
{
	int index = EncodeIndex(x1,y1);

	int x3=0;
	int y3=0;
	if(x1>x2)
	{
		x3 = x1-x2;
	}
	if(x2>x1)
	{
		x3 = x2-x1;
	}
	if(y1>y2)
	{
		y3 = y1-y2;
	}
	if(y2>y1)
	{
		y3 = y2-y1;
	}
	if(x1==x2)
	{
		x3 = x1;
	}
	if(y1==y2)
	{
		y3 = y1;
	}
	std::cout << "X:" << x3 << " Y:" << y3 << "\n\n";
	return x3+y3;
}

int Mapa::DecodeIndexX(int index)
{
	int x;
	x = modulo(index,Mapa_size_Y+1);
	return x;
}

int Mapa::DecodeIndexY(int index)
{
	int y;
	y = index/Mapa_size_Y;
	return y;
}

int Mapa::EncodeIndex(int x, int y)
{
	return int (y*(Mapa_size_Y+1))+x;
}

void Mapa::SpawnMonster()
{
	//pMonster->SetGracz(player);
	pMonster.SetShapeRes(Resolution);
	int freespace = 0;
	int x;
	int y;
	bool col;
	int *index;
	int losujmiejsce;
	std::map<int,int> wolnexy;
	std::map<int,int>::iterator iterwolnexy;
	index = new int[Mapa_size_X*Mapa_size_Y];
	//pMonster->player = player; nie uzywane
	sf::Clock zegar;
	sf::Time czas;

	zegar.restart();
	for(ti_it = vec_Tiles.begin(); ti_it != vec_Tiles.end(); ++ti_it) //skanuj kwadraty
	{
		x = ti_it->GetKwadratPosX();
		y = ti_it->GetKwadratPosY();
		col = ti_it->GetCollidable();
		if(col == true)			// czy kolizja
		{
			++freespace;			//ilosc wolnych
			*index = EncodeIndex(x,y);	// indeks
			wolnexy[freespace] = *index;
		}
	}
	czas = zegar.getElapsedTime();
	std::cout << "iter[ms]: " << czas.asMilliseconds() << std::endl;

	losujmiejsce = rand() % freespace;
	std::cout << "los: " << losujmiejsce << std::endl;
	std::cout << "x: " << x << " y: " << y << std::endl;
	std::cout << "wolnexy[" << wolnexy[losujmiejsce] << "]" << std::endl;
	if(wolnexy[losujmiejsce])
	{
		int ax = DecodeIndexX(wolnexy[losujmiejsce]);
		int ay = DecodeIndexY(wolnexy[losujmiejsce]);
		pMonster.SetIstotaPosX(ax+0.5);
		pMonster.SetIstotaPosY(ay+0.5);
		MonsterList.push_back(pMonster);
		std::cout << "ax: " << ax << std::endl;
		std::cout << "ay: " << ay << std::endl;
	}
	delete index;

}

void Mapa::SpawnMonsters(int NumOfMonsters)
{
	int freespace = 0;
	int x;
	int y;
	bool col;
	int *index;
	int losujmiejsce;
	std::map<int,int> wolnexy;
	std::map<int,int>::iterator iterwolnexy;
	index = new int[vec_Tiles.size()];

//	pMonster = new Enemies();
//	pMonster->player = player; NIe uzywane

	sf::Clock zegar;
	sf::Time czas;
	zegar.restart();

	for(ti_it = vec_Tiles.begin(); ti_it != vec_Tiles.end(); ++ti_it) //skanuj kwadraty
	{
		x = ti_it->GetKwadratPosX();
		y = ti_it->GetKwadratPosY();
		col = ti_it->GetCollidable();
		if(col == false)			// czy kolizja
		{
			++freespace;			//ilosc wolnych
			*index = EncodeIndex(x,y);	// indeks
			wolnexy[freespace] = *index;
		}
	}


	for(int nofmonsters = 0; nofmonsters < NumOfMonsters; nofmonsters++)
	{
//		pMonster = new Enemies();
		pMonster.SetShapeRes(Resolution);

		//pMonster->player = player;
		losujmiejsce = rand() % freespace;
		if(wolnexy[losujmiejsce])
		{
			int ax = DecodeIndexX(wolnexy[losujmiejsce]);
			int ay = DecodeIndexY(wolnexy[losujmiejsce]);
			pMonster.SetIstotaPosX(ax+0.5);
			pMonster.SetIstotaPosY(ay+0.5);
			MonsterList.push_back(pMonster);
			wolnexy.erase(wolnexy[losujmiejsce]);
			std::cout << "ax: " << ax << std::endl;
			std::cout << "ay: " << ay << std::endl;
		}
//		delete pMonster; // nowe
	}
	czas = zegar.getElapsedTime();
	std::cout << "iter[ms]: " << czas.asMilliseconds() << std::endl;
	delete index;
}

void Mapa::KillMonster()
{
	MonsterList.pop_back();
}

void Mapa::MoveMonster()
{
	//static signed int docelowaiyN, docelowaixW;
	int way;
	for( std::list<Enemies>::iterator ist_iter=MonsterList.begin(); ist_iter!=MonsterList.end(); ist_iter++)
	{

		if(ist_iter->docelowa == false)
		{

			ist_iter->docelowaiyN = ist_iter->GetIstotaPosY()-1;
			ist_iter->docelowaixW = ist_iter->GetIstotaPosX()-1;
			ist_iter->docelowa = true;
		}

		if((int)ist_iter->GetIstotaPosX() != (int)player->GetGraczPosX() || (int)ist_iter->GetIstotaPosY() != (int)player->GetGraczPosY())
		{

			way = 1000;
			ist_iter->koniec = -1;
			ist_iter->Zamknieta.clear();
			if(ist_iter->sciezka.empty())
			{
				way = (ist_iter->IstotaSciezka(player->GetGraczPosX(), player->GetGraczPosY(), ist_iter->GetIstotaPosX(), ist_iter->GetIstotaPosY(),	vec_Tiles, Mapa_size_X, Mapa_size_Y));
			}
			else
			{
				way =	ist_iter->sciezka.back();
				if(way == WEST)
				{
					if((int)ist_iter->GetIstotaPosX() == ist_iter->docelowaixW)
					{
						ist_iter->sciezka.pop_back();
						ist_iter->docelowaixW = (int)ist_iter->GetIstotaPosX()-1;
					}
					else way = ist_iter->sciezka.back();
				}
				else if(way == NORTH)
				{
					if((int)ist_iter->GetIstotaPosY() == ist_iter->docelowaiyN)
					{
						ist_iter->sciezka.pop_back();
						ist_iter->docelowaiyN = (int)ist_iter->GetIstotaPosY()-1;
					}
					else way = ist_iter->sciezka.back();
				}
				else if(way == EAST)
				{
					if((int)ist_iter->GetIstotaPosX() == ist_iter->docelowaixW+2)
					{
						ist_iter->sciezka.pop_back();
						ist_iter->docelowaixW = (int)ist_iter->GetIstotaPosX()-1;
					}
					else way = ist_iter->sciezka.back();
				}
				else if(way == SOUTH)
				{
					if((int)ist_iter->GetIstotaPosY() == ist_iter->docelowaiyN+2) // +2 lub +1
					{
						ist_iter->sciezka.pop_back();
						ist_iter->docelowaiyN = (int)ist_iter->GetIstotaPosY()-1;
					}
					else way = ist_iter->sciezka.back();
				}
				//	ist_iter->sciezka.erase(ist_iter->sciezka.begin());
				//	way =	ist_iter->sciezka.front();
			//	std::cout << way << std::endl;
				if(way>= 0 && way <= 10000)
				{
					if(CanMoveMonster(way,ist_iter))
					{
						ist_iter->Wander(player);
						ist_iter->koniec = -1;
					}
					else
					{
						ist_iter->Wander(player);
					}
				}
				//ist_iter->sciezka.clear();
			}

		}
		else
		{
			ist_iter->sciezka.clear();
			ist_iter->Wander(player);
		}


	}
}


bool Mapa::CanMoveMonster(int way, std::list<Enemies>::iterator ist_iter2)
{
	if(way == EAST) // D
	{
		if(TileCollidable(ist_iter2->GetIstotaPosX()+0.2, ist_iter2->GetIstotaPosY()))
		{
			if(ist_iter2->GetIstotaPosX()+0.1 > Mapa_size_X)
			{
				return false;
			}
			else{
				return false;
			}

		}
		else
		{
			if(ist_iter2->GetIstotaPosX()+0.1 > Mapa_size_X+1)
			{
				ist_iter2->SetIstotaPosX(modulo((int)ist_iter2->GetIstotaPosX()+0.1, Mapa_size_X));
				return true;
			}
			else{
				ist_iter2->SetIstotaPosX(ist_iter2->GetIstotaPosX()+0.1);
				return true;}
		}
	}
	if(way== WEST)
	{
		if(TileCollidable(ist_iter2->GetIstotaPosX()-0.2, ist_iter2->GetIstotaPosY()))
		{
			if(ist_iter2->GetIstotaPosX()-0.1 <= Mapa_size_X)
			{
				return false;
			}
			else{
				return false;
			}

		}
		else
		{
			if(ist_iter2->GetIstotaPosX()-0.1 <= 0)
			{
				ist_iter2->SetIstotaPosX(Mapa_size_X+1 - 0.1);
				return true;
			}
			else{
				ist_iter2->SetIstotaPosX(ist_iter2->GetIstotaPosX()-0.1);
				return true;}
		}
	}

	if(way==SOUTH)
	{
		if(TileCollidable(ist_iter2->GetIstotaPosX(), ist_iter2->GetIstotaPosY()+0.2))
		{
			if(ist_iter2->GetIstotaPosY()+0.1>Mapa_size_Y)
			{
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			if(ist_iter2->GetIstotaPosY()+0.1 > Mapa_size_Y+1)
			{
				ist_iter2->SetIstotaPosY(modulo((int)ist_iter2->GetIstotaPosY()+0.1, Mapa_size_Y));
				return true;
			}
			else{
				ist_iter2->SetIstotaPosY(ist_iter2->GetIstotaPosY()+0.1);
				return true;}
		}
	}

	if(way==NORTH)
	{
		if(TileCollidable(ist_iter2->GetIstotaPosX(), ist_iter2->GetIstotaPosY()-0.2))
		{
			if(ist_iter2->GetIstotaPosY()-0.1 <= 0)
			{
				return false;
			}
			else{
				return false;
			}

		}
		else
		{
			if(ist_iter2->GetIstotaPosY()-0.1 <= 0)
			{
				ist_iter2->SetIstotaPosY(Mapa_size_Y+1 - 0.1);
				return true;
			}
			else{
				ist_iter2->SetIstotaPosY(ist_iter2->GetIstotaPosY()-0.1);
				return true;}
		}
	}

}

void Mapa::CreateDefinedMap() // mapka statyczna do testów
{
	if(vec_Tiles.size() <= Mapa_size_X*Mapa_size_Y)
	{
		for(int y=0; y<= Mapa_size_Y; ++y)
		{
			for(int x=0; x<= Mapa_size_X; ++x)
			{
				if(x == 0 && y == 0 || x== 0 && y==Mapa_size_Y || x == Mapa_size_X && y == 0 || x== Mapa_size_X && y == Mapa_size_Y)
				{
				//	pKwadrat = new Tiles;
					pKwadrat.CreateKwadrat(2, 'O', 1, x, y);
					vec_Tiles.push_back(pKwadrat);
					//	map_size[x][y] = 1;
				}
				else
				{
				//	pKwadrat = new Tiles;
					pKwadrat.CreateKwadrat(1, '.', 0, x, y);
					vec_Tiles.push_back(pKwadrat);
				}
			}
		}
		SpawnMonster();
	}
	else
	{
		while(!vec_Tiles.empty())
		{
			vec_Tiles.clear();
			delete player;
			player = new Player();
			player->SetShapeRes(Resolution);		// Mozliwe bugi
		}
		CreateDefinedMap();
	}
}

void Mapa::CreateMapKwadrats()
{
	int ran;
	if(vec_Tiles.size() <= Mapa_size_X*Mapa_size_Y)
	{
		for(int y=0; y<= Mapa_size_Y; ++y)
		{
			for(int x=0; x<= Mapa_size_X; ++x)
			{
				ran = (rand() % 100);
				if(ran <= 70 && ran >= 0)
				{
				//	pKwadrat = new Tiles;
					pKwadrat.CreateKwadrat(1, '.', 0, x, y);
					vec_Tiles.push_back(pKwadrat);
				//	delete pKwadrat;
					//					map_size[x][y] = 0;
				}
				else if(ran > 70 && ran <= 80)
				{
				//	pKwadrat = new Tiles;
					pKwadrat.CreateKwadrat(2, 'O', 1, x, y);
					vec_Tiles.push_back(pKwadrat);
				//	delete pKwadrat;
					//	map_size[x][y] = 1;
				}
				else if ( ran > 80 && ran <= 90)
				{
				//	pKwadrat = new Tiles;
					pKwadrat.CreateKwadrat(3, 'T', 1, x, y);
					vec_Tiles.push_back(pKwadrat);
				//	delete pKwadrat;
					//	map_size[x][y] = 0;
				}
				else if (ran > 90)
				{
				//	pKwadrat = new Tiles;
					pKwadrat.CreateKwadrat(4, '#', 1, x, y);
					vec_Tiles.push_back(pKwadrat);
				//	delete pKwadrat;
					//	map_size[x][y] = 0;
				}
			}
		}
		SpawnMonster();
	}
	else
	{
		while(!vec_Tiles.empty())
		{
			vec_Tiles.clear();
			delete player;
			player = new Player();
		}
		CreateMapKwadrats();
	}
}

void Mapa::RenderConsole()
{
	int ile = 0;
	//DEBUG KONSOLI
	for(int Y = 0; Y<= Mapa_size_Y; Y++)
	{
		for(int X = 0; X<= Mapa_size_X; X++)
		{
			for(ti_it = vec_Tiles.begin(); ti_it!=vec_Tiles.end(); ++ti_it)
			{
				char znak ;
				znak = ti_it->GetSprite();
				//		if(X == pMonster->GetIstotaPosX() && Y==pMonster->GetIstotaPosY())
				//		{
				//			std::cout << "M";
				//		}
				if(X==ti_it->GetKwadratPosX() && Y==ti_it->GetKwadratPosY())
				{
					if(znak == '.')
					{
						std::cout << ".";
					}
					if(znak == 'T')
					{
						std::cout << "T";
					}
					if(znak == 'O')
					{
						std::cout << "O";
					}
					if(znak == '#')
					{
						std::cout << "#";
					}

				}

			}
		}
		std::cout << std::endl;
	}

	// KONIEC DEBUG KONSOLI
}

void Mapa::RenderDebug(sf::RenderWindow &refOkno,int x, int y)
{
	std::cout << x << ":" << y << std::endl;

	int offest_pos_x = player->GetGraczPosX()-Resolution;
	int offest_pos_y = player->GetGraczPosY()-Resolution;
	int pos_offest_pos_x = player->GetGraczPosX()+Resolution;
	int pos_offest_pos_y = player->GetGraczPosY()+Resolution;

	for(int y = offest_pos_y; y<=pos_offest_pos_y; y++)
	{
		for(int x = offest_pos_x; x<= pos_offest_pos_x; x++)
		{
			if(x < Mapa_size_X && y < Mapa_size_Y && x >= 0 && y >= 0)
			{
				int index = ((y*(Mapa_size_Y+1))+x);
				std::cout << vec_Tiles[index].GetSprite();
			}
			else
			{
				int index = modulo(y,Mapa_size_Y+1)+modulo(x,Mapa_size_X);
				std::cout << vec_Tiles[index].GetSprite();
			}
		}
		std::cout << std::endl;
	}
	std::cout << "tisize: " << vec_Tiles.size();
	std::cout << std::endl;

	int index;
	int UoffsetX = -Resolution;
	int	UoffsetY = -Resolution;
	int PoffsetX = Resolution;
	int PoffsetY = Resolution;
	//refOkno.clear();
	for(int Y = UoffsetY; Y<PoffsetY; Y++)
	{
		for(int X = UoffsetX; X<PoffsetX; X++)
		{
			if(X <= Mapa_size_X && Y <= Mapa_size_Y && X>0 && Y>0 )
			{
				index = ((Y*(Mapa_size_Y+1))+X);
				int ix = vec_Tiles[index].GetKwadratPosX();
				int iy = vec_Tiles[index].GetKwadratPosY();
				std::cout << " X:" << ix << " Y:" << iy;
				if(ix == player->GetGraczPosX() && iy == player->GetGraczPosY())
				{

				}
				else if(ix == pMonster.GetIstotaPosX() && iy == pMonster.GetIstotaPosY())
				{

				}
				else
				{
					char znak ;
					znak = vec_Tiles[index].GetSprite();

					if(znak == '.')
					{

					}
					if(znak == 'T')
					{

					}
					if(znak == 'O')
					{

					}
					if(znak == '#')
					{

					}
				}
			}
			//	Y++;
		}
		std::cout << std::endl;
		//	std::cin.get();
	}
}
//////////////USTAWIC TEKSTURE DLA GRACZA JAK DOSTANIE OD ISTOTY ///////////////
void Mapa::RenderMap(sf::RenderWindow &refOkno)
{
	char znak;
	double calk,modfy,modfx, modfxm,modfym, fy, fx,fxm,fym;
	static bool loaded = false;
	//int xxx,yyy;
	int index;
	int x,y, ix, iy;

	sf::Color kolora;
	sf::Vector2f pozycjagracz;



	//if(!rectPrz.getTexture())
	//{
	//	rectPrz.setTexture(&przedmiot);
	//}
	refOkno.clear();
	for(float Y = -Resolution; Y<Resolution+1; Y++)
	{
		for(float X = -Resolution; X<Resolution+1; X++)
		{
			modfx = modf(player->GetGraczPosX(), &calk);
			modfy = modf(player->GetGraczPosY(), &calk);

			y = ((int)player->GetGraczPosY()-((int)Resolution/2)+Y); // resolution-1 lub resolution
			x = ((int)player->GetGraczPosX()-((int)Resolution/2)+X); // (int)Resolution / Resolution
			fy = (-modfy*RectSizeY); // resolution-1 lub resolution przesuniecie mapy o float
			fx = (-modfx*RectSizeX); // (int)Resolution / Resolution
			index = ModuloXY(x,y);
			ix = vec_Tiles[index].GetKwadratPosX();
			iy = vec_Tiles[index].GetKwadratPosY();
			znak = vec_Tiles[index].GetSprite();
			//spritecolor[] = sf::Color(255,0,0);
			rect.setPosition(fx+X*RectSizeX ,fy+Y*RectSizeY);
			if(znak == '.')
			{
			//	rect.setFillColor(sf::Color(255,255,255));
				rect.setTexture(&trawa);
			}
			if(znak == 'T')
			{
			//	rect.setFillColor(sf::Color(255,255,255));
				rect.setTexture(&drzewo);
			}
			if(znak == 'O')
			{
			//	rect.setFillColor(sf::Color(255,255,255)); // 200,200,0
				rect.setTexture(&kamien);
			}
			if(znak == '#')
			{
			//	rect.setFillColor(sf::Color(255,255,255)); // 255,255,0
				rect.setTexture(&woda);
			}
			if(znak == 'S')
			{
				rect.setTexture(&statek);
			}

			if(znak == '1')
			{
				rect.setTexture(&statek01);
			}
			if(znak == '2')
			{
				rect.setTexture(&statek02);
			}
			if(znak == '3')
			{
				rect.setTexture(&statek03);
			}
			if(znak == '4')
			{
				rect.setTexture(&statek04);
			}

			if(vec_Tiles[index].GetCollidable() == true)
			{
				//		col.setPosition(vec_Tiles[index].GetKwadratPosX()*28,vec_Tiles[index].GetKwadratPosY()*28);
			}
			refOkno.draw(rect);

			if(GetPrz(GetKwadrat(ix,iy)) == true ) // do poprawy
			{
				rectPrz.setPosition(fx+X*sf::VideoMode::getDesktopMode().width / Resolution ,fy+Y*sf::VideoMode::getDesktopMode().height/ Resolution );
				refOkno.draw(rectPrz);
			}
			else
			{refOkno.draw(rect);}

			if(ix == (int)player->GetGraczPosX() && iy == (int)player->GetGraczPosY())
			{

				player->SetShapePosition((X*RectSizeX+fx)+modfx*RectSizeX , (Y*RectSizeY+fy+modfy)+modfy*RectSizeY);

			}
			refOkno.draw(player->GraczShape);


		//	refOkno.draw(rect); // podswietlenie pozycji gracza
			for(std::list<Enemies>::iterator monsteriter = MonsterList.begin(); monsteriter != MonsterList.end(); monsteriter++)
			{
				if(ix == (int)monsteriter->GetIstotaPosX() && iy == (int)monsteriter->GetIstotaPosY())
				{
					modfxm= modf(monsteriter->GetIstotaPosX(), &calk);
					modfym= modf(monsteriter->GetIstotaPosY(), &calk);

					monsteriter->SetShapePosition((X*RectSizeX+fx)+modfxm*RectSizeX,(Y*RectSizeY+fy)+modfym*RectSizeY);

					//monsteriter->SetShapePosition(X*RectSizeX+Resolution , Y*RectSizeY+Resolution);
				}
				refOkno.draw(monsteriter->GetShape());
			}
			//if((int)pociskShape.getGlobalBounds().contains(rect.getPosition()))
			//{
			//	pociskShape.setPosition(fx+X*sf::VideoMode::getDesktopMode().width / Resolution ,fy+Y*sf::VideoMode::getDesktopMode().height/ Resolution);
			//}
			if(pociskZegar.getElapsedTime().asSeconds()< 0.5f && (int)pociskShape.getPosition().x != 0)
			{
			refOkno.draw(pociskShape);
			}
		}
		//	refOkno.draw(rect);
		//	refOkno.draw(col);
		/*	}*/
	}


	//player->SetShapePosition(player->GetGraczPosX()*48+(GraczShape.getSize().x/2),player->GetGraczPosY()*48+(GraczShape.getSize().y/2));


	//	refOkno.draw(player->GraczShape);

}

void Mapa::test1(int x, int y)
{
	//	int index  = (y*(Mapa_size_Y+1))+x;
	int xx;
	int yy;
	yy = y/RectSizeY;
	xx = x/RectSizeX;
	yy = modulo(yy,Mapa_size_Y);
	xx = modulo(xx,Mapa_size_X);
	int index = ModuloXY(xx,yy);
	std::cout << "X: " << vec_Tiles[index].GetKwadratPosX() << " Y: " << vec_Tiles[index].GetKwadratPosY() << " " << vec_Tiles[index].GetSprite() << std::endl;
}

void Mapa::test2(int x, int y)
{
	//	int index  = (y*(Mapa_size_Y+1))+x;
	int xx = x;
	int yy = y;

	//	yy = ;
	//	xx = xx/Mapa_size_X;
	int index  = (yy*(Mapa_size_Y+1))+xx;
	//	int index = ((yy+(player->GetGraczPosY()/2))*(Mapa_size_Y+1))+xx+(player->GetGraczPosX()/2);
	std::cout << "X: " << vec_Tiles[index].GetKwadratPosX() << " Y: " << vec_Tiles[index].GetKwadratPosY() << " " << vec_Tiles[index].GetSprite() << std::endl;

}
// Mapa(){}

int Mapa::ModuloXY(int x, int y) // do poprawy
{
	if(x<1)
	{
		x= modulo(x,(Mapa_size_X+1));
	}
	if(y<1)
	{
		y= modulo(y,(Mapa_size_Y+1));
	}
	if(x>Mapa_size_X)
	{
		x = modulo(x,(Mapa_size_X+1));
	}
	if(y>Mapa_size_Y)
	{
		y = modulo(y,(Mapa_size_Y+1));
	}
	return (y*(Mapa_size_Y+1))+x;
}

bool Mapa::TileCollidable(int x, int y)
{
	if(x<0)
	{
		x = Mapa_size_X;
	}
	if(y<0)
	{
		//y = -y;
		y= Mapa_size_Y;
	}
	if(x>Mapa_size_X)
	{
		x = modulo(x,Mapa_size_X+1);
	}
	if(y>Mapa_size_Y)
	{
		y = modulo(y,Mapa_size_Y+1);
	}
	int index =  (y*(Mapa_size_Y+1))+x;
//	std::cout << "\n   indeks X - "<< vec_Tiles[index].GetKwadratPosX() << " indeks Y -  " << vec_Tiles[index].GetKwadratPosY() << "\n";// do debugowania
	if(index > vec_Tiles.size())
	{
		index = modulo(index,(Mapa_size_Y+1)*Mapa_size_X);
	}
	//	std::cout << "x: " << vec_Tiles.at(index).GetKwadratPosX() << " y:" << vec_Tiles.at(index).GetKwadratPosY() << std::endl;

	if(vec_Tiles[index].GetCollidable() == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Mapa::SetMapMaxXY(int mapmaxx, int mapmaxy)
{
	Mapa_size_X = mapmaxx;
	Mapa_size_Y = mapmaxy;
}

float Mapa::GetResolution() // float/ int
{
	return Resolution;
}

void Mapa::SetResolution(int res)
{
	Resolution = res;
}

bool Mapa::CanMove(int way)  // int - 1 // float - 0.25 // NIE UZYWANA
{
	float g_py; //  miejsce postaci y
	float g_px; // miejsce postaci x
	g_py = player->py;
	g_px = player->px;

	if(way == EAST) // D
	{
		if(!TileCollidable(g_px+1,g_py))
		{
			if(player->px+0.25 <= Mapa_size_X)  // +1 / + 0.25
			{
				//	if(player->px+1 == ti_it->GetKwadratPosX() && g_py == ti_it->GetKwadratPosY() && ti_it->GetCollidable() == false)
				//	{
				player->px = player->px+0.25; // px + 1 / px +0.25
				return true;
				//	}
			}
			else // prawo
			{
				//	if(modulo(player->px, Mapa_size_X) == ti_it->GetKwadratPosX() && g_py == ti_it->GetKwadratPosY() && ti_it->GetCollidable() == false)
				//	{
				player->px = modulo(player->px, Mapa_size_X);
				return true;
				//	}
			}
		}
	}
	else if (way == SOUTH) // S
	{
		if(!TileCollidable(g_px,g_py+1))
		{
			if(player->py+0.25 <= Mapa_size_Y)
			{
				//	if(player->py+1 == ti_it->GetKwadratPosY() && g_px == ti_it->GetKwadratPosX() && ti_it->GetCollidable() == false)
				//	{
				player->py = player->py+0.25;
				return true;
				//		}
			}
			else // dol
			{
				//		if(modulo(player->py, Mapa_size_Y) == ti_it->GetKwadratPosY() && player->px == ti_it->GetKwadratPosX() && ti_it->GetCollidable() == false)
				//		{
				player->py = modulo(player->py, Mapa_size_Y);
				return true;
				//		}
			}
		}
	}
	else if (way == WEST) // A
	{
		if(!TileCollidable(g_px-1,g_py))
		{
			if(player->px-0.25 >= 0)
			{
				//	if(player->px-1 == ti_it->GetKwadratPosX() && g_py == ti_it->GetKwadratPosY()  && ti_it->GetCollidable() == false)
				//	{
				player->px = player->px-0.25;
				return true;
				//	}
			}
			else // lewo
			{
				//	if(modulo(player->px,Mapa_size_X) + Mapa_size_X == ti_it->GetKwadratPosX() && modulo(player->py,Mapa_size_Y) + Mapa_size_Y == ti_it->GetKwadratPosY() && ti_it->GetCollidable() == false)
				//	{
				player->px = modulo(player->px,Mapa_size_X) + Mapa_size_X;
				return true;
				//	}
			}
		}
		return false;
	}

	else if ( way == NORTH) // W
	{
		if(!TileCollidable(g_px,g_py-1))
		{
			if(player->py-0.25 >= 0)
			{
				//	if(player->py-1 == ti_it->GetKwadratPosY() && g_px == ti_it->GetKwadratPosX() && ti_it->GetCollidable() == false)
				//	{
				player->py = player->py-0.25;
				return true;
				//	}
			}
			else
			{
				//if(modulo(player->py, Mapa_size_Y) + Mapa_size_Y == ti_it->GetKwadratPosY() && modulo(player->px,Mapa_size_X) + Mapa_size_X == ti_it->GetKwadratPosX() && ti_it->GetCollidable() == false)
				//{
				player->py = modulo(player->py, Mapa_size_Y) + Mapa_size_Y;
				return true;
				//}
			}

		}
		return false;
	}

}

void Mapa::MoveGracz(int way)
{
	if(CanMove(way) == true)
	{
		//std::cout << "X: " << player->GetGraczPosX() << " Y: " << player->GetGraczPosY() << std::endl;
		//		player->Idz(way);
	}
}

void Mapa::UpdateGraczPos(float kat, float dlugoscklatki) // kat i dlugosc klatki
{
	double velY = cos(kat * M_PI / 180);
    double velX = sin(kat * M_PI / 180);
	static float vel = 0.8f; // 0.8f 0.5f <-- 0.6f
	float speed = dlugoscklatki * vel;
	//std::cout << "kat: " << kat << "\n";
	//std::cout << "Y: " << velY << "\n";
	//std::cout << "X: " << velX << "\n";
	//std::cout << speed << std::endl;

	player->MovementSpeedX= speed* velX;
	player->MovementSpeedY = speed* -velY;
}


void Mapa::GraczColliding()
{
	if(player->MovementSpeedX > 0.0)	// Prawo
	{
		if(player->px+0.2>Mapa_size_X)
		{
			if(TileCollidable(player->px+0.2,player->py)) // tilecolid moze float/int
			{
				player->MovementSpeedX = 0;
			}
			if(player->px+player->MovementSpeedX > Mapa_size_X+1)
			{
				player->px = 0; // lub player->px = modulo(Mapa_size_X, player->py);
			}
		}
		else
		{
			if(TileCollidable(player->px+0.2, player->py)) // dziala
			{
				player->MovementSpeedX = 0;
			}
		}

	}
	else if(player->MovementSpeedX < 0.0)	// Lewo
	{
		if(player->px-0.2<=0) // <= badz <
		{
			if(TileCollidable(Mapa_size_X,player->py))
			{
				player->MovementSpeedX = 0;
			}
			if(player->px-player->MovementSpeedX <= 0) // dziala
			{
				player->px = Mapa_size_X+1-MovementSpeedX;
			}
		}

		else
		{
			if(TileCollidable(player->px-0.2, player->py)) // dziala
			{
				player->MovementSpeedX = 0;
			}
		}
	}
	if(player->MovementSpeedY > 0.0)	// Dol
	{
		if(player->py+0.2>Mapa_size_Y)
		{
			if(TileCollidable(player->px,player->py+0.2)) // py+0.2 lub 0
			{
				player->MovementSpeedY = 0;
			}
			if(player->py+player->MovementSpeedY > Mapa_size_Y+1) // dziala
			{
				player->py = 0;// 0 lub modulo(player->py, Mapa_size_Y)
			}
		}
		else
		{
			if(TileCollidable(player->px, player->py+0.2))
			{
				player->MovementSpeedY = 0;
			}
		}
	}
	else if(player->MovementSpeedY < 0.0)	//Gora
	{
		if(player->py-0.2<=0)
		{
			if(TileCollidable(player->px,Mapa_size_Y))
			{
				player->MovementSpeedY = 0;
			}
			if(player->py-player->MovementSpeedY <= 0) // dziala
			{
				player->py = Mapa_size_Y+1-MovementSpeedY;
			}
		}
		else
		{
			if(TileCollidable(player->px, player->py-0.2))
			{
				player->MovementSpeedY = 0;
			}
		}
	}
}

void Mapa::SaveMap()
{
	std::ofstream zapis ("mapa0.dat");
	zapis << Mapa_size_X << "\n";
	zapis << Mapa_size_Y << "\n";
	zapis << "0" << "\n";	// pozycja gracza w x
	zapis << "2" << "\n";	// pozycja gracza w y
	if(zapis.is_open())
	{
		for(int x =0; x<=Mapa_size_X; x++)
		{
			for(int y=0; y<=Mapa_size_Y; y++)
			{
				zapis << vec_Tiles[y+x*(Mapa_size_Y+1)].GetSprite();
			}
			zapis << "\n";
		}
		//Zapisz tutaj pozycje istot
		zapis << MonsterList.size() << "\n"; //Zapisz ilosc istot
		for(std::list<Enemies>::iterator monsteriter = MonsterList.begin(); monsteriter != MonsterList.end(); monsteriter++)
		{
			zapis << monsteriter->GetIstotaPosX() << "\n";	//X
			zapis << monsteriter->GetIstotaPosY() << "\n";  //Y
		}
		zapis.close();
	}
	else
	{
		// blad nie mozna otworzyc pliku
	}
}


Tiles* Mapa::GetKwadrat(int posx, int posy)
{
	int index = EncodeIndex(posx, posy);
	{
		//std::cout << "Created: " << std::endl;
		//std::cout << vec_Tiles[index].GetKwadratPosX() << vec_Tiles[index].GetKwadratPosY() << std::endl;
		return &vec_Tiles[index];

	}
}

//przedmioty

void Mapa::DebugShape(int x, int y) // sprawdz czy MonsterShape jest pod kursorem
{
	for(std::list<Enemies>::iterator monsteriter = MonsterList.begin(); monsteriter != MonsterList.end(); monsteriter++)
			{
	std::cout << "X " << monsteriter->GetShape().getPosition().x << std::endl;
	std::cout << "Y " << monsteriter->GetShape().getPosition().y << std::endl;
	if(monsteriter->GetShape().getGlobalBounds().contains(x,y))
	{
		std::cout << monsteriter->GetIstotaPosX() << std::endl;
		std::cout << " jest! " << std::endl;
		std::cout << "HP " << monsteriter->GetHealth() << std::endl;
	}
	else
	{
		std::cout << " brak " << std::endl;
	}
		}
}

void Mapa::UpdatePociskPos(float kat, float dlugoscklatki)
{
	float velY = cos(kat * M_PI / 180);
    float velX = sin(kat * M_PI / 180);
	double bx = pociskShape.getPosition().x;
	double by = pociskShape.getPosition().y;
	static int indeksprzedmiot = 0;

	if(pociskZegar.getElapsedTime().asSeconds() < 0.5f)
	{
		pociskShape.setPosition(bx+=velX*1000*dlugoscklatki,by+=velY*1000*dlugoscklatki);
	}
	else
	{
	//	pociskShape.setPosition(5000,5000);
	//	pociskShape.setRadius(0.0f);
		//std::cout<< pociskZegar.getElapsedTime().asSeconds()<< std::endl;
	}

	for(std::list<Enemies>::iterator monsteriter = MonsterList.begin(); monsteriter != MonsterList.end(); monsteriter++)
	{
		if(pociskShape.getGlobalBounds().contains(monsteriter->GetShape().getPosition()) && (int)pociskShape.getPosition().x != 0)
		{ //monsteriter->GetShape().getGlobalBounds().contains(pociskShape.getPosition()
			monsteriter->SetHealth(rand() % 30 + 1); // 30 - 1
			pociskShape.setPosition(-5000,-5000);
			if(monsteriter->GetHealth()<20)
			{
				GetKwadrat(monsteriter->GetIstotaPosX(),monsteriter->GetIstotaPosY())->StworzPrz(indeksprzedmiot, "wer");
				indeksprzedmiot++;
				MonsterList.erase(monsteriter);
				break;
			}
		}
		else
		{
			//	std::cout << " brak " << std::endl;
		}
	}


}

void Mapa::AttackShape(int x, int y, float kat) // Atak
{
	if(pociskZegar.getElapsedTime().asSeconds()>0.5f )
	{
	player->GraczShape.setTextureRect(sf::IntRect(0,64,64,64));
	pociskShape.setPosition(player->GraczShape.getPosition().x,player->GraczShape.getPosition().y);
	kat = player->GraczShape.getRotation()-180;
	float velY = cos(kat * M_PI / 180);
    float velX = sin(kat * M_PI / 180);
	pociskShape.setRotation(-kat);
	pociskZegar.restart();
	}

}

void Mapa::Podnies(int x, int y) // DOPISAC MODULO JESZCZE
{
	 double modfx,modfy,calk;
	//int yy = ((int)player->GetGraczPosY()-((int)Resolution/2)+y/(int)RectSizeY);
	//int xx = ((int)player->GetGraczPosX()-((int)Resolution/2)+x/(int)RectSizeX);
	modfx= modf(player->GetGraczPosX(), &calk);
	modfy= modf(player->GetGraczPosY(), &calk);
	float yy = (player->GetGraczPosY()+modfy-(Resolution/2)+y/RectSizeY); //float/int
	float xx = (player->GetGraczPosX()+modfx-(Resolution/2)+x/RectSizeX); //float/int
	yy = modulo(yy,Mapa_size_Y);
	xx = modulo(xx,Mapa_size_X);
	int index = ModuloXY(xx,yy);
	//std::cout << "y "<<y << std::endl;		// debugowanie
	//std::cout << "x "<<x << std::endl;
	//std::cout << "yy "<<yy << std::endl;
	//std::cout << "xx "<<xx << std::endl;
	//std::cout << "index " <<index << std::endl;

	if((xx == (int)player->GetGraczPosX()+1 || xx == (int)player->GetGraczPosX()-1 || xx==(int)player->GetGraczPosX()) && (yy == (int)player->GetGraczPosY()+1
		|| yy==(int)player->GetGraczPosY()-1 || yy==(int)player->GetGraczPosY()))
	{
	if(vec_Tiles[index].itemy.empty() == false)
	{
		//	graczitemy = std::move(vec_Tiles[index].itemy);
			graczitemy.push_back(vec_Tiles[index].itemy.back());
			vec_Tiles[index].itemy.pop_back();
	}
		//itemy.clear();
	}
}

void Mapa::Napraw()
{
	std::cout << graczitemy.size() << std::endl;
	if(graczitemy.empty()==false)
	{
		player->SetGraczHP(player->GetGraczHP()+(player->GetGraczHP()+400)/player->GetGraczHP());
		graczitemy.pop_back();
	}
}

void Mapa::Upusc(int x,int y)
{
	 double modfx,modfy,calk;

	//int yy = ((int)player->GetGraczPosY()-((int)Resolution/2)+y/(int)RectSizeY);//  mozliwe do poprawki
	//int xx = ((int)player->GetGraczPosX()-((int)Resolution/2)+x/(int)RectSizeX);//
	modfx= modf(player->GetGraczPosX(), &calk);
	modfy= modf(player->GetGraczPosY(), &calk);
	int yy = (player->GetGraczPosY()+modfy-(Resolution/2)+y/RectSizeY);
	int xx = (player->GetGraczPosX()+modfx-(Resolution/2)+x/RectSizeX);
	yy = modulo(yy,Mapa_size_Y);
	xx = modulo(xx,Mapa_size_X);
	int index = ModuloXY(xx,yy); //
	//if(xx == player->GetGraczPosX()  && yy == player->GetGraczPosY() ||
	//	xx==player->GetGraczPosX()-1 && yy==player->GetGraczPosY() ||
	//	xx==player->GetGraczPosX()+1 && yy==player->GetGraczPosY() ||
	//	xx==player->GetGraczPosX() && yy==player->GetGraczPosY()-1 ||
	//	xx==player->GetGraczPosX() && yy==player->GetGraczPosY()+1)
	//{
	if((xx == (int)player->GetGraczPosX()+1 || xx == (int)player->GetGraczPosX()-1 || xx==(int)player->GetGraczPosX()) && (yy == (int)player->GetGraczPosY()+1
		|| yy==(int)player->GetGraczPosY()-1 || yy==(int)player->GetGraczPosY()))
	{
		if(graczitemy.empty() == false)
		{
			vec_Tiles[index].itemy = std::move(graczitemy);
		}
	}
}
