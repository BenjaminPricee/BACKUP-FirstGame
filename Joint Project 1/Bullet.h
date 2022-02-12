#pragma once

#include "SFML/Graphics.hpp" 
#include<iostream>
#include"Globals.h"
#include"Player.h"

class Bullet
{
private:
	// Textures and Sprite
	sf::Texture textureUp;
	sf::Texture textureLeft;
	sf::Texture textureDown;
	sf::Texture textureRight;
	sf::Sprite sprite;

	// Data Members
	bool fired;
	bool shooting;
	float speed;
	int direction;
	int hitbox; 

public:
	// Construction
	Bullet();
	void loadImage();

	// Return Functions
	sf::Sprite getBody();
	bool getShooting();
	int getHitbox();

	// Movement
	void movement(Player t_player);

	// interactions
	void fire();
	void hit();
};