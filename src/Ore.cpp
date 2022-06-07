#include "Ore.h"
#include "Ore.h"
#include<iostream>

Ore::Ore(int const & value, sf::Vector2f  const& position) :Collectable{ sprite,value }, position{ position }
{
	
	initTexture("Tile_36.png");
	initSprite();
	initAudiomanager();
	initGamemusic();
}



void Ore::update(Collider &other)
{
	if (getCollider().CheckCollision(other, 0.0f)) 
	{
		getCollected();
	}
}

void Ore::render(sf::RenderTarget& target)
{
	target.draw(sprite);
}

void Ore::getCollected()
{
	std::cout << "ore collected" << std::endl;
	audiomanager->playMusic("collect");
}

void Ore::initTexture(std::string const& name)
{
	std::string url = "C:/Users/MSI/Downloads/earthcenter/Textures/";
	if (!texture.loadFromFile(url + name))
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
void Ore::initAudiomanager()
{
	audiomanager = std::make_unique<AudioManager>();
}

void Ore::initGamemusic()
{
	std::string collect = "C:/Users/MSI/Downloads/earthcenter/Textures/collect.ogg";

	audiomanager->addMusic("collect", collect);
}

Collider Ore::getCollider()
{
	return Collider(sprite);
}

 sf::Vector2f Ore::getPosition() const
{
	return position;
}
