#include"AudioManager.h"
#include <iostream>
AudioManager::AudioManager()
{
}

void AudioManager::addSound(std::string name, std::string url)
{
	this->sounds[name] = std::make_shared<sf::Sound>();
	sf::SoundBuffer sound_buffer;
	if(!sound_buffer.loadFromFile(url))std::cout<<"AUDIOMANAGER::FAILED TO LOAD BUFFER FILE"<<std::endl;
	this->sounds[name]->setBuffer(sound_buffer);
}

void AudioManager::addMusic(std::string name, std::string url)
{
	this->musics[name] = std::make_shared<sf::Music>();
	this->musics[name]->openFromFile(url);
}

void AudioManager::playMusic(std::string name)
{
	if(this->musics[name]->getStatus()!= this->musics[name]->Playing &&name!="collect")
	this->musics[name]->play();
	else if(name=="collect")
	{
		this->musics[name]->stop();
		this->musics[name]->play();
	}
}

void AudioManager::playSound(std::string name)
{
	if (this->sounds[name]->getStatus() != this->sounds[name]->Playing)
		this->sounds[name]->play();
}
void AudioManager::stopMusic(std::string name)
{
	
		this->musics[name]->stop();
}

void AudioManager::stopSound(std::string name)
{
	
		this->sounds[name]->stop();
}
std::map<std::string, std::shared_ptr<sf::Sound>> AudioManager::getSounds() const
{
	return sounds;
}

std::map<std::string, std::shared_ptr<sf::Music>> AudioManager::getMusics()const
{
	return musics;

}




