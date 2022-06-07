#include "Destroyable.h"

Destroyable::Destroyable(int hp) :
	hp{hp}
{
	
}

Destroyable::~Destroyable()
{
}


const int Destroyable::getHp() const
{
	return hp;
}

void Destroyable::getDamaged(int damage)
{
	hp -= damage;
}