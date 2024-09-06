#include <SFML/Graphics.hpp>

#include <chrono>
#include <thread>
#include <iostream>

#include "Game.hpp"
#include "Constants.hpp"

Game::Game() :
	state(GameState::Playing),
	window(sf::VideoMode(GameConstants::SCREEN_WIDTH, GameConstants::SCREEN_HEIGHT), "Space Invaders"),
	player(),
	lag(0),
	enemyLag(0),
	lastTime(Clock::now())
{
	
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	try {
		GameConstants::getSpriteSheet();
	} catch (const std::runtime_error& e) {
		state = GameState::Crashed;
		std::cerr << "Could not load sprite sheet" << std::endl;
	}
}

void Game::handleInput(const sf::Event& event) {
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

void Game::handleEvent(const sf::Event& event) {
	if (event.type == sf::Event::Closed) {
		window.close();
	} else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
		handleInput(event);
	}	
}

void Game::update() {
	player.update();
	lag -= FrameDuration(1);
	enemyLag++;
	if (enemyLag >= 30) {
		// TODO: Implement Enemy Manager
		std::cout << "Updating enemies" << std::endl;
		enemyLag = 0;
	}
}



void Game::drawGUI() {
	sf::RectangleShape bottomLine;
	bottomLine.setSize(sf::Vector2f(GameConstants::SCREEN_WIDTH, 4));
	bottomLine.setFillColor(GameConstants::PLAYER_COLOR);
	bottomLine.setPosition(0, GameConstants::SCREEN_HEIGHT - 4);
	window.draw(bottomLine);

}

void Game::render() {
	window.clear(sf::Color::Black);
	drawGUI();
	player.draw(window);
	window.display();
}

int Game::loop() {
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			handleEvent(event);
		}
		Clock::time_point currentTime = Clock::now();
		FrameDuration elapsed = std::chrono::duration_cast<FrameDuration>(currentTime - lastTime);
		lastTime = currentTime;
		lag += elapsed;

		while (lag.count() > 0) {
			update();
		}
		
		render();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		if (state == GameState::Crashed) {
			window.close();
			std::cerr << "Game crashed" << std::endl;
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}
