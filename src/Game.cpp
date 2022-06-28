#include "Game.h"
#include "Game.h"

/**
*constructeur / facade
*/
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initPlayer();
	this->initGameWorld();
	this->initShader();
	this->initFonts();
	this->initText();
	this->initFossiles();
	this->initObstacles(numberOfObstacles);
	this->initOres(maxores);
	this->initMagnets(10);
	this->initAudiomanager();
	this->initGamemusic();
	this->initFinish();

}


/*
* la methode qui lance le jeux
*/
void Game::run()
{
	while (this->window->isOpen())
	{
		gameWorld->updateTime();
		this->update();
		this->render();
	}
}

/*
* render all game objects in the window
*/
void Game::render()
{
	this->window->clear(sf::Color(135, 206, 235)); //supprimer l'ancien frame
	this->gameWorld->render(*this->window, &shader, player->getPos());
	this->renderFossiles();
	this->renderObstacles();
	this->renderOres();


	if (this->isfinish)
	{
		this->finish->render(*this->window);
	}

	
	this->mapdemo.load("resources/map.tmx");
	MapLayer layerZero(mapdemo, 0);
	//MapLayer layerOne(mapdemo, 1);
	sf::Time duration = globalClock.getElapsedTime();
	layerZero.update(duration);
	this->window->draw(layerZero);
	//this->window->draw(layerOne);
	this->player->render(*this->window);
	this->renderFossilsPopup();
	this->window->setView(view);
	this->gameWorld->renderTimerText(*this->window);
	this->gameWorld->renderGUI(*this->window, view_h);

	if (this->endGame)
	{
		this->window->draw(gameover);
	}
	if (player->getMagnetStat())
	{
		magnet_icon_texture.loadFromFile("resources/textures/magnet_mini.png");
		magnet_icon.setTexture(magnet_icon_texture);
		magnet_icon.setOrigin(magnet_icon.getGlobalBounds().width / 2.f, magnet_icon.getGlobalBounds().height / 2.f);
		magnet_icon.setPosition(view.getCenter().x + view_h/2-magnet_icon.getGlobalBounds().width/2 , view.getCenter().y + view.getSize().y/2- magnet_icon.getGlobalBounds().height/2);
		window->draw(magnet_icon);
	}
	this->window->display();
}

/*
* update game objects
*/
void Game::update()
{
	audiomanager->playMusic("background");

	this->pollEvents();
	int value = 19;
	value -= (int)gameWorld->getTimer() % 20;

	

	if (!this->endGame && !this->pause && !this->isfinish)
	{
		if (gameWorld->playerGotDamaged()) {

			player->loseHp(5);

		}

		this->updateInput();
		this->updateCollision();
		this->player->update();
		this->updateOres();
		this->updateObstacles();

		this->updateView();
		this->window->setView(view);
		this->gameWorld->updateTimerText(view.getCenter(), view_h);
		this->gameWorld->updateGUI(*player);
		updateFossils();
	}
	this->updateMousePosition();

	if (this->isfinish)
	{
		this->finish->Updatequiz(this->getMousPositionView(), view.getCenter());
		this->audiomanager->stopMusic("moving");
		audiomanager->stopMusic("background");
	}
	if (this->gameWorld->getMaxTimer() < this->gameWorld->getTimer())
	{
		this->endGame = true;

	}
	if (this->player->getHp() <= 0)
	{
		this->endGame = true;
		
	}
	if(this->endGame)
	{
		gameOver();
	}

}


