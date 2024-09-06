#include <iostream>
#include <vector>
#include <optional>

#include "Player.hpp"
#include "Projectile.hpp"
#include "Constants.hpp"

Player::Player() {
	sprite.setTexture(GameConstants::getSpriteSheet());
	sprite.setTextureRect(GameConstants::PLAYER_FRAMES[0]);
	sprite.setScale(4.0f, 4.0f);
	sprite.setColor(GameConstants::PLAYER_COLOR);
	
	float posX = (static_cast<float>(GameConstants::SCREEN_WIDTH) - sprite.getGlobalBounds().width) / 2.0;
	float posY = static_cast<float>(GameConstants::SCREEN_HEIGHT) - sprite.getGlobalBounds().height - 20.0f;
	sprite.setPosition(posX, posY);
}

void Player::draw(sf::RenderTarget& window) {
	if (state == PlayerState::Alive) {
		sprite.setTextureRect(GameConstants::PLAYER_FRAMES[0]);
	} else if (state == PlayerState::Dead) {
		// TODO: Death logic
	}
	window.draw(sprite);
	if (projectile) {
		projectile->draw(window);
	}
}

void Player::update() {
	if (movingLeft && !movingRight && sprite.getPosition().x > GameConstants::WALL_LEFT) {
		sprite.move(-1.0 * Player::SPEED, 0.0);
	} else if (!movingLeft && movingRight && sprite.getPosition().x + sprite.getGlobalBounds().width < GameConstants::WALL_RIGHT) {
		sprite.move(1.0 * Player::SPEED, 0.0);
	}
	if (projectile) {
		projectile->move();
		sf::FloatRect projectileBounds = projectile->getCollisionBox();
		if (projectileBounds.top < GameConstants::WALL_TOP || projectileBounds.top + projectileBounds.height > GameConstants::WALL_BOTTOM) {
			projectile = std::nullopt;
		}
	}
}

void Player::shoot() {
	if (!projectile) {
		projectile = Projectile(ProjectileType::Player, sprite.getGlobalBounds(), PROJECTILE_SPEED);
	}
}
