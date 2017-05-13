#include "ThetaEngine.h"
#include <iostream>

extern std::list<Theta::GameObject*> GameObjects;
extern Theta::CardSprite * Deck;
extern Theta::Table* ptr_table;
extern bool mark_deck[NR_MAX_CARDS_DECK];
extern std::vector<int> IndxAvailable;

namespace Theta {

	namespace Spells {



		void invokeCharacter(int indexInDeck)
		{
			if (mark_deck[indexInDeck]) {

				for (unsigned int i = 0; i < ptr_table->player_hand.getNrCards(); i++)
				{
					if (ptr_table->player_hand.getCard(i).getCardPtr()->getID() == Deck[indexInDeck].getCardPtr()->getID()) {

						if (!ptr_table->player_table.isFull()) { // if it can be moved , move it to the player_table

							ptr_table->player_table.copy_card(&ptr_table->player_hand, i);
							ptr_table->player_hand.erase_card(i);
						}
						break;
					}
				}
			}
			else {

				ptr_table->player_table.add_card(Deck[indexInDeck]);
				mark_deck[indexInDeck] = true;
				IndxAvailable.erase(find(IndxAvailable.begin(), IndxAvailable.end(), indexInDeck));
			}
		}

		/*void wait(int turnsToWait)
		{

		}
		*/

		void shuffleAttributes()
		{
			std::vector<std::pair <int, int> >allStats;
			int i;

			for (i = 1; i < ptr_table->player_table.getNrCards(); ++i)
			{
				allStats.push_back(std::make_pair(0, 0));
				allStats.back().first = ptr_table->player_table.getCard(i).getCardPtr()->getAttack();
				allStats.back().second = ptr_table->player_table.getCard(i).getCardPtr()->getDefense();
			}

			for (i = 1; i < ptr_table->enemy_table.getNrCards(); ++i)
			{
				allStats.push_back(std::make_pair(0, 0));
				allStats.back().first = ptr_table->enemy_table.getCard(i).getCardPtr()->getAttack();
				allStats.back().second = ptr_table->enemy_table.getCard(i).getCardPtr()->getDefense();
			}

			std::random_shuffle(allStats.begin(), allStats.end());

			for (i = 1; i < ptr_table->player_table.getNrCards(); ++i)
			{
				ptr_table->player_table.getCard(i).getCardPtr()->setAttack(allStats.back().first);
				ptr_table->player_table.getCard(i).getCardPtr()->setDefense(allStats.back().second);
				ptr_table->player_table.getCard(i).updateText();
				allStats.pop_back();
			}

			for (i = 1; i < ptr_table->enemy_table.getNrCards(); ++i)
			{
				ptr_table->enemy_table.getCard(i).getCardPtr()->setAttack(allStats.back().first);
				ptr_table->enemy_table.getCard(i).getCardPtr()->setDefense(allStats.back().second);
				ptr_table->enemy_table.getCard(i).updateText();
				allStats.pop_back();
			}
		}

		void freeze(int index)
		{
			if (ptr_table->enemy_table.getNrCards() > 1) {
				ptr_table->enemy_table.getCard(index).getCardPtr()->setTurnsToWait(
					ptr_table->enemy_table.getCard(index).getCardPtr()->getTurnsToWait() + 1);
			}

			//ptr_table->enemy_table.PH_CARDS[index].getCardPtr()->setTurnsToWait(
			//ptr_table->enemy_table.PH_CARDS[index].getCardPtr()->getTurnsToWait() + 1);
		}

