#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <vector>
class GameWorld
{
public:
	GameWorld();
	~GameWorld();
	
	//GETERS
	const int getgridLenth()const;
	const int getgridWidth()const;
	const float getMaxTimer()const;
	const float getTimer()const;

	void updateTime();
	void updateTimerText(const sf::Vector2f& player_pos);
	void renderTimerText(sf::RenderTarget& target);
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, sf::Vector2f playerPos = sf::Vector2f());

private:
	int gridLenth;
	int gridWidth;
	int firstLayer, secondLayer, thirdLayer, fourthLayer, fifthLayer;

	float maxTimer;
	float timer;

	sf::Vector2i exitPos;
	sf::Vector2i playerPos;
	sf::Clock clock;
	sf::Text timerText;
	sf::Font timerFont;
	sf::Sprite sky;
	sf::Texture skyTexture;
	std::vector<sf::Vector2i> enemyPos;
	std::vector<std::vector<Tile*>>tiles;
	
	void setUpInitialState();
	void setUpEnemyPositions();
	void setUpTiles();
	void initTextTimer(std::string font_name);
	void initskysprite();
	
	

};

