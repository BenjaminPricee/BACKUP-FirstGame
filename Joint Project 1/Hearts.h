#pragma once

#include "SFML/Graphics.hpp" 
#include<iostream>
#include"Globals.h"
#include"Player.h"

class Hearts
{
private:
	// Texture
	sf::Texture texture;

	// Sprites
	sf::Sprite heartOne;
	sf::Sprite heartTwo;
	sf::Sprite heartThree;

	// single data member
	int amount;

public:
	// Construction
	Hearts();
	void loadImages();

	// Return Functions
	sf::Sprite getHeartOne();
	sf::Sprite getHeartTwo();
	sf::Sprite getHeartThree();

	// Updates Lives
	void updateHearts(int t_heartCount);

	// Resets
	void reset();

};