// Name: Ben Price
// Login: C00260297
// Date: 25/04/2021
// Approximate time taken: 50hrs
//---------------------------------------------------------------------------
// Project description: TEMPLATE
// ---------------------------------------------------------------------------
// Known Bugs:
// None

//////////////////////////////////////////////////////////// 
// include correct library file for release and debug versions
//////////////////////////////////////////////////////////// 

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "Game.h"   // include Game header file

int main()
{
	Game aGame;
	aGame.loadContent();
	aGame.run();

	return 0;
}

Game::Game() : window(sf::VideoMode(static_cast<int>(SCREEN_WIDTH), static_cast<int>(SCREEN_HEIGHT)), "Joint Project Game", sf::Style::Default)
// Default constructor
{
}

// Loads Content
void Game::loadContent()
// Load the font file & setup the message string
{
	// Font Load
	if (!m_font.loadFromFile("ASSETS/FONTS/BebasNeue.otf"))
	{
		std::cout << "error with font file file";
	}

	// Set up score counter
	m_score.setFont(m_font);  // set the font for the text
	m_score.setCharacterSize(24); // set the text size
	m_score.setFillColor(sf::Color::White); // set the text colour
	m_score.setPosition(10, 10);  // its position on the screen

	// GAMEOVER message set
	m_gameOver.setFont(m_font);
	m_gameOver.setCharacterSize(92);
	m_gameOver.setFillColor(sf::Color::White);
	m_gameOver.setPosition((SCREEN_WIDTH / 2) - 160, (SCREEN_HEIGHT / 2) - 128);
	m_gameOver.setString("GAME OVER");
	
	// Restart message set
	m_restart.setFont(m_font);
	m_restart.setCharacterSize(32);
	m_restart.setFillColor(sf::Color::Red);
	m_restart.setPosition((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2));
	m_restart.setString("RESTART (R)");
	m_restart.setOrigin(64, 0);

	// Map Setup
	dayTime = true;
	if (!backgroundDayTexture.loadFromFile("ASSETS/IMAGES/map_day.png"))
	{
		std::cout << "Background Problems";
	}
	if (!backgroundNightTexture.loadFromFile("ASSETS/IMAGES/map_night.png"))
	{
		std::cout << "Backgroung (night) problem";
	}
	backgroundSprite.setTexture(backgroundDayTexture);
	backgroundSprite.setScale(2, 2);
	backgroundSprite.setPosition(0, 0);

	// Other Variables
	gameMode = 1;
	score = 0;
	alienKills = 0;
}


void Game::run()
// This function contains the main game loop which controls the game. 
{
	srand((int)time(nullptr)); // set the seed once

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);

	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// the clock object keeps the time.
	sf::Clock clock;

	clock.restart();

	while (window.isOpen())
	{
		// check if the close window button is clicked on
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//get the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();

		//update every 60th of a second
		//only when the time since last update is greater than 1/60 update the world.
		if (timeSinceLastUpdate > timePerFrame)
		{
			update();
			draw();

			// reset the timeSinceLastUpdate to 0 
			timeSinceLastUpdate = sf::Time::Zero;
		}
	}  // end while loop

}

