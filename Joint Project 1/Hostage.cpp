#include"Hostage.h"

// Constructor
Hostages::Hostages()
{
	// Data members
	isAlive = true;
	hitbox = 16;

	loadImage();
}

// loads image
void Hostages::loadImage()
{
	if (!texture.loadFromFile("ASSETS/IMAGES/hostage.png"))
	{
		std::cout << "Hostage problem" << std::endl;
	}

	// Sets to random location on bottom half of screen
	int randomLocationX = std::rand() % SCREEN_WIDTH;
	int randomLocationY = (std::rand() % (SCREEN_HEIGHT / 2)) + (SCREEN_HEIGHT / 2);
	sprite.setTexture(texture);
	sprite.setPosition(randomLocationX, randomLocationY);
}

// Return Functions
sf::Sprite Hostages::getBody()
{
	return sprite;
}
int Hostages::getHitbox()
{
	return hitbox;
}
bool Hostages::getAlive()
{
	return isAlive;
}

// Kills and sets to bay
void Hostages::die()
{
	isAlive = false;
	sprite.setPosition(HOSTAGE_BAY, HOSTAGE_BAY);
}

// Regenerates all
void Hostages::reset()
{
	isAlive = true;
	int randomLocationX = std::rand() % SCREEN_WIDTH;
	int randomLocationY = (std::rand() % (SCREEN_HEIGHT / 2)) + (SCREEN_HEIGHT / 2);
	sprite.setPosition(randomLocationX, randomLocationY);
}