		void merge_and_drag(int indx1, int indx2, int indx3) {

			int playerCards = ptr_table->player_table.getNrCards();
			bool ok1 = false, ok2 = false;
			for (int i = 0; i < playerCards; ++i)
			{
				if (ptr_table->player_table.getCard(i).getCardPtr()->getID() == indx1)
					ok1 = true;
				if (ptr_table->player_table.getCard(i).getCardPtr()->getID() == indx2)
					ok2 = true;
			}
			if (ok1 && ok2) {

				for (int i = 0; i < ptr_table->player_table.getNrCards(); ++i)
				{
					if (ptr_table->player_table.getCard(i).getCardPtr()->getID() == indx1)
					{
						ptr_table->player_table.erase_card(i);
						i--;
					}
				}
				for (int i = 0; i < ptr_table->player_table.getNrCards(); ++i)
				{
					if (ptr_table->player_table.getCard(i).getCardPtr()->getID() == indx2)
					{
						ptr_table->player_table.erase_card(i);
						i--;
					}
				}
				invokeCharacter(indx3);
			}
		}

		void merge()
		{
			merge_and_drag(16, 7, 28);
			merge_and_drag(17, 19, 27);
		}

		void destroy(int index)
		{
			if (ptr_table->enemy_table.getNrCards() > 1) {
				if (index == 0)
					index++;

				ptr_table->enemy_table.erase_card(index);
			}
		}

		void increaseAttackAlly(int index, int attack)
		{
			//if (ptr_table->player_table.getNrCards() > 1) {
			ptr_table->player_table.getCard(index).getCardPtr()->increaseAttack(attack);
			ptr_table->player_table.getCard(index).updateText();
			//}
		}

		void increaseAttackEnemy(int index, int attack)
		{
			//if (ptr_table->enemy_table.getNrCards() > 1) {
			ptr_table->enemy_table.getCard(index).getCardPtr()->increaseAttack(attack);
			ptr_table->enemy_table.getCard(index).updateText();
			//}
		}

		void increaseDefenseAlly(int index, int defense)
		{
			//if (ptr_table->player_table.getNrCards() > 1) {
			ptr_table->player_table.getCard(index).getCardPtr()->increaseDefense(defense);
			ptr_table->player_table.getCard(index).updateText();
			//}
		}

		void increaseDefenseEnemy(int index, int defense)
		{
			//if (ptr_table->enemy_table.getNrCards() > 1) {
			ptr_table->enemy_table.getCard(index).getCardPtr()->increaseDefense(defense);
			ptr_table->enemy_table.getCard(index).updateText();
			//}
		}

		void increaseAttackAllies(int attack)
		{
			for (int index = 0; index < ptr_table->player_table.getNrCards(); ++index)
			{
				increaseAttackAlly(index, attack);
			}
		}

		void increaseAttackEnemies(int attack)
		{
			for (int index = 0; index < ptr_table->enemy_table.getNrCards(); ++index)
			{
				increaseAttackEnemy(index, attack);
			}
		}

		void increaseDefenseAllies(int defense)
		{
			for (int index = 0; index < ptr_table->player_table.getNrCards(); ++index)
			{
				increaseDefenseAlly(index, defense);
			}
		}

		void increaseDefenseEnemies(int defense)
		{
			for (int index = 0; index < ptr_table->enemy_table.getNrCards(); ++index)
			{
				increaseDefenseEnemy(index, defense);
			}
		}

		void increaseAttributesAlly(int index, int attack, int defense)
		{
			//if (ptr_table->player_table.getNrCards() > 1) {
			increaseAttackAlly(index, attack);
			increaseDefenseAlly(index, defense);
			//}
		}

		void increaseAttributesEnemy(int index, int attack, int defense)
		{
			//if (ptr_table->enemy_table.getNrCards() > 1) {
			increaseAttackEnemy(index, attack);
			increaseDefenseEnemy(index, defense);
			//}
		}

		void increaseAttributesAllies(int attack, int defense)
		{
			increaseAttackAllies(attack);
			increaseDefenseAllies(defense);
		}

		void increaseAttributesEnemies(int attack, int defense)
		{
			increaseAttackEnemies(attack);
			increaseDefenseEnemies(defense);
		}


		void decreaseAttackAlly(int index, int attack)
		{
			//if (ptr_table->player_table.getNrCards() > 1) {
			ptr_table->player_table.getCard(index).getCardPtr()->decreaseAttack(attack);
			ptr_table->player_table.getCard(index).updateText();
			//}
		}

