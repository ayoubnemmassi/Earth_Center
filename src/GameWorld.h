#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Player.h"
#include <vector>
class GameWorld
{
public:
	GameWorld(const Player& player);
	~GameWorld();
	
	//GETERS
	const int getgridLength()const;
	const int getLayerLength()const;
	const int getgridWidth()const;
	const float getMaxTimer()const;
	const float getTimer()const;

	void updateTime();
	void updateTimerText(const sf::Vector2f& player_pos,float view_h);
	void renderTimerText(sf::RenderTarget& target);
	void updateGUI( Player& player);
	const bool playerGotDamaged();
	void renderGUI(sf::RenderTarget& target,float view_h);
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, sf::Vector2f playerPos = sf::Vector2f());

private:
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBackground;
	int gridLength;
	int gridWidth;
	int firstLayer, secondLayer, thirdLayer, fourthLayer, fifthLayer, layertiles;

	float maxTimer;
	float timer;
	float maxCooldown;
	float cooldown;


	sf::Vector2i exitPos;
	sf::Vector2i playerPos;
	sf::Clock clock;
	sf::Text timerText;
	sf::Font timerFont;
	sf::Sprite sky;
	sf::Texture skyTexture;
	std::vector<sf::Vector2i> enemyPos;
	std::vector<std::vector<std::unique_ptr<Tile>>>tiles;
	
	void setUpInitialState();
	void setUpEnemyPositions();
	void setUpTiles();
	void initTextTimer(std::string font_name);
	void initskysprite();
	void initGUI(const Player& player);
	
	

};