/*
* init functions
*/
void Game::initWindow()
{

	this->view.setSize(VIEW_HEIGHT, VIEW_HEIGHT);
	this->videoMode.height = 600;
	this->videoMode.width = 600;
	this->window = std::make_unique< sf::RenderWindow>(this->videoMode, "Earth Center", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	texturerender.create(600, 600);
	this->window->setFramerateLimit(120);
	this->window->setVerticalSyncEnabled(false);
}
void Game::initPlayer()
{
	this->player = std::make_unique<Player>("spear", "resources/Textures/graytank.png");

}
void Game::initTextures()
{

}
void Game::initFonts()
{
	if (!this->font.loadFromFile("resources/Fonts/Dosis-Light.ttf"))
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
	this->gameWorld = std::make_unique<GameWorld>(*player);
	this->numberOfObstacles = gameWorld->getgridWidth() / 288;
	this->maxores = 30;
}

void Game::initVariables()
{
	this->isfinish = false;
	this->window = nullptr;
	VIEW_HEIGHT = 600;
	//this->points = 0;
	//this->mouseHeld = false;
	this->popup = false;
	this->endGame = false;
	this->pause = false;
	view_h = VIEW_HEIGHT;
}

void Game::gameOver()
{
	
	this->audiomanager->addMusic("gameover", "resources/Textures/gameover.ogg");
	this->audiomanager->stopMusic("moving");
	this->audiomanager->stopMusic("background");
	std::cout << "getstatus" << this->audiomanager->getMusics()["gameover"]->getStatus() << std::endl;
	
	this->audiomanager->playMusic("gameover");
	
	gameovertexture.loadFromFile("resources/Textures/gameover.png");
	gameover.setTexture(gameovertexture);
	gameover.setOrigin(gameover.getGlobalBounds().width / 2.f, gameover.getGlobalBounds().height / 2.f);
	gameover.setPosition(view.getCenter());
}

void Game::initObstacles(int numberOfObstacles)
{
	int x = 144;
	firstLayerObstacles.resize(numberOfObstacles);
	secondLayerObstacles.resize(numberOfObstacles);
	thirdLayerObstacles.resize(numberOfObstacles);
	for (int i = 0; i < numberOfObstacles; i++)
	{
		firstLayerObstacles[i] = std::make_unique<Obstacle>(sf::Vector2f(x, gameWorld->getLayerLength() + 288), 10);
		secondLayerObstacles[i] = std::make_unique<Obstacle>(sf::Vector2f(x, gameWorld->getLayerLength() * 2 + 288), 20);
		thirdLayerObstacles[i] = std::make_unique<Obstacle>(sf::Vector2f(x, gameWorld->getLayerLength() * 3 + 288), 30);
		x += 288;
	}



}

void Game::initOres(int maxores)
{
	//ores.resize(maxores);

	for (int i = 0; i < maxores; i++)
	{
		sf::Vector2f pos(random(144, gameWorld->getgridWidth() - 144),
			random(2 * 288 + 144, gameWorld->getgridLength() - 144));

		ores.push_back(CollectableFactory::createCollectable(1, 2, pos, "collect"));
	}


}
void Game::initMagnets(int maxMagnets)
{
	

	for (int i = 0; i < maxMagnets; i++)
	{
		sf::Vector2f pos(random(144, gameWorld->getgridWidth() - 144),
			random(2 * 288 + 144, gameWorld->getgridLength() - 144));

		ores.push_back(CollectableFactory::createCollectable(2, 2, pos, "collect"));
	}


}
void Game::initShader()
{
	if (!this->shader.loadFromFile("resources/Textures/vertex_shader.vert", "resources/Textures/fragment_shader.frag"))
		std::cout << "ERROR ::Game::init texture:: failed to load shader" << std::endl;
}

void Game::initFossiles()
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("resources/trex.xml");
	if (!result)
	{
		std::cerr << "Could not open file visage.xml because " << result.description() << std::endl;
		
	}
	std::string dino_name = "";
	//this->fossiles.resize(1);
	/*for (int i = 0; i < 3; i++) {
		if (i == 0) { dino_name = "Parasaurolophus.png"; }
		else if (i == 1) { dino_name = "Triceratops.png"; }
		else { dino_name = "trex.png"; }
		sf::Vector2f pos(random(0, 30 * 288 - 720),
			random(4 * 288, gameWorld->getLayerLength() * 3 + 288));
		this->fossiles[i] = std::make_unique<Fossil>(dino_name, pos);
	}*/
	
	for (auto child : doc.child("Fossils").children())
	{
		sf::Vector2f pos(random(0, 30 * 288 - 720),
			random(4 * 288, gameWorld->getLayerLength() * 3 + 288));
		this->fossiles.push_back ( std::make_unique<Fossil>(child, pos));
	}
}

void Game::initAudiomanager()
{
	audiomanager = std::make_unique<AudioManager>();
}

void Game::initGamemusic()
{
	std::string bgmusic_url = "resources/Textures/backgroundmusic.ogg";
	std::string collect = "resources/Textures/collect.ogg";
	std::string movingsound_url = "resources/Textures/tank2.wav";
	std::string drillsound_url = "resources/Textures/drill.wav";

	audiomanager->addMusic("background", bgmusic_url);
	audiomanager->addMusic("collect", collect);
	audiomanager->addMusic("drill", drillsound_url);
	audiomanager->addMusic("moving", movingsound_url);

	audiomanager->getMusics()["moving"]->setPlayingOffset(sf::milliseconds(100));
	audiomanager->getMusics()["moving"]->setVolume(5);
	audiomanager->getMusics()["drill"]->setVolume(50);
	audiomanager->getMusics()["background"]->setVolume(30);
}

