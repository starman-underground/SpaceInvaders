#include <SFML/Graphics.hpp>

#include <vector>
#include <optional>
#include <iostream>

#include "EnemyManager.hpp"
#include "Constants.hpp"
#include "Enemy.hpp"

EnemyManager::EnemyManager() {
	placeEnemies();
	loadSprites();
}

void EnemyManager::placeEnemies() {
	enemies.reserve(5 * 11);

	float centerX = static_cast<float>(GameConstants::SCREEN_WIDTH) / 2.0f - 40.0f;
	float centerY = static_cast<float>(GameConstants::SCREEN_HEIGHT) / 2.0f - 40.0f;
	
	EnemyType type = EnemyType::Three;
	for (float offsetY = 0.0f; offsetY < 5.0f; offsetY += 1.0f) {
		if (offsetY > 1.1f) {
			type = EnemyType::Two;
		} 
		if (offsetY > 3.1f) {
			type = EnemyType::One;
		}
		for (int offsetX = 0.0f; offsetX < 6.0f; offsetX += 1.0f) {
			if (offsetX == 0.0f) {
				enemies.emplace_back(type, sf::Vector2f(centerX, centerY - (offsetY * EnemyManager::HORIZONTAL_SPACE)));
			} else {
				enemies.emplace_back(type, sf::Vector2f(centerX - (offsetX * EnemyManager::HORIZONTAL_SPACE), centerY - (offsetY * EnemyManager::VERTICAL_SPACE)));
				enemies.emplace_back(type, sf::Vector2f(centerX + (offsetX * EnemyManager::HORIZONTAL_SPACE), centerY - (offsetY * EnemyManager::VERTICAL_SPACE)));
			}
		}
	}
}

void EnemyManager::loadSprites() {
	sf::Texture& spriteSheet = GameConstants::getSpriteSheet(); 
	enemy1Frames[0] = sf::Sprite(spriteSheet, GameConstants::ENEMY1_FRAMES[0]);
	enemy1Frames[0].setScale(GameConstants::RATIO, GameConstants::RATIO);
	enemy1Frames[1] = sf::Sprite(spriteSheet, GameConstants::ENEMY1_FRAMES[1]);
	enemy1Frames[1].setScale(GameConstants::RATIO, GameConstants::RATIO);
	enemy2Frames[0] = sf::Sprite(spriteSheet, GameConstants::ENEMY2_FRAMES[0]);
	enemy2Frames[0].setScale(GameConstants::RATIO, GameConstants::RATIO);
	enemy2Frames[1] = sf::Sprite(spriteSheet, GameConstants::ENEMY2_FRAMES[1]);
	enemy2Frames[1].setScale(GameConstants::RATIO, GameConstants::RATIO);
	enemy3Frames[0] = sf::Sprite(spriteSheet, GameConstants::ENEMY3_FRAMES[0]);
	enemy3Frames[0].setScale(GameConstants::RATIO, GameConstants::RATIO);
	enemy3Frames[1] = sf::Sprite(spriteSheet, GameConstants::ENEMY3_FRAMES[1]);
	enemy3Frames[1].setScale(GameConstants::RATIO, GameConstants::RATIO);
}

void EnemyManager::draw(sf::RenderTarget& window) {
	for (Enemy& enemy : enemies) {
		if (enemy.state == EnemyState::Alive) {
			const sf::FloatRect& enemyBox = enemy.getCollisionBox();
			if (enemy.getType() == EnemyType::One) {
				enemy1Frames[enemyFrameIdx].setPosition(enemyBox.left, enemyBox.top);
				window.draw(enemy1Frames[enemyFrameIdx]);
			} else if (enemy.getType() == EnemyType::Two) {
				enemy2Frames[enemyFrameIdx].setPosition(enemyBox.left, enemyBox.top);
				window.draw(enemy2Frames[enemyFrameIdx]);
			} else if (enemy.getType() == EnemyType::Three) {
				enemy3Frames[enemyFrameIdx].setPosition(enemyBox.left, enemyBox.top);
				window.draw(enemy3Frames[enemyFrameIdx]);
			}
		}
	}
}

void EnemyManager::moveEnemies() {
	if (movingRight) {
		bool hitWall = false;
		for (Enemy& enemy : enemies) {
			enemy.move(Direction::Right);
			hitWall = hitWall || (enemy.state == EnemyState::Alive && enemy.hitRightWall());
		}
		if (hitWall) {
			movingRight = false;
			for (Enemy& enemy : enemies) {
				enemy.move(Direction::Down);
				enemy.move(Direction::Left);
			}
		}

	} else {
		bool hitWall = false;
		for (Enemy& enemy : enemies) {
			enemy.move(Direction::Left);
			hitWall = hitWall || (enemy.state == EnemyState::Alive && enemy.hitLeftWall());
		}
		if (hitWall) {
			movingRight = true;
			for (Enemy& enemy : enemies) {
				enemy.move(Direction::Down);
				enemy.move(Direction::Right);
			}
		}
	}
}

std::vector<Projectile> EnemyManager::shootEnemies() {
	std::vector<Projectile> newProjectiles;
	for (Enemy& enemy : enemies) {
		std::optional<Projectile> p = enemy.shoot();
		if (p) {
			newProjectiles.push_back(p.value());
		}
	}
	return newProjectiles;
}

void EnemyManager::update() {
	frameAccumulator++;
	while (frameAccumulator >= EnemyManager::FRAMES_PER_UPDATE) {
		enemyFrameIdx = enemyFrameIdx == 0 ? 1 : 0;
		moveEnemies();
		frameAccumulator -= EnemyManager::FRAMES_PER_UPDATE;
	}
}

unsigned int EnemyManager::checkCollision(const sf::FloatRect& projectileBox) {
	for (Enemy& enemy : enemies) {
		if (enemy.state == EnemyState::Alive && enemy.getCollisionBox().intersects(projectileBox)) {
			enemy.state = EnemyState::Dead;
			switch(enemy.getType()) {
				case EnemyType::One:
					return 40;
				case EnemyType::Two:
					return 20;
				case EnemyType::Three:
					return 10;
			};
		}
	}
	return 0;
}
