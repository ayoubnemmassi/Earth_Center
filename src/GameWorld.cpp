#include "GameWorld.h"
GameWorld::GameWorld()
{
	maxTimer = 200;
	firstLayer = 1, secondLayer = 8, thirdLayer =8, fourthLayer = 8, fifthLayer = 8;
	gridLenth = firstLayer + secondLayer + thirdLayer + fourthLayer + fifthLayer;
	gridWidth = 30;
	setUpInitialState();
	initTextTimer("PixellettersFull.ttf");
	initskysprite();
}

GameWorld::~GameWorld()
{
}


//INIT FUNCTIONS
void GameWorld::initTextTimer(std::string font_name)
{
	std::string url = "C:/Users/MSI/Downloads/earthcenter/Fonts/";

	if (!timerFont.loadFromFile(url + font_name))
		std::cout << "gameworld :: cant load " << font_name << std::endl;

	timerText.setFont(timerFont);
	this->timerText.setCharacterSize(50);
	this->timerText.setFillColor(sf::Color::Red);
	this->timerText.setString("none");
}

void GameWorld::initskysprite()
{
	std::string url = "C:/Users/MSI/Downloads/earthcenter/Textures/";
	if(!skyTexture.loadFromFile(url + "sky.jpg"))std::cout<<"mased9atch"<<std::endl;
	sky.setTexture(skyTexture);
	sky.setPosition(0, -sky.getGlobalBounds().height);
}



//RENDER FUNCTOINS
void GameWorld::render(sf::RenderTarget& target, sf::Shader* shader, sf::Vector2f playerPos)
{
	
	for (int i = 0; i < gridLenth;i++)
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


//UPDATE FUNCTIONS
void GameWorld::updateTime()
{
	timer= clock.getElapsedTime().asSeconds();
	system("cls");
	std::cout << this->timer << std::endl;
}

void GameWorld::updateTimerText(const sf::Vector2f &player_pos)
{
	
	timerText.setString(std::to_string(timer));
	
}


//SETIP FUNCTIONS
void GameWorld::setUpInitialState()
{
	exitPos = sf::Vector2i(1, 0);
	playerPos = sf::Vector2i(gridWidth-1,gridWidth-1);

//RESIZE TILES FOR OPTIMIZATION
	this->tiles.resize(gridLenth);
	for (int x = 0; x < gridLenth; x++)
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
	std::string url = "C:/Users/MSI/Downloads/earthcenter/Textures/";
	std::string tile = "";

	for (int i = 0; i < gridLenth;i++)
	{
		if(i<firstLayer){ tile = "grass1.png"; }
		else if(i<=secondLayer&&i>=firstLayer){ tile = "dirt.png"; }
		else if(i<=thirdLayer+secondLayer ){ tile = "darkdirt.png"; }
		else if(i<=fourthLayer+thirdLayer+secondLayer ){ tile = "darkdirt2.png"; }
		else if(i<=fifthLayer+fourthLayer+thirdLayer+secondLayer ){ tile = "solid.png"; }
		 
		tilew = 0;
		for (int j = 0;j < gridWidth ;j++)
		{
			
			tiles[i][j] = new Tile(url+tile, tilew, tileh, false, false);
			tilew += 288;

		}
		tileh += 288;
	}
}


//GETERS
const int GameWorld::getgridLenth() const
{
	return gridLenth*tiles[1][1]->sprite.getGlobalBounds().height;
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
