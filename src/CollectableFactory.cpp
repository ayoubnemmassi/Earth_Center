#include"CollectableFactory.h"

 std::unique_ptr<Collectable > CollectableFactory:: createCollectable(int type, int value, sf::Vector2f pos,std::string name)
{
	std::unique_ptr <Collectable>  collectable = nullptr;
	switch (type)
	{
	case 1:
	{
		collectable = std::make_unique<Ore>(value, pos,name);
		break;
	}
	default:
	{
		std::cout << "invalid type" << std::endl;
		return nullptr;
	}
	break;
	}
	return collectable;
}


