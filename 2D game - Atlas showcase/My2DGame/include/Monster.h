#ifndef MONSTER_H
#define MONSTER_H
#include "MathLib.h"
#include <SFML/Graphics.hpp>
#include <iostream>
class Monster
{
    public:
        Monster();
        ~Monster();

        sf::Sprite monsterSprite;
        sf::CircleShape monsterShape;
        void DrawMonster(sf::RenderWindow &refRenderWindow);
        void SetDestination(double monsterDestX, double monsterDestY);
        void GoToPos(double monsterDestX, double monsterDestY);
        void HandleLogic();
        void BindWindow(sf::RenderWindow &refRenderWindow);

        sf::RenderWindow *game_render_window;
        sf::Texture texture;
        sf::VertexArray LinePoint;

    protected:

    private:
        bool keepMoving;
        float rotAngle;

        double monsterDestX;
        double monsterDestY;

        double monsterPosX;
        double monsterPosY;
        double monsterDeltaX;
        double monsterDeltaY;
        float monsterSpeed;
        float monsterMaxSpeed;

};

#endif // MONSTER_H
