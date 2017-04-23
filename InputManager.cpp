#include "ThetaEngine.h"

using namespace Theta;

extern std::list<GameObject*> GameObjects;
extern GameObject* moving;

InputManager::InputManager() {


}

InputManager InputManager::I_Manager;

void InputManager::set_mouse_oldpos(sf::Vector2i obj) {

	this->mouse_oldpos = obj;
}

sf::Vector2i InputManager::get_mouse_oldpos() {

	return this->mouse_oldpos;
}

void InputManager::handleInput() {

	std::list<GameObject*>::iterator it;
	for (it = GameObjects.begin(); it != GameObjects.end(); it++)
	{
		Theta::Table* ptr_table = dynamic_cast<Theta::Table*> (*it);
		if (ptr_table != nullptr) {

			if (moving == nullptr) {

				for (unsigned int i = 0; i < ptr_table->player_hand.nr_cards; i++) {

					/** Detect if mouse is on any card in order to get highlight **/
					if (ptr_table->player_hand.PH_CARDS[i].getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(Window::getHandle()))) {

						if (ptr_table->player_hand.PH_CARDS[i].ok_highlight == false) {

							ptr_table->player_hand.PH_CARDS[i].ok_highlight = true;
							ptr_table->player_hand.PH_CARDS[i].change_state();

						}
					}
					else {

						if (ptr_table->player_hand.PH_CARDS[i].ok_highlight == true) {

							ptr_table->player_hand.PH_CARDS[i].ok_highlight = false;
							ptr_table->player_hand.PH_CARDS[i].change_state();

						}

					}
				}
			}
			if (moving != nullptr) {

				CardSprite* moving_card = static_cast<CardSprite*>(moving);

				sf::Vector2i mouse_newpos = sf::Mouse::getPosition(Window::getHandle());
				sf::Vector2f current_pos = moving_card->getPosition();
				current_pos.x += (mouse_newpos.x - mouse_oldpos.x);
				current_pos.y += (mouse_newpos.y - mouse_oldpos.y);

				if (ptr_table->getGlobalBounds().contains(current_pos) && ptr_table->getGlobalBounds().contains(current_pos + moving_card->getSize())) {
					moving_card->setPosition(current_pos);
				}
				mouse_oldpos = mouse_newpos;
			}
		}
	}
}