// Player class declaration
#pragma once

#include "SFML/Graphics.hpp" 
#include<iostream>
#include"Globals.h"
#include<math.h>

class Player
{
private:
	// Texture and Sprite
	sf::Texture texture;
	sf::Sprite sprite;

	int health;  // the health of the player
	int direction; // Direction
	float speed;  // the speed of the player
	int score;   // the player score
	int lives; // life count
	int hitbox; // Hitbox

	// For animation
	int frameNo;
	float frameValue;
	float frameIncrement;

public:
	// Construction
	Player();
	void loadImages();

	// Functoins for returning data members
	sf::Sprite getBody();
	int getDirection();
	int getHealth();
	int getHitbox();
	int getScore();

	// Movement Functions
	void moveDown();
	void moveUp();
	void moveLeft();
	void moveRight();

	// Animation
	void animate();

	// Score
	void scoreUp();
	void scoreDown();

	void takeDamage(); // For taking damamge

	// Reset function
	void reset();
};

