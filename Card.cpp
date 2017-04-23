#include "Card.h"

using namespace Theta;

Card::Card()
{
	ID = 1;
	Mana = 1;
	Swag = 1;
	Attack = 1;
	Defense = 1;
}


Card::~Card()
{
}

int Card::getID()
{
	return ID;
}

int Card::getMana()
{
	return Mana;
}

int Card::getSwag()
{
	return Swag;
}

int Card::getAttack()
{
	return Attack;
}

int Card::getDefense()
{
	return Defense;
}

void Card::setAttack(int attack)
{
	Attack = attack;
}

void Card::setDefense(int defense)
{
	Defense = defense;
}

void Card::setID(int id)
{
	ID = id;
}

void Card::setMana(int mana)
{
	Mana = mana;
}

void Card::setSwag(int swag)
{
	Swag = swag;
}