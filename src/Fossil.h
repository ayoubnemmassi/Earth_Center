#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <iostream>
#include <map>

class Fossil
{
public:
	Fossil();
	Fossil(std::string,sf::Vector2f);
	~Fossil();



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

	const sf::Sprite getSprite() const;
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
};

