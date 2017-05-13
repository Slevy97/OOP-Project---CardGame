#include "ThetaEngine.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <Windows.h>

using namespace Theta;

extern std::list<GameObject*> GameObjects;
extern GameObject* moving;
extern GameObject* attacking_cards[2];
std::queue<std::thread> threads;
std::unordered_map<std::string, void (EventManager::*) () > functions;
extern CardSprite Player;
extern CardSprite Enemy;
extern std::map < int, bool > actsOnAllies;
/** **/
extern std::map < int, void(*)(const char *, ...) > abilities;
extern std::map < int, const char * > nrArgsAndTypes;
extern std::map < int, bool > requiresIndex;

EventManager::EventManager() {

	functions[std::string("mouse_outside")] = &EventManager::mouse_outside;
	functions[std::string("detect_movement")] = &EventManager::detect_movement;
	functions[std::string("detect_attack")] = &EventManager::detect_attack;
	functions[std::string("detach_movement")] = &EventManager::detach_movement;
	functions[std::string("checkGameTableInteractions")] = &EventManager::checkGameTableInteractions;
}

EventManager EventManager::E_Manager;

void add_thread(const std::string& f_name) {

	threads.push(std::thread(functions[f_name], &EventManager::getHandle()));
}

void clear_threads() {

	while (!threads.empty())
	{
		if (threads.front().joinable())
			threads.front().join();
		threads.pop();
	}
}

void EventManager::handleEvent(sf::Event& event) {

	this->event = event;
	switch (event.type) {

		case sf::Event::Closed:
			Window::getHandle().close();
			break;
		case sf::Event::MouseEntered:
			break;
		case sf::Event::MouseLeft:
			break;
		case sf::Event::MouseMoved:
			add_thread("mouse_outside");
			break;

		case sf::Event::MouseButtonPressed:
			if (event.key.code == sf::Mouse::Left)
			{
				add_thread("detect_movement");
				add_thread("detect_attack");
				update_players();
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (event.key.code == sf::Mouse::Left)
			{
				add_thread("detach_movement");
				add_thread("checkGameTableInteractions");
				update_players();
			}
			break;
		default: break;
	}
	clear_threads();
}

void EventManager::update_players() {

	std::list<GameObject*>::iterator it;
	for (it = GameObjects.begin(); it != GameObjects.end(); it++) {

		Theta::Table* ptr_table = dynamic_cast<Theta::Table*> (*it);
		if (ptr_table != nullptr) {
			
			Player.getCardPtr()->setDefense(ptr_table->player_table.getCard(0).getCardPtr()->getDefense());
			Enemy.getCardPtr()->setDefense(ptr_table->enemy_table.getCard(0).getCardPtr()->getDefense());
		}
	}
}

void EventManager::erase_cards() {

	std::list<GameObject*>::iterator it;
	for (it = GameObjects.begin(); it != GameObjects.end(); it++) {

		Theta::Table* ptr_table = dynamic_cast<Theta::Table*> (*it);
		if (ptr_table != nullptr) {

			for (int i = 1; i < ptr_table->player_table.getNrCards(); i++) {

				if (ptr_table->player_table.PH_CARDS[i].card_ptr->getDefense() <= 0) {

					ptr_table->player_table.erase_card(i);
					i--;
				}
				
			}
			for (int i = 1; i < ptr_table->enemy_table.getNrCards(); i++) {

				if (ptr_table->enemy_table.PH_CARDS[i].card_ptr->getDefense() <= 0) {

					ptr_table->enemy_table.erase_card(i);
					i--;
				}
			}
		}
	}
}

void EventManager::mouse_outside() {

	if (moving != nullptr) {  // checks if any object is moving

		std::list<GameObject*>::iterator it;
		Theta::Table* ptr_table = nullptr;
		for (it = GameObjects.begin(); it != GameObjects.end(); it++) { // get the table object

			ptr_table = dynamic_cast<Theta::Table*> (*it);
			if (ptr_table != nullptr) {
				break;
			}
		}

		if (ptr_table != nullptr)
		{
			CardSprite* moving_card = static_cast<CardSprite*>(moving);
			sf::Vector2f current_pos = moving_card->getPosition();

			unsigned int indx_card = UNDEF;
			for (unsigned int i = 0; i < ptr_table->player_hand.nr_cards; i++) { // get the index of the moving card in the Cardzone

				if (&ptr_table->player_hand.PH_CARDS[i] == moving_card) {

					indx_card = i;
					break;
				}
			}

			if (indx_card != UNDEF) {

				// if the mouse gets out the table while there is a moving card, move the card back to its initial position
				if (!ptr_table->getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(Window::getHandle()))) {
					sf::Vector2f initial_pos = ptr_table->player_hand.PH_CARDS[indx_card].initial_pos;
					ptr_table->player_hand.PH_CARDS[indx_card].setPosition(initial_pos);
					moving = nullptr;
				}
			}
		}
	}
}

