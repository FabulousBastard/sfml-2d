#include "Game.h"
 

//private fun.
void Game::initVariables()
{
	this->window = nullptr;

	//game logic
	this->points = 0;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 10;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "Title");

	this->window->setFramerateLimit(60);

}

void Game::initEnemys()
{
	this->enemy.setPosition(10.f, 10.f);

	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Green);
	//this->enemy.setOutlineColor(sf::Color::White);
	//this->enemy.setOutlineThickness(1.f);
}

//constructors
Game::Game() 
{
	this->initVariables();
	this->initWindow();
	this->initEnemys();

}

Game::~Game() 
{
	delete this->window;
}

//accessors
const bool Game::runing() const
{
	return this->window->isOpen();
}


void Game::spawnEnemy()
{
	/*
	spawns enemies and sets their colors and positions
		-sets rand. position.
		-sets rand. color.
		-adds enemy to the vector
	*/

	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);

	this->enemy.setFillColor(sf::Color::Green);

	//spawn the enemy
	this->enemies.push_back(this->enemy);

	//remove enemies at end of screen
}

void Game::updateEnemys()
{
	/*
		Updates the enemy spawn timer and spawns enemies
		when the total amount of enemies is smaller then the
		max.
		Moves the enemies downwards
		Removes the enemies at the edge of the screen.
	*/
	//updating the timer that spawns the enemys
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else {
			this->enemySpawnTimer += 1.f;
		}
	}
	//Moving and updateing the enemies
	for (int i =0; i < this->enemies.size(); i++)
	{
		bool deleted = false;

		this->enemies[i].move(0.f, 4.f);

		//checked if clicked upon
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
			{
				deleted = true;

				//gain points
				this->points += 10.f;
			}
		}

		//if a enemy is past the bottom of thescreen
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			deleted = true;
		}

		//finale delet
		if(deleted)
			this->enemies.erase(this->enemies.begin() + i);
	}
}

//functions
void Game::pollEvents()
{
	while (this->window->pollEvent(this->e))
	{
		// "close requested" event: we close the window
		if (this->e.type == sf::Event::Closed){
			this->window->close();
		}
	} 
}

void Game::updateMousePositions()
{
	//updates the mouse positions:
	//	-mouse position relative to window(Vector2i)

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);

	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::update()
{
	this->pollEvents();
	
	//update mouse position
	this->updateMousePositions();

	this->updateEnemys();
}

void Game::renderEnemies()
{
	//rendering all the enemies
	for (auto& e : this->enemies)
	{
		this->window->draw(e);
	}
}

void Game::render()
{
	/*
		Renders the game objects
		returns void
	*/
	this->window->clear();//clears last frame

	//Draw game objects
	this->renderEnemies();

	this->window->display();//displays shit i think
}