#include <SFML/Graphics.hpp>

#include <iostream>

#include "Projectile.hpp"
#include "Constants.hpp"

Projectile::Projectile(ProjectileType type, const sf::FloatRect& shooterPos) : type{type} {
	sprite = sf::Sprite(GameConstants::getSpriteSheet());
	frameIdx = 0;
	if (type == ProjectileType::Player) {
		numFrames = 1;
		sprite.setPosition(shooterPos.left + shooterPos.width / 2.0f, shooterPos.top - GameConstants::PLAYER_PROJECTILE_FRAMES[frameIdx].height);
	} else {
		numFrames = 4;
		sprite.setPosition(shooterPos.left + shooterPos.width / 2.0f, shooterPos.top + shooterPos.height);
	}
	sprite.setScale(GameConstants::RATIO, GameConstants::RATIO);
	updateSprite();
}

void Projectile::updateSprite() {
	switch(type) {
		case ProjectileType::Player:
			sprite.setTextureRect(GameConstants::PLAYER_PROJECTILE_FRAMES[frameIdx]);
			break;
		case ProjectileType::Enemy1:
			sprite.setTextureRect(GameConstants::ENEMY1_PROJECTILE_FRAMES[frameIdx]);
			break;
		case ProjectileType::Enemy2:
			sprite.setTextureRect(GameConstants::ENEMY2_PROJECTILE_FRAMES[frameIdx]);
			break;
		case ProjectileType::Enemy3:
			sprite.setTextureRect(GameConstants::ENEMY3_PROJECTILE_FRAMES[frameIdx]);
			break;
	};
}

void Projectile::draw(sf::RenderTarget& window) const {
	window.draw(sprite);
}

void Projectile::update() {
	frameIdx = (frameIdx + 1) % numFrames;
	updateSprite();
}

void Projectile::move() {
	if (type == ProjectileType::Player) {
		sprite.move(0.0f, -1.0f * Projectile::SPEED);	
	} else {
		sprite.move(0.0f, 1.0f * Projectile::SPEED);
	}
}

bool Projectile::outOfBounds() const {
	sf::FloatRect bounds = sprite.getGlobalBounds();
	return bounds.top < GameConstants::WALL_TOP || bounds.top + bounds.height > GameConstants::WALL_BOTTOM;
}

sf::FloatRect Projectile::getCollisionBox() const {
	return sprite.getGlobalBounds();
}
