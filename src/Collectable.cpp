#include"Collectable.h"

Collectable::Collectable(sf::Sprite& sprite):
	 sprite{sprite}
{
}





 sf::Sprite Collectable::getSprite() const
{
	return sprite;
}



 void Collectable::initAudiomanager()
 {
	 audiomanager = std::make_unique<AudioManager>();
 }

 void Collectable::initGamemusic(std::string const & name)
 {
	 std::string url = "resources/Textures/";
	 audiomanager->addMusic(name, url+name+".ogg");
	 
 }
