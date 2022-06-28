#include "Crystal.h"
#include<iostream>

Crystal::Crystal(int const& value, sf::Vector2f  const& position, std::string const& name) :Collectable{ sprite }, position{ position }, name{name},value{value}
{
	
	initTexture(name+".png");
	initSprite();
	initAudiomanager();
	initGamemusic("collect");
}




void Crystal::render(sf::RenderTarget& target)
{
	target.draw(sprite);
}

void Crystal::collected(Player & player)
{
	player.collectOre(value);
	
}

std::string Crystal::test()
{
	return "ore";
}

void Crystal::initTexture(std::string const & Orename)
{
	
	std::string url = "resources/Textures/";
	if (!texture.loadFromFile(url + Orename))
	{
		std::cout << "ERROR::ORE::FAILED TO LOAD TEXTURE" << std::endl;
	}
}

void Crystal::initSprite()
{
	sprite.setTexture(texture);
	sprite.setOrigin(static_cast<sf::Vector2f>(sprite.getTexture()->getSize()) / 2.f);
	sprite.setPosition(position);

}

Collider Crystal::getCollider()
{
	return Collider(sprite);
}

 sf::Vector2f Crystal::getPosition() const
{
	return position;
}
 int Crystal::getValue() const
 {
	 return value;
 }