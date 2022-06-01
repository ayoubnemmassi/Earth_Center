#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <ctime>
#include <iostream>
#include <sstream>
class Player
{
public:
	Player();
	~Player();
	void update();
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL);
	void move(const float dirX, const float dirY,float deltatime);
	void updateAttack();
	const bool canAttack();
	const sf::Vector2f& getPos()const;
	const sf::FloatRect getBounds() const;
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);

private:
	sf::Sprite sprite;
	sf::Texture texture;
	float movementSpeed;
	float attackCooldown;
	float attackCooldownMax;

	//private functions
	void initTexture();
	void initSprite();
	void initVariables();
};