void Game::initFinish()
{
	finish = std::make_unique<Finish>(view.getCenter());
}


/*
* update functions
*/
void Game::updateInput()
{
	if (!this->isfinish) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			this->player->move(-1.f, 0.f, DeltaTime());
			audiomanager->playMusic("moving");
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			this->player->move(1.f, 0.f, DeltaTime());
			audiomanager->playMusic("moving");
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			this->player->move(0.f, -1.f, DeltaTime());
			audiomanager->playMusic("moving");
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			this->player->move(0.f, 1.f, DeltaTime());
			audiomanager->playMusic("moving");
		}
		/*
		* music stops when all keyboard inputs are not pressed
		*/
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			audiomanager->stopMusic("moving");
		}
	}
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

/*
* change la position de la camera pour fixer le player au centre
*/
void Game::updateView()
{
	bool middle = true;
	std::cout << view.getCenter().x - view.getSize().x / 2 << std::endl;
	//camera left collision
	if (player->getPos().x - view.getSize().x / 2 <= 0) {
		view.setCenter(view.getSize().x / 2, player->getPos().y);
		middle = false;
	}
	//camera right collision
	else if (player->getPos().x + view.getSize().x / 2 >= gameWorld->getgridWidth())
	{
		view.setCenter(gameWorld->getgridWidth() - view.getSize().x / 2, player->getPos().y);
		middle = false;
	}
	//camera bottom left collision
	if (player->getPos().y + view.getSize().y / 2 >= gameWorld->getgridLength() && player->getPos().x - view.getSize().x / 2 <= 0)
	{
		view.setCenter(view.getSize().x / 2, gameWorld->getgridLength() - view.getSize().y / 2);
		middle = false;
	}
	//camera bottom right collision
	else if (player->getPos().y + view.getSize().y / 2 >= gameWorld->getgridLength() && player->getPos().x + view.getSize().x / 2 >= gameWorld->getgridWidth())

	{
		view.setCenter(gameWorld->getgridWidth() - view.getSize().x / 2, gameWorld->getgridLength() - view.getSize().y / 2);
		middle = false;
	}
	//middle bottom
	else if (player->getPos().y + view.getSize().y / 2 >= gameWorld->getgridLength())
	{
		view.setCenter(player->getPos().x, gameWorld->getgridLength() - view.getSize().y / 2);
		middle = false;
	}
	
	if (middle)
	{
		view.setCenter(player->getPos());
	}
	std::cout << "player->getPos().y+view.getSize().y/2: " << player->getPos().y + view.getSize().y / 2 << std::endl;
}

void Game::updateCollision()
{
	if (!isfinish) {
		//left
		if (player->getBounds().left < 0.f)
		{
			//std::cout << "left: " << player->getBounds().left << "width" << player->getBounds().width;
			player->setPosition(0.f, player->getBounds().top);
		}
		//right
		else if (player->getBounds().left + player->getBounds().width >= gameWorld->getgridWidth())
		{
			//std::cout << "left: " << player->getBounds().left << "width" << player->getBounds().width;
			player->setPosition(gameWorld->getgridWidth() - player->getBounds().width, player->getBounds().top);
		}
		//top
		if (player->getBounds().top < 0.f)
		{
			player->setPosition(player->getBounds().left, 0.f);
		}
		//bottom
		else if (player->getBounds().top + player->getBounds().height >= gameWorld->getgridLength())
		{
			player->setPosition(player->getBounds().left, gameWorld->getgridLength() - player->getBounds().height);
			if(fossiles.size()==0)
			{
				finish->setUpQuiz();
				isfinish = true;
			}
			


		}
	}
}

void Game::updateObstacles()
{
	int i = 0, j = 0, k = 0;
	for (const auto& o : firstLayerObstacles)
	{
		if (o) {
			Collider collider = player->getCollider();
			if (o->getCollider().CheckCollision(collider, 1.0f) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))

			{
				audiomanager->getMusics()["drill"]->setPlayingOffset(sf::seconds(6));
				audiomanager->playMusic("drill");
				o->getDamaged(1);
				o->update();
				if (o->getHp() <= 0)
				{
					firstLayerObstacles.erase(firstLayerObstacles.begin() + i);
					i--;
				}
			}
			else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				audiomanager->stopMusic("drill");
			}
		}
		i++;

	}

	for (const auto& o : secondLayerObstacles)
	{
		if (o) {
			Collider collider = player->getCollider();
			if (o->getCollider().CheckCollision(collider, 1.0f) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))

			{
				audiomanager->getMusics()["drill"]->setPlayingOffset(sf::seconds(6));
				audiomanager->playMusic("drill");
				o->getDamaged(1);
				o->update();
				if (o->getHp() <= 0)
				{
					secondLayerObstacles.erase(secondLayerObstacles.begin() + j);
					j--;
				}
			}
			else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				audiomanager->stopMusic("drill");
			}
		}
		j++;
	}

	for (const auto& o : thirdLayerObstacles)
	{
		if (o) {
			Collider collider = player->getCollider();
			if (o->getCollider().CheckCollision(collider, 1.0f) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))

			{
				audiomanager->getMusics()["drill"]->setPlayingOffset(sf::seconds(6));
				audiomanager->playMusic("drill");
				o->getDamaged(1);
				o->update();
				if (o->getHp() <= 0)
				{
					thirdLayerObstacles.erase(thirdLayerObstacles.begin() + k);
					k--;
				}
			}
			else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				audiomanager->stopMusic("drill");
			}
		}
		k++;
	}
}

