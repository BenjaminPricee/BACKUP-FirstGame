#include"Bullet.h"

// Constructor
Bullet::Bullet()
{
	// Sets Datamembers
	fired = false;
	shooting = false;
	speed = 15;
	direction = 0;
	hitbox = 10; // Defines hitbox

	loadImage();
}

// Loads Images
void Bullet::loadImage()
{
	if (!textureUp.loadFromFile("ASSETS/IMAGES/bullet_up.png"))
	{
		std::cout << "Bullet up problem" << std::endl;
	}
	if (!textureDown.loadFromFile("ASSETS/IMAGES/bullet_down.png"))
	{
		std::cout << "Bullet down problem" << std::endl;
	}
	if (!textureLeft.loadFromFile("ASSETS/IMAGES/bullet_left.png"))
	{
		std::cout << "Bullet left problem" << std::endl;
	}
	if (!textureRight.loadFromFile("ASSETS/IMAGES/bullet_right.png"))
	{
		std::cout << "Bullet right problem" << std::endl;
	}

	// Sets default texture adn position
	sprite.setTexture(textureUp);
	sprite.setPosition(BULLET_BAY, BULLET_BAY);
}

// Return Functions
sf::Sprite Bullet::getBody()
{
	return sprite;
}
bool Bullet::getShooting()
{
	return shooting;
}
int Bullet::getHitbox()
{
	return hitbox;
}

// Movement
void Bullet::movement(Player t_player)
{
	// If not fired or shooting, set to bay off screen
	if (fired == false && shooting == false)
	{
		sprite.setPosition(BULLET_BAY, BULLET_BAY);
	}

	// if fired while not shooting, activate shooting and fire from position of player
	if (fired == true && shooting == false)
	{
		shooting = true;
		fired = false;
		sprite.setPosition(t_player.getBody().getPosition());
		direction = t_player.getDirection();
	}

	// Movement for shooting
	if (shooting == true)
	{
		// Takes position and increses in direction
		sf::Vector2f position{ sprite.getPosition() };
		sf::Vector2f move{ 0,0 };

		if (direction == 2)
		{
			move = { 0,speed };
			sprite.setTexture(textureDown);
		}
		else if (direction == 3)
		{
			move = { 0,-speed };
			sprite.setTexture(textureUp);
		}
		else if (direction == 1)
		{
			move = { -speed,0 };
			sprite.setTexture(textureLeft);
		}
		else if (direction == 0)
		{
			move = { speed,0 };
			sprite.setTexture(textureRight);
		}

		// Adds vector to position and sets
		position += move;
		sprite.setPosition(position);
	}
}

// Um
void Bullet::fire()
{
	fired = true;
}

// Kills shooting and firing upon hit
void Bullet::hit()
{
	shooting = false;
	fired = false;
}
