#include "Menu.h"
#include <iostream>

using namespace Theta;

Menu::Menu(float width, float height, unsigned int n = 0, ...) {

	if (!font.loadFromFile("font.ttf"))
	{
		// handle error
	}
	/** **/
	va_list v_list;
	va_start(v_list, n);
	/** **/
	this->menu.resize(n);
	this->selectedItemIndex = 0;
	char* buffer;
	for (unsigned int i = 0; i < n; i++)
	{
		buffer = va_arg(v_list, char*);
		menu[i].setFont(font);
		menu[i].setCharacterSize(50);
		if (i == 2)
			menu[i].setFillColor(sf::Color::Black);
		else
			menu[i].setFillColor(sf::Color::White);
		menu[i].setString(buffer);
		menu[i].setPosition(sf::Vector2f(width / 2 - 50, height / n * i + height / (3 * n)));
	}
	va_end(v_list);
	if (menu.size() > 0)
	{
		menu[0].setFillColor(sf::Color::Red);
		menu[0].setStyle(sf::Text::Bold);
		menu[0].setCharacterSize(60);
	}
}

Menu::~Menu() {}

void Menu::draw(sf::RenderWindow& window) {

	for (unsigned int i = 0; i < menu.size(); i++)
		window.draw(menu[i]);
}

void Menu::MoveUp() {

	menu[this->selectedItemIndex].setFillColor(sf::Color::White);
	menu[this->selectedItemIndex].setStyle(sf::Text::Regular);
	menu[this->selectedItemIndex].setCharacterSize(50);
	if (--this->selectedItemIndex < 0)
		this->selectedItemIndex = menu.size() - 1;
	menu[this->selectedItemIndex].setFillColor(sf::Color::Red);
	menu[this->selectedItemIndex].setStyle(sf::Text::Bold);
	menu[this->selectedItemIndex].setCharacterSize(60);
}

void Menu::MoveDown() {

	menu[this->selectedItemIndex].setFillColor(sf::Color::White);
	menu[this->selectedItemIndex].setStyle(sf::Text::Regular);
	menu[this->selectedItemIndex].setCharacterSize(50);
	if (++this->selectedItemIndex >= menu.size())
		this->selectedItemIndex = 0;
	menu[this->selectedItemIndex].setFillColor(sf::Color::Red);
	menu[this->selectedItemIndex].setStyle(sf::Text::Bold);
	menu[this->selectedItemIndex].setCharacterSize(60);
}

void Menu::ShowWaiting()
{
	menu[2].setFillColor(sf::Color::White);
}

void Menu::changePoints(int i)
{
	if (i == 0)
		menu[2].setString("Waiting.");
	else if (i == 1)
		menu[2].setString("Waiting..");
	else if (i == 2)
		menu[2].setString("Waiting...");
}

void Menu::setSelectedItem(unsigned int indx) {

	if (indx != 2 && indx >= 0 && indx < menu.size())
	{
		menu[this->selectedItemIndex].setFillColor(sf::Color::White);
		menu[this->selectedItemIndex].setStyle(sf::Text::Regular);
		menu[this->selectedItemIndex].setCharacterSize(50);
		this->selectedItemIndex = indx;
		menu[this->selectedItemIndex].setFillColor(sf::Color::Red);
		menu[this->selectedItemIndex].setStyle(sf::Text::Bold);
		menu[this->selectedItemIndex].setCharacterSize(60);
	}
}

unsigned int Menu::collide(sf::Vector2i mouse_pos) const {

	for (unsigned int i = 0; i < menu.size(); i++)
	{
		if (menu[i].getGlobalBounds().contains(sf::Vector2f(mouse_pos)))
			return i;
	}
	return UNDEF;
}