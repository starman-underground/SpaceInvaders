#pragma once

#include <SFML/Graphics.hpp>

#include <random>
#include <optional>

#include "Projectile.hpp"

enum class EnemyType {
	One,
	Two,
	Three,
};

enum class Direction {
	Up,
	Down,
	Left,
	Right
};

enum class EnemyState {
	Alive,
	Dead
};

class Enemy {
	public:
		Enemy(EnemyType type, sf::Vector2f startPos);

		std::optional<Projectile> shoot();
		void move(Direction dir);		

		bool hitLeftWall();
		bool hitRightWall();

		const sf::FloatRect& getCollisionBox();
		EnemyType getType();

		EnemyState state;

	private:
		EnemyType type;
		sf::FloatRect boundingBox;

		inline static std::random_device rd{};
		inline static std::mt19937 gen{rd()};
		inline static std::uniform_real_distribution<> dis{0.0, 1.0};

		static constexpr double SHOOT_CHANCE = 0.0002;
};
