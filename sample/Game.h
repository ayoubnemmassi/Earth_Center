#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <ctime>
#include<map>
#include <iostream>
#include <sstream>
#include "Player.h"
#include "Tile.h"
#include "GameWorld.h"
#include"Fossil.h"
#include"Enemy.h"
class Game
{
public:
	/*
	* default constructor 
	*/
	Game();
	/*
	*  destructor
	*/
	~Game();
	
	void run();	
	void render();
	void update();
	void pollEvents();

	float DeltaTime();

	//geters
	const bool getWindowIsOpen()const;
	const bool getEndGame()const;
	const bool getPopUpChanged()const;

private:
	/*
	* window
	*/
	  //variables
	  sf::RenderWindow* window;
	  sf::VideoMode videoMode;
	  
	  //functions
	  void initWindow();

	/*
	* view
	*/
	  //variables
       sf::View view;
	   float VIEW_HEIGHT;
	  
	   //functions
	   void updateView();

	//texture
	sf::RenderTexture texturerender;
	std::map<std::string, sf::Texture*> textures;

	void initTextures();

	/*
	* text
	*/
	  //variables
	  sf::Text uiText;
	  sf::Font font;
	  
	  //functions
	  void initFonts();
	  void initText();
	  void renderText(sf::RenderTarget& target);
	  void updateText();

	/*
	* fossil
	*/
	  //variables
	  std::vector<Fossil*>fossiles;
	  
	  //functions
	  void renderFossiles();
	  void spawnFossiles();
	  void updateFossils();
	  void renderFossilsPopup();

	/*
	* game mechanics
	*/
	  //variables
	  sf::Event event;
	  sf::Vector2i mousPosition;
	  sf::Vector2f mousPositionView;
	  sf::Clock sclock;
	  bool endGame;
	  bool pause;
	  bool popup;
	  bool PopUpChanged;
	  bool mouseHeld;
	  unsigned points;
	  int health;

	  //functions
	  void updateInput();
	  void updateMousePosition();
	  void updateCollision();
	  int random(int const nbMin, int const nbMax);

	/*
	* player
	*/
	  //variables
	  Player* player;

	  //functions
	  void initPlayer();

	/*
	* enemy
	*/
	  //variables
	  std::vector<sf::RectangleShape>enemies;
	  Enemy* enemy;

	  //functions
	  void initEnemies();

    /*
    * graphic
    */
	  //variables
	  sf::Shader shader;

	  //functions
	  void initShader();
	  void resize();
	
	/*
	* Map
	*/
	  //variables
	  Tile* map;
	  GameWorld* gameWorld;

	  //functions
	  void initGameWorld();

    /*
    * Global
    */
	  void initVariables();
	
	
	
	

	
	
	
	
	
	
	
	
	
	
	
	

};

