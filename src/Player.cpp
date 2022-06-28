#include "Player.h"



Player::Player(const std::string& name, const std::string& spriteurl):name{name},spriteURL{ spriteurl }
{
	
	this->initTexture();
	this->initSprite();
	this->initVariables();
	setPosition(600, 100);
	initAudiomanager();
}



const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}
void Player::update()
{
	std::cout << "hp: " << hp << "max hp :" << hpmax << std::endl;
	this->updateAttack();
	if (collectedores == 3)
	{
		resistance = 0.3;
		texture.loadFromFile("resources/Textures/bluetank.png");
		sprite.setTexture(texture);
	}
	else if(collectedores==6)
	{
		resistance = 0.6;
		texture.loadFromFile("resources/Textures/redtank.png");
		sprite.setTexture(texture);
	}
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
void Player::updateHp(const int &timer)
{

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
	ismagnet = false;
	this->movementSpeed =30.f;
	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;
	this->collectedores = 0;
	this->hpmax = 50;
	this->hp = this->hpmax;
	resistance = 0;
}
void Player::initAudiomanager()
{
	audiomanager = std::make_unique<AudioManager>();
}
void Player::initTexture()
{
	if(!this->texture.loadFromFile(spriteURL))
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

void Player::drill(Collider& other)
{
}

void Player::collectOre(int value)
{
	collectedores++;
	gainHp(value);
}

std::string Player::getName() const
{
	return name;
}

std::string Player::getSpriteURL() const
{
	return spriteURL;
}

float Player::getMouvementSpeed() const
{
	return movementSpeed;
}

int Player::getHp() const
{
	return hp;
}

int Player::getHpMax() const
{
	return hpmax;
}

 Collider Player::getCollider()
{
	return Collider(sprite);
}

 void Player::loseHp(int value)
 {
	 hp -= value-(resistance*value);
	 
 }

 void Player::gainHp(int value)
 {
	 if (hp >= hpmax)
	 {
		 hp = hpmax;
	 }
	 hp += value;
 }

 void Player::magnetCollected()
 {
	 ismagnet = true;
	 std::string magnetsound_url = "resources/Textures/magnet.ogg";
	 audiomanager->addMusic("magnet", magnetsound_url);
	 audiomanager->playMusic("magnet");
 }
 void Player::magnetUsed()
 {
	 ismagnet = false;
	 audiomanager->stopMusic("magnet");

 }

 bool Player::getMagnetStat() const
 {
	 return ismagnet;
 }