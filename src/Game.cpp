#include "Game.h"

Game::Game()
{
	this->initVariables();
	this->initWindow();
	//this->initTextures();
	this->initPlayer();
	
	this->initFonts();
	this->initText();
	this->spawnFossiles();
	this->initShader();
	this->initGameWorld();
	
	//player->setPosition(100,gameWorld->getgridLenth() );
}
Game::~Game()
{
	delete this->window;
	delete this->player;

	for (auto& i : this->textures) {
		delete i.second;
	}

	delete this->gameWorld;
}

void Game::run()
{
	while (this->window->isOpen())
	{
		gameWorld->updateTime();
		this->update();
		this->render();
	}
}
//sf::Clock globalClock;
void Game::render()
{
	std::string s = "The name Tyrannosaurus means king of the tyrant lizards";
	std::cout << "size of string" << s.size() << std::endl;
	this->window->clear(sf::Color(135,206,235));
	this->gameWorld->render(*this->window, &shader, player->getPos());
	this->renderFossiles();
	this->player->render(*this->window);
	/*mapdemo.load("C:/Users/MSI/Downloads/earthcenter/Textures/demo.tmx");
	MapLayer layerZero(mapdemo, 0);
	MapLayer layerOne(mapdemo, 1);
	sf::Time duration = globalClock.getElapsedTime();
	layerZero.update(duration);
	window->draw(layerZero);
	window->draw(layerOne);*/
	/*sf::Sprite test;
	sf::Texture test2;
	test2.loadFromFile()*/
	this->gameWorld->renderTimerText(*this->window);
	this->renderFossilsPopup();
	this->window->setView(view);
	this->window->display();
}

void Game::update()
{
	this->pollEvents();

	gameWorld->updateTimerText(player->getPos());
	if (!this->endGame || !this->pause)
	{
		this->updateInput();
		this->updateCollision();
		this->player->update();
		this->updateView();
		this->updateMousePosition();
		//this->updateText();

	}

	if (this->gameWorld->getMaxTimer() < this->gameWorld->getTimer())
	{
		this->endGame = true;


	}
	if (this->health <= 0)
	{
		this->endGame = true;
	}
	std::cout << "playerpos" << player->getPos().y << std::endl;
	std::cout << "endpos" << gameWorld->getgridLenth() << std::endl;

}



//INIT FUNCTIONS 
void Game::initWindow()
{
	//this->view.setCenter(0.f, 0.f);
	this->view.setSize(VIEW_HEIGHT, VIEW_HEIGHT);
	this->videoMode.height = 600;
	this->videoMode.width = 600;
	this->window = new sf::RenderWindow(this->videoMode, "Game 3", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	texturerender.create(600, 600);
	this->window->setFramerateLimit(120);
	this->window->setVerticalSyncEnabled(false);
}
void Game::initPlayer()
{
	this->player = new Player();

}
void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("C:/Users/MSI/Downloads/game3/Textures/bullet.png");
		
}
void Game::initFonts()
{
	if (!this->font.loadFromFile("C:/Users/MSI/Downloads/game3/Fonts/Dosis-Light.ttf"))
	{
		std::cout << "ERROR ::GAME:: failed to load font" << std::endl;
	}
}
void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(12);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("None");
}
void Game::initGameWorld()
{
	this->gameWorld = new GameWorld();
}

void Game::initVariables()
{
	this->window = nullptr;
	VIEW_HEIGHT = 600;
	this->points = 0;
	this->mouseHeld = false;
	this->popup = false;
	this->health = 10;
	this->endGame = false;
	this->pause = false;

}
void Game::initShader()
{
	if (!this->shader.loadFromFile("C:/Users/MSI/Downloads/earthcenter/Textures/vertex_shader.vert", "C:/Users/MSI/Downloads/earthcenter/Textures/fragment_shader.frag"))
		std::cout << "ERROR ::Game::init texture:: failed to load shader" << std::endl;
}



//UPDATE FUNCTIONS
void Game::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f,DeltaTime());
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f, DeltaTime());
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f, DeltaTime());
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f, DeltaTime());
}
void Game::updateText()
{
	std::stringstream ss;
	ss << "Points: " << this->points << "\n"
		<< "Health: " << this->health << "\n";

	this->uiText.setString(ss.str());
}

