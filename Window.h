#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include "SFML\Graphics.hpp"
#include <vector>

#define STD_WIDTH 1024
#define STD_HEIGHT 768

namespace Theta {

	/** Window - Theta class that represents the window of the game **/
	class Window : public sf::RenderWindow {

	private:
		static Window window;
		Window();
		Window(const Window&) {}
		void operator=(const Window& window) {}
		/** **/
		std::vector<sf::VideoMode> videoModes;
		bool _isFullScreen = false;
	public:

		~Window() {}
		static Window& getHandle() {
			return window;
		}
		/** **/
		bool isFullscreen() {
			return _isFullScreen;
		}
		void goFullScreen();
		void goStdScreen();
	};
}

#endif // !WINDOW_H_INCLUDED

