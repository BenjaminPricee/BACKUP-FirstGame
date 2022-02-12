// Player class declaration
#pragma once

#include "SFML/Graphics.hpp" 
#include<iostream>
#include"Globals.h"
#include"Player.h"

class FlyingEnemy
{
private:
	// Texture and Sprite
	sf::Texture texture;
	sf::Sprite sprite;

	// Data Members
	float speed;
	bool isAlive;
	int hitbox;

	// For animation
	int frameNo;
	float frameValue;
	float frameIncrement;

public:
	// Construction
	FlyingEnemy();
	void loadImage();

	// Functions for data members
	sf::Sprite getBody();
	int getHitbox();

	// Movement
	void followMovement(Player t_player);

	// Animation
	void animate();

	// Resets
	void die();
	void reset();
};