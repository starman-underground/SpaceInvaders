#include <SFML/Graphics.hpp>

#include <chrono>
#include <thread>
#include <optional>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#include "Game.hpp"
#include "EnemyManager.hpp"
#include "Constants.hpp"

Game::Game() :
	state(GameState::Playing),
	enemyManager(),
	player(),
	playerProjectile(std::nullopt),
	score(0),
	lives(3),
	window(sf::VideoMode(GameConstants::SCREEN_WIDTH, GameConstants::SCREEN_HEIGHT), "Space Invaders"),
	backgroundRect(sf::Vector2f(GameConstants::SCREEN_WIDTH, GameConstants::SCREEN_HEIGHT)),
	lastTime(Clock::now()),
	lag(0),
	projectileFrameAccumulator(0)
{
	
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	try {
		GameConstants::getSpriteSheet();
	} catch (const std::runtime_error& e) {
		state = GameState::Crashed;
		std::cerr << "Could not load sprite sheet" << std::endl;
	}
	loadShaders();
	shadeBackground();
}

void Game::loadShaders() {
	if (!vignetteShader.loadFromFile("shaders/vignette.frag", sf::Shader::Fragment)) {
		state = GameState::Crashed;
		std::cerr << "Could not load vignette shader" << std::endl;
	}
	if (!gaussianBlurShader.loadFromFile("shaders/gaussianblur.frag", sf::Shader::Fragment)) {
		state = GameState::Crashed;
		std::cerr << "Could not load gaussian blur shader" << std::endl;
	}
	if (!radialBlurShader.loadFromFile("shaders/radialblur.frag", sf::Shader::Fragment)) {
		state = GameState::Crashed;
		std::cerr << "Could not load radial blur shader" << std::endl;
	}
}

void Game::shadeBackground() {
	texBuffer1.create(GameConstants::SCREEN_WIDTH, GameConstants::SCREEN_HEIGHT);
	texBuffer2.create(GameConstants::SCREEN_WIDTH, GameConstants::SCREEN_HEIGHT);
	
	texBuffer1.clear();
	vignetteShader.setUniform("resolution", sf::Vector2f(window.getSize()));
	texBuffer1.draw(backgroundRect, &vignetteShader);
	texBuffer1.display();

	background.setTexture(texBuffer1.getTexture());
}

