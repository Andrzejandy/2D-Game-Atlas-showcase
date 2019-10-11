#include "Monster.h"

Monster::Monster()
{
    std::cout << "monster begin" << std::endl;
    game_render_window = nullptr;
    //ctor
    keepMoving = false;
    monsterMaxSpeed = 1;
    monsterPosX = 40;
    monsterPosY = 70;
    monsterShape.setPointCount(3);
    monsterShape.setRadius(40);
    monsterShape.setOutlineColor(sf::Color(25,25,25));
    monsterShape.setOutlineThickness(5);
    monsterShape.setFillColor(sf::Color(0,125,0));
    monsterShape.setOrigin(40,40);
    //monsterShape.setRotation(-90);
    monsterDeltaX = 0.0;
    monsterDeltaY = 0.0;
    texture.loadFromFile("monster.png");
    monsterSprite.setTexture(texture);
    monsterSprite.setOrigin(texture.getSize().x/2,texture.getSize().y/2);
    monsterSprite.setPosition(monsterPosX,monsterPosY);
    monsterSprite.setScale(1.5,1.5);
    rotAngle = 0.0;
    rotAngle = atan2(monsterDeltaX,monsterDeltaY);

    LinePoint.setPrimitiveType(sf::Lines);
    LinePoint.resize(2);
  //  monsterPosX = 40;
  //  monsterPosY = 70;
  //  monsterSprite.setPosition(monsterPosX,monsterPosY);
  //  monsterSprite.setColor(sf::Color(10,10,10));
  std::cout << "monster class" << std::endl;
}

Monster::~Monster()
{
    //dtor
}

void Monster::BindWindow(sf::RenderWindow &refRenderWindow)
{
    game_render_window = &refRenderWindow;
}

void Monster::DrawMonster(sf::RenderWindow &refRenderWindow)
{
    refRenderWindow.draw(monsterSprite);
    refRenderWindow.draw(LinePoint);
}

void Monster::SetDestination(double monsterDestX, double monsterDestY)
{
    this->monsterDestX = monsterDestX;
    this->monsterDestY = monsterDestY;
}

//  monsterShape.move(std::cos(3.14159265 * angle / 180.f)  * speed  *-1, std::sin(3.14159265 * angle / 180.f) * speed  *-1);
void Monster::GoToPos(double posX, double posY)
{
    sf::Vector2i vPos(posX,posY);
    sf::Vector2f vDest = game_render_window->mapPixelToCoords(vPos);
    monsterDestX = vDest.x;
    monsterDestY = vDest.y;
    keepMoving = true;
    LinePoint[0].position.x = monsterPosX;
    LinePoint[0].position.y = monsterPosY;
    LinePoint[0].color = sf::Color::White;
    LinePoint[1].position.x = posX;
    LinePoint[1].position.y = posY;
    LinePoint[1].color = sf::Color::White;
    rotAngle = (atan2(monsterPosX - monsterDestX, monsterPosY - monsterDestY)*180/3.14)*-1;
  //  std::cout << rotAngle << std::endl;
    double destDeltaX = monsterPosX - monsterDestX;
    double destDeltaY = monsterPosY - monsterDestY;
    double dist = DistanceTwoPoints(monsterPosX, monsterPosY, monsterDestX, monsterDestY);
 //   std::cout << "d: " << dist << std::endl;
}

void Monster::HandleLogic()
{
    /*
      0 1 2 3 4 5 6 x
     0
     1
     2
     3
     4
     5
     6
     y
    */
    double destDeltaX = monsterDestX - monsterPosX;
    double destDeltaY = monsterDestY - monsterPosY;

  //  double destDeltaX = monsterPosX - monsterDestX;
  //  double destDeltaY = monsterPosY - monsterDestY;
    double dist = DistanceTwoPoints(monsterPosX, monsterPosY, monsterDestX, monsterDestY);

    sf::Vector2f delta;
    delta.x = destDeltaX;
    delta.y = destDeltaY;
    sf::Vector2f distancenorm;
    distancenorm.x = delta.x / dist;
    distancenorm.y = delta.y / dist;
   // monsterShape.setPosition(monsterPosX,monsterPosY);
    if(keepMoving == true)
    {
        destDeltaX = monsterDestX - monsterPosX;
        destDeltaY = monsterDestY - monsterPosY;

        dist = DistanceTwoPoints(monsterPosX, monsterPosY, monsterDestX, monsterDestY);
        if(dist>35)
        {
            rotAngle = (atan2(monsterPosY - monsterDestY, monsterPosX - monsterDestX)*180/3.141592654);
            monsterSprite.setRotation(rotAngle-90);
            double velX = sin(monsterSprite.getRotation() * 3.141592654 / 180);//*destDeltaX/100;
            double velY = cos(monsterSprite.getRotation() * 3.141592654 / 180);//*destDeltaY/100;
            monsterPosX += velX+destDeltaX/100;
            monsterPosY -= velY-destDeltaY/100;
            monsterSprite.setPosition(monsterPosX, monsterPosY);
            LinePoint[0].position.x = monsterPosX;
            LinePoint[0].position.y = monsterPosY;
        }
        /*
        if(monsterDestX-1>monsterPosX)    //Go Right
        {
            if(monsterDeltaX<monsterMaxSpeed)
            {
                monsterDeltaX += 0.1;
            }
        }
        if(monsterDestX+1<monsterPosX)   //Go Left
        {
            if(monsterDeltaX-1>-monsterMaxSpeed)
            {
                monsterDeltaX -= 0.1;
            }
        }
        if(monsterDestY+1>monsterPosY)    //Go South
        {
            if(monsterDeltaY<monsterMaxSpeed)
            {
                monsterDeltaY += 0.1;
            }
        }
        if(monsterDestY-1<monsterPosY)   //Go North
        {
            if(monsterDeltaY>-monsterMaxSpeed)
            {
                monsterDeltaY -= 0.1;
            }
        }
        monsterPosX+=monsterDeltaX;
        monsterPosY+=monsterDeltaY;
        monsterShape.setPosition(monsterPosX,monsterPosY);

        if(monsterPosX == monsterDeltaX && monsterPosY == monsterDeltaY)
        {
            keepMoving = false;
        }
        */
    }
}
