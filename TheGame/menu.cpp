#include "menu.h"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

menu::menu(float width, float height) {
	font.loadFromFile("fuente3.ttf");

	mainmenu[0].setFont(font);
	mainmenu[0].setFillColor(Color{ 255, 255, 255 });
	mainmenu[0].setString("Play");
	mainmenu[0].setCharacterSize(120);
	mainmenu[0].setPosition(Vector2f(400, height / (4)));

	mainmenu[1].setFont(font);
	mainmenu[1].setFillColor(Color::Red);
	mainmenu[1].setString("Instrucciones");
	mainmenu[1].setCharacterSize(120);
	mainmenu[1].setPosition(Vector2f(400, height / (4) + 200));

	mainmenu[2].setFont(font);
	mainmenu[2].setFillColor(Color::Red);
	mainmenu[2].setString("Exit");
	mainmenu[2].setCharacterSize(120);
	mainmenu[2].setPosition(Vector2f(400, height / (4) + 400));

	selected = 0;

}

menu::~menu() {}

void menu::setSelected(int n) {
	selected = n;
}

void menu::draw(RenderWindow& window) {
	for (int i = 0; i < 3; i++)
	{
		window.draw(mainmenu[i]);
	}
}

void menu::MoveDown() {
	if (selected + 1 <= 3) {
		mainmenu[selected].setFillColor(Color::Red);
		selected++;
		if (selected == 3) {
			selected = 0;
		}
		mainmenu[selected].setFillColor(Color{ 255, 255, 255 });
	}
}

void menu::MoveUp() {
	if (selected - 1 >= -1) {
		mainmenu[selected].setFillColor(Color::Red);
		selected--;
		if (selected == -1) {
			selected = 2;
		}
		mainmenu[selected].setFillColor(Color{ 255, 255, 255 });

	}

}