#ifndef EVENT_MANAGER_H_INCLUDED
#define EVENT_MANAGER_H_INCLUDED
#include "SFML\Graphics.hpp"

namespace Theta {

	/** EventManager - Singleton that handles the events
	* that occur in the application. **/

	class EventManager {

	private:
		static EventManager E_Manager;
		EventManager();
		EventManager(const EventManager&) {}
		void operator= (EventManager&) {}
		sf::Event event;
	public:
		~EventManager() {}
		static EventManager& getHandle() {
			return E_Manager;
		}
		void handleEvent(sf::Event& event);
		void detect_movement(); // function that handles that movement of the GameObject - CardSprite
		void detach_movement(); // function that lets off the GameObject - CardSprite from the movement action
		void mouse_outside();
		sf::Event getEvent() {
			return this->event;
		}
	};
}

#endif // !EVENT_MANAGER_H_INCLUDED
