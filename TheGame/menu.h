#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


class menu
{
public:
	Text mainmenu[3];

	menu(int width, int height);

	void draw(RenderWindow& window);

	void MoveUp();
	void MoveDown();
	void setSelected(int n);

	int pressed() {
		return selected;
	}

	~menu();

private:
	int selected;
	Font font;
};

