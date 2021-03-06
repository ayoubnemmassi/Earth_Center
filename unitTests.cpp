#include <gtest/gtest.h>
#include "Player.h"
#include "Tile.h"
#include "GameWorld.h"
#include"Fossil.h"
#include"Enemy.h"
#include"Obstacle.h"
#include"Crystal.h"
#include"CollectableFactory.h"
#include"Finish.h"
#include "Game.h"
#include<SFML/Audio.hpp>
Game* game;
TEST(TestGame, TestPlayer) {
	game = new Game();
	//game.getPLayer();
	std::unique_ptr<Player> player;
	player = std::make_unique<Player>("spear", "resources/Textures/graytank.png");
	std::cout << "holla " << game->getPLayer().getName() << std::endl;
	EXPECT_EQ(player->getName(), game->getPLayer().getName());
	EXPECT_EQ(player->getSpriteURL(), game->getPLayer().getSpriteURL());
	EXPECT_EQ(player->getHpMax(), game->getPLayer().getHpMax());
	EXPECT_EQ(game->getPLayer().getHpMax(), game->getPLayer().getHp());
	EXPECT_EQ(player->getMouvementSpeed(), game->getPLayer().getMouvementSpeed());
}
TEST(TestGame, TestFossil) {

	int i = 0;
	std::string dino_name;

	EXPECT_EQ(game->getFossiles().size(), 3);
	for (auto const& f : game->getFossiles())
	{
		if (i == 0) { dino_name = "trex.png"; }
		else if (i == 1) { dino_name = "Parasaurolophus.png"; }
		else { dino_name = "Triceratops.png"; }
		EXPECT_EQ(f->getName(), dino_name);
		i++;
	}

}
TEST(TestGame, Testore)
{

	EXPECT_EQ(static_cast<Crystal*>(game->getOres()[1].get())->getValue(), 2);
	int pos = 1;
	game->OreCollected(pos);
	EXPECT_EQ(game->getOres().size(), 39);

}
TEST(TestGame, TestFinish)
{
	EXPECT_EQ(game->getFinish().getQuizQuestions().size() * game->getFinish().getQuizQuestions()[0].size(), 9);
}
TEST(TestGame, TestCollectabelFactory)
{
	std::unique_ptr<Collectable> c = CollectableFactory::createCollectable(1, 2, sf::Vector2f(0.f, 0.f), "purple");
	EXPECT_EQ(c->test(), "ore");


}
TEST(TestGame, TestAudioManager)
{

	EXPECT_EQ(game->getAudioManager().getMusics().size(), 4);
	game->getAudioManager().playMusic("background");
	EXPECT_EQ(game->getAudioManager().getMusics()["background"]->getStatus(), sf::Music::Playing);
	game->getAudioManager().stopMusic("background");
	EXPECT_EQ(game->getAudioManager().getMusics()["background"]->getStatus(), sf::Music::Stopped);
	delete game;


}