#include"Collectable.h"

Collectable::Collectable(sf::Sprite& sprite,int value):
	value{ value }, sprite{sprite}
{
}

Collectable::~Collectable()
{
}

void Collectable::getCollected(std::string const& name)
{
	audiomanager->playMusic(name);
}


 sf::Sprite Collectable::getSprite() const
{
	return sprite;
}

 int Collectable::getValue() const
 {
	 return value;
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
