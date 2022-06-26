#pragma once
#include<SFML/Graphics.hpp>
#include"Collectable.h"
#include"AudioManager.h"
class Magnet:public Collectable
{
public:
	Magnet(sf::Vector2f  const& position, std::string const& name);
	virtual~Magnet() = default;
	 void render(sf::RenderTarget& target) override;
	
	 Collider getCollider() 		       override;
	 void initTexture(std::string const& name) override;
	 void initSprite() override;
	 void collected(Player & player)  override;
	 std::string test() 			       override;
	
	 sf::Vector2f getPosition()const;
										 
private:
	sf::Vector2f position;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::String name;
};
