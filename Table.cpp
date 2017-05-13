#include "Table.h"
#include <iostream>

using namespace Theta;

extern GameObject* moving;

Table::Table(float width, float height) :

	player_hand(width, 0.33f * height, 0.0f, 0.66f * height),
	player_table(width, 0.33f * height, 0.0f, 0.33f * height),
	enemy_table(width, 0.33f * height, 0.0f, 0.0f) {

	this->setSize(sf::Vector2f(width, height));
	this->setRectTexture("background.png");
}

void Table::draw(sf::RenderWindow& window) {

	window.draw((sf::RectangleShape) (*this));
	//window.draw((sf::RectangleShape)player_hand);
	//window.draw((sf::RectangleShape)player_table);
	//window.draw((sf::RectangleShape)enemy_table);
	player_hand.draw(window);
	player_table.draw(window);
	enemy_table.draw(window);

	CardSprite* moving_card = static_cast <CardSprite*> (moving);
	if (moving_card != nullptr)
		moving_card->draw(window);
}

void Table::setRectTexture(const std::string& where_to_find) {

	if (where_to_find != "\0") {

		if (!table_texture.loadFromFile(where_to_find)) {

			std::cerr << "Error: Could not open program's data !\n";
			exit(1);
		}
		this->setTexture(&(this->table_texture));
	}
}

Table::~Table() {}