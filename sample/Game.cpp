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
void Game::render()
{
	this->window->clear(sf::Color(135,206,235));
	this->gameWorld->render(*this->window, &shader, player->getPos());
	this->renderFossiles();
	this->player->render(*this->window);
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


}



//INIT FUNCTIONS 
void Game::initWindow()
{
	this->view.setCenter(0.f, 0.f);
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
	view.setCenter(player->getPos());
}

void Game::updateCollision()
{
	if (player->getBounds().left < 0.f)
	{
		std::cout << "left: " << player->getBounds().left << "width" << player->getBounds().width;
		player->setPosition(0.f, player->getBounds().top);
	}
	else if (player->getBounds().left + player->getBounds().width >= gameWorld->getgridWidth() * 288)
	{
		std::cout << "left: " << player->getBounds().left << "width" << player->getBounds().width;
		player->setPosition(gameWorld->getgridWidth() * 288 - player->getBounds().width, player->getBounds().top);
	}

	if (player->getBounds().top < 0.f)
	{
		player->setPosition(player->getBounds().left, 0.f);
	}
	else if (player->getBounds().top < 0.f + player->getBounds().height >= gameWorld->getgridLenth() * 288)
	{
		player->setPosition(player->getBounds().left, gameWorld->getgridLenth() * 288 - player->getBounds().height);
	}

}



//RENDER FUNCTIONS
void Game::renderFossilsPopup()
{
	int i = 0;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !popup)
	{

		bool deleted = false;
		for (i = 0; i < this->fossiles.size() && deleted == false; i++)
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

	}
	else if (popup)
	{
		fossiles[i]->initPopUpSprite(view.getCenter());
		fossiles[i]->renderPopUp(*this->window);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
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