void EventManager::detect_movement() {

	InputManager::getHandle().set_mouse_oldpos(sf::Mouse::getPosition(Window::getHandle()));
	std::list<GameObject*>::iterator it;
	for (it = GameObjects.begin(); it != GameObjects.end(); it++) {

		Theta::Table* ptr_table = dynamic_cast<Theta::Table*> (*it);
		if (ptr_table != nullptr) {

			for (unsigned int i = 0; i < ptr_table->player_hand.nr_cards; i++) {

				// if the mouse is clicked on any card from the player hand
				if (ptr_table->player_hand.PH_CARDS[i].getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(Window::getHandle()))) {

					if (ptr_table->player_hand.PH_CARDS[i].isCard && ptr_table->player_hand.PH_CARDS[i].isRect) {

						if (moving == nullptr) // if no other card was already chosen
							moving = &ptr_table->player_hand.PH_CARDS[i];
						break;
					}
				}
			}
		}
	}
}

bool enough_mana(int indx) {

	std::list<GameObject*>::iterator it;
	Theta::Table* ptr_table = nullptr;
	for (it = GameObjects.begin(); it != GameObjects.end(); it++) { // get the table object

		ptr_table = dynamic_cast<Theta::Table*> (*it);
		if (ptr_table != nullptr) {
			break;
		}
	}

	if (ptr_table != nullptr)
	{
		int card_mana = ptr_table->player_hand.getCard(indx).getCardPtr()->getMana();
		int player_mana = Player.getCardPtr()->getMana();
		if (player_mana >= card_mana) {

			Player.getCardPtr()->setMana(player_mana - card_mana);
			return true;
		}
	}
	return false;
}

