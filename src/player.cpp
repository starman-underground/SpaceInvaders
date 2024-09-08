#include <iostream>
#include <vector>
#include <optional>

#include "Player.hpp"
#include "Projectile.hpp"
#include "Constants.hpp"

Player::Player() {
	sprite.setTexture(GameConstants::getSpriteSheet());
	sprite.setTextureRect(GameConstants::PLAYER_FRAMES[0]);
	sprite.setScale(GameConstants::RATIO, GameConstants::RATIO);
	sprite.setColor(GameConstants::PLAYER_COLOR);
	
	float posX = (static_cast<float>(GameConstants::SCREEN_WIDTH) - sprite.getGlobalBounds().width) / 2.0;
	float posY = static_cast<float>(GameConstants::SCREEN_HEIGHT) - sprite.getGlobalBounds().height - 25.0f;
	sprite.setPosition(posX, posY);
}

void Player::draw(sf::RenderTarget& window) {
	if (state == PlayerState::Alive) {
		sprite.setTextureRect(GameConstants::PLAYER_FRAMES[0]);
	} else if (state == PlayerState::Dead) {
		if ((deathAnimationAccumulator / GameConstants::FRAMES_PER_DEATH_ANIMATION) % 2 == 0) {
			sprite.setTextureRect(GameConstants::PLAYER_DEATH_FRAMES[0]);
		} else {
			sprite.setTextureRect(GameConstants::PLAYER_DEATH_FRAMES[1]);
		}
		deathAnimationAccumulator += 1;
	}
	window.draw(sprite);
}

void Player::update() {
	if (movingLeft && !movingRight && sprite.getPosition().x > GameConstants::WALL_LEFT) {
		sprite.move(-1.0 * Player::SPEED, 0.0);
	} else if (!movingLeft && movingRight && sprite.getPosition().x + sprite.getGlobalBounds().width < GameConstants::WALL_RIGHT) {
		sprite.move(1.0 * Player::SPEED, 0.0);
	}
}

Projectile Player::shoot() {
	return Projectile(ProjectileType::Player, sprite.getGlobalBounds());
}


const sf::FloatRect Player::getCollisionBox() const {
	return sprite.getGlobalBounds();
}