void Game::updateOres()
{
	int i=0;
	for (auto & collectable :ores)
	{
		if (collectable) {
			Collider collider = player->getCollider();
			if (collectable->getCollider().CheckCollision(collider, 0.0f))
			{
				this->OreCollected(i);

			}
		}
		i++;
	}
}
void Game::updateFossils()
{

	for (auto& fossil : fossiles)
	{
		if (fossil && player->getMagnetStat())
		{

			Collider collider = player->getCollider();

			if (abs(fossil->getDistance(collider).x) < 400 || abs(fossil->getDistance(collider).y) < 400)
			{
				fossil->setPosition(player->getPos());
				player->magnetUsed();
			}
		}
	}
}
void Game::OreCollected(int& position)
{
	audiomanager->playMusic("collect");
	//player->collectOre(ores[position]->getValue());
	ores[position]->collected(*player);
	ores.erase(ores.begin() + position);
	maxores--;
	position--;
		
}

/*
* render functions
*/
int i = 0;
void Game::renderFossilsPopup()
{

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !popup)
	{

		bool deleted = false;
		for (i = 0; i < this->fossiles.size() && !popup; i++)
		{
			if (this->fossiles[i]->getSprite().getGlobalBounds().contains(this->mousPositionView))
			{
				deleted = true;

				this->points += 1;

				fossiles[i]->initPopUpSprite(view.getCenter());
				fossiles[i]->updatePopup();

				fossiles[i]->renderPopUp(*this->window);
				this->popup = true;
				finish->addCorrectanswers(fossiles[i]->getQuestionFromFossils());
				fossiles[i]->gotCollected();
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
		if (popup) {

			fossiles.erase(fossiles.begin() + i);

		}

		popup = false;
		PopUpChanged = true;

	}
}

void Game::renderFossiles()
{
	for (const auto& f : this->fossiles)
	{
		if (f)
		{
			f->render(*this->window);
		}

	}
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}

void Game::renderObstacles()
{
	for (const auto& o : firstLayerObstacles)
	{
		o->render(*window);
	}
	for (const auto& o : secondLayerObstacles)
	{
		o->render(*window);
	}
	for (const auto& o : thirdLayerObstacles)
	{
		o->render(*window);
	}
}

void Game::renderOres()
{
	/*for (int i = 0; i < maxores; i++)
	{
		ores[i]->render(*window);
	}*/
	for(auto const &collectable :ores)
	{
		collectable->render(*window);
	}
}


/*
* getters
*/
const bool Game::getEndGame() const
{
	return this->endGame;
}
const bool Game::getPopUpChanged() const
{
	return PopUpChanged;
}
Player& Game::getPLayer() const
{
	return *player;
}
Finish& Game::getFinish() const
{
	return *finish;
}
std::vector<std::unique_ptr<Fossil>> const& Game::getFossiles() const
{
	return fossiles;
}
std::vector<std::unique_ptr<Collectable>> const& Game::getOres() const
{
	return ores;
}
AudioManager& Game::getAudioManager() const
{
	return *audiomanager;
}
const bool Game::getWindowIsOpen()const
{
	return this->window->isOpen();
}
sf::Vector2f Game::getMousPositionView() const
{
	return this->mousPositionView;
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
			if (this->event.key.code == sf::Keyboard::P)
			{
				music.play();

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
	view_h = VIEW_HEIGHT * aspectRatio;
}

int Game::random(int const nbMin, int const nbMax)
{
	static std::default_random_engine engine;
	std::uniform_int_distribution<> distribution(nbMin, nbMax);

	return distribution(engine);
}


float Game::DeltaTime()
{
	return sclock.restart().asSeconds();
}