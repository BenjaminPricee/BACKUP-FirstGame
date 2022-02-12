
#include "Player.h"   // include Player header file

Player::Player()
{
	// Data members
	health = 3;
	direction = 0;
	speed = 4;
	score = 0;
	lives = 3;
	hitbox = 15; // Hitbox size

	// Animation
	frameNo = 0;
	frameValue = 0.0f;
	frameIncrement = 0.125f;

	loadImages();
}

// Loads Images
void Player::loadImages()
{
	if (!texture.loadFromFile("ASSETS/IMAGES/player.png"))
	{
		std::cout << "Problem 0" << std::endl;
	}

	// Sets texture, position and rectangle
	sprite.setTexture(texture);
	sprite.setPosition((SCREEN_WIDTH / 2), (SCREEN_HEIGHT - 32.0f));
	sprite.setOrigin(16, 16);
	sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
}

// Return Functions
sf::Sprite Player::getBody()
{
	return sprite;
}
int Player::getDirection()
{
	return direction;
}
int Player::getHealth()
{
	return health;
}
int Player::getHitbox()
{
	return hitbox;
}
int Player::getScore()
{
	return score;
}

// Movement Down
void Player::moveDown()
{
	sf::Vector2f position{ sprite.getPosition() };

	if (position.y < (SCREEN_HEIGHT - 64))
	{
		sf::Vector2f move{ 0,speed };
		position += move;

		sprite.setPosition(position);
	}

	direction = 2;
}

// Movement Up
void Player::moveUp()
{
	sf::Vector2f position{ sprite.getPosition() };

	if (position.y > 0)
	{
		sf::Vector2f move{ 0,speed };
		position -= move;

		sprite.setPosition(position);
	}

	direction = 3;
}

// Movement Left
void Player::moveLeft()
{
	sf::Vector2f position{ sprite.getPosition() };

	if (position.x > 0)
	{
		sf::Vector2f move{ speed,0 };
		position -= move;
		sprite.setPosition(position);
	}

	direction = 1;
}

// movement right
void Player::moveRight()
{
	sf::Vector2f position{ sprite.getPosition() };

	if (position.x < (SCREEN_WIDTH - 64))
	{
		sf::Vector2f move{ speed,0 };
		position += move;
		sprite.setPosition(position);
	}

	direction = 0;
}

// Animates
void Player::animate()
{
	// Gets frames and compares. updates box location accordingly
	int oldFrame = frameNo;
	frameValue += frameIncrement;
	frameNo = static_cast<int>(frameValue);
	frameNo = frameNo % 4;

	if (oldFrame != frameNo)
	{
		sprite.setTextureRect(sf::IntRect(frameNo * 64, (direction * 64), 64, 64));
	}
}

// Adds to score
void Player::scoreUp()
{
	score += 10;
}

// Takes from score
void Player::scoreDown()
{
	score -= 10;
}

// Takes Health
void Player::takeDamage()
{
	health -= 1;
}

// Completely regenerates
void Player::reset()
{
	health = 3;
	direction = 0;
	speed = 4;
	score = 0;
	lives = 3;
	hitbox = 15;

	sprite.setPosition((SCREEN_WIDTH / 2), (SCREEN_HEIGHT - 32.0f));
}

