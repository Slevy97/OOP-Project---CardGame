#ifndef THETA_ENGINE_H_INCLUDED
#define THETA_ENGINE_H_INCLUDED

#include "GameManager.h"
#include "InputManager.h"
#include "EventManager.h"
#include "NetworkManager.h"
#include "Window.h"
#include "Table.h"
#include "GameTable.h"
#include "FinalLayer.h"
#include "Menu.h"
#include "Spells.h"
#include "SFML\Graphics.hpp"
#include "SFML\Network.hpp"
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <bitset>
#include <thread>
#include <unordered_map>
#include <map>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <Windows.h>
#include <sstream>
#define UNDEF -1
#define oo (1 << 30)

namespace Theta {

	/** ThetaEngine - Singleton that manages all the components of the game:
	* -	GameManager
	* -	EventManager
	* -	InputManager
	* -	Window
	**/
	class ThetaEngine {

	private:
		static ThetaEngine T_Engine;
		static GameManager& G_Manager;
		static EventManager& E_Manager;
		static InputManager& I_Manager;
		static NetworkManager& N_Manager;
		static Window& window;
		ThetaEngine();
		ThetaEngine(const ThetaEngine&) {}
		void operator=(const ThetaEngine&) {}
	public:
		~ThetaEngine();
		void Initialize();
		static ThetaEngine& getHandle() {
			return T_Engine;
		}
		static GameManager& getGameManager() {
			return G_Manager;
		}
		static EventManager& getEventManager() {
			return E_Manager;
		}
		static InputManager& getInputManager() {
			return I_Manager;
		}
		static Window& getWindow() {
			return window;
		}
		static NetworkManager& getNetworkManager() {
			return N_Manager;
		}
	};

	bool isOnTheTable(sf::RectangleShape* moving_card, sf::RectangleShape* table);
}

#endif // !THETA_ENGINE_H_INCLUDED

