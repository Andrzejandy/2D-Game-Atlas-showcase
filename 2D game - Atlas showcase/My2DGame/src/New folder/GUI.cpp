#include "GUI.h"

GUI::GUI(void)
{
	if(!GUIFONT.loadFromFile("Resources//fonts//arial.ttf"))
		GUIFONT.loadFromFile("arial.ttf");
	if(!toolboxtex.loadFromFile("Resources//sprites//przedmiot.png"))
		toolboxtex.loadFromFile("przedmiot.png");
	rectHP.setFillColor(sf::Color::Red);
	rectHP.setPosition(sf::VideoMode::getDesktopMode().width*0.05,sf::VideoMode::getDesktopMode().height*0.92);
	rectTHP.setFont(GUIFONT);
	rectTHP.setPosition(rectHP.getPosition().x, rectHP.getPosition().y - 40);
	rectTHP.setColor(sf::Color(255,255,255));
	toolboxT.setFont(GUIFONT);
	gui1.setPrimitiveType(sf::Quads);
	gui1.resize(4);

	toolboxT.setPosition(sf::VideoMode::getDesktopMode().width*0.155,sf::VideoMode::getDesktopMode().height*0.87);
	toolboxShape.setTexture(&toolboxtex);
	toolboxShape.setPosition(sf::VideoMode::getDesktopMode().width*0.13,sf::VideoMode::getDesktopMode().height*0.89);

	if(!gui1tex.loadFromFile("Resources//sprites//GUI//1.png"))
		gui1tex.loadFromFile("1.png");
}

GUI::~GUI(void)
{
}

void GUI::LoadGUI(int WinX, int WinY)
{
		gui1[0].position = sf::Vector2f(WinX-(WinX*0.79),WinY-(WinY*0.04)); //x350 y400
		gui1[1].position = sf::Vector2f(WinX-(WinX*0.97),WinY-(WinY*0.04));	//x300 y400
		gui1[2].position = sf::Vector2f(WinX-(WinX*0.97),WinY-(WinY*0.14)); //x300 y350
		gui1[3].position = sf::Vector2f(WinX-(WinX*0.79),WinY-(WinY*0.14)); //x350 y350
		gui1[0].texCoords = sf::Vector2f(0,0);
		gui1[1].texCoords = sf::Vector2f(70,0);
		gui1[2].texCoords = sf::Vector2f(70,50);
		gui1[3].texCoords = sf::Vector2f(0,50);

}

void GUI::RenderGUI(sf::RenderWindow &refOkno, int GraczHP, int graczitemysize)
{
	//refOkno.draw(gui1, &gui1tex); //kwadracik szary GUI

	toolboxShape.setSize(sf::Vector2f(sf::VideoMode::getDesktopMode().width*0.08,sf::VideoMode::getDesktopMode().height*0.08));
	rectHP.setSize(sf::Vector2f(GraczHP,20));
	GraczTHP << GraczHP;

	toolboxSS << graczitemysize;
	toolboxT.setString(toolboxSS.str());

	rectTHP.setString(GraczTHP.str());


	refOkno.draw(toolboxT);
	refOkno.draw(toolboxShape);

	refOkno.draw(rectHP); // hp gui
	refOkno.draw(rectTHP); //hp gui
	toolboxSS.str("");
	toolboxSS.clear();
	GraczTHP.str("");
	GraczTHP.clear();
}
