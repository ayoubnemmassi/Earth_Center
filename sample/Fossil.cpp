#include "Fossil.h"
#include "Fossil.h"
#include "Fossil.h"
#include"Fossil.h"

Fossil::Fossil()
{
}

Fossil::Fossil(std::string name,sf::Vector2f pos)
{
	this->name = name;
	initTexture(name);
	initSprite(name);
	initPopUpTexture();
	
	sprite.setPosition(pos);
	randomnumber = 0;
	if (name == "Parasaurolophus.png") { initParainfo(); }
	if (name == "trex.png") { initTrexinfo();  }
	if (name == "Triceratops.png") { initTricinfo();  }
}

Fossil::~Fossil()
{
}

void Fossil::update()
{
}

void Fossil::updatePopup()
{
	randomnumber = rand() % 2;
}

void Fossil::render(sf::RenderTarget& target)
{
	target.draw(sprite);
}

void Fossil::renderPopUp(sf::RenderTarget& target)
{

	//printf(popup.ge)
	if (name == "Parasaurolophus.png") {  initinfotext(parainfo[randomnumber]); }
	if (name == "trex.png") {  initinfotext(trextinfo[randomnumber]); }
	if (name == "Triceratops.png") {  initinfotext(tricinfo[randomnumber]); }
	
	target.draw(popup);
	target.draw(infotext);
}

void Fossil::initTrexinfo()
{
	trextinfo.push_back("The name 'Tyrannosaurus' means 'king of the tyrant lizards");
	trextinfo.push_back("The T-Rex is believed to have had the strongest bite of any land animal roughly 12,814 pounds of force");
	trextinfo.push_back("The T-Rex was given its names in 1905 by the then president of the American Museum of Natural History Henry Fairfield");

}

void Fossil::initParainfo()
{
	parainfo.push_back("The name Parasaurolophus means: “Near Crested Lizard");
	parainfo.push_back("has an estimated length of 31 feet");
	parainfo.push_back("has an estimated weight of 2.8 tons");
	
	
	
}

void Fossil::initTricinfo()
{
	tricinfo.push_back("The Triceratops can be up to 9 meters long or 29.52 feet");
	tricinfo.push_back("It weighed around 12 metric tons or 12,000 kilograms");
	tricinfo.push_back("The Triceratops can run up to 32 kilometers per hour");
}

void Fossil::initinfotext(std::string info)
{
	if (!infoFont.loadFromFile("C:/Users/MSI/Downloads/earthcenter/Fonts/FontFile.ttf")) 
	{
		std::cout << "error" << std::endl;
	}
	infotext.setFont(infoFont);
	infotext.setFillColor(sf::Color::Black);
	infotext.setCharacterSize(35);
	infotext.setString(info);
	infotext.setOrigin(infotext.getGlobalBounds().width / 2, infotext.getGlobalBounds().height / 2);
	infotext.setPosition(popup.getPosition().x+popup.getGlobalBounds().width/2, popup.getPosition().y + popup.getGlobalBounds().height / 2);


}



void Fossil::initTexture(std::string name)
{
	std::string url = "C:/Users/MSI/Downloads/earthcenter/Textures/";
	if (!this->texture.loadFromFile(url+name))
		std::cout << "ERROR ::Player::init texture:: failed to load texture" << std::endl;
}
void Fossil::initSprite(std::string name)
{
	
	this->sprite.setTexture(this->texture);
	if (name.compare("Triceratops.png")|| name.compare("Parasaurolophus.png")) { this->sprite.scale(0.6f, 0.6f); }
	//if (name.compare("Triceratops.png")) { this->sprite.scale(0.7f, 0.7f); }
	else {
		this->sprite.scale(0.2f, 0.2f);
	     }

}

void Fossil::initPopUpTexture()
{
	if (!this->texturePopUp.loadFromFile("C:/Users/MSI/Downloads/earthcenter/Textures/popupwood.png"))
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
}

const sf::Sprite Fossil::getSprite() const
{
	return this->sprite;
}