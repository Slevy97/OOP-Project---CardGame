#ifndef GAME_MANAGER_H_INCLUDED
#define GAME_MANAGER_H_INCLUDED
#include "GameObject.h"
#include <list>

namespace Theta {

	/** GameManager - Singleton that manages the game. **/

	class GameManager {

	private:
		static GameManager G_Manager;
		GameManager();
		GameManager(const GameManager&) {}
		void operator= (GameManager&) {}
		
	public:
		~GameManager() {}
		static GameManager& getHandle() {
			return G_Manager;
		}
		void draw_game();
		void add_GameObject(GameObject*); // function that adds GameObjects in the game in order to be drawn
		void erase_GameObject(GameObject*); // function that erases a GameObject from the list of GameObjects 
		void erase_GameObjects(); // function that erases all the GameObjects from the game
		void change_state(); // function that changes the state of the window (windowed, fullscreen)
	};
}

#endif // !GAME_MANAGER_H_INCLUDED
