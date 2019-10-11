#include "Enemies.h"
#define M_PI 3.141
Enemies::Enemies()
{
    //ctor
}

Enemies::~Enemies()
{
    //dtor
}


int Enemies::modulo(int a, int b)
{
	return (a%b+b)%b;
}

int Enemies::GetHealth()
{
	return health;
}


float Enemies::GetIstotaPosX()
{
	return e_px;
}
float Enemies::GetIstotaPosY()
{
	return e_py;
}

int Enemies::GetIstotaId()
{
	return e_id;
}

bool Komparator(Tiles const & L, Tiles const & R)
{
	return L.funkcheu < R.funkcheu;
}

bool Enemies::GetGracz(float res, Player postac) // pozycje postaci
{
	float pos_e_py_offset = e_py + res;
	float pos_e_px_offset = e_px + res;
	float neg_e_py_offset = e_py - res;
	float neg_e_px_offset = e_px - res;
	for(int y = neg_e_py_offset; y<= pos_e_py_offset; y++)
	{
		for(int x = neg_e_px_offset; x<= pos_e_px_offset; x++)
		{	// x == postac.px && y == postac.py
			if(postac.py > neg_e_py_offset && postac.py < pos_e_py_offset && postac.px > neg_e_px_offset && postac.px < pos_e_px_offset) // postac
			{
				return true;
				//	break;
			}

		}
	}
	return false;
}

void Enemies::SetGracz(Player *gracz)
{
	//*pPostac = *gracz;
}

void Enemies::SetHealth(int hp)
{
	health = health-hp;
	Gmonster.setTextureRect(sf::IntRect(54,0,18,12));
}

void Enemies::SetIstotaPosX(float E_PX)
{
	e_px = E_PX;
}
void Enemies::SetIstotaPosY(float E_PY)
{
	e_py = E_PY;
}

void Enemies::SetIstotaPosXY(float E_PX, float E_PY)
{
	e_px = E_PX;
	e_py = E_PY;
}

void Enemies::SetShapeRes(float resolution)
{
	int	RectSizeX = sf::VideoMode::getDesktopMode().width / resolution;
	int	RectSizeY = sf::VideoMode::getDesktopMode().height / resolution;
	Gmonster.setSize(sf::Vector2f (RectSizeX/3, RectSizeY/3));
	Gmonster.setOrigin(Gmonster.getSize().x/2,Gmonster.getSize().y/2);
}



sf::RectangleShape Enemies::GetShape()
{
	return Gmonster;
}

float Enemies::GetIstotaRot()
{
	return IstotaSpriteRot;
}


void Enemies::Attack(Player *postac)
{
	int randmg;
	randmg = (rand() % 10)+5;

	postac->SetGraczHP(postac->GetGraczHP()-randmg);
	//std::cout << pPostac->GetGraczHP();
	//Wander();
}

void Enemies::Move(int way, Player *postac)
{

	switch (way)
	{
	case NORTH:
		{
			e_py+0.10;
			break;
		}
	case SOUTH:
		{
			e_py+0.10;
			break;
		}
	case WEST:
		{
			e_px+0.10;
			break;
		}
	case EAST:
		{
			e_py+0.10;
			break;
		}

	default:
		Wander(postac);
		break;
	}

}

