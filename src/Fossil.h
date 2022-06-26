#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <iostream>
#include <map>
#include"AudioManager.h"
#include "pugixml.hpp"
#include <Collider.h>

class Fossil
{
public:


	Fossil(pugi::xml_node node, sf::Vector2f pos);

	void initPopUpTexture();
	void initPopUpSprite(const sf::Vector2f& playerPos);
	
	void updatePopup();
	void render(sf::RenderTarget& target);
	void renderPopUp(sf::RenderTarget& target);

	void initinfo(pugi::xml_node node);
	void initinfotext(std::string info);
	void gotCollected();
	std::string getQuestionFromFossils()const;
	std::string getName() const;
	
	const sf::Sprite getSprite() const;
	 int getInfoNumber() const;
	 sf::Vector2f getDistance(Collider& other) const;
	 void setPosition(sf::Vector2f pos);
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
	std::vector<std::string> fossilInfo;

	int randomnumber;

	void initTexture(std::string name);
	void initSprite(std::string name);
	void initVariables();

	std::unique_ptr< AudioManager> audiomanager;
	void initAudiomanager();
	void initGamemusic();
};

