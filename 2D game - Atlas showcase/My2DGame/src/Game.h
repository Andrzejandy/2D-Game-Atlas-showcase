#ifndef GAME_H
#define GAME_H
#define _WIN32_WINNT 0x0500
#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <ctime>
#include <windows.h>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Player.h"
#include "Enumeratory.h"
#include "Monster.h"
#include "Animation.h"
#include "Camera.h"
class Game
{
    public:
        Game(sf::RenderWindow &g_window);
        ~Game();

        bool InitWindow(void);
        void BindWindow(sf::RenderWindow &game_render_window);
        bool LoadMenuFont();
        void MenuCreateText();
        void MenuRuntime();
        void CreateMenu(void);
        void HandleInput(void);
        void HandleLogic(void);
        void HandleRender(void);

        sf::RenderWindow &game_render_window;

        void SetGameStatus(int i);
        int GetGameStatus();
        void SetupRenderWindow(int height, int width);

    protected:

    private:
        //sf::Font MenuFont;
    	//sf::Text MenuText4,MenuText3, MenuText2, MenuText1, MenuText;
    	Player player;
    	Monster monster;
    	Camera camera;
        int Game_Status;

};

#endif // GAME_H
