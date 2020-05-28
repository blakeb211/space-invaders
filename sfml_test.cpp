#include "stdlibs.h"
#include <SFML/Graphics.hpp>


int main() {
  const int gameWidth = 800;
  const int gameHeight = 600;
  // Create the window of the application
  sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight, 32), "SFML Pong",
      sf::Style::Titlebar | sf::Style::Close);
  
  while (window.isOpen())
  {
    // Handle events
    sf::Event event;
    while (window.pollEvent(event))
    {
      // Window closed or escape key pressed: exit
      if ((event.type == sf::Event::Closed) ||
          ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
      {
        window.close();
        break;
      }

      // Space key pressed: play
      if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
      {
        
      }
    }

  }
    return 0;
}
