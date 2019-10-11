#include "Game.h"
#define DegToRad 0.0174532925

clock_t t;
clock_t tlast;
sf::Clock zegar2;

static	sf::Time timeFPS; // fps
static sf::Clock clockFPS;// fps

// window.mapPixelToCoords(sf::Mouse::getPosition(window));

Game::Game(sf::RenderWindow &g_window) : game_render_window(g_window)
{
    std::cout << "Setting game status..." << std::endl;
    SetGameStatus(game_running);
    std::cout << "Game Staus Set" << std::endl;

    camera.BindView(g_window);
    monster.BindWindow(g_window);
    g_window.setView(camera.cameraView);
    MenuCreateText();
    std::cout << "game class" << std::endl;
}

Game::~Game(void)
{
}
    int Game::GetGameStatus()
    {
        return Game_Status;
    }

	void Game::SetGameStatus(int i)
	{
		switch(i)
		{
		case game_menu:
			{
				Game_Status = game_menu;
				break;
			}
		case game_map_select:
			{
				Game_Status = game_map_select;
				break;
			}
		case game_running:
			{
				Game_Status = game_running;
				break;
			}
		default:
			{
				break;
			}
		}
	}

bool Game::LoadMenuFont()
{
/*
    if(!MenuFont.loadFromFile("resources/arial.ttf"))
	{
	    if(!MenuFont.loadFromFile("arial.ttf"))
        {
            return EXIT_FAILURE;
        }
        else
        {
            return true;
        }

        return false;
    }
    else
    {
        return true;
    }
*/
    return true;
}

void Game::MenuCreateText()
{
    /*
    if(!LoadMenuFont())
    {
        std::cout << "Font arial.ttf couldn't be located in resources/fonts or in .exe folder" << std::endl;
        game_render_window.close();
    }
	int x = game_render_window.getSize().x/2.5 , y = game_render_window.getSize().y/2.5;
	MenuText.setFont(MenuFont);
	MenuText.setFillColor(sf::Color(0,255,0));
	MenuText.setPosition(x,y);
	MenuText.setString("New Game");

	MenuText1.setFont(MenuFont);
	MenuText1.setFillColor(sf::Color(255,255,255));
	MenuText1.setPosition(x,y+50);

	MenuText2.setFont(MenuFont);
	MenuText2.setFillColor(sf::Color(255,255,255));
	MenuText2.setPosition(x,y+100);
	MenuText2.setString(L"Back to game");

	MenuText4.setFont(MenuFont);
	MenuText4.setFillColor(sf::Color(255,255,255));
	MenuText4.setPosition(x,y+150);

	MenuText3.setFont(MenuFont);
	MenuText3.setFillColor(sf::Color(255,255,255));
	MenuText3.setPosition(x,y+200);
	MenuText3.setString(L"Quit");
*/
}

