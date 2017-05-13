#include "ThetaEngine.h"
#include <iostream>

using namespace Theta;

std::list<GameObject*> GameObjects;
GameObject* moving = nullptr;
GameObject* attacking_cards[2] = { nullptr, nullptr };

CardSprite * Deck = nullptr;
int nrCards;
bool mark_deck[NR_MAX_CARDS_DECK];
std::vector<int> IndxAvailable;
std::map < int, bool > actsOnAllies;
/** **/
CardSprite Player;
CardSprite Enemy;
/** */
std::map < int, void(*)(const char *, ...) > abilities;
std::map < int, const char * > nrArgsAndTypes =
{
	{ 0, "i" },
	{ 1, "" },
	{ 2, "i" },
	{ 3, "" },
	{ 4, "i" },
	{ 5, "ii" },
	{ 6, "ii" },
	{ 7, "ii" },
	{ 8, "ii" },
	{ 9, "i" },
	{ 10, "i" },
	{ 11, "i" },
	{ 12, "i" },
	{ 13, "iii" },
	{ 14, "iii" },
	{ 15, "ii" },
	{ 16, "ii" },
	{ 17, "ii" },
	{ 18, "ii" },
	{ 19, "ii" },
	{ 20, "ii" },
	{ 21, "i" },
	{ 22, "i" },
	{ 23, "i" },
	{ 24, "i" },
	{ 25, "iii" },
	{ 26, "iii" },
	{ 27, "ii" },
	{ 28, "ii" },
	{ 29, "" },
	{ 30, "i" },
	{ 31, "ii" },
	{ 32, "" },
	{ 33, "" },
	{ 34, "i" },
	{ 35, "" }
};

std::map < int, bool > requiresIndex;

Theta::Table * ptr_table;


GameManager::GameManager() {

}

GameManager::~GameManager() {

	if (Deck != nullptr)
		delete[] Deck;
}

GameManager GameManager::G_Manager;

void GameManager::draw_game() {
	
	Window::getHandle().clear();
	for (std::list<GameObject*>::iterator it = GameObjects.begin(); it != GameObjects.end(); it++)
	{
		(*it)->draw(Window::getHandle());
	}
	Window::getHandle().display();
}

void GameManager::add_GameObject(GameObject* obj) {

	GameObjects.push_back(obj);
}

void GameManager::erase_GameObject(GameObject* obj) {

	std::list<GameObject*>::iterator it;
	for (it = GameObjects.begin(); it != GameObjects.end(); it++)
		if ((*it) == obj)
			break;
	if (it != GameObjects.end())
	{
		delete[] * it;
		GameObjects.erase(it);
	}
}

void GameManager::erase_GameObjects() {

	while (!GameObjects.empty())
	{
		delete[] * GameObjects.begin();
		GameObjects.pop_front();
	}
}

void GameManager::change_state() {

	if (Window::getHandle().isFullscreen() == false)
	{
		this->erase_GameObjects();
		Window::getHandle().goFullScreen();
	}
	else
	{
		this->erase_GameObjects();
		Window::getHandle().goStdScreen();
	}
}

bool Theta::GameManager::drag_card()
{
	if (IndxAvailable.size() && !ptr_table->player_hand.isFull()) {

		unsigned int rand_indx = rand() % IndxAvailable.size();
		ptr_table->player_hand.add_card(Deck[IndxAvailable[rand_indx]]);
		mark_deck[IndxAvailable[rand_indx]] = true;

		std::swap(IndxAvailable[rand_indx], IndxAvailable[IndxAvailable.size() - 1]);
		IndxAvailable.pop_back();
		return true;
	}
	else return false;
}

void create_players() {

	Player.createCardPtr();
	Player.getCardPtr()->setID(30);
	Player.getCardPtr()->setAttack(0);
	Player.getCardPtr()->setDefense(100);
	Player.getCardPtr()->setSwag(oo);
	Player.getCardPtr()->setMana(100);
	Player.getCardPtr()->setNrLives(1);
	Player.getCardPtr()->setTurnsToWait(0);
	Player.getCardPtr()->setNrAttacksToAvoid(0);
	Player.getCardPtr()->setNrAttacksToMiss(0);
	Player.SetCardSprite("player.png");
	/** **/
	ptr_table->player_table.add_card(Player);


	Enemy.createCardPtr();
	Enemy.getCardPtr()->setID(31);
	Enemy.getCardPtr()->setAttack(0);
	Enemy.getCardPtr()->setDefense(100);
	Enemy.getCardPtr()->setSwag(oo);
	Enemy.getCardPtr()->setMana(100);
	Enemy.getCardPtr()->setNrLives(1);
	Enemy.getCardPtr()->setTurnsToWait(0);
	Enemy.getCardPtr()->setNrAttacksToAvoid(0);
	Enemy.getCardPtr()->setNrAttacksToMiss(0);
	Enemy.SetCardSprite("player.png");


	ptr_table->enemy_table.add_card(Enemy);
}

