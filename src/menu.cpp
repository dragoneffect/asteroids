#include "../include/menu.h"
#include "../include/gui.h"
#include <list>

bool menu(RenderWindow &window, bool &running) {

  list<Gui> buttons;

  for (int i = 0, j = 220; i < 2; i++, j += 70) {
    buttons.emplace_back(300, j, "button.png");
  }

  //шрифт для строк и сами строки
  sf::Font font;
  font.loadFromFile("etc/font.ttf");

  sf::Text text_start, text_exit;

  text_start.setFont(font);
  text_start.setPosition(350, 220);
  text_exit.setFont(font);
  text_exit.setPosition(360, 290);

  string Start = "START";
  string Exit = "EXIT";

  //пока меню не закрыто, цикл работает
  while (running) {
    //обрабатываем события
    sf::Event event;
    while (window.pollEvent(event)) {
      //если нажата клавиша Esc, меню закрывается, игра продолжается
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::Escape) {
        running = false;
      }
      //если курсор находится в заданной области и происходит нажатие левой
      //кнопки мыши, то при нажатии первой кнопки игра продолжается. а еще
      //подсвечивается текст, если навести курсор

      //возобновление игры
      if (IntRect(300, 220, 190, 45).contains(Mouse::getPosition(window))) {
        text_start.setColor(sf::Color::Blue);
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
          running = false;
        }
      }
      //закрытие игры
      else if (IntRect(300, 290, 190, 45)
                   .contains(Mouse::getPosition(window))) {
        text_exit.setColor(sf::Color::Blue);
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
          window.close();
          running = false;
        }
      }

      else {
        text_start.setColor(sf::Color::White);
        text_exit.setColor(sf::Color::White);
      }
    }

    //выводим название кнопок на экран
    std::stringstream first, second;
    first << Start;
    text_start.setString(first.str());
    second << Exit;
    text_exit.setString(second.str());

    window.draw(text_start);
    window.draw(text_exit);

    for (auto &button : buttons) {
      button.model_sprite.setColor(sf::Color(255, 255, 255, 128));
      window.draw(button.model_sprite);
    }

    window.display();
  }
  return false;
}
