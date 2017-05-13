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

/** **/
CardSprite Player;
CardSprite Enemy;
/** */



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