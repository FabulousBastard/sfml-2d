#pragma once

#include <iostream>
#include <vector>
#include <ctime>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

/*
	class that acts as the game engine.
	wraper class
*/

class Game
{
private:
	//private fun.
	void initVariables();
	void initWindow();
	void initEnemys();

	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event e;

	//mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//game logic
	int points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;

	//game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

public:
	//constructor destructor
	Game();
	virtual ~Game();

	//accessors
	const bool runing() const;

	//functions
	void spawnEnemy();
	void updateEnemys();

	void pollEvents();
	void updateMousePositions();
	void update();

	void renderEnemies();
	void render();
};