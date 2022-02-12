#include"UFOs.h"

// Constructor
UFOs::UFOs()
{
	// Data members
	speed = 6;
	isAlive = true;

	hitbox = 32; // Hitbox size

	loadImage();
}

// Loads Image
void UFOs::loadImage()
{
	if (!texture.loadFromFile("ASSETS/IMAGES/UFO.png"))
	{
		std::cout << "Enemy 2 problem" << std::endl;
	}

	// Sets random location
	int randomLocationX = std::rand() % SCREEN_WIDTH;
	int randomLocationY = (std::rand() % SCREEN_HEIGHT) * -1;
	sprite.setTexture(texture);
	sprite.setPosition(randomLocationX, randomLocationY);

	// Sets random direction
	int random = (std::rand() % 2) + 1;
	if (random == 1)
	{
		goingRight = true;
	}
	else
	{
		goingRight = false;
	}
}

// Return Functions
sf::Sprite UFOs::getBody()
{
	return sprite;
}
int UFOs::getHitbox()
{
	return hitbox;
}

void UFOs::movement()
{
	if (isAlive == true)
	{
		// Checks if hitting screen boundry, then moves either down or across
		sf::Vector2f current{ sprite.getPosition() };
		sf::Vector2f newLocation{ 0,0 };

		if (current.x > (SCREEN_WIDTH - 64))
		{
			goingRight = false;;
			newLocation.y += 32;
		}

		if (current.x < 0)
		{
			goingRight = true;
			newLocation.y += 32;
		}

		if (goingRight == true)
		{
			newLocation.x += speed;
		}
		else
		{
			newLocation.x -= speed;
		}

		// adds and sets location
		current += newLocation;
		sprite.setPosition(current);
	}
	else
	{
		// Regenerates on death
		int randomLocationX = std::rand() % SCREEN_WIDTH;
		int randomLocationY = ((std::rand() % SCREEN_HEIGHT) / 4) * -1;
		sprite.setPosition(randomLocationX, randomLocationY);
		isAlive = true;
	}
}

// Kills
void UFOs::die()
{
	isAlive = false;
}

// regenerates
void UFOs::reset()
{
	isAlive = true;

	int randomLocationX = std::rand() % SCREEN_WIDTH;
	int randomLocationY = (std::rand() % SCREEN_HEIGHT) * -1;
	sprite.setPosition(randomLocationX, randomLocationY);
}

