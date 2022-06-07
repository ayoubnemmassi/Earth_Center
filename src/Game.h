#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Time.hpp>
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
#include"Obstacle.h"
#include"Ore.h"
#include"AudioManager.h"
#include"Finish.h"
#include <tmxlite/Map.hpp>
#include"SFMLOrthogonalLayer.h"

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
	Player &getPLayer() const;
	Finish &getFinish() const;
   std::vector<std::unique_ptr<Fossil>> const &getFossiles()const;
   std::vector<std::unique_ptr<Ore>> const& getOres() const;
private:
	/*
	* window
	*/
	  //variables
	  sf::RenderWindow* window;
	  sf::VideoMode videoMode;
	  tmx::Map mapdemo;
	  sf::Clock globalClock;
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
	  std::vector< std::unique_ptr<Fossil>>fossiles;
	  
	  //functions
	  void renderFossiles();
	  void initFossiles();
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

	  sf::Vector2f getMousPositionView()const;

	/*
	* player
	*/
	  //variables
	 std::unique_ptr<Player>  player;

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
	
	
	
	/*
	* obstacles
	*/
	  std::vector<std::unique_ptr< Obstacle>>firstLayerObstacles;
	  std::vector<std::unique_ptr< Obstacle>>secondLayerObstacles;
	  std::vector<std::unique_ptr< Obstacle>>thirdLayerObstacles;
	  
	  int numberOfObstacles;

	  void initObstacles(int numberOfObstacles);
	  void updateObstacles();
	  void renderObstacles();

	/*
	* ore
	*/
	  Ore* ore;
	  std::vector<std::unique_ptr< Ore>>ores;

	  int maxores;

	  void initOres(int maxores);
	  void updateOres();
	  void renderOres();
	
	  sf::SoundBuffer soundBuffer;
	  sf::SoundBuffer mouvingSoundBuffer;
	  sf::Sound sound;
	  sf::Sound mouvingSound;
	  sf::Music music;
	
	  std::unique_ptr< AudioManager> audiomanager;
	  void initAudiomanager();
	  void initGamemusic();
	  /*
	  * finish
	  */
	  //variables
	  std::unique_ptr<Finish>finish;
	  bool isfinish;
	  //functions
	  void initFinish();

};

