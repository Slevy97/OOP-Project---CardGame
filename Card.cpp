#include "Card.h"

using namespace Theta;

Card::Card()
{
	ID = 1;
	Mana = 1;
	Swag = 1;
	Attack = 1;
	Defense = 1;
	TurnsToWait = 0;
	NrLives = 1;
	NrAttacks = 1;
	NrAttacksToMiss = 0;
	NrAttacksToAvoid = 0;
	Spell = 0;
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

int Card::getTurnsToWait()
{
	return TurnsToWait;
}

int Card::getNrLives()
{
	return NrLives;
}

int Card::getNrAttacks()
{
	return NrAttacks;
}

int Card::getNrAttacksToMiss()
{
	return NrAttacksToMiss;
}

int Card::getNrAttacksToAvoid()
{
	return NrAttacksToAvoid;
}

int Card::getSpell()
{
	return Spell;
}

std::vector < int > Card::getArgs()
{
	return Args;
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

void Card::setTurnsToWait(int turnsToWait)
{
	TurnsToWait = turnsToWait;
}

void Card::setNrLives(int nrLives)
{
	NrLives = nrLives;
}

void Card::setNrAttacks(int nrAttacks)
{
	NrAttacks = nrAttacks;
}

void Card::setNrAttacksToMiss(int nrAttacksToMiss)
{
	NrAttacksToMiss = nrAttacksToMiss;
}

void Card::setNrAttacksToAvoid(int nrAttacksToAvoid)
{
	NrAttacksToAvoid = nrAttacksToAvoid;
}

void Card::setSpell(int spell)
{
	Spell = spell;
}

void Card::setArgs(std::vector < int > args)
{
	Args = args;
}

void Card::addArg(int arg)
{
	Args.push_back(arg);
}

void Card::increaseAttack(int attack)
{
	Attack += attack;
}

void Card::increaseDefense(int defense)
{
	Defense += defense;
}

void Card::decreaseAttack(int attack)
{
	Attack -= attack;
}

void Card::decreaseDefense(int defense)
{
	Defense -= defense;
}

bool Card::canAttack()
{
	if (TurnsToWait > 0)
	{
		return false;
	}

	return true;
}