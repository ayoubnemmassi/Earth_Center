#pragma once
#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "AudioManager.h"
class Finish
{
public:
	Finish(const sf::Vector2f&  position);
	virtual ~Finish()=default;
	void render(sf::RenderTarget& target);
	void update();
	void initSprites(const sf::Vector2f&  position);
	void initTextures();
	void initQuiz();
	void addCorrectanswers(const std::string & answer);
	void Updatequiz(const sf::Vector2f & mousePos, const sf::Vector2f& viewpos);
	void initFonts();
	void setUpQuiz();
	void initrandomQuestions();
	void win();
	bool getWin()const;
	std::vector < std::vector<sf::Text> > getQuizQuestions()const;
private:
	sf::Sprite winSprite;
	sf::Texture winTexture;
	sf::Sprite genieSprite;
	sf::Texture genieTexture;
	sf::Sprite quizSprite;
	sf::Texture quizTexture;
	std::vector < std::vector<sf::Text> > quizQuestions;
	std::vector < std::string > correctQuestions;
	std::vector < std::string > randomtQuestions;
	sf::Font textFont;

	bool iswining;
	bool isquiz;
	int quizNumber;

	std::unique_ptr< AudioManager> audiomanager;
	void initAudiomanager();
	void initGamemusic();
};



