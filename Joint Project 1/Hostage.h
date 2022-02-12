#pragma once

#include "SFML/Graphics.hpp" 
#include<iostream>
#include"Globals.h"

class Hostages
{
private:
	// Texture and Sprite
	sf::Texture texture;
	sf::Sprite sprite;

	// Data Members
	bool isAlive;
	int hitbox;

public:
	// Construction
	Hostages();
	void loadImage();

	// Return Functions
	sf::Sprite getBody();
	int getHitbox();
	bool getAlive();

	// Reset functions
	void die();
	void reset();

};