#pragma once
#include<SFML/Graphics.hpp>
#include"Collider.h"
class Collectable
{
public:
	Collectable(sf::Sprite& sprite,int value);
	~Collectable();

	virtual void getCollected()=0;
	virtual void render(sf::RenderTarget &target)=0;
	virtual void update(Collider& other)=0;

	  virtual Collider getCollider()=0;
	 sf::Sprite getSprite()const;
	 int getValue()const;
	
private:
	int value;
	sf::Sprite sprite;
};

