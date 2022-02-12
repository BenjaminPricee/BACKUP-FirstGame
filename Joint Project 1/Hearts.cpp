#include"Hearts.h"

// Constructor
Hearts::Hearts()
{
	// Data member
	amount = 3;

	loadImages();
}

// Loads Image
void Hearts::loadImages()
{
	if (!texture.loadFromFile("ASSETS/IMAGES/heart.png"))
	{
		std::cout << "Heart problem (uh oh)" << std::endl;
	}

	// Heart Textures
	heartOne.setTexture(texture);
	heartTwo.setTexture(texture);
	heartThree.setTexture(texture);

	// Positions
	heartOne.setPosition(64, (SCREEN_HEIGHT - 64));
	heartTwo.setPosition(96, (SCREEN_HEIGHT - 64));
	heartThree.setPosition(128, (SCREEN_HEIGHT - 64));
}

// Return Functions
sf::Sprite Hearts::getHeartOne()
{
	return heartOne;
}
sf::Sprite Hearts::getHeartTwo()
{
	return heartTwo;
}
sf::Sprite Hearts::getHeartThree()
{
	return heartThree;
}

// Upadtes based on lives
void Hearts::updateHearts(int t_heartCount)
{
	amount = t_heartCount;

	if (amount == 2)
	{
		heartThree.setPosition(HEART_BAY, HEART_BAY);
	}

	if (amount == 1)
	{
		heartTwo.setPosition(HEART_BAY, HEART_BAY);
	}

	if (amount == 0)
	{
		heartOne.setPosition(HEART_BAY, HEART_BAY);
	}
}

// Complete reset
void Hearts::reset()
{
	amount = 3;

	heartOne.setPosition(64, (SCREEN_HEIGHT - 64));
	heartTwo.setPosition(96, (SCREEN_HEIGHT - 64));
	heartThree.setPosition(128, (SCREEN_HEIGHT - 64));
}