void Game::updateMousePosition()
{
	this->mousPosition = sf::Mouse::getPosition(*this->window);
	this->mousPositionView = this->window->mapPixelToCoords(this->mousPosition);
}
void Game::updateView()
{
	bool middle = true;
	std::cout << view.getCenter().x - view.getSize().x /2  << std::endl;
	//left
	if (player->getPos().x - view.getSize().x / 2 <= 0) {
		view.setCenter(view.getSize().x / 2, player->getPos().y);
		middle = false;
	}
	//right
	else if (player->getPos().x + view.getSize().x / 2 >= gameWorld->getgridWidth())
	{
		view.setCenter(gameWorld->getgridWidth() -view.getSize().x / 2, player->getPos().y);
		middle = false;
	}
	//bottom
	if (player->getPos().y + view.getSize().y / 2 >= gameWorld->getgridLenth() && player->getPos().x - view.getSize().x / 2 <= 0)
	{
		//view.setCenter(player->getPos());
		view.setCenter(view.getSize().x / 2, gameWorld->getgridLenth() - view.getSize().y / 2);
		middle = false;
	}
	else if (player->getPos().y + view.getSize().y / 2 >= gameWorld->getgridLenth() && player->getPos().x + view.getSize().x / 2 >= gameWorld->getgridWidth())
		
	{
		//view.setCenter(player->getPos());
		view.setCenter(gameWorld->getgridWidth() - view.getSize().x / 2, gameWorld->getgridLenth() - view.getSize().y / 2);
		middle = false;
	}
	else
	  if(player->getPos().y+view.getSize().y/2>=gameWorld->getgridLenth())
	{
		//view.setCenter(player->getPos());
		 view.setCenter(player->getPos().x, gameWorld->getgridLenth()-view.getSize().y / 2);
		 middle = false;
	}

	 
	if(middle)
	{
		//view.setCenter(player->getPos().x, view.getSize().y / 2);
		 view.setCenter(player->getPos());
	}
	std::cout << "player->getPos().y+view.getSize().y/2: " << player->getPos().y + view.getSize().y / 2 << std::endl;
}

void Game::updateCollision()
{
	if (player->getBounds().left < 0.f)
	{
		std::cout << "left: " << player->getBounds().left << "width" << player->getBounds().width;
		player->setPosition(0.f, player->getBounds().top);
	}
	else if (player->getBounds().left + player->getBounds().width >= gameWorld->getgridWidth() )
	{
		std::cout << "left: " << player->getBounds().left << "width" << player->getBounds().width;
		player->setPosition(gameWorld->getgridWidth()  - player->getBounds().width, player->getBounds().top);
	}

	if (player->getBounds().top < 0.f)
	{
		player->setPosition(player->getBounds().left, 0.f);
	}
	else if (player->getBounds().top + player->getBounds().height >= gameWorld->getgridLenth() )
	{
		player->setPosition(player->getBounds().left, gameWorld->getgridLenth()  - player->getBounds().height);
	}

}


int i = 0;
//RENDER FUNCTIONS
void Game::renderFossilsPopup()
{
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !popup)
	{

		bool deleted = false;
		for (i = 0; i < this->fossiles.size()&&!popup ; i++)
		{
			if (this->fossiles[i]->getSprite().getGlobalBounds().contains(this->mousPositionView))
			{
				deleted = true;

				this->points += 1;

				fossiles[i]->initPopUpSprite(view.getCenter());
				fossiles[i]->updatePopup();

				fossiles[i]->renderPopUp(*this->window);
				this->popup = true;

				std::cout << "points: " << this->points << std::endl;
			}
		}
		i--;
	}
	else if (popup)
	{
		fossiles[i]->initPopUpSprite(view.getCenter());
		fossiles[i]->renderPopUp(*this->window);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		/*if (popup) {
			delete fossiles[i];
			fossiles.erase(fossiles.begin() + i);
		}*/
		
		popup = false;
		PopUpChanged = true;

	}
}
void Game::renderFossiles()
{
	for (auto* f : this->fossiles)
	{

		f->render(*this->window);
	}
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}



//GETERS
const bool Game::getEndGame()const
{
	return this->endGame;
}
const bool Game::getPopUpChanged() const
{
	return PopUpChanged;
}
const bool Game::getWindowIsOpen()const
{
	return this->window->isOpen();
}




void Game::pollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed)
			this->window->close();

		if (this->event.type == sf::Event::KeyPressed)
		{
			if (this->event.key.code == sf::Keyboard::K)
			{
				this->window->close();

			}
		}
		if (this->event.type == sf::Event::Resized)
		{
			resize();
		}
	}
}

void Game::resize()
{
	float aspectRatio = float(window->getSize().x) / float(window->getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int Game::random(int const nbMin, int const nbMax)
{
	static std::default_random_engine engine;
	std::uniform_int_distribution<> distribution(nbMin, nbMax);

	return distribution(engine);
}
void Game::spawnFossiles()
{
	std::string dino_name = "";
	this->fossiles.resize(3);
	for (int i = 0;i < 3;i++) {
		if (i == 0) { dino_name = "Parasaurolophus.png"; }
		else if(i==1){ dino_name = "Triceratops.png"; }
		else{ dino_name = "trex.png"; }
		sf::Vector2f pos(static_cast<float>(rand() % static_cast<int>(33*288 - 1200)),
			random(4 * 288, 12 * 288));
		this->fossiles[i] = (new Fossil(dino_name, pos));
	}


}
float Game::DeltaTime()
{
	return sclock.restart().asSeconds();
}