void Game::HandleInput(void)
{
    sf::Event event;
    while(game_render_window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            game_render_window.close();
        }
        if(event.type == sf::Event::KeyPressed)
        {
            if(Game_Status == game_running)
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::R:
                            player.manualFrame = !player.manualFrame;
                            std::cout << player.manualFrame << std::endl;
                        break;

                    case sf::Keyboard::T:
                            player.currentFrame++;
                            if(player.currentFrame>player.maxFramesNow) { player.currentFrame = 1; }
                            std::cout << player.currentFrame << "/" << player.maxFramesNow << std::endl;
                        break;
                    case sf::Keyboard::G:
                            player.currentFrame--;
                            if(player.currentFrame<1) { player.currentFrame = player.maxFramesNow; }
                            std::cout << player.currentFrame << "/" << player.maxFramesNow << std::endl;
                        break;
                    case sf::Keyboard::Y:
                        player.frameData++;
                        std::cout << "frameData: " << player.frameData << std::endl;
                        if(player.frameData>1) { player.frameData = 0; }
                        break;
                    case sf::Keyboard::H:
                        player.frameData--;
                        std::cout << "frameData: " << player.frameData << std::endl;
                        if(player.frameData<0) { player.frameData =1; }
                        break;
                    case sf::Keyboard::U:
                        player.frameIncrementVal+=0.001;
                        std::cout << "Val: " << player.frameIncrementVal << std::endl;
                        if(player.frameIncrementVal<0) { player.frameIncrementVal =1; }
                        break;
                    case sf::Keyboard::J:
                        player.frameIncrementVal-=0.001;
                        std::cout << "Val: " << player.frameIncrementVal << std::endl;
                        if(player.frameIncrementVal<0) { player.frameIncrementVal =1; }
                        break;
                    default:
                        break;
                }
            }
        }
        if(event.type == sf::Event::MouseWheelMoved)
        {
            if(event.mouseWheel.delta > 0)
            {
                float scaleX = player.playerSprite.getScale().x;
                float scaleY = player.playerSprite.getScale().y;
                float log_scaleX = log(scaleX - 5) / log(10);
                camera.ZoomView(1.1);
            }
            else if(event.mouseWheel.delta < 0)
            {
                float scaleX = player.playerSprite.getScale().x;
                float scaleY = player.playerSprite.getScale().y;
                float log_scaleX = log(scaleX - 5) / log(10);
                camera.ZoomView(0.9);
            }
        }
    }
    if(Game_Status == game_menu)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
			game_render_window.close();
        }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			Game_Status = game_running;
		}
    }
    else if(Game_Status == game_running)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            player.Up = true;
        }
        else
        {
            player.Up = false;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            player.playerAngle-=0.05;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            player.Down = true;
        }
        else
        {
            player.Down = false;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            player.playerAngle+=0.05;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            Game_Status = game_menu;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            camera.PanView(0,-1);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            camera.PanView(0,1);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            camera.PanView(-1,0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            camera.PanView(1,0);
        }
        if(event.type == sf::Event::MouseMoved)
        {
            monster.GoToPos(sf::Mouse::getPosition(game_render_window).x,sf::Mouse::getPosition(game_render_window).y);
        }
    }
}

void Game::HandleLogic(void)
{
    player.HandleMovement();
    monster.HandleLogic();
}

void Game::HandleRender(void)
{
    if(Game_Status == game_running)
    {
        game_render_window.clear(sf::Color(0,200,0,255));
        game_render_window.setView(camera.cameraView);
        player.DrawFrame(game_render_window);
       //monster.DrawMonster(game_render_window);
        game_render_window.display();
    }
    else if(Game_Status == game_menu)
    {
        game_render_window.clear();
        CreateMenu();
        game_render_window.display();
    }
}

void Game::CreateMenu(void)
{
    sf::VertexArray VBackground(sf::Quads, 4);
    VBackground[0].color = sf::Color(5,5,5);
    VBackground[1].color = sf::Color(5,5,5);
    VBackground[2].color = sf::Color(100,100,100);
    VBackground[3].color = sf::Color(100,100,100);
    VBackground[0].position = sf::Vector2f(0,0);
    VBackground[1].position = sf::Vector2f(sf::VideoMode::getDesktopMode().width,0);
    VBackground[2].position = sf::Vector2f(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height);
    VBackground[3].position = sf::Vector2f(0,sf::VideoMode::getDesktopMode().height);
    game_render_window.draw(VBackground);
}

int main(int argc, char **argv)
{

    unsigned int WinSizeX=sf::VideoMode::getDesktopMode().width , WinSizeY=sf::VideoMode::getDesktopMode().height;
	float dlugoscklatki = 0.01f;
    sf::RenderWindow window(sf::VideoMode(WinSizeX, WinSizeY), "Game Animation Test, WASD to move, ESC to close, Mouse Wheel to change scale");
    std::cout << "window" << std::endl;
    Game game(window);
    std::cout << "game" << std::endl;
    window.setFramerateLimit(60);
    #ifdef _DEBUG
#else
    HWND hWnd = GetConsoleWindow();
    ShowWindow( hWnd, SW_SHOW );
#endif

    while (window.isOpen())
    {
		clockFPS.restart();
		timeFPS = clockFPS.getElapsedTime();
		dlugoscklatki = timeFPS.asSeconds();

        game.HandleInput();
        game.HandleLogic();
        game.HandleRender();
    }
    return 0;
}
