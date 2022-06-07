#pragma once
#include<SFML/Graphics.hpp>
class Destroyable
{
public:
	Destroyable(int hp);
	~Destroyable();
	void virtual update()=0;
	const int getHp()const;
	void getDamaged(int damage);
private:
	int hp;

};

