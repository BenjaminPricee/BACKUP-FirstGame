// Game class declaration
#pragma once

#include "SFML/Graphics.hpp" 
#include <iostream>
#include <cstdlib>  // include support for randomizing
#include <ctime>   // supports ctime function
#include<math.h> // For square root function
#include<string> // for conversion from int to string

// Header File Additions
#include "Globals.h"  
#include "Player.h"   
#include"FlyingEnemy.h"
#include"UFOs.h"
#include"Bullet.h"
#include"Hearts.h"
#include"Hostage.h"

class Game
{
private:
	// Window
	sf::RenderWindow window;

	// Player
	Player thePlayer;

	// Hostages
	Hostages hostages[MAX_HOSTAGES];

	// Enemies
	FlyingEnemy mikeWazowski;
	FlyingEnemy flyingEyeball;
	UFOs Spaceships[MAX_UFOS];

	// For maps
	bool dayTime;
	sf::Texture backgroundDayTexture;
	sf::Texture backgroundNightTexture;
	sf::Sprite backgroundSprite;

	// Small Sprites
	Bullet pew;
	Hearts lives;

	// for gamemodes
	int score;
	int alienKills;

	// restart message
	sf::Text m_restart;
	sf::Text m_gameOver;

	// Gamemode setter (1 = gameplay, 2 = restart screen)
	int gameMode;

public:
	sf::Font m_font;  // font for writing text
	sf::Text m_score;  // text to write on the screen

public:
	// Construction
	Game();
	void	loadContent();

	// Basic functions
	void	run();
	void	update();
	void	draw();

	// Collision Detections
	void bulletCollision();
	void enemyCollision();

	// Map update
	void mapUpdate();
};