void EventManager::detach_movement() {

	if (moving != nullptr) {  // checks if any object is moving

		std::list<GameObject*>::iterator it;
		Theta::Table* ptr_table = nullptr;
		for (it = GameObjects.begin(); it != GameObjects.end(); it++) { // get the table object

			ptr_table = dynamic_cast<Theta::Table*> (*it);
			if (ptr_table != nullptr) {
				break;
			}
		}

		if (ptr_table != nullptr)
		{
			CardSprite* moving_card = static_cast<CardSprite*>(moving);
			sf::Vector2f current_pos = moving_card->getPosition();

			unsigned int indx_card = UNDEF;
			for (unsigned int i = 0; i < ptr_table->player_hand.nr_cards; i++) { // get the index of the moving card in the Cardzone

				if (&ptr_table->player_hand.PH_CARDS[i] == moving_card) {

					indx_card = i;
					break;
				}
			}

			if (indx_card != UNDEF) {

				if (isOnTheTable(moving_card, &ptr_table->player_table) || isOnTheTable(moving_card, &ptr_table->enemy_table)) { // if the card is on the player_table

					sf::Vector2f initial_pos = ptr_table->player_hand.PH_CARDS[indx_card].initial_pos;
					ptr_table->player_hand.PH_CARDS[indx_card].setPosition(initial_pos); // put the card moved in the initial position

					if (!ptr_table->player_table.isFull() && enough_mana(indx_card)) { // if it can be moved , move it to the player_table

						ptr_table->player_table.copy_card(&ptr_table->player_hand, indx_card);
						ptr_table->player_hand.erase_card(indx_card);

						/** Call the card spell **/
					
						int SpellIndex = ptr_table->player_table.getCard(ptr_table->player_table.getNrCards() - 1).getCardPtr()->getSpell();
						std::vector<int> args = ptr_table->player_table.getCard(ptr_table->player_table.getNrCards() - 1).getCardPtr()->getArgs();
						if (requiresIndex[SpellIndex] == false)
						{
							switch (strlen(nrArgsAndTypes[SpellIndex])) {

								case 0:
									abilities[SpellIndex](nrArgsAndTypes[SpellIndex]);
									break;
								case 1:
									abilities[SpellIndex](nrArgsAndTypes[SpellIndex], args[0]);
									break;
								case 2:
									abilities[SpellIndex](nrArgsAndTypes[SpellIndex], args[0], args[1]);
									break;
								case 3: 
									abilities[SpellIndex](nrArgsAndTypes[SpellIndex], args[0], args[1], args[2]);
									break;
							}
						}
						else
						{
							int indexAlly = rand() % ptr_table->player_table.getNrCards();
							int indexEnemy = rand() % ptr_table->enemy_table.getNrCards();

							switch (strlen(nrArgsAndTypes[SpellIndex])) {

								case 0:
									abilities[SpellIndex](nrArgsAndTypes[SpellIndex]);
									break;
								case 1:
									if (actsOnAllies[SpellIndex])
										abilities[SpellIndex](nrArgsAndTypes[SpellIndex], indexAlly);
									else
										abilities[SpellIndex](nrArgsAndTypes[SpellIndex], indexEnemy);

									break;
								case 2:
									if (actsOnAllies[SpellIndex])
										abilities[SpellIndex](nrArgsAndTypes[SpellIndex], indexAlly, args[0]);
									else
										abilities[SpellIndex](nrArgsAndTypes[SpellIndex], indexEnemy, args[0]);

									break;
								case 3:
									if (actsOnAllies[SpellIndex])
										abilities[SpellIndex](nrArgsAndTypes[SpellIndex], indexAlly, args[0], args[1]);
									else
										abilities[SpellIndex](nrArgsAndTypes[SpellIndex], indexEnemy, args[0], args[1]);
									break;
							}
						}
						erase_cards();
						NetworkManager::getHandle().sendTable();
					}
				}
				else { // if the card is not on the player_table and is dropped, move it to the initial position

					sf::Vector2f initial_pos = ptr_table->player_hand.PH_CARDS[indx_card].initial_pos;
					ptr_table->player_hand.PH_CARDS[indx_card].setPosition(initial_pos);
				}
			}
		}
		moving = nullptr;
	}
}

void EventManager::reset_attack() {

	CardSprite* aux;
	if (attacking_cards[0] != nullptr)
	{
		aux = static_cast<CardSprite*> (attacking_cards[0]);
		if (aux->is_ready_for_attack == true)
		{
			aux->change_attack_state();
			aux->is_ready_for_attack = false;
		}
		attacking_cards[0] = nullptr;
	}
	if (attacking_cards[1] != nullptr)
	{
		aux = static_cast<CardSprite*> (attacking_cards[1]);
		if (aux->is_ready_for_attack == true)
		{
			aux->change_attack_state();
			aux->is_ready_for_attack = false;
		}
		attacking_cards[1] = nullptr;
	}
}

