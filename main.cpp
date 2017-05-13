#include <iostream>
#include "ThetaEngine.h"

using namespace std;

Theta::Table* ptr;
bool myTurn = false;
bool adatesc = false;

int main() {

	srand(time(NULL));

	Theta::GameManager& G_Manager = Theta::ThetaEngine::getGameManager();
	Theta::InputManager& I_Manager = Theta::ThetaEngine::getInputManager();
	Theta::EventManager& E_Manager = Theta::ThetaEngine::getEventManager();
	Theta::NetworkManager& N_Manager = Theta::ThetaEngine::getNetworkManager();
	Theta::Window& window = Theta::ThetaEngine::getWindow();
	sf::Event event;
	std::string final_text;

	Theta::Menu* ptrmenu = new Theta::Menu(window.getSize().x, window.getSize().y, 3, "Play", "Exit", "Waiting...");
	G_Manager.add_GameObject(ptrmenu);

	bool inmeniu = true;
	bool adatplay = false;

	int i = 0;
	N_Manager.acquireplayerID();
	N_Manager.getTurnNow();
	while (window.isOpen() && inmeniu)
	{
		while (window.pollEvent(event)) {
			switch (event.type) // if the event type is:
			{
			case sf::Event::MouseMoved:
				ptrmenu->setSelectedItem(ptrmenu->collide(sf::Mouse::getPosition(window)));
				break;
			case sf::Event::MouseButtonPressed:
				if (event.key.code == sf::Mouse::Left && ptrmenu->collide(sf::Mouse::getPosition(window)) != UNDEF)
				{
					if (ptrmenu->getSelectedItem() == 0 && !adatplay)
					{
						adatplay = true;
						N_Manager.play();
						ptrmenu->ShowWaiting();
					}
					else if (ptrmenu->getSelectedItem() == 1)
					{
						inmeniu = false;
						adatesc = true;
						window.close();
					}
				}
				break;
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
				break;
			}
		}
		G_Manager.draw_game();
		if (adatplay)
		{
			if (N_Manager.checkStart())
				inmeniu = false;
			ptrmenu->changePoints(i);
			i++;
			if (i > 2)
				i = 0;
		}
	}
	G_Manager.erase_GameObjects();
	
	ptr = new Theta::Table(window.getSize().x * 0.75f, window.getSize().y * 1.0f);
	Theta::GameTable* ptr2 = new Theta::GameTable(window.getSize().x, window.getSize().y);
	G_Manager.add_GameObject(ptr);
	G_Manager.add_GameObject(ptr2);
	G_Manager.InitializeGame();

	bool inGame = true;
	G_Manager.drag_card();
	if (!adatesc)
	{
		while (window.isOpen() && inGame) {

			while (window.pollEvent(event)) {

				if (myTurn)
					E_Manager.handleEvent(event);
				if (event.type == sf::Event::MouseButtonReleased) {

					if (myTurn)
					{
						//
					}
					if (event.key.code == sf::Mouse::Left)
					{
						E_Manager.checkGameTableClose();
					}
				}		
			}
			if (myTurn)
				I_Manager.handleInput();
			else
			{
				N_Manager.checkAction();
				N_Manager.getTurn();
			}

			E_Manager.update_players();

			/** Check for win or lose **/

			if (G_Manager.check_win())
			{
				final_text = "You won !! Press any key to exit !!";
				inGame = false;
			}
			else if (G_Manager.check_lose()) {
				final_text = "You lost !! Press any key to exit !!";
				inGame = false;
			}
			G_Manager.draw_game();
		}
	}

	Theta::FinalLayer* ptrf = new Theta::FinalLayer(window.getSize().x * 1.0f, window.getSize().y * 1.0f);
	G_Manager.add_GameObject(ptrf);
	ptrf->setString(final_text);

	while (window.isOpen()) {

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::KeyReleased) {
				window.close();
			}
		}
		G_Manager.draw_game();
	}

	G_Manager.erase_GameObjects();
	N_Manager.restart();
	return 0;
}