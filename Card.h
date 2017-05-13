#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

#include "SFML\Graphics.hpp"
#include "GameObject.h"
#include <vector>

namespace Theta {

	class Card {

	private:
		int ID;
		int Mana;
		int Swag;

		int Attack;
		int Defense;

		int TurnsToWait;
		int NrLives;
		int NrAttacks;
		int NrAttacksToMiss;
		int NrAttacksToAvoid;


		int Spell; //holds the index
		std::vector < int > Args;
		/*
		La NrArgType - dimensiune string-ului reprezinta nr de argumente si :

		i -> int
		s -> string
		c -> char
		f -> float
		d -> double

		Cand vrem sa apelam o functie, verificam daca are nevoie de index. Daca da, event/input manager ni-l da. Apoi extragem argumentele
		si apelam functia astfel:
		abilities[Spell](NrArgType, argumentele extrase, daca exista)
		*/

	public:
		Card();
		~Card();

		int getID();
		int getMana();
		int getSwag();
		int getAttack();
		int getDefense();
		int getTurnsToWait();
		int getNrLives();
		int getNrAttacks();
		int getNrAttacksToMiss();
		int getNrAttacksToAvoid();
		int getSpell();
		std::vector < int > getArgs();

		void setAttack(int attack);
		void setDefense(int defense);
		void setID(int id);
		void setMana(int mana);
		void setSwag(int swag);
		void setTurnsToWait(int turnsToWait);
		void setNrLives(int nrLives);
		void setNrAttacks(int nrAttacks);
		void setNrAttacksToMiss(int nrAttacksToMiss);
		void setNrAttacksToAvoid(int nrAttacksToAvoid);
		void setSpell(int spell);
		void setArgs(std::vector < int > args);

		void addArg(int arg);

		void increaseAttack(int attack);
		void increaseDefense(int defense);

		void decreaseAttack(int attack);
		void decreaseDefense(int defense);

		bool canAttack();
	};
}

#endif // ! CARD_H_INCLUDED