bool GameManager::check_win() {
	
	if (Enemy.getCardPtr()->getDefense() <= 0)
		return true;
	return false;
}

bool GameManager::check_lose() {

	if (Player.getCardPtr()->getDefense() <= 0)
		return true;
	return false;
}

void GameManager::InitializeGame()
{
	std::list<GameObject*>::iterator it;
	for (it = GameObjects.begin(); it != GameObjects.end(); it++) { // get the table object

		ptr_table = dynamic_cast<Theta::Table*> (*it);
		if (ptr_table != nullptr) {
			break;
		}
	}

	/** **/
	create_players();
	/** **/

	//map spells and index requirements

	abilities[0] = Theta::Spells::invokeCharacter;								requiresIndex[0] = false;
	abilities[1] = Theta::Spells::shuffleAttributes;							requiresIndex[1] = false;
	abilities[2] = Theta::Spells::freeze;										requiresIndex[2] = true;					actsOnAllies[2] = false;
	abilities[3] = Theta::Spells::merge;										requiresIndex[3] = false;
	abilities[4] = Theta::Spells::destroy;										requiresIndex[4] = true;					actsOnAllies[4] = false;


	abilities[5] = Theta::Spells::increaseAttackAlly;							requiresIndex[5] = true;					actsOnAllies[5] = true;
	abilities[6] = Theta::Spells::increaseAttackEnemy;							requiresIndex[6] = true;					actsOnAllies[6] = false;

	abilities[7] = Theta::Spells::increaseDefenseAlly;							requiresIndex[7] = true;					actsOnAllies[7] = true;
	abilities[8] = Theta::Spells::increaseDefenseEnemy;							requiresIndex[8] = true;					actsOnAllies[8] = false;

	abilities[9] = Theta::Spells::increaseAttackAllies;							requiresIndex[9] = false;
	abilities[10] = Theta::Spells::increaseAttackEnemies;						requiresIndex[10] = false;

	abilities[11] = Theta::Spells::increaseDefenseAllies;						requiresIndex[11] = false;
	abilities[12] = Theta::Spells::increaseDefenseEnemies;						requiresIndex[12] = false;

	abilities[13] = Theta::Spells::increaseAttributesAlly;						requiresIndex[13] = true;					actsOnAllies[13] = true;
	abilities[14] = Theta::Spells::increaseAttributesEnemy;						requiresIndex[14] = true;					actsOnAllies[14] = false;

	abilities[15] = Theta::Spells::increaseAttributesAllies;					requiresIndex[15] = false;
	abilities[16] = Theta::Spells::increaseAttributesEnemies;					requiresIndex[16] = false;

	abilities[17] = Theta::Spells::decreaseAttackAlly;							requiresIndex[17] = true;					actsOnAllies[17] = true;
	abilities[18] = Theta::Spells::decreaseAttackEnemy;							requiresIndex[18] = true;					actsOnAllies[18] = false;

	abilities[19] = Theta::Spells::decreaseDefenseAlly;							requiresIndex[19] = true;					actsOnAllies[19] = true;
	abilities[20] = Theta::Spells::decreaseDefenseEnemy;						requiresIndex[20] = true;					actsOnAllies[20] = false;

	abilities[21] = Theta::Spells::decreaseAttackAllies;						requiresIndex[21] = false;
	abilities[22] = Theta::Spells::decreaseAttackEnemies;						requiresIndex[22] = false;

	abilities[23] = Theta::Spells::decreaseDefenseAllies;						requiresIndex[23] = false;
	abilities[24] = Theta::Spells::decreaseDefenseEnemies;						requiresIndex[24] = false;

	abilities[25] = Theta::Spells::decreaseAttributesAlly;						requiresIndex[25] = true;					actsOnAllies[25] = true;
	abilities[26] = Theta::Spells::decreaseAttributesEnemy;						requiresIndex[26] = true;					actsOnAllies[26] = false;

	abilities[27] = Theta::Spells::decreaseAttributesAllies;					requiresIndex[27] = false;
	abilities[28] = Theta::Spells::decreaseAttributesEnemies;					requiresIndex[28] = false;


	abilities[29] = Theta::Spells::stealCard;									requiresIndex[29] = false;
	abilities[30] = Theta::Spells::stealAttributes;								requiresIndex[30] = true;

	abilities[31] = Theta::Spells::miss;										requiresIndex[31] = true;
	abilities[32] = Theta::Spells::freezeAll;									requiresIndex[32] = false;

	abilities[33] = Theta::Spells::destroyTrump;								requiresIndex[33] = false;
	abilities[34] = Theta::Spells::destroySwag;									requiresIndex[34] = false;

	abilities[35] = Theta::Spells::nothing;										requiresIndex[35] = false;

	//parse file

	std::ifstream fin("cards.in");
	char buffer[BufferDim];
	int i;
	int nr;
	bool isNegative;

	fin >> nrCards;
	Deck = new CardSprite[nrCards];

	fin.getline(buffer, BufferDim, '\n'); //ignoram caracterele puse cu scop de a ne ajuta sa intelegem formatul fisierului

	for (int ind = 0; ind < nrCards; ++ind) {

		IndxAvailable.push_back(ind);

		i = 0;
		fin.getline(buffer, BufferDim, '\n');

		Deck[ind].createCardPtr();

		//ID

		nr = 0;
		while (buffer[i] >= '0' && buffer[i] <= '9')
		{
			nr = nr * 10 + (buffer[i] - '0');
			++i;
		}

		Deck[ind].getCardPtr()->setID(nr);

		//Attack

		while (buffer[i] != '-' && (buffer[i] < '0' || buffer[i] > '9')) ++i;

		if (buffer[i] == '-')
		{
			isNegative = true;
			++i;
		}
		else
		{
			isNegative = false;
		}

		nr = 0;
		while (buffer[i] >= '0' && buffer[i] <= '9')
		{
			nr = nr * 10 + (buffer[i] - '0');
			++i;
		}

		if (isNegative == true)
			nr *= -1;

		Deck[ind].getCardPtr()->setAttack(nr);

		//Defense

		while (buffer[i] != '-' && (buffer[i] < '0' || buffer[i] > '9')) ++i;

		if (buffer[i] == '-')
		{
			isNegative = true;
			++i;
		}
		else
		{
			isNegative = false;
		}

		nr = 0;
		while (buffer[i] >= '0' && buffer[i] <= '9')
		{
			nr = nr * 10 + (buffer[i] - '0');
			++i;
		}

		if (isNegative == true)
			nr *= -1;

		Deck[ind].getCardPtr()->setDefense(nr);

		//Swag

		while (buffer[i] != '-' && (buffer[i] < '0' || buffer[i] > '9')) ++i;

		if (buffer[i] == '-')
		{
			isNegative = true;
			++i;
		}
		else
		{
			isNegative = false;
		}

		nr = 0;
		while (buffer[i] >= '0' && buffer[i] <= '9')
		{
			nr = nr * 10 + (buffer[i] - '0');
			++i;
		}

		if (isNegative == true)
			nr *= -1;

		Deck[ind].getCardPtr()->setSwag(nr);

		//Mana

		while (buffer[i] != '-' && (buffer[i] < '0' || buffer[i] > '9')) ++i;

		if (buffer[i] == '-')
		{
			isNegative = true;
			++i;
		}
		else
		{
			isNegative = false;
		}

		nr = 0;
		while (buffer[i] >= '0' && buffer[i] <= '9')
		{
			nr = nr * 10 + (buffer[i] - '0');
			++i;
		}

		if (isNegative == true)
			nr *= -1;

		Deck[ind].getCardPtr()->setMana(nr);

		//NrLives

		while (buffer[i] != '-' && (buffer[i] < '0' || buffer[i] > '9')) ++i;

		if (buffer[i] == '-')
		{
			isNegative = true;
			++i;
		}
		else
		{
			isNegative = false;
		}

		nr = 0;
		while (buffer[i] >= '0' && buffer[i] <= '9')
		{
			nr = nr * 10 + (buffer[i] - '0');
			++i;
		}

		if (isNegative == true)
			nr *= -1;

		Deck[ind].getCardPtr()->setNrLives(nr);

		//TurnsToWait

		while (buffer[i] != '-' && (buffer[i] < '0' || buffer[i] > '9')) ++i;

		if (buffer[i] == '-')
		{
			isNegative = true;
			++i;
		}
		else
		{
			isNegative = false;
		}

		nr = 0;
		while (buffer[i] >= '0' && buffer[i] <= '9')
		{
			nr = nr * 10 + (buffer[i] - '0');
			++i;
		}

		if (isNegative == true)
			nr *= -1;

		Deck[ind].getCardPtr()->setTurnsToWait(nr);

		//NrAttacks

		while (buffer[i] != '-' && (buffer[i] < '0' || buffer[i] > '9')) ++i;

		if (buffer[i] == '-')
		{
			isNegative = true;
			++i;
		}
		else
		{
			isNegative = false;
		}

		nr = 0;
		while (buffer[i] >= '0' && buffer[i] <= '9')
		{
			nr = nr * 10 + (buffer[i] - '0');
			++i;
		}

		if (isNegative == true)
			nr *= -1;

		Deck[ind].getCardPtr()->setNrAttacks(nr);

		//NrAttacksToMiss

		while (buffer[i] != '-' && (buffer[i] < '0' || buffer[i] > '9')) ++i;

		if (buffer[i] == '-')
		{
			isNegative = true;
			++i;
		}
		else
		{
			isNegative = false;
		}

		nr = 0;
		while (buffer[i] >= '0' && buffer[i] <= '9')
		{
			nr = nr * 10 + (buffer[i] - '0');
			++i;
		}

		if (isNegative == true)
			nr *= -1;

		Deck[ind].getCardPtr()->setNrAttacksToMiss(nr);

		//NrAttacksToAvoid

		while (buffer[i] != '-' && (buffer[i] < '0' || buffer[i] > '9')) ++i;

		if (buffer[i] == '-')
		{
			isNegative = true;
			++i;
		}
		else
		{
			isNegative = false;
		}

		nr = 0;
		while (buffer[i] >= '0' && buffer[i] <= '9')
		{
			nr = nr * 10 + (buffer[i] - '0');
			++i;
		}

		if (isNegative == true)
			nr *= -1;

		Deck[ind].getCardPtr()->setNrAttacksToAvoid(nr);

		//Spell

		while (buffer[i] != '-' && (buffer[i] < '0' || buffer[i] > '9')) ++i;

		if (buffer[i] == '-')
		{
			isNegative = true;
			++i;
		}
		else
		{
			isNegative = false;
		}

		nr = 0;
		while (buffer[i] >= '0' && buffer[i] <= '9')
		{
			nr = nr * 10 + (buffer[i] - '0');
			++i;
		}

		if (isNegative == true)
			nr *= -1;

		Deck[ind].getCardPtr()->setSpell(nr); //set the spell index

		int nrArgumentsToRead = strlen(nrArgsAndTypes[nr]) - (requiresIndex[nr] == true ? 1 : 0);
		if (nrArgumentsToRead >= 1) {
			for (int j = 0; j < nrArgumentsToRead; ++j)
			{
				while (buffer[i] < '0' || buffer[i] > '9') ++i;

				if (buffer[i] == '-')
				{
					isNegative = true;
					++i;
				}
				else
				{
					isNegative = false;
				}

				int nr1 = 0;
				while (buffer[i] >= '0' && buffer[i] <= '9')
				{
					nr1 = nr1 * 10 + (buffer[i] - '0');
					++i;
				}

				if (isNegative == true)
					nr1 *= -1;
				Deck[ind].getCardPtr()->addArg(nr1);
			}
		}

		//WhereToFind

		while (!((buffer[i] >= 'A' && buffer[i] <= 'Z') || (buffer[i] >= 'a' && buffer[i] <= 'z'))) ++i;

		std::string whereToFind;
		while (buffer[i] != '\0' && buffer[i] != '\n')
		{
			whereToFind.push_back(buffer[i]);
			++i;
		}

		Deck[ind].SetCardSprite(whereToFind);

	}

	mark_deck[29] = true;
	mark_deck[30] = true;
	IndxAvailable.erase(find(IndxAvailable.begin(), IndxAvailable.end(), 29));
	IndxAvailable.erase(find(IndxAvailable.begin(), IndxAvailable.end(), 30));

	fin.close();
}