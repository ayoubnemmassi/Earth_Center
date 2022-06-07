#include "Obstacle.h"
#include <iostream>
Obstacle::Obstacle(sf::Vector2f position,int hp):Destroyable{hp}
{
	
	initTexture("rock.png");
	initSprite();
	sprite.setOrigin(static_cast<sf::Vector2f>(sprite.getTexture()->getSize() )/ 2.0f);
	sprite.setPosition(position);
	 
}

Obstacle::~Obstacle()
{
}

void Obstacle::render(sf::RenderTarget& target)
{
	target.draw(sprite);
}

Collider Obstacle::getCollider()
{
	return Collider(sprite);
}

void Obstacle::initTexture(std::string name)
{
	std::string url="C:/Users/MSI/Downloads/earthcenter/Textures/";
	if(!texture.loadFromFile(url + name))
	{
		std::cout << "ERROR::OBSTACLE::FAILED TO LOAD TEXTURE" << std::endl;
	}
	if (!damageTexture.loadFromFile(url + "damagedrock.png"))
	{
		std::cout << "ERROR::OBSTACLE::FAILED TO LOAD TEXTURE" << std::endl;
	}

}

void Obstacle::initSprite()
{
	sprite.setTexture(texture);
}

void Obstacle::update()
{
	if(this->getHp()<5&&this->getHp()>0)
	{
		sprite.setTexture(damageTexture);
	}
	else if(getHp()<=0)
	{
		std::cout << "obstacle destroyed" << std::endl;
	}
}


