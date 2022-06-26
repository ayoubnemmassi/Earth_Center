#include "Magnet.h"
#include<iostream>

Magnet::Magnet( sf::Vector2f  const& position, std::string const& name) :Collectable{ sprite }, position{ position }, name{ name }
{

	initTexture("Magnetite.png");
	initSprite();
	initAudiomanager();
	initGamemusic("collect");
}





void Magnet::render(sf::RenderTarget& target)
{
	target.draw(sprite);
}

void Magnet::collected(Player & player)  
{
	player.magnetCollected();


}


std::string Magnet::test()
{
	return "Magnet";
}

void Magnet::initTexture(std::string const& Magnetname)
{

	std::string url = "resources/Textures/";
	if (!texture.loadFromFile(url + Magnetname))
	{
		std::cout << "ERROR::Magnet::FAILED TO LOAD TEXTURE" << std::endl;
	}
}

void Magnet::initSprite()
{
	sprite.setTexture(texture);
	sprite.setOrigin(static_cast<sf::Vector2f>(sprite.getTexture()->getSize()) / 2.f);
	sprite.setPosition(position);

}

Collider Magnet::getCollider()
{
	return Collider(sprite);
}

sf::Vector2f Magnet::getPosition() const
{
	return position;
}