void EventManager::detect_attack() {

	std::list<GameObject*>::iterator it;
	for (it = GameObjects.begin(); it != GameObjects.end(); it++) {

		Theta::Table* ptr_table = dynamic_cast<Theta::Table*> (*it);
		if (ptr_table != nullptr) {

			for (unsigned int i = 0; i < ptr_table->player_table.nr_cards; i++) {

				// if the mouse is clicked on any card from the player table
				if (ptr_table->player_table.PH_CARDS[i].getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(Window::getHandle()))) {

					if (ptr_table->player_table.PH_CARDS[i].isCard && ptr_table->player_table.PH_CARDS[i].isRect && ptr_table->player_table.PH_CARDS[i].card_ptr->canAttack()) {

						/** **/
						if (attacking_cards[0] == nullptr) {

							if (ptr_table->player_table.PH_CARDS[i].is_ready_for_attack == false) {
								attacking_cards[0] = &ptr_table->player_table.PH_CARDS[i];
								ptr_table->player_table.PH_CARDS[i].change_attack_state();
								ptr_table->player_table.PH_CARDS[i].is_ready_for_attack = true;
							}
						}
						else
						{
							if (attacking_cards[0] == &ptr_table->player_table.PH_CARDS[i]) {

								if (ptr_table->player_table.PH_CARDS[i].is_ready_for_attack == true) {
									ptr_table->player_table.PH_CARDS[i].is_ready_for_attack = false;
									ptr_table->player_table.PH_CARDS[i].change_attack_state();
									attacking_cards[0] = nullptr;
								}
							}
						}
						/** **/
						break;
					}
				}
			}

			for (unsigned int i = 0; i < ptr_table->enemy_table.nr_cards; i++) {

				if (ptr_table->enemy_table.PH_CARDS[i].getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(Window::getHandle()))) {

					if (ptr_table->enemy_table.PH_CARDS[i].isCard && ptr_table->enemy_table.PH_CARDS[i].isRect) {

						if (attacking_cards[0] != nullptr) {

							attacking_cards[1] = &ptr_table->enemy_table.PH_CARDS[i];
							attack_cards(i);
							break;
						}

					}

				}
			}
		}
	}
}

void EventManager::attack_cards(int indx_enemy_card) {

	CardSprite* card;

	if (attacking_cards[0] != nullptr && attacking_cards[1] != nullptr) {

		/** Do the attack !!**/

		card = static_cast<CardSprite*> (attacking_cards[0]);
		card->getCardPtr()->setTurnsToWait(card->getCardPtr()->getTurnsToWait() + 1);
		unsigned int player_attack = card->getCardPtr()->getAttack();
		Spells::decreaseDefenseEnemy(indx_enemy_card, player_attack);

		card = static_cast<CardSprite*> (attacking_cards[1]);
		this->reset_attack();

		if (indx_enemy_card != 0) {

			if (card->getCardPtr()->getDefense() <= 0)
				Spells::destroy(indx_enemy_card);
		}

		NetworkManager::getHandle().sendTable();
	}
}

void EventManager::checkGameTableInteractions()
{
	std::list<GameObject*>::iterator it;
	for (it = GameObjects.begin(); it != GameObjects.end(); it++) {

		Theta::GameTable * ptr_gt = dynamic_cast<Theta::GameTable *> (*it);

		if (ptr_gt != nullptr)
		{
			if (ptr_gt->getEndTurnButtonGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(Window::getHandle())))
			{
				NetworkManager::getHandle().endTurn();
			}
		}
	}
}

void EventManager::checkGameTableClose()
{
	std::list<GameObject*>::iterator it;
	for (it = GameObjects.begin(); it != GameObjects.end(); it++) {

		Theta::GameTable * ptr_gt = dynamic_cast<Theta::GameTable *> (*it);

		if (ptr_gt != nullptr)
		{

			if (ptr_gt->getExitButtonGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(Window::getHandle())))
			{
				Window::getHandle().close();
			}
		}
	}
}