#include <SFML/Graphics.hpp>

#include <optional>

#include "Enemy.hpp"
#include "Constants.hpp"
#include "Projectile.hpp"

Enemy::Enemy(EnemyType type, sf::Vector2f startPos) : type(type),
	boundingBox(startPos.x, startPos.y, GameConstants::RATIO * 16.0f, GameConstants::RATIO * 8.0f),
	state(EnemyState::Alive) {}

std::optional<Projectile> Enemy::shoot() {
	if (dis(gen) < SHOOT_CHANCE) {
		switch(type) {
			case EnemyType::One:
				return Projectile(ProjectileType::Enemy1, getCollisionBox());
			case EnemyType::Two:
				return Projectile(ProjectileType::Enemy2, getCollisionBox());
			case EnemyType::Three:
				return Projectile(ProjectileType::Enemy3, getCollisionBox());
		};
	}
	return std::nullopt;
}

void Enemy::move(Direction dir) {
	switch(dir) {
		case Direction::Up:
			boundingBox.top -= boundingBox.height;
			break;
		case Direction::Down:
			boundingBox.top += boundingBox.height;
			break;
		case Direction::Left:
			boundingBox.left -= boundingBox.width / 4.0f;
			break;
		case Direction::Right:
			boundingBox.left += boundingBox.width / 4.0f;
			break;
	};
}

bool Enemy::hitRightWall() {
	return boundingBox.left + boundingBox.width > GameConstants::WALL_RIGHT;
}

bool Enemy::hitLeftWall() {
	return boundingBox.left < GameConstants::WALL_LEFT;
}

const sf::FloatRect& Enemy::getCollisionBox() {
	return boundingBox;
}

EnemyType Enemy::getType() {
	return type;
}

