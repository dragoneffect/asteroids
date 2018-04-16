#include <SFML/Graphics.hpp>

using namespace sf; //�������� ������������ ���� sf, ����� ��������� �� ������ sf::

int main() {
	RenderWindow window(sf::VideoMode(800, 600), "texture");
	Image heroimage; //������� ������ �����������
	heroimage.loadFromFile("images/pl1.png"); //��������� � ���� ����
	Texture herotexture; //������� ������ ��������
	herotexture.loadFromImage(heroimage);//�������� � ���� ������ ����������� 
	Sprite herosprite;//������� ������ ������ 
	herosprite.setTexture(herotexture);//�������� � ���� ������ ��������
	herosprite.setPosition(50, 495);//��������� ���������� ��������� ������� 
	herotexture.setSmooth(true);
	while (!(Keyboard::isKeyPressed(Keyboard::Escape))) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) { herosprite.move(0.1, 0); }//�������� 
		if (Keyboard::isKeyPressed(Keyboard::Left)) { herosprite.move(-0.1, 0); }
	window.clear();
	window.draw(herosprite);
	window.display();
	}
	return 0;
}
