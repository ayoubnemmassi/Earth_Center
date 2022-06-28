#include "GameWorld.h"
#include "GameWorld.h"
GameWorld::GameWorld(const Player &player)
{
	maxTimer = 300;
	firstLayer = 1, secondLayer = 8, thirdLayer =8, fourthLayer = 8, fifthLayer = 8;
	gridLength = firstLayer + secondLayer + thirdLayer + fourthLayer + fifthLayer;
	gridWidth = 30;
	layertiles = 8;
	setUpInitialState();
	initTextTimer("PixellettersFull.ttf");
	initskysprite();
	initGUI(player);
	maxCooldown = 50.f;
	cooldown = 0.f;	
}

GameWorld::~GameWorld()
{
}


//INIT FUNCTIONS
void GameWorld::initTextTimer(std::string font_name)
{
	std::string url = "resources/Fonts/";

	if (!timerFont.loadFromFile(url + font_name))
		std::cout << "gameworld :: cant load " << font_name << std::endl;

	timerText.setFont(timerFont);
	this->timerText.setCharacterSize(50);
	this->timerText.setFillColor(sf::Color::Red);
	this->timerText.setString("none");
}

void GameWorld::initskysprite()
{
	std::string url = "resources/Textures/";
	if(!skyTexture.loadFromFile(url + "sky.jpg"))std::cout<<"mased9atch"<<std::endl;
	sky.setTexture(skyTexture);
	sky.setPosition(0, -sky.getGlobalBounds().height);
}
void GameWorld::initGUI(const Player& player)
{
	this->playerHpBar.setSize(sf::Vector2f(200.f, 30.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBackground = this->playerHpBar;
	this->playerHpBackground.setFillColor(sf::Color(25, 25, 25, 200));


}


//RENDER FUNCTOINS
void GameWorld::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f playerPos)
{
	
	for (int i = 0; i < gridLength;i++)
	{
		for (int j = 0;j < gridWidth;j++)
		{
			if (shader) {
				if(playerPos.y< 288 * 3)
				{
					shader->setUniform("ambient", sf::Glsl::Vec4(1-(playerPos.y*0.001), 1 - (playerPos.y * 0.001), 1 - (playerPos.y * 0.001), 1));
				}
				else if(playerPos.y>288*3)
				{
					//std::cout << "r: " << r << " b: " << b << std::endl;
					shader->setUniform("ambient", sf::Glsl::Vec4(0.2,0.2,0.5,1));

				}
				shader->setUniform("hasTexture", true);
				shader->setUniform("lightPos", playerPos);
				target.draw(tiles[i][j]->sprite, shader);
			}
			else
				target.draw(tiles[i][j]->sprite);
		}
	}
	
	//target.draw(sky);
}

void GameWorld::renderTimerText(sf::RenderTarget& target)
{
	target.draw(timerText);
}


void GameWorld::renderGUI(sf::RenderTarget& target, float view_h)
{

	this->playerHpBar.setPosition(target.getView().getCenter().x - view_h / 2, target.getView().getCenter().y - 310.f);
	this->playerHpBackground.setPosition(target.getView().getCenter().x - view_h / 2, target.getView().getCenter().y - 310.f);
	target.draw(this->playerHpBackground);
	target.draw(this->playerHpBar);
}


//UPDATE FUNCTIONS
void GameWorld::updateTime()
{
	timer= clock.getElapsedTime().asSeconds();
	
	system("cls");
	
}
void GameWorld::updateGUI( Player  &player)
{
	if (this->cooldown < this->maxCooldown)
		this->cooldown += 0.5f;
	
	float hpPercent = static_cast<float>(player.getHp()) / static_cast<float>(player.getHpMax());
	this->playerHpBar.setSize(sf::Vector2f(playerHpBackground.getSize().x * hpPercent, playerHpBar.getSize().y));
}

void GameWorld::updateTimerText(const sf::Vector2f &player_pos,float view_h)	
{
	
	std::cout << "view_h:" << view_h << std::endl;
	timerText.setString(std::to_string((int)timer)+"s");
	timerText.setPosition(player_pos.x - view_h/2, player_pos.y +230.f);
	
}


//SETUP FUNCTIONS
void GameWorld::setUpInitialState()
{
	exitPos = sf::Vector2i(1, 0);
	playerPos = sf::Vector2i(gridWidth-1,gridWidth-1);

//RESIZE TILES FOR OPTIMIZATION
	this->tiles.resize(gridLength);
	for (int x = 0; x < gridLength; x++)
	{
		this->tiles[x].resize(gridWidth);
		
	}
	
	setUpTiles();
}

void GameWorld::setUpEnemyPositions()
{
	enemyPos.clear();
	enemyPos.push_back(sf::Vector2i(0,2));
	enemyPos.push_back(sf::Vector2i(6,0));
	enemyPos.push_back(sf::Vector2i(2,7));

}

void GameWorld::setUpTiles()
{
	int tilew=0;
	int tileh=0;
	std::string url = "resources/Textures/";
	std::string tile = "";

	for (int i = 0; i < gridLength;i++)
	{
		if(i<firstLayer){ tile = "grass1.png"; }
		else if(i<=secondLayer&&i>=firstLayer){ tile = "dirt.png"; }
		else if(i<=thirdLayer+secondLayer ){ tile = "darkdirt.png"; }
		else if(i<=fourthLayer+thirdLayer+secondLayer ){ tile = "darkdirt2.png"; }
		else if(i<=fifthLayer+fourthLayer+thirdLayer+secondLayer ){ tile = "solid.png"; }
		 
		tilew = 0;
		for (int j = 0;j < gridWidth ;j++)
		{
			
			tiles[i][j] = std::make_unique< Tile>(url+tile, tilew, tileh, false, false);
			tilew += 288;

		}
		tileh += 288;
	}
}


//GETERS
const int GameWorld::getgridLength() const
{
	return gridLength*tiles[1][1]->sprite.getGlobalBounds().height;
}

const int GameWorld::getLayerLength() const
{
	return layertiles * tiles[1][1]->sprite.getGlobalBounds().height;
}

const int GameWorld::getgridWidth() const
{
	return gridWidth* tiles[1][1]->sprite.getGlobalBounds().width;
}

const float GameWorld::getMaxTimer() const
{
	return maxTimer;
}

const float GameWorld::getTimer() const
{
	return timer;
}

const bool GameWorld::playerGotDamaged()
{
	if (this->cooldown >= this->maxCooldown)
	{
		this->cooldown = 0.f;
		return true;
	}
	return false;
}