void Game::update()
// This function takes the keyboard input and updates the game world
{
	if (gameMode == 1)
	{
		// Moves and animates player accordingly
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			thePlayer.moveDown();
			thePlayer.animate();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			thePlayer.moveUp();
			thePlayer.animate();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			thePlayer.moveLeft();
			thePlayer.animate();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			thePlayer.moveRight();
			thePlayer.animate();
		}
		// Fires Bullet
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			pew.fire();
		}

		// Map Input and update
		if (alienKills > 20)
		{
			dayTime = false;
		}
		mapUpdate();

		// Collision Detection
		bulletCollision();
		enemyCollision();

		// Update Lives
		lives.updateHearts(thePlayer.getHealth());

		// Movement
		pew.movement(thePlayer);
		mikeWazowski.followMovement(thePlayer);
		flyingEyeball.followMovement(thePlayer);

		// Movement for array
		for (int i = 0; i < MAX_UFOS; i++)
		{
			Spaceships[i].movement();
		}

		// Animation in flying enemies
		mikeWazowski.animate();
		flyingEyeball.animate();

		// Restart checkers
		if (thePlayer.getHealth() < 1)
		{
			gameMode = 2;
		}
		if (alienKills == 50)
		{
			gameMode = 2;
		}
	}

	// Restart Screen
	if (gameMode == 2)
	{
		// Moves score
		m_score.setPosition(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 64);

		// Big Reset on R press
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			// Sets Gamemode back
			gameMode = 1;
			alienKills = 0;
			dayTime = true;

			// Fixes score
			m_score.setPosition(10, 10);
			score = 0;

			// Reset Sprites
			thePlayer.reset();
			lives.reset();
			mikeWazowski.reset();
			flyingEyeball.reset();
			for (int i = 0; i < MAX_UFOS;i++)
			{
				Spaceships[i].reset();
			}
			for (int j = 0; j < MAX_HOSTAGES; j++)
			{
				hostages[j].reset();
			}
		}
	}
}

void Game::draw()
// This function draws the game world
{
	// Gameplay drawing
	if (gameMode == 1)
	{
		// Clear the screen and draw your game sprites
		window.clear();

		// Draws Background first
		window.draw(backgroundSprite);

		// Updates score
		m_score.setString(std::to_string(thePlayer.getScore()));

		// Draws Message and sprites
		window.draw(m_score); 
		window.draw(thePlayer.getBody());
		window.draw(pew.getBody());

		// Drawing for arrays
		for (int i = 0; i < MAX_HOSTAGES; i++)
		{
			window.draw(hostages[i].getBody());
		}
		for (int i = 0; i < MAX_UFOS; i++)
		{
			window.draw(Spaceships[i].getBody());
		}

		// Draws Flying enemies
		window.draw(mikeWazowski.getBody());
		window.draw(flyingEyeball.getBody());

		// Heart Display (last)
		window.draw(lives.getHeartOne());
		window.draw(lives.getHeartTwo());
		window.draw(lives.getHeartThree());

		window.display();
	}
	
	// Restart screen drawing
	if (gameMode == 2)
	{
		window.clear();

		// Draws very little 
		window.draw(backgroundSprite);
		window.draw(m_restart);
		window.draw(m_gameOver);
		window.draw(m_score);

		window.display();
	}
}

// Bullet collision checking
void Game::bulletCollision()
{
	// Only checks while shooting
	if (pew.getShooting() == true)
	{
		// gets position
		sf::Vector2f bulletPosition{ pew.getBody().getPosition() };

		// Checks collision with screen border
		if (bulletPosition.x < 0 || bulletPosition.x > SCREEN_WIDTH)
		{
			pew.hit();
		}
		if (bulletPosition.y < 0 || bulletPosition.y > SCREEN_HEIGHT)
		{
			pew.hit();
		}

		// Collision in Enemy Array
		for (int i = 0; i < MAX_UFOS; i++)
		{
			// Gets position and distance between them
			sf::Vector2f ufoPosition{ Spaceships[i].getBody().getPosition() };
			int distance = sqrt(((bulletPosition.x - ufoPosition.x) * (bulletPosition.x - ufoPosition.x)) + ((bulletPosition.y - ufoPosition.y) * (bulletPosition.y - ufoPosition.y)));

			// If distance is less than hitboxes added
			if (distance < (pew.getHitbox()+Spaceships[i].getHitbox()))
			{
				pew.hit(); // hits
				Spaceships[i].die(); // kills spaceship
				thePlayer.scoreUp(); // adds points
				alienKills += 1; // adds to alien kills
			}
		}

		// Collision in Flying enemy 1 (same as spaceships)
		sf::Vector2f mikeLocation{ mikeWazowski.getBody().getPosition() };
		int mikeDistance = sqrt(((bulletPosition.x - mikeLocation.x) * (bulletPosition.x - mikeLocation.x)) + ((bulletPosition.y - mikeLocation.y) * (bulletPosition.y - mikeLocation.y)));

		if (mikeDistance < (mikeWazowski.getHitbox() + pew.getHitbox()))
		{
			pew.hit();
			mikeWazowski.die();
			thePlayer.scoreUp();
			alienKills += 1;
		}

		// Collision in flying enemy 2 (Same as above)
		sf::Vector2f eyeballLocation{ flyingEyeball.getBody().getPosition() };
		int eyeballDistance = sqrt(((bulletPosition.x - eyeballLocation.x) * (bulletPosition.x - eyeballLocation.x)) + ((bulletPosition.y - eyeballLocation.y) * (bulletPosition.y - eyeballLocation.y)));

		if (eyeballDistance < (flyingEyeball.getHitbox() + pew.getHitbox()))
		{
			pew.hit();
			flyingEyeball.die();
			thePlayer.scoreUp();
			alienKills += 1;
		}
	}
}

