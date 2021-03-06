#pragma once
#include <SFML/Graphics.hpp>

class Collider
{
public:
	Collider(sf::Sprite &body);
	
	void move(float dx, float dy);
	bool CheckCollision(Collider& other, float push);
	const sf::Vector2f getPosition()const;
	const sf::Vector2f getHalfSize()const;

	sf::Vector2f getDistance(Collider& other)const ;

private:
	sf::Sprite& body;
	sf::Vector2f distance;
};

