#include "Player.h"
Player::Player()
{
	
	this->initTexture();
	this->initSprite();
	this->initVariables();
	setPosition(600, 100);
}

Player::~Player()
{
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
		//sf::FloatRect(this->sprite.getGlobalBounds().left- this->sprite.getGlobalBounds().width/2, this->sprite.getGlobalBounds().top - this->sprite.getGlobalBounds().height / 2, this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().height);//this->sprite.getGlobalBounds().;
}
void Player::update()
{
	this->updateAttack();
}

void Player::render(sf::RenderTarget& target, sf::Shader* shader)
{
	if (shader) {
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", getPos());
		target.draw(this->sprite, shader);
	}
	else
		target.draw(this->sprite);

}
void Player::move(const float dirX, const float dirY,float deltatime)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}
void Player::updateAttack()
{
	if(this->attackCooldown<this->attackCooldownMax)
	this->attackCooldown += 0.5f;

}
const bool Player::canAttack()
{
	if(this->attackCooldown>=this->attackCooldownMax)
	{
		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}
const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}
void Player::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.scale(0.7f, 0.7f);
	this->sprite.setOrigin(static_cast<sf::Vector2f>(sprite.getTexture()->getSize() / static_cast<unsigned> (2)));

}
void Player::initVariables()
{
	this->movementSpeed = 15.f;
	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;
}
void Player::initTexture()
{
	if(!this->texture.loadFromFile("C:/Users/MSI/Downloads/earthcenter/Textures/redtank.png"))
		std::cout << "ERROR ::Player::init texture:: failed to load texture" << std::endl;
}


void Player::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x+getBounds().width/2, y+ getBounds().height / 2);
}

