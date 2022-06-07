#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<vector>
#include<map>
class AudioManager
{
public:
	AudioManager();
	virtual ~AudioManager()=default;
	void addSound(std::string name,std::string url);
	void addMusic(std::string name, std::string url);
	void playMusic(std::string name);
	void playSound(std::string name);
	void stopMusic(std::string name);
	void stopSound(std::string name);
	std::map<std::string , std::shared_ptr<sf::Sound>> getSounds() const;
	std::map<std::string , std::shared_ptr<sf::Music>> getMusics() const;
	//std::vector<std::unique_ptr<sf::SoundBuffer>> getsoundBuffers();

private:
	std::map<std::string ,std::shared_ptr<sf::Sound>>  sounds;
	std::map<std::string ,std::shared_ptr<sf::Music>>  musics;
	//std::vector<std::unique_ptr<sf::SoundBuffer>>  soundBuffers;
}
;
