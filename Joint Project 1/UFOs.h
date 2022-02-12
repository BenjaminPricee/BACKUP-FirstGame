#pragma once

#include "SFML/Graphics.hpp" 
#include<iostream>
#include"Globals.h"

class UFOs
{
private:
	// Texture and Sprite
	sf::Texture texture;
	sf::Sprite sprite;

	// Data members
	float speed;
	bool isAlive;
	bool goingRight;
	int hitbox;

public:
	// Construciton
	UFOs();
	void loadImage();

	// Functions for data members
	sf::Sprite getBody();
	int getHitbox();

	// Movement
	void movement();

	// Reset Functions
	void die();
	void reset();

};