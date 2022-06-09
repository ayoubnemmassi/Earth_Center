#pragma once
#include<SFML/Graphics.hpp>
#include"Collectable.h"
#include"AudioManager.h"
class Ore:public Collectable
{
public:
	Ore(int const &value,sf::Vector2f const& position, std::string const& name);
	virtual~Ore()=default;
	void update(Collider& other)override;
	void render(sf::RenderTarget& target)override;
	void getCollected(std::string const& name)override;
	std::string test()override;
	Collider getCollider()override;
	sf::Vector2f getPosition()const;
private:
	sf::Vector2f position;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::String name;
	void initTexture(std::string const& name);
	void initSprite();
	

};

