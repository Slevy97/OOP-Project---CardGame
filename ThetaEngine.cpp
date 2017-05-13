#include "ThetaEngine.h"

using namespace Theta;

ThetaEngine::ThetaEngine() {

}

void ThetaEngine::Initialize() {

}

ThetaEngine::~ThetaEngine() {


}

ThetaEngine ThetaEngine::T_Engine;
Window& ThetaEngine::window(Window::getHandle());
GameManager& ThetaEngine::G_Manager(GameManager::getHandle());
EventManager& ThetaEngine::E_Manager(EventManager::getHandle());
InputManager& ThetaEngine::I_Manager(InputManager::getHandle());
NetworkManager& ThetaEngine::N_Manager(NetworkManager::getHandle());


bool Theta::isOnTheTable(sf::RectangleShape* moving_card, sf::RectangleShape* table) {

	const sf::Vector2f card_pos = moving_card->getPosition();
	const sf::Vector2f card_size = moving_card->getSize();
	const sf::Vector2f table_pos = table->getPosition();
	const sf::Vector2f table_size = table->getSize();

	if (table->getGlobalBounds().intersects(moving_card->getGlobalBounds())) {

		float x_axis[4] = { card_pos.x, card_pos.x + card_size.x, table_pos.x, table_pos.x + table_size.x };
		float y_axis[4] = { card_pos.y + card_size.y, card_pos.y, table_pos.y + table_size.y, table_pos.y };
		std::sort(x_axis, x_axis + 4);
		std::sort(y_axis, y_axis + 4);

		if ((x_axis[2] - x_axis[1]) * (y_axis[2] - y_axis[1]) - 0.5f * card_size.x * card_size.y > 1e-9)
			return true;
	}
	return false;
}