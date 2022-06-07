#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <ctime>
#include <iostream>
#include <sstream>
#include "Collider.h"
class Player
{
public:
	Player(const std::string &name,const std::string & spriteurl);
	virtual ~Player()=default;
	void update();
	void render(sf::RenderTarget& target, sf::Shader* shader = nullptr);
	void move(const float dirX, const float dirY,float deltatime);
	void updateAttack();
	void updateHp(const int &timer);
	const bool canAttack();
	const sf::Vector2f& getPos()const;
	const sf::FloatRect getBounds() const;
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	void drill(Collider &other);
	void collectOre(int value);
	std::string getName()const;
	std::string getSpriteURL()const;
	int getHp()const;
	int getHpMax()const;
	Collider getCollider();
	void loseHp(int value);
	void gainHp(int value);
	

private:

	std::string name;
	std::string spriteURL;
	sf::Sprite sprite;
	sf::Texture texture;
	float movementSpeed;
	float attackCooldown;
	float attackCooldownMax;

	int hp;
	int hpmax;
	int collectedores;
	

	//private functions
	void initTexture();
	void initSprite();
	void initVariables();
	
};

