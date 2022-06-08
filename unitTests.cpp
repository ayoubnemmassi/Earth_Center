#include <gtest/gtest.h>
#include "Player.h"
#include "Tile.h"
#include "GameWorld.h"
#include"Fossil.h"
#include"Enemy.h"
#include"Obstacle.h"
#include"Ore.h"

#include"Finish.h"
#include "Game.h"
Game* game;
TEST(TestGame, TestPlayer) {
	game = new Game();
	//game.getPLayer();
	std::unique_ptr<Player> player;
	player = std::make_unique<Player>("spear", "C:/Users/MSI/Downloads/earthcenter/Textures/graytank.png");
	std::cout << "holla " << game->getPLayer().getName() << std::endl;
	EXPECT_EQ(player->getName(), game->getPLayer().getName());
	EXPECT_EQ(player->getSpriteURL(), game->getPLayer().getSpriteURL());
}
TEST(TestGame, TestFossil) {

	int i = 0;
	std::string dino_name;

	EXPECT_EQ(game->getFossiles().size(), 3);
	for (auto const& f : game->getFossiles())
	{
		if (i == 0) { dino_name = "Parasaurolophus.png"; }
		else if (i == 1) { dino_name = "Triceratops.png"; }
		else { dino_name = "trex.png"; }
		EXPECT_EQ(f->getName(), dino_name);
		i++;
	}

}
TEST(TestGame, Testore)
{
	EXPECT_EQ(game->getOres().size(), 30);
	EXPECT_EQ(game->getOres()[1]->getValue(), 2);

}
TEST(TestGame, TestFinish)
{
	EXPECT_EQ(game->getFinish().getQuizQuestions().size() * game->getFinish().getQuizQuestions()[0].size(), 9);
}
