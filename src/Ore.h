#pragma once
#include<SFML/Graphics.hpp>
#include"Collectable.h"
#include"AudioManager.h"
class Ore:public Collectable
{
public:
	Ore(int const &value,sf::Vector2f const& position);
	virtual~Ore()=default;
	void update(Collider& other)override;
	void render(sf::RenderTarget& target)override;
	void getCollected()override;
	Collider getCollider()override;
	 sf::Vector2f getPosition()const;
private:
	sf::Vector2f position;
	sf::Sprite sprite;
	sf::Texture texture;
	void initTexture(std::string const& name);
	void initSprite();
	
	std::unique_ptr< AudioManager> audiomanager;
	void initAudiomanager();
	void initGamemusic();
};

