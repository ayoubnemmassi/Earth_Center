#pragma once
#include<SFML/Graphics.hpp>
#include"Collider.h"
#include"AudioManager.h"
#include <Player.h>
class Collectable
{
public:
	Collectable(sf::Sprite& sprite);
	

	virtual void collected(Player & player)=0;
	virtual void render(sf::RenderTarget &target)=0;
	
	virtual Collider getCollider()=0;
	virtual void initSprite() = 0;
	virtual void initTexture(std::string const& Orename) = 0;
	virtual std::string test() = 0;
	  sf::Sprite getSprite()const;
	 
protected:
	
	  virtual void initAudiomanager();
	  virtual void initGamemusic(std::string const & name);
	
	
private:
	std::unique_ptr< AudioManager> audiomanager;

	sf::Sprite sprite;
};

