#include <SFML/Graphics.hpp>
#include "menu.h"
using namespace std;
using namespace sf;
int pagenum = 1000;
int main()
{

	RenderWindow window(VideoMode(1920, 1080), "Game");
	menu menu(1920, 1080);


	Texture mainmenubg;
	mainmenubg.loadFromFile("hell.jpg");
	Sprite bg;
	bg.setTexture(mainmenubg);

	while (true) {
		if (pagenum == 1000) {
			while (window.isOpen()) {
				Event event;
				while (window.pollEvent(event)) {
					if (event.type == Event::Closed) {
						window.close();
						break;
					}


					if (event.type == Event::KeyPressed) {
						if (event.key.code == Keyboard::Up) {
							menu.MoveUp();
						}
						if (event.key.code == Keyboard::Down) {
							menu.MoveDown();
						}
						if (event.key.code == Keyboard::Return) {
							if (menu.pressed()==0) {
								pagenum = 0;
							}
							if (menu.pressed() == 1) {
								pagenum = 1;
							}
							if (menu.pressed() == 2) {
								pagenum = -1;
							}

						}
					}

				}

				window.clear();
				if (pagenum != 1000) {
					break;
				}
				window.draw(bg);
				menu.draw(window);
				window.display();
			}
			if (pagenum == -1) {
				window.close();
				break;
			}
			if (pagenum == 0) {
				
			}

		}
	}
}