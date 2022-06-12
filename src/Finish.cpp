#include "Finish.h"


Finish::Finish(const sf::Vector2f &  position)
{
	initFonts();
	initTextures();
	initSprites(position);
	initrandomQuestions();
	initQuiz();
	initAudiomanager();
	initGamemusic();
	

}

void Finish::render(sf::RenderTarget& target)
{
	if(isquiz){
		//target.draw(genieSprite);
		target.draw(quizSprite);
		float y = target.getView().getCenter().y - 100;
		for (int i = 0;i < quizQuestions[quizNumber].size();i++)
		{

			quizQuestions[quizNumber][i].setPosition(target.getView().getCenter().x, y);
			target.draw(quizQuestions[quizNumber][i]);
			y += 100;
		}
	}
	else if(iswining)
	{
		target.draw(winSprite);
	}
	
	
}

void Finish::update()
{
}

void Finish::initSprites(const sf::Vector2f&  position)
{
	quizSprite.setTexture(quizTexture);

	quizSprite.setOrigin(quizSprite.getGlobalBounds().width/ 2.f, quizSprite.getGlobalBounds().height / 2.f);
	genieSprite.setTexture(genieTexture);
	genieSprite.setPosition(position.x+200,position.y);
	winSprite.setTexture(winTexture);
	
	
	winSprite.setOrigin(winSprite.getGlobalBounds().width / 2.f, winSprite.getGlobalBounds().height / 2.f);
}

void Finish::initTextures()
{

	if(!quizTexture.loadFromFile("resources/Textures/quiz4.png"))
	{

	}
	if (!genieTexture.loadFromFile(""))
	{

	}
	if (!winTexture.loadFromFile("resources/Textures/win1.png"))
	{

	}
}

void Finish::initQuiz()
{
	quizNumber = 0;
	this->isquiz = true;
	this->iswining = false;
	quizQuestions.resize(3);
	
	for (auto &p : quizQuestions)
	{
		p.resize(3);
		
	}
	

}
void Finish::initAudiomanager()
{
	audiomanager = std::make_unique<AudioManager>();
}

void Finish::initGamemusic()
{
	std::string firstquestion = "resources/Textures/firstquestion.ogg";
	std::string secondquestion ="resources/Textures/secondquestion.ogg";
	std::string finalquestion = "resources/Textures/finalquestion.ogg";
	std::string win = "resources/Textures/win.ogg";
	audiomanager->addMusic("firstquestion", firstquestion);
	audiomanager->addMusic("secondquestion", secondquestion);
	audiomanager->addMusic("finalquestion", finalquestion);
	audiomanager->addMusic("win", win);
	

}

void Finish::addCorrectanswers(const std::string &answer)
{
	correctQuestions.push_back(answer);
}

void Finish::Updatequiz(const sf::Vector2f &mousePos, const sf::Vector2f& viewpos)
{
	if(isquiz)
	{
		quizSprite.setPosition(viewpos);
		if(quizNumber==0){ audiomanager->playMusic("firstquestion"); }
		else if (quizNumber == 1) { audiomanager->stopMusic("firstquestion"); audiomanager->playMusic("secondquestion"); }
		else if(quizNumber == 2){ audiomanager->stopMusic("secondquestion"); audiomanager->playMusic("finalquestion"); }
	}
	else 
	{
		winSprite.setPosition(viewpos);
	}
	
		for(auto const &q :quizQuestions[quizNumber])
		{
			if(q.getGlobalBounds().contains(mousePos)&& sf::Mouse::isButtonPressed(sf::Mouse::Left) )
			
			{
				for(auto const &a :correctQuestions)
				{
					std::string answer= q.getString();
					if(answer == a)
					{
						if (quizNumber >= 2)
							win();
						else
						quizNumber++;
						
					}
				}
				
			}
		}
	
}


void Finish::initFonts()
{
	if (!textFont.loadFromFile("resources/Fonts/FontFile.ttf"))
	{
		std::cout << "error" << std::endl;
	}
}

void Finish::setUpQuiz()
{
	for (auto& p : quizQuestions)
	{
		int correctAnswerPos = rand() % 3;
		for (int i=0;i<p.size();i++)
		{
			if(i==correctAnswerPos)
			{
				sf::Text answer;
				answer.setFont(textFont);
				answer.setCharacterSize(30);
				answer.setFillColor(sf::Color::Black);
				answer.setString(correctQuestions[correctAnswerPos]);
				answer.setOrigin(answer.getGlobalBounds().width / 2, answer.getGlobalBounds().height / 2);
				p[i] = answer;
			}
			else
			{
				sf::Text answer;
				answer.setFont(textFont);
				answer.setCharacterSize(30);
				answer.setFillColor(sf::Color::Black);
				answer.setString(randomtQuestions[i]);
				answer.setOrigin(answer.getGlobalBounds().width / 2, answer.getGlobalBounds().height / 2);
				p[i] = answer;
			}

				
		}
	}

}

void Finish::initrandomQuestions()
{
	randomtQuestions.push_back("Trex have the wakest bite");
	randomtQuestions.push_back("Trex name means 'Near Crested Lizard'");
	randomtQuestions.push_back("Trexwas given its names in 1905 by Ding Leyuan");
	randomtQuestions.push_back("The name Parasaurolophus means: “king of the tyrant lizards");
	randomtQuestions.push_back("Parasaurolophus believed to have had the strongest bite");
	randomtQuestions.push_back("The Parasaurolophus can run up to 32 kilometers per hour");
	randomtQuestions.push_back("Triceratops has an estimated length of 31 feet");
	randomtQuestions.push_back("The name Triceratops means king of the tyrant lizards");
	randomtQuestions.push_back("The Triceratops can be up to 15 meters long or 29.52 feet");
}

void Finish::win()
{
	audiomanager->stopMusic("finalquestion");
	audiomanager->playMusic("win");
	isquiz = false;
	iswining = true;

}

bool Finish::getWin() const
{
	return iswining;
}

std::vector<std::vector<sf::Text>> Finish::getQuizQuestions() const
{
	return quizQuestions;
}


