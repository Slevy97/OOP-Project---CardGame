#include "ThetaEngine.h"
#include <iostream>

using namespace Theta;

extern GameObject* moving;
extern CardSprite* Deck;

CardZone::CardZone(float width, float height, float wp, float hp) {

	this->setSize(sf::Vector2f(width, height));
	this->setPosition(sf::Vector2f(wp, hp));
	nr_cards = 0;
	float card_size_X = (width - 20 * (NR_MAX_CARDS + 1)) / NR_MAX_CARDS;
	float card_size_Y = height - 20 * 2;
	for (int i = 0; i < NR_MAX_CARDS; i++) {

		PH_CARDS[i].SetCardRect(card_size_X, card_size_Y, wp + 20 * (i + 1) + card_size_X * i, hp + 20);

		PH_CARDS[i].setTextPosition(wp + 20 * (i + 1) + card_size_X * i, hp + 20);
	}
}

void CardZone::draw(sf::RenderWindow& window) {

	for (unsigned int i = 0; i < nr_cards; i++)
	{
		if (&PH_CARDS[i] != moving)
			PH_CARDS[i].draw(window);
	}
}

void CardZone::add_card(const std::string& where_to_find) {

	EventManager::getHandle().reset_attack();
	if (nr_cards < NR_MAX_CARDS) {

		nr_cards++;
		PH_CARDS[nr_cards - 1].SetCardSprite(where_to_find);
	}
}

void CardZone::add_card(const CardSprite& obj) {

	EventManager::getHandle().reset_attack();
	if (nr_cards < NR_MAX_CARDS) {

		nr_cards++;
		PH_CARDS[nr_cards - 1].copy_content(obj);
	}
}

void CardZone::add_card(int index) {

	add_card(Deck[index]);
}

void CardZone::erase_card(unsigned int indx) {

	EventManager::getHandle().reset_attack();
	if (indx >= 0 && indx < nr_cards) {

		for (unsigned int i = indx; i < nr_cards; i++)
		{
			PH_CARDS[i].copy_content(PH_CARDS[i + 1]);
		}
		nr_cards--;
	}
}

void CardZone::copy_card(CardZone* cz_ptr, unsigned int indx) {

	EventManager::getHandle().reset_attack();
	if (cz_ptr != nullptr && indx >= 0 && indx < cz_ptr->nr_cards && nr_cards < NR_MAX_CARDS) {

		nr_cards++;
		PH_CARDS[nr_cards - 1].copy_content(cz_ptr->PH_CARDS[indx]);
	}
}

bool CardZone::isFull() {

	return (nr_cards == NR_MAX_CARDS);
}

void CardZone::setRectColor(const sf::Color& color) {

	this->setFillColor(color);
}

void CardZone::setRectTexture(const std::string& where_to_find) {

	if (where_to_find != "\0") {

		if (!cardzone_texture.loadFromFile(where_to_find)) {

			std::cerr << "Error: Could not open program's data !\n";
			exit(1);
		}
		this->setTexture(&(this->cardzone_texture));
	}
}

int CardZone::getNrCards()
{
	return nr_cards;
}

CardSprite & CardZone::getCard(int index)
{
	if (index >= 0 && index < nr_cards)
	{
		return PH_CARDS[index];
	}
	else
		throw;
}

void CardZone::setCard(int index, CardSprite cardSprite)
{
	if (index >= 0 && index < nr_cards)
	{
		PH_CARDS[index] = cardSprite;
	}
}