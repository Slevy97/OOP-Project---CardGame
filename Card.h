#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

#include "SFML\Graphics.hpp"
#include "GameObject.h"

namespace Theta {

	class Card {

		private:
			int ID;
			int Mana;
			int Swag;

			int Attack;
			int Defense;

		public:
			Card();
			~Card();

			int getID();
			int getMana();
			int getSwag();
			int getAttack();
			int getDefense();

			void setAttack(int attack);
			void setDefense(int defense);
			void setID(int id);
			void setMana(int mana);
			void setSwag(int swag);
	};
}

#endif // ! CARD_H_INCLUDED