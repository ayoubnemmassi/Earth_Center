#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class Tile
{
public:
	Tile(std::string,float,float,bool,bool);
	~Tile();
	void update();
	void render(sf::RenderTarget& target,sf::Shader *shader=NULL,sf::Vector2f playerPos=sf::Vector2f());
	bool steUpSprite(std::string);
	

	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f pos;
	bool isFree;
	bool isExit;
private:



	
	//private functions
	void initTexture();
	void initSprite();
};

