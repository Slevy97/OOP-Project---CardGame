#include "ThetaEngine.h"
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace Theta;

extern std::list<GameObject*> GameObjects;
extern GameObject* moving;

EventManager::EventManager() {}

EventManager EventManager::E_Manager;

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
			mouse_outside();
			break;

		case sf::Event::MouseButtonPressed:
			if (event.key.code == sf::Mouse::Left)
				detect_movement();
			break;
		case sf::Event::MouseButtonReleased:
			if (event.key.code == sf::Mouse::Left)
				detach_movement();
			break;
		default: break;
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

						if (!ptr_table->player_table.isFull()) { // if it can be moved , move it to the player_table

							ptr_table->player_table.copy_card(&ptr_table->player_hand, indx_card);
							ptr_table->player_hand.erase_card(indx_card); 
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

