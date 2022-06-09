#pragma once
#include<SFML/Graphics.hpp>
#include "Collider.h"
#include <iostream>
#include "Destroyable.h"
class Obstacle:public Destroyable
{
public:
	Obstacle(sf::Vector2f position,int hp);

	void render(sf::RenderTarget& target);
	Collider getCollider();
	
	void update();

private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Texture damageTexture;

	void initTexture(std::string name);
	void initSprite();
};