		void decreaseAttackEnemy(int index, int attack)
		{
			//if (ptr_table->enemy_table.getNrCards() > 1) {
			ptr_table->enemy_table.getCard(index).getCardPtr()->decreaseAttack(attack);
			ptr_table->enemy_table.getCard(index).updateText();
			//}
		}

		void decreaseDefenseAlly(int index, int defense)
		{
			//if (ptr_table->player_table.getNrCards() > 1) {
			ptr_table->player_table.getCard(index).getCardPtr()->decreaseDefense(defense);
			ptr_table->player_table.getCard(index).updateText();
			//}
		}

		void decreaseDefenseEnemy(int index, int defense)
		{
			//if (ptr_table->enemy_table.getNrCards() > 1) {
			ptr_table->enemy_table.getCard(index).getCardPtr()->decreaseDefense(defense);
			ptr_table->enemy_table.getCard(index).updateText();
			//}
		}

		void decreaseAttackAllies(int attack)
		{
			for (int index = 0; index < ptr_table->player_table.getNrCards(); ++index)
			{
				decreaseAttackAlly(index, attack);
			}
		}

		void decreaseAttackEnemies(int attack)
		{
			for (int index = 0; index < ptr_table->enemy_table.getNrCards(); ++index)
			{
				decreaseAttackEnemy(index, attack);
			}
		}

		void decreaseDefenseAllies(int defense)
		{
			for (int index = 0; index < ptr_table->player_table.getNrCards(); ++index)
			{
				decreaseDefenseAlly(index, defense);
			}
		}

		void decreaseDefenseEnemies(int defense)
		{
			for (int index = 0; index < ptr_table->enemy_table.getNrCards(); ++index)
			{
				decreaseDefenseEnemy(index, defense);
			}
		}

		void decreaseAttributesAlly(int index, int attack, int defense)
		{
			//if (ptr_table->player_table.getNrCards() > 1) {
			decreaseAttackAlly(index, attack);
			decreaseDefenseAlly(index, defense);
			//}
		}

		void decreaseAttributesEnemy(int index, int attack, int defense)
		{
			//if (ptr_table->enemy_table.getNrCards() > 1) {
			decreaseAttackEnemy(index, attack);
			decreaseDefenseEnemy(index, defense);
			//}
		}

		void decreaseAttributesAllies(int attack, int defense)
		{
			decreaseAttackAllies(attack);
			decreaseDefenseAllies(defense);
		}

		void decreaseAttributesEnemies(int attack, int defense)
		{
			decreaseAttackEnemies(attack);
			decreaseDefenseEnemies(defense);
		}


		void stealCard()
		{
			if (ptr_table->enemy_table.getNrCards() > 1) {

				int indexCardToSteal = rand() % ptr_table->enemy_table.getNrCards();
				if (indexCardToSteal == 0)
					indexCardToSteal++;

				if (!ptr_table->player_table.isFull())
				{
					ptr_table->player_table.add_card(ptr_table->enemy_table.getCard(indexCardToSteal));
					ptr_table->enemy_table.erase_card(indexCardToSteal);
				}
			}
		}

		void stealAttributes(int index)
		{
			/**for (int i = 0; i < ptr_table->player_table.getNrCards(); ++i)
			{
			if (ptr_table->player_table.getCard(i).getWhereToFind() == "DaniMocanu.png")
			{
			ptr_table->player_table.getCard(i).getCardPtr()->setAttack(
			ptr_table->enemy_table.getCard(index).getCardPtr()->getAttack());

			ptr_table->player_table.getCard(i).getCardPtr()->setDefense(
			ptr_table->enemy_table.getCard(index).getCardPtr()->getDefense());

			ptr_table->enemy_table.getCard(index).getCardPtr()->setAttack(1);
			ptr_table->enemy_table.getCard(index).getCardPtr()->setDefense(1);

			break;
			}
			}**/
		}

