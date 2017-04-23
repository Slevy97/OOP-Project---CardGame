#ifndef INPUT_MANAGER_H_INCLUDED
#define INPUT_MANAGER_H_INCLUDED

namespace Theta {

	/**	InputManager - Singleton that handles the input events
	* that occur in the application.
	**/

	class InputManager {

	private:
		static InputManager I_Manager;
		InputManager();
		InputManager(const InputManager&) {}
		void operator= (InputManager&) {}
		sf::Vector2i mouse_oldpos;
	public:
		~InputManager() {}
		static InputManager& getHandle() {
			return I_Manager;
		}
		void handleInput();
		sf::Vector2i get_mouse_oldpos();
		void set_mouse_oldpos(sf::Vector2i);
	};
}

#endif // !INPUT_MANAGER_H_INCLUDED