// Collision with player
void Game::enemyCollision()
{
	// Gets plater location
	sf::Vector2f playerLocation{ thePlayer.getBody().getPosition() };

	for (int i = 0; i < MAX_UFOS; i++)
	{
		// gets distance between entities
		sf::Vector2f ufoPosition{ Spaceships[i].getBody().getPosition() };
		int distanceToPlayer = sqrt(((playerLocation.x - ufoPosition.x) * (playerLocation.x - ufoPosition.x)) + ((playerLocation.y - ufoPosition.y) * (playerLocation.y - ufoPosition.y)));

		// If distance is smaller than added hitboxes...
		if (distanceToPlayer < (Spaceships[i].getHitbox() + thePlayer.getHitbox()))
		{
			Spaceships[i].die(); // Kills
			thePlayer.scoreDown(); // Loses Score
			thePlayer.takeDamage(); // Takes life
		}

		// Same system with hostages, but also kills hostage
		for (int j = 0; j < MAX_HOSTAGES; j++)
		{
			sf::Vector2f hostagePosition{ hostages[j].getBody().getPosition() };
			int distanceToHostage = sqrt(((hostagePosition.x - ufoPosition.x) * (hostagePosition.x - ufoPosition.x)) + ((hostagePosition.y - ufoPosition.y) * (hostagePosition.y - ufoPosition.y)));

			if (distanceToHostage < Spaceships[i].getHitbox() + hostages[j].getHitbox())
			{
				hostages[j].die();
				thePlayer.scoreDown();
			}
		}

	}

	// Same system for flying enemies, but they do not abduct hostages
	sf::Vector2f mikeLocation{ mikeWazowski.getBody().getPosition() };
	int mikeDistance = sqrt(((playerLocation.x - mikeLocation.x) * (playerLocation.x - mikeLocation.x)) + ((playerLocation.y - mikeLocation.y) * (playerLocation.y - mikeLocation.y)));

	if (mikeDistance < (mikeWazowski.getHitbox() + thePlayer.getHitbox()))
	{
		mikeWazowski.die();
		thePlayer.scoreDown();
		thePlayer.takeDamage();
	}

	sf::Vector2f eyeballLocation{ flyingEyeball.getBody().getPosition() };
	int eyeballDistance = sqrt(((playerLocation.x - eyeballLocation.x) * (playerLocation.x - eyeballLocation.x)) + ((playerLocation.y - eyeballLocation.y) * (playerLocation.y - eyeballLocation.y)));

	if (eyeballDistance < (flyingEyeball.getHitbox() + thePlayer.getHitbox()))
	{
		flyingEyeball.die();
		thePlayer.scoreDown();
		thePlayer.takeDamage();
	}
}

// Updates Map
void Game::mapUpdate()
{
	if (dayTime == true)
	{
		backgroundSprite.setTexture(backgroundDayTexture);
	}
	else
	{
		backgroundSprite.setTexture(backgroundNightTexture);
	}
}