		void miss(int index, int nrAttacksToMiss)
		{
			ptr_table->enemy_table.getCard(index).getCardPtr()->setNrAttacksToMiss(
				ptr_table->enemy_table.getCard(index).getCardPtr()->getNrAttacksToMiss() + nrAttacksToMiss);
		}


		void freezeAll()
		{
			int enemyCards = ptr_table->enemy_table.getNrCards();

			for (int i = 0; i < enemyCards; ++i)
			{
				freeze(i);
			}
		}

		void checkPrezente()
		{

		}

		void checkEmpowers()
		{

		}

		void destroyTrump()
		{
			int enemyCards = ptr_table->enemy_table.getNrCards();

			for (int i = 0; i < enemyCards; ++i)
			{
				if (ptr_table->enemy_table.getCard(i).getCardPtr()->getID() == 18)
				{
					ptr_table->enemy_table.erase_card(i);
					break;
				}
			}
		}

		void destroySwag(int swag)
		{
			std::vector < int > toDestroy;

			for (int index = 0; index < ptr_table->enemy_table.getNrCards(); ++index)
			{
				if (ptr_table->enemy_table.getCard(index).getCardPtr()->getSwag() < swag)
					toDestroy.push_back(index);
			}

			for (int index = toDestroy.size() - 1; index >= 0; --index)
			{
				destroy(toDestroy[index]);
			}
		}

		void nothing()
		{

		}


		/* Varianta uniformizata a spell-urilor */


		void invokeCharacter(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 1)
			{
				//err
			}
			else
			{
				va_list vl;

				va_start(vl, nrArgumentsAndTypes);

				while (*nrArgumentsAndTypes != '\0')
				{
					switch (*nrArgumentsAndTypes)
					{
					case 'i':
					{
						int indexInDeck = va_arg(vl, int);
						invokeCharacter(indexInDeck);
						break;
					}
					default: break; //err
					}

					++nrArgumentsAndTypes;
				}

				va_end(vl);
			}
		}

		//void wait()

