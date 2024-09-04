#include <iostream>
#include <vector>

#include "player.hpp"
#include "projectile.hpp"
#include "constants.hpp"

Player::Player() {
	sprite.setTexture(GameConstants::getSpriteSheet());
	sprite.setTextureRect(GameConstants::PLAYER_FRAMES[0]);
	sprite.setScale(4.0f, 4.0f);

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
	int i = 1;
	for (const Projectile& projectile : projectiles) {
		projectile.draw(window);
		i += 1;
	}
}

void Player::update() {
	if (movingLeft && !movingRight && sprite.getPosition().x > GameConstants::WALL_LEFT) {
		sprite.move(-1.0 * Player::SPEED, 0.0);
	} else if (!movingLeft && movingRight && sprite.getPosition().x + sprite.getGlobalBounds().width < GameConstants::WALL_RIGHT) {
		sprite.move(1.0 * Player::SPEED, 0.0);
	}

	for (auto projectile = projectiles.begin(); projectile != projectiles.end(); ) {
		projectile->move();
		sf::FloatRect projectileBounds = projectile->getCollisionBox();
		if (projectileBounds.top < GameConstants::WALL_TOP) {
			projectile = projectiles.erase(projectile);
		} else if (projectileBounds.top + projectileBounds.height > GameConstants::WALL_BOTTOM) {
			projectile = projectiles.erase(projectile);
		} else {
			projectile++;
		}
	}
}

void Player::shoot() {
	projectiles.emplace_back(ProjectileType::Player, sprite.getGlobalBounds(), PROJECTILE_SPEED); 
}
