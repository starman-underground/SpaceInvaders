#include <iostream>
#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include "player.hpp"


void handleInput(Player& player, const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.scancode == sf::Keyboard::Scan::Left || event.key.scancode == sf::Keyboard::Scan::A) {
			player.movingLeft = true;
		}
		if (event.key.scancode == sf::Keyboard::Scan::Right || event.key.scancode == sf::Keyboard::Scan::D) {
			player.movingRight = true;
		}
	} else if (event.type == sf::Event::KeyReleased) {
		if (event.key.scancode == sf::Keyboard::Scan::Left || event.key.scancode == sf::Keyboard::Scan::A) {
			player.movingLeft = false;
		}
		if (event.key.scancode == sf::Keyboard::Scan::Right || event.key.scancode == sf::Keyboard::Scan::D) {
			player.movingRight = false;
		}
	}

}

int main() {
	auto window = sf::RenderWindow{ sf::VideoMode(GameConstants::SCREEN_WIDTH, GameConstants::SCREEN_HEIGHT), "Space Invaders" };
	window.setFramerateLimit(120);
	sf::Texture spriteSheet;
	
	if(!spriteSheet.loadFromFile("/Users/sreekommalapati/Projects/SpaceInvaders/assets/SpriteSheet.png")) {
		window.close();
		return EXIT_FAILURE;
	}
	Player player = Player(spriteSheet);

	while (window.isOpen()) {
		

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			} else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
				handleInput(player, event);
			}

		}
		
		player.move();

		window.clear(sf::Color::Black);
		player.draw(window);
		window.display();
	}

	return EXIT_SUCCESS;
}
