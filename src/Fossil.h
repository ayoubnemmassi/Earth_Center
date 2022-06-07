#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <iostream>
#include <map>
#include"AudioManager.h"

class Fossil
{
public:

	Fossil(std::string const&,sf::Vector2f);

	void initPopUpTexture();
	void initPopUpSprite(const sf::Vector2f& playerPos);
	void update();
	void updatePopup();
	void render(sf::RenderTarget& target);
	void renderPopUp(sf::RenderTarget& target);
	void initTrexinfo();
	void initParainfo();
	void initTricinfo();
	void initinfotext(std::string info);
	void gotCollected();
	std::string getQuestionFromFossils()const;
	std::string getName() const;
	
	const sf::Sprite getSprite() const;
	 int getInfoNumber() const;
private:

	sf::Text infotext;
	sf::Font infoFont;
	sf::Sprite sprite;
	sf::Sprite popup;
	sf::Texture texture;
	sf::Texture texturePopUp;
	sf::Vector2f pos;
	std::map<std::string, Fossil> informations;
	std::string name;
	std::vector<std::string> trextinfo;
	std::vector<std::string> parainfo;
	std::vector<std::string> tricinfo;

	int randomnumber;

	void initTexture(std::string name);
	void initSprite(std::string name);
	void initVariables();

	std::unique_ptr< AudioManager> audiomanager;
	void initAudiomanager();
	void initGamemusic();
};

