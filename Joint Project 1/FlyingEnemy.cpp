#include"FlyingEnemy.h"

FlyingEnemy::FlyingEnemy()
{
	// Data Members
	speed = 2;
	isAlive = true;

	// Hitbox
	hitbox = 24;

	// Animation
	frameNo = 0;
	frameValue = 0.0f;
	frameIncrement = 0.125f;

	loadImage();
}

// Loads Images
void FlyingEnemy::loadImage()
{
	if (!texture.loadFromFile("ASSETS/IMAGES/flying_alien.png"))
	{
		std::cout << "Flying Enemy problem" << std::endl;
	}

	// sets Texture, position and square for animation
	sprite.setTexture(texture);
	sprite.setPosition((SCREEN_WIDTH / 2), -256);
	sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
}

// Return Functions
sf::Sprite FlyingEnemy::getBody()
{
	return sprite;
}
int FlyingEnemy::getHitbox()
{
	return hitbox;
}

// Takes Player location and follows
void FlyingEnemy::followMovement(Player t_player)
{
	if (isAlive == true)
	{
		// Takes locations
		sf::Vector2f playerLocation{ t_player.getBody().getPosition() };
		sf::Vector2f enemyLocation{ sprite.getPosition() };
		sf::Vector2f movement{ 0,0 };

		// Compares locations and adds to movement vector accordingly
		if (playerLocation.x > enemyLocation.x)
		{
			movement.x += speed;
		}
		if (playerLocation.x < enemyLocation.x)
		{
			movement.x -= speed;
		}
		if (playerLocation.y > enemyLocation.y)
		{
			movement.y += speed;
		}
		if (playerLocation.y < enemyLocation.y)
		{
			movement.y -= speed;
		}

		// Adds and sets movement
		enemyLocation += movement;
		sprite.setPosition(enemyLocation);
	}
	else
	{
		// Randomly respawns enemy when dead
		int randomLocationX = std::rand() % SCREEN_WIDTH;
		int randomLocationY = ((std::rand() % SCREEN_HEIGHT) / 2) * -1;
		sprite.setPosition(randomLocationX, randomLocationY);
		isAlive = true; // Makes Alive
	}
}

// Kills enemy
void FlyingEnemy::die()
{
	isAlive = false;
}

// Animation
void FlyingEnemy::animate()
{
	// Creates Frames to compare
	int oldFrame = frameNo;
	frameValue += frameIncrement;
	frameNo = static_cast<int>(frameValue);
	frameNo = frameNo % 3; // Because theres 3 images on the sheet

	// Should always happen
	if (oldFrame != frameNo)
	{
		// Sets box on spritesheet to the right ever so many frames
		sprite.setTextureRect(sf::IntRect(frameNo * 64, 0, 64, 64));
	}
}

// Resets to random location
void FlyingEnemy::reset()
{
	int randomLocationX = std::rand() % SCREEN_WIDTH;
	int randomLocationY = ((std::rand() % SCREEN_HEIGHT) / 2) * -1;
	sprite.setPosition(randomLocationX, randomLocationY);
}
