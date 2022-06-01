#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <ctime>
#include <iostream>
#include <sstream> 

class Enemy
{
public:
	Enemy(float pos_x, float pos_y);
	~Enemy();
	//functions
	void update();
	void render(sf::RenderTarget& target);

private:
	sf::CircleShape shape;
	int type;
	int hp;
	int hpMax;
	int damage;
	int points;
	void initShape();
	void initVariables();
};

