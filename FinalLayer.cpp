#include "ThetaEngine.h"
#include <iostream>

using namespace Theta;

FinalLayer::FinalLayer(float width, float height) {

	this->setPosition(width / 5, height / 2);
	this->setSize(sf::Vector2f(width / 4, height / 3));

	if (!font.loadFromFile("Cocogoose_trial.otf"))
	{
		std::cout << "Could not load font!\n";
	}

	this->finaltext.setFont(font);
	this->finaltext.setCharacterSize((60 * Window::getHandle().getSize().x) / FULL_WIDTH);
	this->finaltext.setFillColor(sf::Color::Green);
	this->finaltext.setPosition(this->getPosition());
}

FinalLayer::~FinalLayer() {

}
///
void FinalLayer::draw(sf::RenderWindow& window) {

	//window.draw((sf::RectangleShape) (*this));
	this->finaltext.draw(window);
}

void FinalLayer::setRectTexture(const std::string& where_to_find) {
	
	if (where_to_find != "\0") {

		if (!table_texture.loadFromFile(where_to_find)) {

			std::cerr << "Error: Could not open program's data !\n";
			exit(1);
		}
		this->setTexture(&(this->table_texture));
	}
}

void FinalLayer::setString(const std::string& final) {

	this->finaltext.setString(final);
}