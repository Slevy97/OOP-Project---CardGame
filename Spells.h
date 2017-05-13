#ifndef SPELLS_H_INCLUDED
#define SPELLS_H_INCLUDED

#include <fstream>
#include <stdarg.h>

#define BufferDim 300

namespace Theta {

	namespace Spells {

		//Theta::Table* getTablePtr(); // set aside
		void invokeCharacter(int indexInDeck); //second type
											   //void wait(int turnsToWait); //third type
		void shuffleAttributes(); //first type
		void freeze(int index); //third type
		void merge(); //first type
		void destroy(int index); //third type

								 // increase

		void increaseAttackAlly(int index, int attack);
		void increaseAttackEnemy(int index, int attack);

		void increaseDefenseAlly(int index, int defense);
		void increaseDefenseEnemy(int index, int defense);

		void increaseAttackAllies(int attack);
		void increaseAttackEnemies(int attack);

		void increaseDefenseAllies(int defense);
		void increaseDefenseEnemies(int defense);

		void increaseAttributesAlly(int index, int attack, int defense);
		void increaseAttributesEnemy(int index, int attack, int defense);

		void increaseAttributesAllies(int attack, int defense); //third type
		void increaseAttributesEnemies(int attack, int defense); //fourth type

																 // decrease

		void decreaseAttackAlly(int index, int attack);
		void decreaseAttackEnemy(int index, int attack);

		void decreaseDefenseAlly(int index, int defense);
		void decreaseDefenseEnemy(int index, int defense);

		void decreaseAttackAllies(int attack);
		void decreaseAttackEnemies(int attack);

		void decreaseDefenseAllies(int defense);
		void decreaseDefenseEnemies(int defense);

		void decreaseAttributesAlly(int index, int attack, int defense);
		void decreaseAttributesEnemy(int index, int attack, int defense);

		void decreaseAttributesAllies(int attack, int defense); //third type
		void decreaseAttributesEnemies(int attack, int defense); //fourth type

		void stealCard(); //first type
						  //void avoidAttack(); //first type
		void stealAttributes(int index); //to see
										 //void setNrLives(int nrLives, int index); //
		void miss(int index, int nrAttacksToMiss);
		//void setNrAttacks();
		void freezeAll();
		void checkPrezente();
		void checkEmpowers();
		void destroyTrump();
		void destroySwag(int swag);

		void nothing();



		/* Varianta uniformizata a spell-urilor */



		//void getTablePtr(const char * nrArgumentsAndTypes, ...); // set aside
		void invokeCharacter(const char * nrArgumentsAndTypes, ...); //second type
																	 //void wait(const char * nrArgumentsAndTypes, ...); //third type
		void shuffleAttributes(const char * nrArgumentsAndTypes, ...); //first type
		void freeze(const char * nrArgumentsAndTypes, ...); //third type
		void merge(const char * nrArgumentsAndTypes, ...); //first type
		void destroy(const char * nrArgumentsAndTypes, ...); //third type


															 // increase

		void increaseAttackAlly(const char * nrArgumentsAndTypes, ...);
		void increaseAttackEnemy(const char * nrArgumentsAndTypes, ...);

		void increaseDefenseAlly(const char * nrArgumentsAndTypes, ...);
		void increaseDefenseEnemy(const char * nrArgumentsAndTypes, ...);

		void increaseAttackAllies(const char * nrArgumentsAndTypes, ...);
		void increaseAttackEnemies(const char * nrArgumentsAndTypes, ...);

		void increaseDefenseAllies(const char * nrArgumentsAndTypes, ...);
		void increaseDefenseEnemies(const char * nrArgumentsAndTypes, ...);

		void increaseAttributesAlly(const char * nrArgumentsAndTypes, ...);
		void increaseAttributesEnemy(const char * nrArgumentsAndTypes, ...);

		void increaseAttributesAllies(const char * nrArgumentsAndTypes, ...); //third type
		void increaseAttributesEnemies(const char * nrArgumentsAndTypes, ...); //fourth type

																			   // decrease

		void decreaseAttackAlly(const char * nrArgumentsAndTypes, ...);
		void decreaseAttackEnemy(const char * nrArgumentsAndTypes, ...);

		void decreaseDefenseAlly(const char * nrArgumentsAndTypes, ...);
		void decreaseDefenseEnemy(const char * nrArgumentsAndTypes, ...);

		void decreaseAttackAllies(const char * nrArgumentsAndTypes, ...);
		void decreaseAttackEnemies(const char * nrArgumentsAndTypes, ...);

		void decreaseDefenseAllies(const char * nrArgumentsAndTypes, ...);
		void decreaseDefenseEnemies(const char * nrArgumentsAndTypes, ...);

		void decreaseAttributesAlly(const char * nrArgumentsAndTypes, ...);
		void decreaseAttributesEnemy(const char * nrArgumentsAndTypes, ...);

		void decreaseAttributesAllies(const char * nrArgumentsAndTypes, ...); //third type
		void decreaseAttributesEnemies(const char * nrArgumentsAndTypes, ...); //fourth type

																			   //altele

		void stealCard(const char * nrArgumentsAndTypes, ...); //first type
															   //void avoidAttack(const char * nrArgumentsAndTypes, ...); //first type
		void stealAttributes(const char * nrArgumentsAndTypes, ...); //to see
																	 //void setNrLives(const char * nrArgumentsAndTypes, ...); //
		void miss(const char * nrArgumentsAndTypes, ...);
		//void setNrAttacks(const char * nrArgumentsAndTypes, ...);
		void freezeAll(const char * nrArgumentsAndTypes, ...);
		void checkPrezente(const char * nrArgumentsAndTypes, ...);
		void checkEmpowers(const char * nrArgumentsAndTypes, ...);
		void destroyTrump(const char * nrArgumentsAndTypes, ...);
		void destroySwag(const char * nrArgumentsAndTypes, ...);

		void nothing(const char * nrArgumentsAndTypes, ...);
	}

}

#endif // !SPELLS_H_INCLUDED