#include "Player.h"
#define M_PI 3.141/*59265358979323846*/

Player::Player() : px(1),py(1)
{
	hp = 100;
	px = 1.5;
	py = 1.5;
	MovementSpeedX = 0;
	MovementSpeedY = 0;
	if(!GraczTekstura.loadFromFile("Resources//sprites//postacaa.png"))
	GraczTekstura.loadFromFile("postacaa.png");
	GraczShape.setTexture(&GraczTekstura);
}

Player::~Player()
{
    //dtor
}

int Player::GetGraczHP()
{
	return hp;
}

float Player::GetGraczPosX() // int/float
{
	return px;
}

float Player::GetGraczPosY() // int/float
{
	return py;
}

int Player::GetGraczNorthPos(int distance)
{
	return py-distance;
}

int Player::GetGraczSouthPos(int distance)
{
	return py+distance;
}

int Player::GetGraczEastPos(int distance)
{
	return px+distance;
}


int Player::GetGraczWestPos(int distance)
{
	return px-distance;
}

void Player::SetShapeRes(float resolution) //int/float
{
	float	RectSizeX = sf::VideoMode::getDesktopMode().width / resolution;
	float	RectSizeY = sf::VideoMode::getDesktopMode().height / resolution;
	GraczShape.setSize(sf::Vector2f (RectSizeX/1.4, RectSizeY));
	GraczShape.setOrigin(GraczShape.getSize().x/2,GraczShape.getSize().y/2);
	GraczShape.setTextureRect(sf::IntRect(0,0,64,64));

}

void Player::SetGraczHP(int HP)
{
	hp = HP;
}

void Player::SetGraczPos(float posx, float posy) // int/float
{
	px = posx;
	py = posy;
}

void Player::SetShapePosition(float x, float y) // int/float
{
	GraczShape.setPosition(x,y);
}

//Rot
void Player::SetSpriteRot(float rot)
{
	GraczSpriteRot = rot;

}

void Player::RotateSprite(sf::RenderWindow &refOkno)
{
	sf::Vector2i myszrot = sf::Mouse::getPosition(refOkno);
	float deltax = GraczShape.getPosition().x - myszrot.x;
	float deltay = GraczShape.getPosition().y - myszrot.y;
	GraczShape.setRotation(-90);
	GraczShape.rotate(atan2(deltay,deltax)*180/M_PI);
}

float Player::GetGraczRot(float GraczSpriteRot)
{
	return GraczSpriteRot;
}

void Player::UpdateSpeed(float dlugoscklatki, float czas)
{
	float momentum = 0.000008f*dlugoscklatki;
	int animacjax=128;
	if(MovementSpeedX != 0 || MovementSpeedY != 0)
	{
		animacjax+= 64;
		if(ZegarGraczAnimacja.getElapsedTime().asSeconds() >0.2f)
		{

			if (GraczShape.getTextureRect().left == 192)
				GraczShape.setTextureRect(sf::IntRect(256,0,64,64));
			else if(GraczShape.getTextureRect().left == 256)
			{
				GraczShape.setTextureRect(sf::IntRect(64,0,64,64));
			}
			else if(GraczShape.getTextureRect().left == 64)
			{
				GraczShape.setTextureRect(sf::IntRect(0,0,64,64));
			}
			  else
				GraczShape.setTextureRect(sf::IntRect(animacjax,0,64,64));
		}
		if(ZegarGraczAnimacja.getElapsedTime().asSeconds() > 0.2f)
		{
			ZegarGraczAnimacja.restart();
		}

	}
	else if(MovementSpeedX == 0 && MovementSpeedY == 0 && ZegarGraczAnimacja.getElapsedTime().asSeconds() >0.5f)
	{
		GraczShape.setTextureRect(sf::IntRect(128,0,64,64));
	ZegarGraczAnimacja.restart();
	}

	if(MovementSpeedX < -0.00005f) //.00005f
	{
		MovementSpeedX += momentum;
	}
	if(MovementSpeedY < -0.00005f)
	{
		MovementSpeedY += momentum;
	}
	if(MovementSpeedX > 0.00005f)
	{
		MovementSpeedX -= momentum;
	}
	if(MovementSpeedY > 0.00005f)
	{
		MovementSpeedY -= momentum;
	}

	if(MovementSpeedX > -0.00005f && MovementSpeedX < 0.00005f)
	{
		MovementSpeedX = 0.0f;
	}
	if(MovementSpeedY > -0.00005f && MovementSpeedY < 0.00005f)
	{
		MovementSpeedY = 0.0f;
	}

	if(ZegarGraczAnimacja.getElapsedTime().asSeconds() > 0.2f)
	{

	}

	px = px + MovementSpeedX;
	py = py + MovementSpeedY;
}
