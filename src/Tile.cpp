#include "Tile.h"

Tile::Tile(std::string textureName ,float x, float y, bool passable,bool exit)
{
	if (!steUpSprite(textureName))
	{
		return;
	}
	this->pos = sf::Vector2f(x, y);
	this->sprite.setPosition(pos);
	this->isFree = passable;
	this->isExit = exit;
	/*this->initTexture();
	this->initSprite();*/
}

bool Tile::steUpSprite(std::string textureName)
{
	if (!this->texture.loadFromFile(textureName))
	{
		std::cout << "ERROR ::Map::init texture:: failed to load texture" << std::endl;
		return false;
		
	}
	this->texture.setSmooth(true);
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(sf::IntRect(0,0,288,288));
	return true;
}

Tile::~Tile()
{
}

void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target, sf::Shader* shader , sf::Vector2f playerPos)
{
	shader->setUniform("hasTexture", true);
	shader->setUniform("lightPos", playerPos);
	target.draw(this->sprite);
}

void Tile::initTexture()
{
	if (!this->texture.loadFromFile("resources/Textures/Tile_5.png"))
		std::cout << "ERROR ::Map::init texture:: failed to load texture" << std::endl;
}

void Tile::initSprite()
{
	this->sprite.setTexture(this->texture);
}

