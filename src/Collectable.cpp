#include"Collectable.h"

Collectable::Collectable(sf::Sprite& sprite,int value):
	value{ value }, sprite{sprite}
{
}

Collectable::~Collectable()
{
}


 sf::Sprite Collectable::getSprite() const
{
	return sprite;
}

 int Collectable::getValue() const
 {
	 return value;
 }
