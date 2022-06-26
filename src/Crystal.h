#pragma once
#include<SFML/Graphics.hpp>
#include"Collectable.h"
#include"AudioManager.h"

class Crystal:public Collectable
{
public:
	Crystal(int const &value,sf::Vector2f const& position, std::string const& name);
	virtual~Crystal()=default;
	void render(sf::RenderTarget& target)override;
	void collected(Player  & player)override;
	std::string test()override;
	Collider getCollider()override;
	sf::Vector2f getPosition()const;
	int getValue() const;
private:
	sf::Vector2f position;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::String name;
	int value;
	void initTexture(std::string const& name);
	void initSprite();
	

};

