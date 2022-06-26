#pragma once
#include "Collectable.h"
#include "Crystal.h"
#include <Magnet.h>
#include<iostream>
class CollectableFactory
{
public:
	static std::unique_ptr<Collectable>createCollectable(int type, int value, sf::Vector2f pos, std::string name);
	

};
