#include "../include/menu.h"
#include "../include/gui.h"
#include <list>

bool menu(RenderWindow &window, bool &running) {

  list<Gui> buttons;

  for (int i = 0, j = 150; i < 4; i++, j += 70) {
    buttons.emplace_back(300, j, "button.png");
  }

  //шрифт для строк и сами строки
  sf::Font font;
  font.loadFromFile("etc/font.ttf");

  sf::Text text_start, text_rules, text_records, text_exit;

  text_start.setFont(font);
  text_start.setPosition(350, 150);
  text_rules.setFont(font);
  text_rules.setPosition(350, 220);
  text_records.setFont(font);
  text_records.setPosition(325, 290);
  text_exit.setFont(font);
  text_exit.setPosition(360, 360);

  string Start = "START";
  string Rules = "RULES";
  string Records = "RECORDS";
  string Exit = "EXIT";

  //пока меню не закрыто, цикл работает
  while (!running) {
    //обрабатываем события
    sf::Event event;
    while (window.pollEvent(event)) {
      //если нажата клавиша Esc, меню закрывается, игра продолжается
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
          running = true;
        }
      }
      //если курсор находится в заданной области и происходит нажатие левой
      //кнопки мыши, то при нажатии первой кнопки игра продолжается. а еще
      //подсвечивается текст, если навести курсор
      if (IntRect(300, 150, 190, 45).contains(Mouse::getPosition(window))) {
        text_start.setColor(sf::Color::Blue);
        if (event.type == sf::Event::MouseButtonPressed) {
          if (event.mouseButton.button == sf::Mouse::Left) {
            running = true;
          }
        }
      }
      //открытие правил
      else if (IntRect(300, 220, 190, 45)
                   .contains(Mouse::getPosition(window))) {
        text_rules.setColor(sf::Color::Blue);
        /*  if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
            //что-то происходит
            }
          } */
      }
      //открытие рекордов
      else if (IntRect(300, 290, 190, 45)
                   .contains(Mouse::getPosition(window))) {
        text_records.setColor(sf::Color::Blue);
        /*  if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
            //что-то происходит
            }
          } */
      }
      //при нажатии четвертой кнопки происходит выход из игры
      else if (IntRect(300, 360, 190, 45)
                   .contains(Mouse::getPosition(window))) {
        text_exit.setColor(sf::Color::Blue);
        if (event.type == sf::Event::MouseButtonPressed) {
          if (event.mouseButton.button == sf::Mouse::Left) {
            window.close();
            running = true;
          }
        }
      } else {
        text_start.setColor(sf::Color::White);
        text_rules.setColor(sf::Color::White);
        text_records.setColor(sf::Color::White);
        text_exit.setColor(sf::Color::White);
      }
    }

    //выводим название кнопок на экран
    std::stringstream first, second, third, fourth;
    first << Start;
    text_start.setString(first.str());
    second << Rules;
    text_rules.setString(second.str());
    third << Records;
    text_records.setString(third.str());
    fourth << Exit;
    text_exit.setString(fourth.str());

    window.draw(text_start);
    window.draw(text_rules);
    window.draw(text_records);
    window.draw(text_exit);

    for (auto &button : buttons) {
      button.model_sprite.setColor(sf::Color(255, 255, 255, 128));
      window.draw(button.model_sprite);
    }

    window.display();
  }
  return false;
}
