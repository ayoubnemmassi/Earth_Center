#include "Fossil.h"


Fossil::Fossil(pugi::xml_node node,sf::Vector2f pos) :name{ node.attribute("name").value() },pos{pos}
{
	initVariables();
	initTexture(name);
	initSprite(name);
	initPopUpTexture();
	initAudiomanager();
	initGamemusic();
	sprite.setPosition(pos);
	initinfo(node);
}




void Fossil::updatePopup()
{
	 randomnumber = rand() % 3;
}

void Fossil::render(sf::RenderTarget& target)
{
	target.draw(sprite);
}

void Fossil::renderPopUp(sf::RenderTarget& target)
{


	initinfotext(fossilInfo[randomnumber]);
	target.draw(popup);
	target.draw(infotext);
}


void Fossil::initinfo(pugi::xml_node node)
{
	for (auto child : node.children())
	{
		fossilInfo.push_back(child.attribute("text").value());
	}
	
}

void Fossil::initinfotext(std::string info)
{
	if (!infoFont.loadFromFile("resources/Fonts/FontFile.ttf")) 
	{
		std::cout << "error" << std::endl;
	}
	infotext.setFont(infoFont);
	infotext.setFillColor(sf::Color::Black);
	if(info.size()>60){ infotext.setCharacterSize(30); }
	else{ infotext.setCharacterSize(35); }
	infotext.setString(info);
	infotext.setOrigin(infotext.getGlobalBounds().width / 2, infotext.getGlobalBounds().height / 2);
	infotext.setPosition(popup.getPosition().x+popup.getGlobalBounds().width/2, popup.getPosition().y + popup.getGlobalBounds().height / 2);


}

void Fossil::gotCollected()
{
	audiomanager->playMusic("collectFossil");
}

std::string Fossil::getName() const
{
	return name;
}

std::string Fossil::getQuestionFromFossils()const
{
	
	return fossilInfo[randomnumber];
}



void Fossil::initTexture(std::string name)
{
	std::string url = "resources/Textures/";
	if (!this->texture.loadFromFile(url+name))
		std::cout << "ERROR ::Player::init texture:: failed to load texture" << std::endl;
}
void Fossil::initSprite(std::string name)
{
	
	this->sprite.setTexture(this->texture);

}

void Fossil::initPopUpTexture()
{
	if (!this->texturePopUp.loadFromFile("resources/Textures/popupwood.png"))
		std::cout << "ERROR ::Player::init texture:: failed to load texture" << std::endl;
	
}

void Fossil::initPopUpSprite(const sf::Vector2f &playerPos)
{
	popup.setTexture(texturePopUp);
	popup.setScale(0.2f, 0.2f);
	popup.setPosition(playerPos.x-(popup.getTexture()->getSize().x)*0.2/2, playerPos.y -( popup.getTexture()->getSize().y)*0.2 / 2);
}

void Fossil::initVariables()
{
	randomnumber=0;
}
void Fossil::initAudiomanager()
{
	audiomanager = std::make_unique<AudioManager>();
}

void Fossil::initGamemusic()
{
	std::string collect = "resources/Textures/fossilcollected.ogg";

	audiomanager->addMusic("collectFossil", collect);
}

const sf::Sprite Fossil::getSprite() const
{
	return this->sprite;
}

 int Fossil::getInfoNumber() const
{
	return randomnumber;
}
 sf::Vector2f Fossil::getDistance(Collider& other) const
 {
	 sf::Vector2f otherPosition = other.getPosition();
	 float deltaX = otherPosition.x - pos.x;
	 float deltaY = otherPosition.y - pos.y;
	 return sf::Vector2f(deltaX, deltaY);
 }
 void Fossil::setPosition(sf::Vector2f pos)
 {
	 this->pos = pos;
	 sprite.setPosition(this->pos);
 }