void Enemies::Wander(Player *postac)
{
	Enemies::SetIstotaRot(postac);
	static int loop = 1;
	loop += 1;
	if(loop >= 1 && loop < 3)
	{
		Gmonster.setTextureRect(sf::IntRect(18,0,18,12));
	}
	if(loop > 3 && loop < 5)
	{
		Gmonster.setTextureRect(sf::IntRect(0,0,18,12));
	}
	else if(loop > 5)
	{
		loop = 1;
	}


	int ran;

	if(GetGracz(0.95, *postac) == true)	// znalazl gracza w odlegosci 0.95
		{
			ran = (rand() % 9);
			if(ran < 3)	// 30% szans
			{
				Gmonster.setTextureRect(sf::IntRect(36,0,18,12));
				postac->GraczShape.setTextureRect(sf::IntRect(64,64,64,64));
				loop = 0;
				Attack(postac);
			}
		}
}
int Enemies::IstotaSciezka(int px, int py, int ix, int iy,
	std::vector<Tiles> KwadratVec, int sizes_x, int sizes_y) // vektor kwadrat bez parenta (pierwszy wierzcholek)
{
	if(koniec != NORTH && koniec != SOUTH && koniec != WEST && koniec != EAST)
	{
		//czy istota nie na miesjcu
		if(ix != px || iy != py)
		{
			int odlegloscX, odlegloscY;

			static float mnoznik = sqrt((float)KwadratVec.size());


			std::vector<std::pair<int,int>> VecOpenMapa;
			std::map<int,int> OpenMapa;	//Klucz(kierunek) 1 - gora, 2 prawo, 3 dol, 4 lewo, Druga wartosc - funkcja heurystyczna

			//	Otwarta.push_back(KwadratVec[ix+iy*mnoznik]); // indeks kwadratu
			odlegloscX = abs(ix - px);	odlegloscY = abs(iy - py);

			float funkcheu[5];
			funkcheu[0] =  odlegloscX + odlegloscY;
			funkcheu[1] =  odlegloscX + odlegloscY;
			funkcheu[2] =  odlegloscX + odlegloscY;
			funkcheu[3] =  odlegloscX + odlegloscY;
			funkcheu[4] =  odlegloscX + odlegloscY;
			KwadratVec[((int)ix)+(int)iy*mnoznik].funkcheu = funkcheu[0];
			Zamknieta.push_back(KwadratVec[((int)ix+((int)iy)*mnoznik)]);
			// funkcheu i openmapa indeksy sa +1 (west 3; 4) itd
			//Gora
			if(iy-1 >= 0)
			{
				if((((int)ix+((int)iy-1)*mnoznik)) > 0)
				{
					if(KwadratVec[((int)ix+((int)iy-1)*mnoznik)].GetCollidable() == true)	//N
					{
						funkcheu[3] = 100000;
						OpenMapa[3] = funkcheu[3];
						Zamknieta.push_back(KwadratVec[((int)ix+((int)iy-1)*mnoznik)]);
					}	// zabezpieczenie nie moze byc mniejsze od rzeczywistej funkcmin
					else
					{
						odlegloscX = abs(ix - px);	odlegloscY = abs(iy-1 - py);
						funkcheu[3] =  odlegloscX + odlegloscY;
						KwadratVec[((int)ix+((int)iy-1)*mnoznik)].funkcheu =  funkcheu[3];
						OpenMapa[3] = funkcheu[3];
					}
				}
			}
			//Prawo
			if(ix+1 <=sizes_x)
			{
				if((((int)ix+1)+(int)iy*mnoznik) <	KwadratVec.size())
				{
					if(KwadratVec[((int)ix+1)+(int)iy*mnoznik].GetCollidable() == true)	//E
					{
						funkcheu[2] = 100000;
						OpenMapa[2] = funkcheu[2];
						Zamknieta.push_back(KwadratVec[((int)ix+1)+(int)iy*mnoznik]);
					}
					else
					{
						odlegloscX = abs(ix+1 - px);	odlegloscY = abs(iy - py);
						funkcheu[2] = odlegloscX + odlegloscY;
						KwadratVec[((int)ix+1)+(int)iy*mnoznik].funkcheu =  funkcheu[2];
						OpenMapa[2] = funkcheu[2];
					}
				}
			}
			//Dol
			if(iy+1 <= sizes_y)
			{
				if((int)ix+(((int)iy+1)*mnoznik) <	KwadratVec.size())
				{
					if(KwadratVec[(int)ix+(((int)iy+1)*mnoznik)].GetCollidable() == true)	//S
					{
						funkcheu[1] = 100000;
						OpenMapa[1] = funkcheu[1];
						Zamknieta.push_back(KwadratVec[(int)ix+(((int)iy+1)*mnoznik)]);
					}
					else
					{
						odlegloscX = abs(ix - px);	odlegloscY = abs(iy+1 - py);
						funkcheu[1] = odlegloscX + odlegloscY;
						KwadratVec[(int)ix+((int)iy+1)*mnoznik].funkcheu =  funkcheu[1];
						OpenMapa[1] = funkcheu[1];
					}
				}
			}
			//Lewo
			if(ix-1 >=0)
			{
				if((((int)ix-1)+(int)iy*mnoznik) < KwadratVec.size())
				{
					if(KwadratVec[((int)ix-1)+(int)iy*mnoznik].GetCollidable() == true)	//W
					{
						funkcheu[4] = 100000;
						OpenMapa[4] = funkcheu[4];
						Zamknieta.push_back(KwadratVec[((int)ix-1)+(int)iy*mnoznik]);
					}
					else
					{
						{
							odlegloscX = abs(ix-1 - px);	odlegloscY = abs(iy - py);
							funkcheu[4] = odlegloscX + odlegloscY;
							KwadratVec[((int)ix-1)+(int)iy*mnoznik].funkcheu =  funkcheu[4];
							OpenMapa[4] = funkcheu[4];
						}
					}
				}
			}
			for (auto iterator = OpenMapa.begin(); iterator != OpenMapa.end(); ++iterator )
			{
				VecOpenMapa.push_back(*iterator);
			}
			//sortowanie OPEN

			std::sort(VecOpenMapa.begin(),VecOpenMapa.end(),
				[](const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) // [] - lambda
			{
				return lhs.second < rhs.second;  // zamiane pierwszej kolumny indeksu na drug¹ - f. heur w celu sortowania wg. heurystyki
			} );


			if(VecOpenMapa.size() >= 1) // ilosc kierunkow do wyboru
			{
				if(VecOpenMapa[0].second == 100000)
				{
				}
				else if (VecOpenMapa[0].second != 100000)
				{
					// Czy vec mapa first (kierunek) south
					if(VecOpenMapa[0].first == 1) // south
					{
						if(VecOpenMapa[0].second == 0)
						{
							koniec = SOUTH;
							sciezka.push_back(SOUTH);
							return SOUTH;
						}
						if((int)ix+(((int)iy+1)*mnoznik) <	KwadratVec.size())
						{

							KwadratVec[(int)ix+((int)iy+1)*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
							Otwarta.push_back(KwadratVec[((int)ix+((int)iy+1)*mnoznik)]);
						}

					}
					if(VecOpenMapa[0].first == 2) // east
					{
						if(VecOpenMapa[0].second == 0)
						{
							koniec = EAST;
							sciezka.push_back(EAST);
							return EAST;
						}
						if((((int)ix+1)+(int)iy*mnoznik) <	KwadratVec.size())
						{

							KwadratVec[((int)ix+1)+(int)iy*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
							Otwarta.push_back(KwadratVec[((int)ix+1)+(int)iy*mnoznik]);
						}
					}
					if(VecOpenMapa[0].first == 3) // north
					{
						if(VecOpenMapa[0].second == 0)
						{
							koniec = NORTH;
							sciezka.push_back(NORTH);
							return NORTH;
						}

						if((((int)ix+((int)iy-1)*mnoznik)) > 0)
						{

							KwadratVec[(int)ix+((int)iy-1)*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
							Otwarta.push_back(KwadratVec[(int)ix+((int)iy-1)*mnoznik]);
						}

					}
					if(VecOpenMapa[0].first == 4) // west
					{
						if(VecOpenMapa[0].second == 0)
						{
							koniec = WEST;
							sciezka.push_back(WEST);
							return WEST;
						}

						if((((int)ix-1)+(int)iy*mnoznik) < KwadratVec.size())
						{

							KwadratVec[((int)ix-1)+(int)iy*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
							Otwarta.push_back(KwadratVec[((int)ix-1)+(int)iy*mnoznik]);
						}
					}
				}
			}
			if(VecOpenMapa.size() >= 2)
			{

				if(VecOpenMapa[1].second == 100000)
				{
				}
				else if(VecOpenMapa[1].second != 100000)
				{
					if(VecOpenMapa[1].first == 1)
					{
						if(VecOpenMapa[1].second == 0)
						{
							koniec = SOUTH;
							sciezka.push_back(SOUTH);
							return SOUTH;
						}
						if((int)ix+(((int)iy+1)*mnoznik) <	KwadratVec.size())
						{

							KwadratVec[(int)ix+((int)iy+1)*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
							Otwarta.push_back(KwadratVec[((int)ix+((int)iy+1)*mnoznik)]);
						}

					}
					if(VecOpenMapa[1].first == 2)
					{
						if(VecOpenMapa[1].second == 0)
						{
							koniec = EAST;
							sciezka.push_back(EAST);
							return EAST;
						}
						if((((int)ix+1)+(int)iy*mnoznik) <	KwadratVec.size())
						{

							KwadratVec[((int)ix+1)+(int)iy*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
							Otwarta.push_back(KwadratVec[((int)ix+1)+(int)iy*mnoznik]);
						}
					}
					if(VecOpenMapa[1].first == 3)
					{
						if(VecOpenMapa[1].second == 0)
						{
							koniec = NORTH;
							sciezka.push_back(NORTH);
							return NORTH;
						}

						if((((int)ix+((int)iy-1)*mnoznik)) > 0)
						{

							KwadratVec[(int)ix+((int)iy-1)*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
							Otwarta.push_back(KwadratVec[(int)ix+((int)iy-1)*mnoznik]);
						}

					}
					if(VecOpenMapa[1].first == 4)
					{
						if(VecOpenMapa[1].second == 0)
						{
							koniec = WEST;
							sciezka.push_back(WEST);
							return WEST;
						}

						if((((int)ix-1)+(int)iy*mnoznik) < KwadratVec.size())
						{

							KwadratVec[((int)ix-1)+(int)iy*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
							Otwarta.push_back(KwadratVec[((int)ix-1)+(int)iy*mnoznik]);
						}
					}
				}
			}

			if(VecOpenMapa.size() >= 3)
			{
				if(VecOpenMapa[2].second == 100000) // zabezpieczenie
				{
				}
				else if(VecOpenMapa[2].second != 100000)
				{
					if(VecOpenMapa[2].first == 1) // czy kierunek north w 1-szej kolumnie mapy, indeksu 2-wego
					{
						if(VecOpenMapa[2].second == 0)
						{
							koniec = SOUTH;
							sciezka.push_back(SOUTH);
							return SOUTH;
						}
						if((int)ix+(((int)iy+1)*mnoznik) <	KwadratVec.size())

						{

							KwadratVec[(int)ix+((int)iy+1)*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
							Otwarta.push_back(KwadratVec[((int)ix+((int)iy+1)*mnoznik)]);
						}
					}
					if(VecOpenMapa[2].first == 2)
					{
						if(VecOpenMapa[2].second == 0)
						{
							koniec = EAST;
							sciezka.push_back(EAST);
							return EAST;
						}
						if((((int)ix+1)+(int)iy*mnoznik) <	KwadratVec.size())
						{

							KwadratVec[((int)ix+1)+(int)iy*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
							Otwarta.push_back(KwadratVec[((int)ix+1)+(int)iy*mnoznik]);
						}
					}
					if(VecOpenMapa[2].first == 3)
					{
						if(VecOpenMapa[2].second == 0)
						{
							koniec = NORTH;
							sciezka.push_back(NORTH);
							return NORTH;
						}

						if((((int)ix+((int)iy-1)*mnoznik)) > 0)
						{

							KwadratVec[(int)ix+((int)iy-1)*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
							Otwarta.push_back(KwadratVec[(int)ix+((int)iy-1)*mnoznik]);
						}

					}
					if(VecOpenMapa[2].first == 4)
					{
						if(VecOpenMapa[2].second == 0)
						{
							koniec = WEST;
							sciezka.push_back(WEST);
							return WEST;
						}

						if((((int)ix-1)+(int)iy*mnoznik) < KwadratVec.size())
						{

							KwadratVec[((int)ix-1)+(int)iy*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
							Otwarta.push_back(KwadratVec[((int)ix-1)+(int)iy*mnoznik]);
						}
					}
				}
			}

			if(VecOpenMapa.size() >= 4)
			{
				if(VecOpenMapa[3].second == 100000)
				{
				}
				else if (VecOpenMapa[3].second != 100000)
				{
					if(VecOpenMapa[3].first == 1)
					{
						if(VecOpenMapa[3].second == 0)
						{
							koniec = SOUTH;
							sciezka.push_back(SOUTH);
							return SOUTH;
						}
						if((int)ix+(((int)iy+1)*mnoznik) <	KwadratVec.size())
						{

							KwadratVec[(int)ix+((int)iy+1)*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
							Otwarta.push_back(KwadratVec[((int)ix+((int)iy+1)*mnoznik)]);
						}
					}
					if(VecOpenMapa[3].first == 2)
					{
						if(VecOpenMapa[3].second == 0)
						{
							koniec = EAST;
							sciezka.push_back(EAST);
							return EAST;
						}
						if((((int)ix+1)+(int)iy*mnoznik) <	KwadratVec.size())
						{

							KwadratVec[((int)ix+1)+(int)iy*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
							Otwarta.push_back(KwadratVec[((int)ix+1)+(int)iy*mnoznik]);
						}
					}
					if(VecOpenMapa[3].first == 3)
					{
						if(VecOpenMapa[3].second == 0)
						{
							koniec = NORTH;
							sciezka.push_back(NORTH);
							return NORTH;
						}

						if((((int)ix+((int)iy-1)*mnoznik)) > 0)
						{

							KwadratVec[(int)ix+((int)iy-1)*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
							Otwarta.push_back(KwadratVec[(int)ix+((int)iy-1)*mnoznik]);
						}

					}
					if(VecOpenMapa[3].first == 4)
					{
						if(VecOpenMapa[3].second == 0)
						{
							koniec = WEST;
							sciezka.push_back(WEST);
							return WEST;
						}

						if((((int)ix-1)+(int)iy*mnoznik) < KwadratVec.size())
						{

							KwadratVec[((int)ix-1)+(int)iy*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
							Otwarta.push_back(KwadratVec[((int)ix-1)+(int)iy*mnoznik]);
						}
					}
				}
			}

			if(Otwarta.empty() == false)
			{
				while(Otwarta.empty() == false)
				{
					for(int otwarte =  0;  otwarte < Otwarta.size(); otwarte++)
					{
						if(Otwarta[otwarte].funkcheu < 100000)
						{
							for(int sprawdzzamk = 0; sprawdzzamk < Zamknieta.size(); sprawdzzamk++)
							{

								if(Otwarta.size() > otwarte)
								{
									if(Otwarta[otwarte].GetKwadratPosX() ==	Zamknieta[sprawdzzamk].GetKwadratPosX()
										&& Otwarta[otwarte].GetKwadratPosY() ==	Zamknieta[sprawdzzamk].GetKwadratPosY())
									{
										Otwarta.erase(Otwarta.begin()+otwarte);
										sprawdzzamk = -1;
										if(Otwarta.size() <= otwarte)
										{
											otwarte--;
										}
										if(Otwarta.size() <= 0)
										{
											return 1000000;
										}
									}
								}
							}
							if(Otwarta.size() <= 0)
							{
								return 1000000;
							}
							Enemies::IstotaSciezka(
								px,
								py,
								Otwarta[otwarte].GetKwadratPosX(),
								Otwarta[otwarte].GetKwadratPosY(),
								KwadratVec,
								sizes_x,
								sizes_y,
								Otwarta[otwarte].ParentKwadrat
								); // vektor kwadrat - nawrót
							if(koniec == NORTH || koniec == SOUTH || koniec == WEST || koniec == EAST)
							{
								if(iy - Zamknieta.front().GetKwadratPosY() == 0)
								{

								}
								else if(iy - Zamknieta.front().GetKwadratPosY() == 1)
								{
									sciezka.push_back(NORTH);
								}
								else if(iy- Zamknieta.front().GetKwadratPosY() == -1)
								{
									sciezka.push_back(SOUTH);
								}

								if(ix - Zamknieta.front().GetKwadratPosX() == 0)
								{

								}
								else if(ix - Zamknieta.front().GetKwadratPosX() == 1)
								{
									sciezka.push_back(WEST);
								}
								else if(ix- Zamknieta.front().GetKwadratPosX() == -1)
								{
									sciezka.push_back(EAST);
								}
								//sciezka.push_back(koniec);
								return koniec;
							}
						}
					}
				}
				return 1000000;
			}
		}
		//Enemies na miejscu gracza ale powinno byc od -1 do -4 a nizeli -5
		else
		{
			return koniec;
		}
	}
}
//////////////////////////////////////////////V funkcja dla wierzcho³ków z Parentem (rodzic) V /////////////////////////////////

int Enemies::IstotaSciezka(int px, int py, int ix, int iy,
	std::vector<Tiles> KwadratVec, int sizes_x, int sizes_y,
	Tiles* ParentKwadrat) // vektor kwadrat
{
	if(koniec != NORTH && koniec != SOUTH && koniec != WEST && koniec != EAST)
	{
		//czy istota nie na miesjcu
		if(ix != px || iy != py)
		{
			int odlegloscX, odlegloscY;

			static float mnoznik = sqrt((float)KwadratVec.size());

			//std::vector<Tiles> Otwarta;
			std::vector<std::pair<int,int>> VecOpenMapa;
			//	std::vector<std::pair<int,int>> parVecOpenMapa;
			std::map<int,int> OpenMapa;	//Klucz 1 - gora, 2 prawo, 3 dol, 4 lewo, Druga wartosc - funkcja heurystyczna

			//	Otwarta.push_back(KwadratVec[ix+iy*mnoznik]); // indeks kwadratu
			odlegloscX = abs(ix - px);	odlegloscY = abs(iy - py);

			float funkcheu[5], funkcmin;
			funkcheu[0] =  odlegloscX + odlegloscY;
			funkcheu[1] =  odlegloscX + odlegloscY;
			funkcheu[2] =  odlegloscX + odlegloscY;
			funkcheu[3] =  odlegloscX + odlegloscY;
			funkcheu[4] =  odlegloscX + odlegloscY;
			funkcmin = funkcheu[0];

			Otwarta.erase(Otwarta.begin());
			Zamknieta.push_back(KwadratVec[((int)ix+((int)iy)*mnoznik)]);
			// funkcheu i openmapa indeksy sa +1 (west 3; 4) itd
			//Gora
			if(iy-1 >= 0)
			{
				if((((int)ix+((int)iy-1)*mnoznik)) > 0)
				{
					if(KwadratVec[((int)ix+((int)iy-1)*mnoznik)].GetCollidable() == true)	//N
					{
						funkcheu[3] = 100000;
						OpenMapa[3] = funkcheu[3];
						Zamknieta.push_back(KwadratVec[((int)ix+((int)iy-1)*mnoznik)]);
					}	// zabezpieczenie nie moze byc mniejsze od rzeczywistej funkcmin
					else
					{
						odlegloscX = abs(ix - px);	odlegloscY = abs(iy-1 - py);
						funkcheu[3] =  odlegloscX + odlegloscY;
						KwadratVec[((int)ix+((int)iy-1)*mnoznik)].funkcheu =  funkcheu[3];
						OpenMapa[3] = funkcheu[3];
					}
				}
			}
			//Prawo
			if(ix+1 <=sizes_x) // sizes_x / sizes_x+1
			{
				if((((int)ix+1)+(int)iy*mnoznik) <	KwadratVec.size())
				{
					if(KwadratVec[((int)ix+1)+(int)iy*mnoznik].GetCollidable() == true)	//E
					{
						funkcheu[2] = 100000;
						OpenMapa[2] = funkcheu[2];
						Zamknieta.push_back(KwadratVec[((int)ix+1)+(int)iy*mnoznik]);
					}
					else
					{
						odlegloscX = abs(ix+1 - px);	odlegloscY = abs(iy - py);
						funkcheu[2] = odlegloscX + odlegloscY;
						KwadratVec[((int)ix+1)+(int)iy*mnoznik].funkcheu =  funkcheu[2];
						OpenMapa[2] = funkcheu[2];
					}
				}
			}
			//Dol
			if(iy+1 <= sizes_y) // sizes_y / sizes_y+1
			{
				if((int)ix+(((int)iy+1)*mnoznik) <	KwadratVec.size())
				{
					if(KwadratVec[(int)ix+(((int)iy+1)*mnoznik)].GetCollidable() == true)	//S
					{
						funkcheu[1] = 100000;
						OpenMapa[1] = funkcheu[1];
						Zamknieta.push_back(KwadratVec[(int)ix+(((int)iy+1)*mnoznik)]);
					}
					else
					{
						odlegloscX = abs(ix - px);	odlegloscY = abs(iy+1 - py);
						funkcheu[1] = odlegloscX + odlegloscY;
						KwadratVec[(int)ix+((int)iy+1)*mnoznik].funkcheu =  funkcheu[1];
						OpenMapa[1] = funkcheu[1];
					}
				}
			}
			//Lewo
			if(ix-1 >=0)
			{
				if((((int)ix-1)+(int)iy*mnoznik) < KwadratVec.size())
				{
					if(KwadratVec[((int)ix-1)+(int)iy*mnoznik].GetCollidable() == true)	//W
					{
						funkcheu[4] = 100000;
						OpenMapa[4] = funkcheu[4];
						Zamknieta.push_back(KwadratVec[((int)ix-1)+(int)iy*mnoznik]);
					}
					else
					{
						{
							odlegloscX = abs(ix-1 - px);	odlegloscY = abs(iy - py);
							funkcheu[4] = odlegloscX + odlegloscY;
							KwadratVec[((int)ix-1)+(int)iy*mnoznik].funkcheu =  funkcheu[4];
							OpenMapa[4] = funkcheu[4];
						}
					}
				}
			}

			//Dodajemy do wektora kierunki z ich heurystyka

			for (auto iterator = OpenMapa.begin(); iterator != OpenMapa.end(); ++iterator )
			{
				VecOpenMapa.push_back(*iterator);
				//	parVecOpenMapa.push_back(*iterator);	//dodajemy do kontenera od dziecka
			}

			//sortujemy oba
			std::sort(VecOpenMapa.begin(),VecOpenMapa.end(),
				[](const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) // [] - lambda
			{
				return lhs.second < rhs.second;  // zamiane pierwszej kolumny indeksu na drug¹ - f. heur w celu sortowania wg. heurystyki
			} );


			if(VecOpenMapa.size() >= 1) // ilosc kierunkow do wyboru
			{
				if(VecOpenMapa[0].second == 100000)
				{
				}
				else if (VecOpenMapa[0].second != 100000)
				{
					// Czy vec mapa zgadza sie z kluczem
					if(VecOpenMapa[0].first == 1) // south
					{
						if(VecOpenMapa[0].second == 0)
						{
							koniec = SOUTH;
							sciezka.push_back(SOUTH);
							return SOUTH;
						}
						if((int)ix+(((int)iy+1)*mnoznik) <	KwadratVec.size())
						{
							for(int sprawdzzamk = 0; sprawdzzamk < Zamknieta.size(); sprawdzzamk++)
							{
								if(KwadratVec[(int)ix+((int)iy+1)*mnoznik].GetKwadratPosX() == Zamknieta[sprawdzzamk].GetKwadratPosX()
									&& KwadratVec[(int)ix+((int)iy+1)*mnoznik].GetKwadratPosY() == Zamknieta[sprawdzzamk].GetKwadratPosY())
								{
									break;
								}
								if(sprawdzzamk == Zamknieta.size()-1)
								{

									KwadratVec[(int)ix+((int)iy+1)*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
									Otwarta.push_back(KwadratVec[(int)ix+((int)iy+1)*mnoznik]);
								}
							}
						}
					}
					if(VecOpenMapa[0].first == 2) // east
					{
						if(VecOpenMapa[0].second == 0)
						{
							koniec = EAST;
							sciezka.push_back(EAST);
							return EAST;
						}

						if((((int)ix+1)+(int)iy*mnoznik) <	KwadratVec.size())
						{
							for(int sprawdzzamk = 0; sprawdzzamk < Zamknieta.size(); sprawdzzamk++)
							{
								if(KwadratVec[((int)ix+1)+(int)iy*mnoznik].GetKwadratPosX() == Zamknieta[sprawdzzamk].GetKwadratPosX()
									&& KwadratVec[((int)ix+1)+(int)iy*mnoznik].GetKwadratPosY() == Zamknieta[sprawdzzamk].GetKwadratPosY())
								{
									break;
								}
								if(sprawdzzamk == Zamknieta.size()-1)
								{

									KwadratVec[((int)ix+1)+(int)iy*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
									Otwarta.push_back(KwadratVec[((int)ix+1)+(int)iy*mnoznik]);
								}
							}
						}
					}
					if(VecOpenMapa[0].first == 3) // north
					{
						if(VecOpenMapa[0].second == 0)
						{
							koniec = NORTH;
							sciezka.push_back(NORTH);
							return NORTH;
						}

						if((((int)ix+((int)iy-1)*mnoznik)) > 0)
						{
							for(int sprawdzzamk = 0; sprawdzzamk < Zamknieta.size(); sprawdzzamk++)
							{
								if(KwadratVec[(int)ix+((int)iy-1)*mnoznik].GetKwadratPosX() == Zamknieta[sprawdzzamk].GetKwadratPosX()
									&& KwadratVec[(int)ix+((int)iy-1)*mnoznik].GetKwadratPosY() == Zamknieta[sprawdzzamk].GetKwadratPosY())
								{
									break;
								}
								if(sprawdzzamk == Zamknieta.size()-1)
								{

									KwadratVec[(int)ix+((int)iy-1)*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
									Otwarta.push_back(KwadratVec[(int)ix+((int)iy-1)*mnoznik]);
								}
							}
						}

					}
					if(VecOpenMapa[0].first == 4) // west
					{
						if(VecOpenMapa[0].second == 0)
						{
							koniec = WEST;
							sciezka.push_back(WEST);
							return WEST;
						}

						if((((int)ix-1)+(int)iy*mnoznik) < KwadratVec.size())
						{
							for(int sprawdzzamk = 0; sprawdzzamk < Zamknieta.size(); sprawdzzamk++)
							{
								if(KwadratVec[((int)ix-1)+(int)iy*mnoznik].GetKwadratPosX() == Zamknieta[sprawdzzamk].GetKwadratPosX()
									&& KwadratVec[((int)ix-1)+(int)iy*mnoznik].GetKwadratPosY() == Zamknieta[sprawdzzamk].GetKwadratPosY())
								{
									break;
								}
								if(sprawdzzamk == Zamknieta.size()-1)
								{

									KwadratVec[((int)ix-1)+(int)iy*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
									Otwarta.push_back(KwadratVec[((int)ix-1)+(int)iy*mnoznik]);
								}
							}
						}
					}
				}
			}
			if(VecOpenMapa.size() >= 2)
			{

				if(VecOpenMapa[1].second == 100000)
				{
				}
				else if(VecOpenMapa[1].second != 100000)
				{
					if(VecOpenMapa[1].first == 1)
					{
						if(VecOpenMapa[1].second == 0)
						{
							koniec = SOUTH;
							sciezka.push_back(SOUTH);
							return SOUTH;
						}
						if((int)ix+(((int)iy+1)*mnoznik) <	KwadratVec.size())
						{
							for(int sprawdzzamk = 0; sprawdzzamk < Zamknieta.size(); sprawdzzamk++)
							{
								if(KwadratVec[(int)ix+((int)iy+1)*mnoznik].GetKwadratPosX() == Zamknieta[sprawdzzamk].GetKwadratPosX()
									&& KwadratVec[(int)ix+((int)iy+1)*mnoznik].GetKwadratPosY() == Zamknieta[sprawdzzamk].GetKwadratPosY())
								{
									break;
								}
								if(sprawdzzamk == Zamknieta.size()-1)
								{

									KwadratVec[(int)ix+((int)iy+1)*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
									Otwarta.push_back(KwadratVec[(int)ix+((int)iy+1)*mnoznik]);
								}
							}
						}
					}
					if(VecOpenMapa[1].first == 2)
					{
						if(VecOpenMapa[1].second == 0)
						{
							koniec = EAST;
							sciezka.push_back(EAST);
							return EAST;
						}

						if((((int)ix+1)+(int)iy*mnoznik) <	KwadratVec.size())
						{
							for(int sprawdzzamk = 0; sprawdzzamk < Zamknieta.size(); sprawdzzamk++)
							{
								if(KwadratVec[((int)ix+1)+(int)iy*mnoznik].GetKwadratPosX() == Zamknieta[sprawdzzamk].GetKwadratPosX()
									&& KwadratVec[((int)ix+1)+(int)iy*mnoznik].GetKwadratPosY() == Zamknieta[sprawdzzamk].GetKwadratPosY())
								{
									break;
								}
								if(sprawdzzamk == Zamknieta.size()-1)
								{

									KwadratVec[((int)ix+1)+(int)iy*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
									Otwarta.push_back(KwadratVec[((int)ix+1)+(int)iy*mnoznik]);
								}
							}
						}
					}
					if(VecOpenMapa[1].first == 3)
					{
						if(VecOpenMapa[1].second == 0)
						{
							koniec = NORTH;
							sciezka.push_back(NORTH);
							return NORTH;
						}

						if((((int)ix+((int)iy-1)*mnoznik)) > 0)
						{
							for(int sprawdzzamk = 0; sprawdzzamk < Zamknieta.size(); sprawdzzamk++)
							{
								if(KwadratVec[(int)ix+((int)iy-1)*mnoznik].GetKwadratPosX() == Zamknieta[sprawdzzamk].GetKwadratPosX()
									&& KwadratVec[(int)ix+((int)iy-1)*mnoznik].GetKwadratPosY() == Zamknieta[sprawdzzamk].GetKwadratPosY())
								{
									break;
								}
								if(sprawdzzamk == Zamknieta.size()-1)
								{

									KwadratVec[(int)ix+((int)iy-1)*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
									Otwarta.push_back(KwadratVec[(int)ix+((int)iy-1)*mnoznik]);
								}
							}
						}

					}
					if(VecOpenMapa[1].first == 4)
					{
						if(VecOpenMapa[1].second == 0)
						{
							koniec = WEST;
							sciezka.push_back(WEST);
							return WEST;
						}

						if((((int)ix-1)+(int)iy*mnoznik) < KwadratVec.size())
						{
							for(int sprawdzzamk = 0; sprawdzzamk < Zamknieta.size(); sprawdzzamk++)
							{
								if(KwadratVec[((int)ix-1)+(int)iy*mnoznik].GetKwadratPosX() == Zamknieta[sprawdzzamk].GetKwadratPosX()
									&& KwadratVec[((int)ix-1)+(int)iy*mnoznik].GetKwadratPosY() == Zamknieta[sprawdzzamk].GetKwadratPosY())
								{
									break;
								}
								if(sprawdzzamk == Zamknieta.size()-1)
								{

									KwadratVec[((int)ix-1)+(int)iy*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
									Otwarta.push_back(KwadratVec[((int)ix-1)+(int)iy*mnoznik]);
								}
							}
						}
					}
				}
			}

			if(VecOpenMapa.size() >= 3)
			{
				if(VecOpenMapa[2].second == 100000) // zabezpieczenie
				{
				}
				else if(VecOpenMapa[2].second != 100000)
				{
					if(VecOpenMapa[2].first == 1) // czy kierunek north w 1-szej kolumnie mapy, indeksu 2-wego
					{
						if(VecOpenMapa[2].second == 0)
						{
							koniec = SOUTH;
							sciezka.push_back(SOUTH);
							return SOUTH;
						}
						if((int)ix+(((int)iy+1)*mnoznik) <	KwadratVec.size())
						{
							for(int sprawdzzamk = 0; sprawdzzamk < Zamknieta.size(); sprawdzzamk++)
							{
								if(KwadratVec[(int)ix+((int)iy+1)*mnoznik].GetKwadratPosX() == Zamknieta[sprawdzzamk].GetKwadratPosX()
									&& KwadratVec[(int)ix+((int)iy+1)*mnoznik].GetKwadratPosY() == Zamknieta[sprawdzzamk].GetKwadratPosY())
								{
									break;
								}
								if(sprawdzzamk == Zamknieta.size()-1)
								{

									KwadratVec[(int)ix+((int)iy+1)*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
									Otwarta.push_back(KwadratVec[(int)ix+((int)iy+1)*mnoznik]);
								}
							}
						}
					}
					if(VecOpenMapa[2].first == 2)
					{
						if(VecOpenMapa[2].second == 0)
						{
							koniec = EAST;
							sciezka.push_back(EAST);
							return EAST;
						}
						if((((int)ix+1)+(int)iy*mnoznik) <	KwadratVec.size())
						{
							for(int sprawdzzamk = 0; sprawdzzamk < Zamknieta.size(); sprawdzzamk++)
							{
								if(KwadratVec[((int)ix+1)+(int)iy*mnoznik].GetKwadratPosX() == Zamknieta[sprawdzzamk].GetKwadratPosX()
									&& KwadratVec[((int)ix+1)+(int)iy*mnoznik].GetKwadratPosY() == Zamknieta[sprawdzzamk].GetKwadratPosY())
								{
									break;
								}
								if(sprawdzzamk == Zamknieta.size()-1)
								{

									KwadratVec[((int)ix+1)+(int)iy*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
									Otwarta.push_back(KwadratVec[((int)ix+1)+(int)iy*mnoznik]);
								}
							}
						}
					}
					if(VecOpenMapa[2].first == 3)
					{
						if(VecOpenMapa[2].second == 0)
						{
							koniec = NORTH;
							sciezka.push_back(NORTH);
							return NORTH;
						}
						if((((int)ix+((int)iy-1)*mnoznik)) > 0)
						{
							for(int sprawdzzamk = 0; sprawdzzamk < Zamknieta.size(); sprawdzzamk++)
							{
								if(KwadratVec[(int)ix+((int)iy-1)*mnoznik].GetKwadratPosX() == Zamknieta[sprawdzzamk].GetKwadratPosX()
									&& KwadratVec[(int)ix+((int)iy-1)*mnoznik].GetKwadratPosY() == Zamknieta[sprawdzzamk].GetKwadratPosY())
								{
									break;
								}
								if(sprawdzzamk == Zamknieta.size()-1)
								{

									KwadratVec[(int)ix+((int)iy-1)*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
									Otwarta.push_back(KwadratVec[(int)ix+((int)iy-1)*mnoznik]);
								}
							}
						}

					}
					if(VecOpenMapa[2].first == 4)
					{
						if(VecOpenMapa[2].second == 0)
						{
							koniec = WEST;
							sciezka.push_back(WEST);
							return WEST;
						}

						if((((int)ix-1)+(int)iy*mnoznik) < KwadratVec.size())
						{
							for(int sprawdzzamk = 0; sprawdzzamk < Zamknieta.size(); sprawdzzamk++)
							{
								if(KwadratVec[((int)ix-1)+(int)iy*mnoznik].GetKwadratPosX() == Zamknieta[sprawdzzamk].GetKwadratPosX()
									&& KwadratVec[((int)ix-1)+(int)iy*mnoznik].GetKwadratPosY() == Zamknieta[sprawdzzamk].GetKwadratPosY())
								{
									break;
								}
								if(sprawdzzamk == Zamknieta.size()-1)
								{

									KwadratVec[((int)ix-1)+(int)iy*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
									Otwarta.push_back(KwadratVec[((int)ix-1)+(int)iy*mnoznik]);
								}
							}
						}
					}
				}
			}

			if(VecOpenMapa.size() >= 4)
			{
				if(VecOpenMapa[3].second == 100000)
				{
				}
				else if (VecOpenMapa[3].second != 100000)
				{
					if(VecOpenMapa[3].first == 1)
					{
						if(VecOpenMapa[3].second == 0)
						{
							koniec = SOUTH;
							sciezka.push_back(SOUTH);
							return SOUTH;
						}
						if((int)ix+(((int)iy+1)*mnoznik) <	KwadratVec.size())
						{
							for(int sprawdzzamk = 0; sprawdzzamk < Zamknieta.size(); sprawdzzamk++)
							{
								if(KwadratVec[(int)ix+((int)iy+1)*mnoznik].GetKwadratPosX() == Zamknieta[sprawdzzamk].GetKwadratPosX()
									&& KwadratVec[((int)ix+(int)iy+1)*mnoznik].GetKwadratPosY() == Zamknieta[sprawdzzamk].GetKwadratPosY())
								{
									break;
								}
								if(sprawdzzamk == Zamknieta.size()-1)
								{

									KwadratVec[(int)ix+((int)iy+1)*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
									Otwarta.push_back(KwadratVec[(int)ix+((int)iy+1)*mnoznik]);
								}
							}
						}
					}
					if(VecOpenMapa[3].first == 2)
					{
						if(VecOpenMapa[3].second == 0)
						{
							koniec = EAST;
							sciezka.push_back(EAST);
							return EAST;
						}
						if((((int)ix+1)+(int)iy*mnoznik) <	KwadratVec.size())
						{
							for(int sprawdzzamk = 0; sprawdzzamk < Zamknieta.size(); sprawdzzamk++)
							{
								if(KwadratVec[((int)ix+1)+(int)iy*mnoznik].GetKwadratPosX() == Zamknieta[sprawdzzamk].GetKwadratPosX()
									&& KwadratVec[((int)ix+1)+(int)iy*mnoznik].GetKwadratPosY() == Zamknieta[sprawdzzamk].GetKwadratPosY())
								{
									break;
								}
								if(sprawdzzamk == Zamknieta.size()-1)
								{

									KwadratVec[((int)ix+1)+(int)iy*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
									Otwarta.push_back(KwadratVec[((int)ix+1)+(int)iy*mnoznik]);
								}
							}
						}
					}
					if(VecOpenMapa[3].first == 3)
					{
						if(VecOpenMapa[3].second == 0)
						{
							koniec = NORTH;
							sciezka.push_back(NORTH);
							return NORTH;
						}
						if((((int)ix+((int)iy-1)*mnoznik)) > 0)
						{
							for(int sprawdzzamk = 0; sprawdzzamk < Zamknieta.size(); sprawdzzamk++)
							{
								if(KwadratVec[(int)ix+((int)iy-1)*mnoznik].GetKwadratPosX() == Zamknieta[sprawdzzamk].GetKwadratPosX()
									&& KwadratVec[(int)ix+((int)iy-1)*mnoznik].GetKwadratPosY() == Zamknieta[sprawdzzamk].GetKwadratPosY())
								{
									break;
								}
								if(sprawdzzamk == Zamknieta.size()-1)
								{

									KwadratVec[(int)ix+((int)iy-1)*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
									Otwarta.push_back(KwadratVec[(int)ix+((int)iy-1)*mnoznik]);
								}
							}
						}
					}
					if(VecOpenMapa[3].first == 4)
					{
						if(VecOpenMapa[3].second == 0)
						{
							koniec = WEST;
							sciezka.push_back(WEST);
							return WEST;
						}

						if((((int)ix-1)+(int)iy*mnoznik) < KwadratVec.size())
						{
							for(int sprawdzzamk = 0; sprawdzzamk < Zamknieta.size(); sprawdzzamk++)
							{
								if(KwadratVec[((int)ix-1)+(int)iy*mnoznik].GetKwadratPosX() == Zamknieta[sprawdzzamk].GetKwadratPosX()
									&& KwadratVec[((int)ix-1)+(int)iy*mnoznik].GetKwadratPosY() == Zamknieta[sprawdzzamk].GetKwadratPosY())
								{
									break;
								}
								if(sprawdzzamk == Zamknieta.size()-1)
								{

									KwadratVec[((int)ix-1)+(int)iy*mnoznik].ParentKwadrat = &KwadratVec[((int)ix+((int)iy)*mnoznik)];
									Otwarta.push_back(KwadratVec[((int)ix-1)+(int)iy*mnoznik]);
								}
							}
						}
					}
				}
			}


			std::sort(Otwarta.begin(), Otwarta.end(), Komparator );
			Otwarta.erase(std::unique(Otwarta.begin(), Otwarta.end()), Otwarta.end());
			if(Otwarta.empty() == false)
			{
				while(Otwarta.empty() == false)
				{
					for(int otwarte =  0;  otwarte < Otwarta.size(); otwarte++)
					{
						if(Otwarta[otwarte].funkcheu < 100000)
						{
							for(int sprawdzzamk = 0; sprawdzzamk < Zamknieta.size(); sprawdzzamk++)
							{
								if(Otwarta.size() > otwarte)
								{
									if(Otwarta[otwarte].GetKwadratPosX() ==	Zamknieta[sprawdzzamk].GetKwadratPosX()
										&& Otwarta[otwarte].GetKwadratPosY() ==	Zamknieta[sprawdzzamk].GetKwadratPosY())
									{
										Otwarta.erase(Otwarta.begin());
										sprawdzzamk = -1;
										if(Otwarta.size() <= otwarte)
										{
											otwarte--;
										}
										if(Otwarta.size() <= 0)
										{
											return 1000000;
										}
									}
								}
							}
							if(Otwarta.size() <= 0)
							{
								return 1000000;
							}
							if(Otwarta.size() > otwarte)
							{
								Enemies::IstotaSciezka(
									px,
									py,
									Otwarta[otwarte].GetKwadratPosX(),
									Otwarta[otwarte].GetKwadratPosY(),
									KwadratVec,
									sizes_x,
									sizes_y,
									Otwarta[otwarte].ParentKwadrat
									);
							}
							if(koniec == NORTH || koniec == SOUTH || koniec == WEST || koniec == EAST)
							{
								if(koniec != 123456789)
								{
								while(KwadratVec[(int)ix+(int)iy*mnoznik].ParentKwadrat != nullptr)
								{
									if(KwadratVec[(int)ix+(int)iy*mnoznik].ParentKwadrat->ParentKwadrat != nullptr)
									{
										if(KwadratVec[(int)ix+(int)iy*mnoznik].ParentKwadrat->ParentKwadrat->GetKwadratPosY() -  KwadratVec[(int)ix+(int)iy*mnoznik].ParentKwadrat->GetKwadratPosY() == 0)
										{
										}
										else if(KwadratVec[(int)ix+(int)iy*mnoznik].ParentKwadrat->ParentKwadrat->GetKwadratPosY() -  KwadratVec[(int)ix+(int)iy*mnoznik].ParentKwadrat->GetKwadratPosY() == 1)
										{
											sciezka.push_back(NORTH);
										}
										else if(KwadratVec[(int)ix+(int)iy*mnoznik].ParentKwadrat->ParentKwadrat->GetKwadratPosY() -  KwadratVec[(int)ix+(int)iy*mnoznik].ParentKwadrat->GetKwadratPosY() == -1)
										{
											sciezka.push_back(SOUTH);
										}

										if(KwadratVec[(int)ix+(int)iy*mnoznik].ParentKwadrat->ParentKwadrat->GetKwadratPosX() -  KwadratVec[(int)ix+(int)iy*mnoznik].ParentKwadrat->GetKwadratPosX() == 0)
										{
										}
										else if(KwadratVec[(int)ix+(int)iy*mnoznik].ParentKwadrat->ParentKwadrat->GetKwadratPosX() -  KwadratVec[(int)ix+(int)iy*mnoznik].ParentKwadrat->GetKwadratPosX() == 1)
										{
											sciezka.push_back(WEST);
										}
										else if(KwadratVec[(int)ix+(int)iy*mnoznik].ParentKwadrat->ParentKwadrat->GetKwadratPosX() - KwadratVec[(int)ix+(int)iy*mnoznik].ParentKwadrat->GetKwadratPosX() == -1)
										{
											sciezka.push_back(EAST);
										}
									}
									KwadratVec[(int)ix+(int)iy*mnoznik].ParentKwadrat = KwadratVec[(int)ix+(int)iy*mnoznik].ParentKwadrat->ParentKwadrat;

								}
								koniec = 123456789;
								}

									return koniec; // 0 3 3 3 2 2 2 2 3

							}
						}
					}
				}
				return 1000000;
			}
		}
		//Enemies na miejscu gracza ale powinno byc od -1 do -4 a nizeli -5
		else
		{
			return koniec;
		}
	}
}


void Enemies::SetShapePosition(float x, float y) // int float
{
	Gmonster.setPosition(x,y);
}

void Enemies::SetIstotaRot(Player *postac)
{

	float deltay = postac->GraczShape.getPosition().y - Gmonster.getPosition().y;
	float deltax = postac->GraczShape.getPosition().x - Gmonster.getPosition().x;

	Gmonster.setRotation(atan2(deltay,deltax)*180/M_PI+90);
}
