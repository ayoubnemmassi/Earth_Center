#pragma once
#include<SFML/Graphics.hpp>
#include"Collider.h"
#include"AudioManager.h"
class Collectable
{
public:
	Collectable(sf::Sprite& sprite,int value);
	~Collectable();

	virtual void getCollected(std::string const& name);
	virtual void render(sf::RenderTarget &target)=0;
	virtual void update(Collider& other)=0;
	virtual Collider getCollider()=0;
	virtual std::string test() = 0;
	  sf::Sprite getSprite()const;
	  int getValue()const;
protected:
	
	  virtual void initAudiomanager();
	  virtual void initGamemusic(std::string const & name);
	
	
private:
	std::unique_ptr< AudioManager> audiomanager;
	int value;
	sf::Sprite sprite;
};

