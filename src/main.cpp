#include <SFML/Graphics.hpp>

#include <iostream>

#include "projectile.hpp"
#include "constants.hpp"
#include "player.hpp"


void handleInput(Player& player, const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.scancode == sf::Keyboard::Scan::Left || event.key.scancode == sf::Keyboard::Scan::A) {
			player.movingLeft++;
		} else if (event.key.scancode == sf::Keyboard::Scan::Right || event.key.scancode == sf::Keyboard::Scan::D) {
			player.movingRight++;
		} else if (event.key.scancode == sf::Keyboard::Scan::Space) {
			player.shoot();
		}
	} else if (event.type == sf::Event::KeyReleased) {
		if (event.key.scancode == sf::Keyboard::Scan::Left || event.key.scancode == sf::Keyboard::Scan::A) {
			player.movingLeft--;
		} else if (event.key.scancode == sf::Keyboard::Scan::Right || event.key.scancode == sf::Keyboard::Scan::D) {
			player.movingRight--;
		}
	}
}

void handleEvent(const sf::Event& event, sf::RenderWindow& window, Player& player) {
	if (event.type == sf::Event::Closed) {
		window.close();
	} else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
		handleInput(player, event);
	}	
}

void update(Player& player) {
		player.update();
}
		

void render(Player& player, sf::RenderWindow& window) {
	window.clear(sf::Color::Black);
	player.draw(window);
	window.display();
}

int main() {
	
	auto window = sf::RenderWindow{ sf::VideoMode(GameConstants::SCREEN_WIDTH, GameConstants::SCREEN_HEIGHT), "Space Invaders" };
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
	try {
		GameConstants::getSpriteSheet();
	} catch (const std::runtime_error& e) {
		window.close();
	}

	Player player;
	if (window.isOpen()) {
		Player player = Player();
	}

	while (window.isOpen()) {
		
		sf::Event event;
		while (window.pollEvent(event)) {
			handleEvent(event, window, player);
		}
		
		update(player);
		render(player, window);
	}

	return EXIT_SUCCESS;
}
