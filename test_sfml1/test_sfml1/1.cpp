#include <SFML/Graphics.hpp>

using namespace sf; //включаем пространство имен sf, чтобы постоянно не писать sf::

int main() {
	RenderWindow window(sf::VideoMode(800, 600), "texture");
	Image heroimage; //создаем объект изображение
	heroimage.loadFromFile("images/pl1.png"); //загружаем в него файл
	Texture herotexture; //создаем объект текстуры
	herotexture.loadFromImage(heroimage);//передаем в него объект изображение 
	Sprite herosprite;//создаем объект спрайт 
	herosprite.setTexture(herotexture);//передаем в него объект текстуры
	herosprite.setPosition(50, 495);//начальные координаты появления спрайта 
	herotexture.setSmooth(true);
	while (!(Keyboard::isKeyPressed(Keyboard::Escape))) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) { herosprite.move(0.1, 0); }//движение 
		if (Keyboard::isKeyPressed(Keyboard::Left)) { herosprite.move(-0.1, 0); }
	window.clear();
	window.draw(herosprite);
	window.display();
	}
	return 0;
}