void Game::handleInput(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.scancode == sf::Keyboard::Scan::Left || event.key.scancode == sf::Keyboard::Scan::A) {
			player.movingLeft++;
		} else if (event.key.scancode == sf::Keyboard::Scan::Right || event.key.scancode == sf::Keyboard::Scan::D) {
			player.movingRight++;
		} else if (event.key.scancode == sf::Keyboard::Scan::Space && !playerProjectile) {
			playerProjectile = player.shoot();
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

void Game::updateProjectiles() {
	if (playerProjectile) {
		playerProjectile->move();
		sf::FloatRect projectileBounds = playerProjectile->getCollisionBox();
		unsigned int newScore = enemyManager.checkCollision(projectileBounds);
		if (newScore) {
			score += newScore;
			playerProjectile = std::nullopt;
		} else if (playerProjectile->outOfBounds()) {
			playerProjectile = std::nullopt;
		}
	}

	std::vector<Projectile> newProjectiles = enemyManager.shootEnemies();
	for (Projectile p : newProjectiles) {
		enemyProjectiles.push_back(p);
	}
	
	const sf::FloatRect playerBounds = player.getCollisionBox();
	bool playerHit = false;
	for (Projectile& p : enemyProjectiles) {
		p.move();
		if (p.getCollisionBox().intersects(playerBounds)) {
			lives--;
			playerHit = true;
			break;
		}
	}
	if (playerHit) {
		enemyProjectiles.clear();
		playerProjectile = std::nullopt;
		projectileFrameAccumulator = 0;
		player.state = PlayerState::Dead;
		state = GameState::Dying;
	} else {
		enemyProjectiles.erase(std::remove_if(enemyProjectiles.begin(), enemyProjectiles.end(),
			[](const Projectile& p) { return p.outOfBounds(); }),
			enemyProjectiles.end());
		projectileFrameAccumulator++;
		if (projectileFrameAccumulator >= GameConstants::FRAMES_PER_PROJECTILE_ANIMATION) {
			for (Projectile& p : enemyProjectiles) {
				p.update();
			}
			projectileFrameAccumulator -= GameConstants::FRAMES_PER_PROJECTILE_ANIMATION;
		}
	}

}

void Game::update() {
	if (deathFrameAccumulator >= GameConstants::NUM_DEATH_FRAMES) {
		state = GameState::Playing;
		deathFrameAccumulator = 0;
		player.state = PlayerState::Alive;
		player.deathAnimationAccumulator = 0;
	}
	if (state != GameState::Dying && lives <= 0) {
		state = GameState::Finished;
	}
	switch(state) {
		case GameState::Playing:
			player.update();
			updateProjectiles();
			enemyManager.update();
			break;
		case GameState::Dying:
			deathFrameAccumulator++;
			break;
	};
	lag -= FrameDuration(1);
}

void Game::drawScore() {
	sf::Sprite s;
	s.setTexture(GameConstants::getSpriteSheet());
	s.setScale(GameConstants::RATIO, GameConstants::RATIO);

	s.setPosition(40.0f, 40.0f);
	s.setTextureRect(GameConstants::S);
	window.draw(s);
	
	s.move(40.0f, 0.0f);
	s.setTextureRect(GameConstants::C);
	window.draw(s);

	s.move(40.0f, 0.0f);
	s.setTextureRect(GameConstants::O);
	window.draw(s);

	s.move(40.0f, 0.0f);
	s.setTextureRect(GameConstants::R);
	window.draw(s);

	s.move(40.0f, 0.0f);
	s.setTextureRect(GameConstants::E);
	window.draw(s);
	
	s.move(64.0f, 0.0f);
	s.setColor(GameConstants::PLAYER_COLOR);
	for (char c : std::to_string(score)) {
		switch(c) {
			case '0':
				s.setTextureRect(GameConstants::ZERO);
				break;
			case '1':
				s.setTextureRect(GameConstants::ONE);
				break;
			case '2':
				s.setTextureRect(GameConstants::TWO);
				break;
			case '3':
				s.setTextureRect(GameConstants::THREE);
				break;
			case '4':
				s.setTextureRect(GameConstants::FOUR);
				break;
			case '5':
				s.setTextureRect(GameConstants::FIVE);
				break;
			case '6':
				s.setTextureRect(GameConstants::SIX);
				break;
			case '7':
				s.setTextureRect(GameConstants::SEVEN);
				break;
			case '8':
				s.setTextureRect(GameConstants::EIGHT);
				break;
			case '9':
				s.setTextureRect(GameConstants::NINE);
				break;
		};
		window.draw(s);
		s.move(40.0f, 0.0f);
	}

}

void Game::drawLives() {
	sf::Sprite s;
	s.setTexture(GameConstants::getSpriteSheet());
	s.setScale(GameConstants::RATIO, GameConstants::RATIO);

	s.setPosition(window.getSize().x / 2.0f + 120.0f, 40.0f);
	s.setTextureRect(GameConstants::L);
	window.draw(s);
	
	s.move(40.0f, 0.0f);
	s.setTextureRect(GameConstants::I);
	window.draw(s);

	s.move(40.0f, 0.0f);
	s.setTextureRect(GameConstants::V);
	window.draw(s);

	s.move(40.0f, 0.0f);
	s.setTextureRect(GameConstants::E);
	window.draw(s);

	s.move(40.0f, 0.0f);
	s.setTextureRect(GameConstants::S);
	window.draw(s);

	s.setColor(GameConstants::PLAYER_COLOR);
	s.setTextureRect(GameConstants::PLAYER_FRAMES[0]);
	for (int i = 0; i < 3; i++) {
		if (i == lives) {
			s.setColor(GameConstants::ENEMY_COLOR);			
		}
		s.move(80.0f, 0.0f);
		window.draw(s);
	}
}

void Game::drawGameOver() {
	sf::Sprite s;
	s.setTexture(GameConstants::getSpriteSheet());
	s.setScale(GameConstants::RATIO * 2.0f, GameConstants::RATIO * 2.0f);

	s.setPosition(window.getSize().x / 2.0f - 360.0f, window.getSize().y / 3.0f);
	s.setTextureRect(GameConstants::G);
	window.draw(s);
	
	s.move(80.0f, 0.0f);
	s.setTextureRect(GameConstants::A);
	window.draw(s);

	s.move(80.0f, 0.0f);
	s.setTextureRect(GameConstants::M);
	window.draw(s);

	s.move(80.0f, 0.0f);
	s.setTextureRect(GameConstants::E);
	window.draw(s);

	s.move(160.0f, 0.0f);
	s.setTextureRect(GameConstants::O);
	window.draw(s);

	s.move(80.0f, 0.0f);
	s.setTextureRect(GameConstants::V);
	window.draw(s);

	s.move(80.0f, 0.0f);
	s.setTextureRect(GameConstants::E);
	window.draw(s);

	s.move(80.0f, 0.0f);
	s.setTextureRect(GameConstants::R);
	window.draw(s);

}

void Game::drawGUI() {
	sf::RectangleShape bottomLine;
	bottomLine.setSize(sf::Vector2f(GameConstants::SCREEN_WIDTH, 4));
	bottomLine.setFillColor(GameConstants::PLAYER_COLOR);
	bottomLine.setPosition(0, GameConstants::SCREEN_HEIGHT - 4);
	window.draw(bottomLine);
	drawScore();	
	drawLives();
}

void Game::render() {
	window.clear(sf::Color::Black);
	window.draw(background);
	drawGUI();
	if (state == GameState::Playing || state == GameState::Dying) {
		enemyManager.draw(window);
		player.draw(window);
		if (playerProjectile) {
			playerProjectile->draw(window);
		}
		for  (Projectile& p : enemyProjectiles) {
			p.draw(window);
		}
	} else if (state == GameState::Finished) {
		drawGameOver();
	}
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
			if (state == GameState::Crashed) {
				window.close();
				std::cerr << "Game crashed" << std::endl;
				return EXIT_FAILURE;
			}
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
