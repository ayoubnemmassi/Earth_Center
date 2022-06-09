#include "Ore.h"
#include "Ore.h"
#include<iostream>

Ore::Ore(int const& value, sf::Vector2f  const& position, std::string const& name) :Collectable{ sprite,value }, position{ position }, name{name}
{
	
	initTexture("Tile_36.png");
	initSprite();
	initAudiomanager();
	initGamemusic("collect");
}



void Ore::update(Collider &other)
{
	if (getCollider().CheckCollision(other, 0.0f)) 
	{
		getCollected(name);
	}
}

void Ore::render(sf::RenderTarget& target)
{
	target.draw(sprite);
}

void Ore::getCollected(std::string const& Orename)
{
	std::cout << "ore collected" << std::endl;
	
}

std::string Ore::test()
{
	return "ore";
}

void Ore::initTexture(std::string const& Orename)
{
	std::string url = "resources/Textures/";
	if (!texture.loadFromFile(url + Orename))
	{
		std::cout << "ERROR::ORE::FAILED TO LOAD TEXTURE" << std::endl;
	}
}

void Ore::initSprite()
{
	sprite.setTexture(texture);
	sprite.setOrigin(static_cast<sf::Vector2f>(sprite.getTexture()->getSize()) / 2.f);
	sprite.setPosition(position);

}

Collider Ore::getCollider()
{
	return Collider(sprite);
}

 sf::Vector2f Ore::getPosition() const
{
	return position;
}