		void shuffleAttributes(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 0)
			{
				//err
			}
			else
			{
				shuffleAttributes();
			}
		}

		void freeze(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 1)
			{
				//err
			}
			else
			{
				va_list vl;

				va_start(vl, nrArgumentsAndTypes);

				while (*nrArgumentsAndTypes != '\0')
				{
					switch (*nrArgumentsAndTypes)
					{
					case 'i':
					{
						int index = va_arg(vl, int);
						freeze(index);
						break;
					}
					default: break; //err
					}

					++nrArgumentsAndTypes;
				}

				va_end(vl);
			}
		}

		void merge(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 0)
			{
				//err
			}
			else
			{
				merge();
			}
		}

		void destroy(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 1)
			{
				//err
			}
			else
			{
				va_list vl;

				va_start(vl, nrArgumentsAndTypes);

				while (*nrArgumentsAndTypes != '\0')
				{
					switch (*nrArgumentsAndTypes)
					{
					case 'i':
					{
						int index = va_arg(vl, int);
						destroy(index);
						break;
					}
					default: break; //err
					}

					++nrArgumentsAndTypes;
				}

				va_end(vl);
			}
		}

		//toate cu increase si decrease attributes

		// increase

		void increaseAttackAlly(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 2)
			{
				//err
			}
			else
			{
				va_list vl;

				va_start(vl, nrArgumentsAndTypes);

				int index = -1, attack;

				while (*nrArgumentsAndTypes != '\0')
				{
					switch (*nrArgumentsAndTypes)
					{
					case 'i':
					{
						if (index == -1)
							index = va_arg(vl, int);
						else
							attack = va_arg(vl, int);

						break;
					}
					default: break; //err
					}

					++nrArgumentsAndTypes;
				}

				increaseAttackAlly(index, attack);

				va_end(vl);
			}
		}

		void increaseAttackEnemy(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 2)
			{
				//err
			}
			else
			{
				va_list vl;

				va_start(vl, nrArgumentsAndTypes);

				int index = -1, attack;

				while (*nrArgumentsAndTypes != '\0')
				{
					switch (*nrArgumentsAndTypes)
					{
					case 'i':
					{
						if (index == -1)
							index = va_arg(vl, int);
						else
							attack = va_arg(vl, int);

						break;
					}
					default: break; //err
					}

					++nrArgumentsAndTypes;
				}

				increaseAttackEnemy(index, attack);

				va_end(vl);
			}
		}

		void increaseDefenseAlly(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 2)
			{
				//err
			}
			else
			{
				va_list vl;

				va_start(vl, nrArgumentsAndTypes);

				int index = -1, defense;

				while (*nrArgumentsAndTypes != '\0')
				{
					switch (*nrArgumentsAndTypes)
					{
					case 'i':
					{
						if (index == -1)
							index = va_arg(vl, int);
						else
							defense = va_arg(vl, int);

						break;
					}
					default: break; //err
					}

					++nrArgumentsAndTypes;
				}

				increaseDefenseAlly(index, defense);

				va_end(vl);
			}
		}

		void increaseDefenseEnemy(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 2)
			{
				//err
			}
			else
			{
				va_list vl;

				va_start(vl, nrArgumentsAndTypes);

				int index = -1, defense;

				while (*nrArgumentsAndTypes != '\0')
				{
					switch (*nrArgumentsAndTypes)
					{
					case 'i':
					{
						if (index == -1)
							index = va_arg(vl, int);
						else
							defense = va_arg(vl, int);

						break;
					}
					default: break; //err
					}

					++nrArgumentsAndTypes;
				}

				increaseDefenseEnemy(index, defense);

				va_end(vl);
			}
		}

		void increaseAttackAllies(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 1)
			{
				//err
			}
			else
			{
				va_list vl;

				va_start(vl, nrArgumentsAndTypes);

				int attack;

				while (*nrArgumentsAndTypes != '\0')
				{
					switch (*nrArgumentsAndTypes)
					{
					case 'i':
					{
						attack = va_arg(vl, int);
						break;
					}
					default: break; //err
					}

					++nrArgumentsAndTypes;
				}

				increaseAttackAllies(attack);

				va_end(vl);
			}
		}

		void increaseAttackEnemies(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 1)
			{
				//err
			}
			else
			{
				va_list vl;

				va_start(vl, nrArgumentsAndTypes);

				int attack;

				while (*nrArgumentsAndTypes != '\0')
				{
					switch (*nrArgumentsAndTypes)
					{
					case 'i':
					{
						attack = va_arg(vl, int);
						break;
					}
					default: break; //err
					}

					++nrArgumentsAndTypes;
				}

				increaseAttackEnemies(attack);

				va_end(vl);
			}
		}

		void increaseDefenseAllies(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 1)
			{
				//err
			}
			else
			{
				va_list vl;

				va_start(vl, nrArgumentsAndTypes);

				int defense;

				while (*nrArgumentsAndTypes != '\0')
				{
					switch (*nrArgumentsAndTypes)
					{
					case 'i':
					{
						defense = va_arg(vl, int);
						break;
					}
					default: break; //err
					}

					++nrArgumentsAndTypes;
				}

				increaseDefenseAllies(defense);

				va_end(vl);
			}
		}

		void increaseDefenseEnemies(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 1)
			{
				//err
			}
			else
			{
				va_list vl;

				va_start(vl, nrArgumentsAndTypes);

				int defense;

				while (*nrArgumentsAndTypes != '\0')
				{
					switch (*nrArgumentsAndTypes)
					{
					case 'i':
					{
						defense = va_arg(vl, int);
						break;
					}
					default: break; //err
					}

					++nrArgumentsAndTypes;
				}

				increaseDefenseEnemies(defense);

				va_end(vl);
			}
		}

		void increaseAttributesAlly(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 3)
			{
				//err
			}
			else
			{
				va_list vl;

				va_start(vl, nrArgumentsAndTypes);

				int index = -1, attack = -1, defense;

				while (*nrArgumentsAndTypes != '\0')
				{
					switch (*nrArgumentsAndTypes)
					{
					case 'i':
					{
						if (index == -1)
							index = va_arg(vl, int);
						else if (attack == -1)
							attack = va_arg(vl, int);
						else
							defense = va_arg(vl, int);

						break;
					}
					default: break; //err
					}

					++nrArgumentsAndTypes;
				}

				increaseAttributesAlly(index, attack, defense);

				va_end(vl);
			}
		}

		void increaseAttributesEnemy(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 3)
			{
				//err
			}
			else
			{
				va_list vl;

				va_start(vl, nrArgumentsAndTypes);

				int index = -1, attack = -1, defense;

				while (*nrArgumentsAndTypes != '\0')
				{
					switch (*nrArgumentsAndTypes)
					{
					case 'i':
					{
						if (index == -1)
							index = va_arg(vl, int);
						else if (attack == -1)
							attack = va_arg(vl, int);
						else
							defense = va_arg(vl, int);

						break;
					}
					default: break; //err
					}

					++nrArgumentsAndTypes;
				}

				increaseAttributesEnemy(index, attack, defense);

				va_end(vl);
			}
		}

		void increaseAttributesAllies(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 2)
			{
				//err
			}
			else
			{
				va_list vl;

				va_start(vl, nrArgumentsAndTypes);

				int attack = -1, defense;

				while (*nrArgumentsAndTypes != '\0')
				{
					switch (*nrArgumentsAndTypes)
					{
					case 'i':
					{
						if (attack == -1)
							attack = va_arg(vl, int);
						else
							defense = va_arg(vl, int);

						break;
					}
					default: break; //err
					}

					++nrArgumentsAndTypes;
				}

				increaseAttributesAllies(attack, defense);

				va_end(vl);
			}
		}

		void increaseAttributesEnemies(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 2)
			{
				//err
			}
			else
			{
				va_list vl;

				va_start(vl, nrArgumentsAndTypes);

				int attack = -1, defense;

				while (*nrArgumentsAndTypes != '\0')
				{
					switch (*nrArgumentsAndTypes)
					{
					case 'i':
					{
						if (attack == -1)
							attack = va_arg(vl, int);
						else
							defense = va_arg(vl, int);

						break;
					}
					default: break; //err
					}

					++nrArgumentsAndTypes;
				}

				increaseAttributesEnemies(attack, defense);

				va_end(vl);
			}
		}

		// decrease

		void decreaseAttackAlly(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 2)
			{
				//err
			}
			else
			{
				va_list vl;

				va_start(vl, nrArgumentsAndTypes);

				int index = -1, attack;

				while (*nrArgumentsAndTypes != '\0')
				{
					switch (*nrArgumentsAndTypes)
					{
					case 'i':
					{
						if (index == -1)
							index = va_arg(vl, int);
						else
							attack = va_arg(vl, int);

						break;
					}
					default: break; //err
					}

					++nrArgumentsAndTypes;
				}

				decreaseAttackAlly(index, attack);

				va_end(vl);
			}
		}

		void decreaseAttackEnemy(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 2)
			{
				//err
			}
			else
			{
				va_list vl;

				va_start(vl, nrArgumentsAndTypes);

				int index = -1, attack;

				while (*nrArgumentsAndTypes != '\0')
				{
					switch (*nrArgumentsAndTypes)
					{
					case 'i':
					{
						if (index == -1)
							index = va_arg(vl, int);
						else
							attack = va_arg(vl, int);

						break;
					}
					default: break; //err
					}

					++nrArgumentsAndTypes;
				}

				decreaseAttackEnemy(index, attack);

				va_end(vl);
			}
		}

		void decreaseDefenseAlly(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 2)
			{
				//err
			}
			else
			{
				va_list vl;

				va_start(vl, nrArgumentsAndTypes);

				int index = -1, defense;

				while (*nrArgumentsAndTypes != '\0')
				{
					switch (*nrArgumentsAndTypes)
					{
					case 'i':
					{
						if (index == -1)
							index = va_arg(vl, int);
						else
							defense = va_arg(vl, int);

						break;
					}
					default: break; //err
					}

					++nrArgumentsAndTypes;
				}

				decreaseDefenseAlly(index, defense);

				va_end(vl);
			}
		}

		void decreaseDefenseEnemy(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 2)
			{
				//err
			}
			else
			{
				va_list vl;

				va_start(vl, nrArgumentsAndTypes);

				int index = -1, defense;

				while (*nrArgumentsAndTypes != '\0')
				{
					switch (*nrArgumentsAndTypes)
					{
					case 'i':
					{
						if (index == -1)
							index = va_arg(vl, int);
						else
							defense = va_arg(vl, int);

						break;
					}
					default: break; //err
					}

					++nrArgumentsAndTypes;
				}

				decreaseDefenseEnemy(index, defense);

				va_end(vl);
			}
		}

		void decreaseAttackAllies(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 1)
			{
				//err
			}
			else
			{
				va_list vl;

				va_start(vl, nrArgumentsAndTypes);

				int attack;

				while (*nrArgumentsAndTypes != '\0')
				{
					switch (*nrArgumentsAndTypes)
					{
					case 'i':
					{
						attack = va_arg(vl, int);
						break;
					}
					default: break; //err
					}

					++nrArgumentsAndTypes;
				}

				decreaseAttackAllies(attack);

				va_end(vl);
			}
		}

		void decreaseAttackEnemies(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 1)
			{
				//err
			}
			else
			{
				va_list vl;

				va_start(vl, nrArgumentsAndTypes);

				int attack;

				while (*nrArgumentsAndTypes != '\0')
				{
					switch (*nrArgumentsAndTypes)
					{
					case 'i':
					{
						attack = va_arg(vl, int);
						break;
					}
					default: break; //err
					}

					++nrArgumentsAndTypes;
				}

				decreaseAttackEnemies(attack);

				va_end(vl);
			}
		}

		void decreaseDefenseAllies(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 1)
			{
				//err
			}
			else
			{
				va_list vl;

				va_start(vl, nrArgumentsAndTypes);

				int defense;

				while (*nrArgumentsAndTypes != '\0')
				{
					switch (*nrArgumentsAndTypes)
					{
					case 'i':
					{
						defense = va_arg(vl, int);
						break;
					}
					default: break; //err
					}

					++nrArgumentsAndTypes;
				}

				decreaseDefenseAllies(defense);

				va_end(vl);
			}
		}

		void decreaseDefenseEnemies(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 1)
			{
				//err
			}
			else
			{
				va_list vl;

				va_start(vl, nrArgumentsAndTypes);

				int defense;

				while (*nrArgumentsAndTypes != '\0')
				{
					switch (*nrArgumentsAndTypes)
					{
					case 'i':
					{
						defense = va_arg(vl, int);
						break;
					}
					default: break; //err
					}

					++nrArgumentsAndTypes;
				}

				decreaseDefenseEnemies(defense);

				va_end(vl);
			}
		}

		void decreaseAttributesAlly(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 3)
			{
				//err
			}
			else
			{
				va_list vl;

				va_start(vl, nrArgumentsAndTypes);

				int index = -1, attack = -1, defense;

				while (*nrArgumentsAndTypes != '\0')
				{
					switch (*nrArgumentsAndTypes)
					{
					case 'i':
					{
						if (index == -1)
							index = va_arg(vl, int);
						else if (attack == -1)
							attack = va_arg(vl, int);
						else
							defense = va_arg(vl, int);

						break;
					}
					default: break; //err
					}

					++nrArgumentsAndTypes;
				}

				decreaseAttributesAlly(index, attack, defense);

				va_end(vl);
			}
		}

		void decreaseAttributesEnemy(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 3)
			{
				//err
			}
			else
			{
				va_list vl;

				va_start(vl, nrArgumentsAndTypes);

				int index = -1, attack = -1, defense;

				while (*nrArgumentsAndTypes != '\0')
				{
					switch (*nrArgumentsAndTypes)
					{
					case 'i':
					{
						if (index == -1)
							index = va_arg(vl, int);
						else if (attack == -1)
							attack = va_arg(vl, int);
						else
							defense = va_arg(vl, int);

						break;
					}
					default: break; //err
					}

					++nrArgumentsAndTypes;
				}

				decreaseAttributesEnemy(index, attack, defense);

				va_end(vl);
			}
		}

		void decreaseAttributesAllies(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 2)
			{
				//err
			}
			else
			{
				va_list vl;

				va_start(vl, nrArgumentsAndTypes);

				int attack = -1, defense;

				while (*nrArgumentsAndTypes != '\0')
				{
					switch (*nrArgumentsAndTypes)
					{
					case 'i':
					{
						if (attack == -1)
							attack = va_arg(vl, int);
						else
							defense = va_arg(vl, int);

						break;
					}
					default: break; //err
					}

					++nrArgumentsAndTypes;
				}

				decreaseAttributesAllies(attack, defense);

				va_end(vl);
			}
		}

		void decreaseAttributesEnemies(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 2)
			{
				//err
			}
			else
			{
				va_list vl;

				va_start(vl, nrArgumentsAndTypes);

				int attack = -1, defense;

				while (*nrArgumentsAndTypes != '\0')
				{
					switch (*nrArgumentsAndTypes)
					{
					case 'i':
					{
						if (attack == -1)
							attack = va_arg(vl, int);
						else
							defense = va_arg(vl, int);

						break;
					}
					default: break; //err
					}

					++nrArgumentsAndTypes;
				}

				decreaseAttributesEnemies(attack, defense);

				va_end(vl);
			}
		}

		void stealCard(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 0)
			{
				//err
			}
			else
			{
				stealCard();
			}
		}

		//avoid attack

		void stealAttributes(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 1)
			{
				//err
			}
			else
			{
				va_list vl;

				va_start(vl, nrArgumentsAndTypes);

				while (*nrArgumentsAndTypes != '\0')
				{
					switch (*nrArgumentsAndTypes)
					{
					case 'i':
					{
						int index = va_arg(vl, int);
						stealAttributes(index);
						break;
					}
					default: break; //err
					}

					++nrArgumentsAndTypes;
				}

				va_end(vl);
			}
		}

		//setnrlives

		void miss(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 2)
			{
				//err
			}
			else
			{
				va_list vl;

				va_start(vl, nrArgumentsAndTypes);

				int index = -1, nrAttacksToMiss;
				while (*nrArgumentsAndTypes != '\0')
				{
					switch (*nrArgumentsAndTypes)
					{
					case 'i':
					{
						if (index == -1)
							index = va_arg(vl, int);
						else
							nrAttacksToMiss = va_arg(vl, int);


						break;
					}
					default: break; //err
					}

					++nrArgumentsAndTypes;
				}

				miss(index, nrAttacksToMiss);

				va_end(vl);
			}
		}

		//setnrattacks

		void freezeAll(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 0)
			{
				//err
			}
			else
			{
				freezeAll();
			}
		}

		//checkprezente

		void checkPrezente(const char * nrArgumentsAndTypes, ...)
		{

		}

		//checkempowers

		void checkEmpowers(const char * nrArgumentsAndTypes, ...)
		{

		}

		void destroyTrump(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 0)
			{
				//err
			}
			else
			{
				destroyTrump();
			}
		}

		void destroySwag(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 1)
			{
				//err
			}
			else
			{
				va_list vl;

				va_start(vl, nrArgumentsAndTypes);

				int swag;
				while (*nrArgumentsAndTypes != '\0')
				{
					switch (*nrArgumentsAndTypes)
					{
					case 'i':
					{
						swag = va_arg(vl, int);

						break;
					}
					default: break; //err
					}

					++nrArgumentsAndTypes;
				}

				destroySwag(swag);

				va_end(vl);
			}
		}

		void nothing(const char * nrArgumentsAndTypes, ...)
		{
			if (strlen(nrArgumentsAndTypes) != 0)
			{
				//err
			}
			else
			{
				nothing();
			}
		}
	}
}