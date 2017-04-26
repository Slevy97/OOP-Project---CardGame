#include <iostream>
#define _CRTDBG_MAP_ALLOC  
#include <cstdlib> 
#include <crtdbg.h>  
#include "ThetaEngine.h"

using namespace std;

int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	Theta::GameManager& G_Manager = Theta::ThetaEngine::getGameManager();
	Theta::InputManager& I_Manager = Theta::ThetaEngine::getInputManager();
	Theta::EventManager& E_Manager = Theta::ThetaEngine::getEventManager();
	Theta::Window& window = Theta::ThetaEngine::getWindow();
	sf::Event event;

	Theta::Table* ptr = new Theta::Table(window.getSize().x * 0.75f, window.getSize().y * 1.0f);

	G_Manager.add_GameObject(ptr);
	
	while (window.isOpen()) {

		while (window.pollEvent(event)) {
			
			E_Manager.handleEvent(event);
			if (event.type == sf::Event::KeyReleased) {

				if (event.key.code == sf::Keyboard::Q) {

					ptr->player_hand.add_card("cardback.png");
				}
				else if (event.key.code == sf::Keyboard::W) {
					ptr->player_hand.add_card("cardback2.png");
				}
				else if (event.key.code == sf::Keyboard::E) {
					ptr->player_hand.add_card("cardback3.png");
				}
			}
		}
		I_Manager.handleInput();
		G_Manager.draw_game();
	}

	G_Manager.erase_GameObjects();
	return 0;
}