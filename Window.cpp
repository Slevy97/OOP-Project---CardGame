#include "Window.h"

using namespace Theta;

Window::Window() : RenderWindow(sf::VideoMode(STD_WIDTH, STD_HEIGHT), "CARD GAME", sf::Style::Titlebar | sf::Style::Close) {

	this->clear();
	this->display();
	videoModes = sf::VideoMode::getFullscreenModes();
	this->goFullScreen();
}

Window Window::window;

void Window::goFullScreen() {

	if (_isFullScreen == false) {

		this->create(videoModes[0], "CARD GAME", sf::Style::Fullscreen);
		_isFullScreen = true;
	}
}

void Window::goStdScreen() {

	if (_isFullScreen == true) {
		this->create(sf::VideoMode(STD_WIDTH, STD_HEIGHT), "CARD GAME", sf::Style::Titlebar | sf::Style::Close);
		_isFullScreen = false;
	}
}