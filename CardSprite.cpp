#include "ThetaEngine.h"
#include <iostream>

using namespace Theta;

CardSprite::CardSprite() {

	isCard = false;
	isRect = false;
	this->card_ptr = nullptr;
	this->ok_highlight = false;
	this->is_ready_for_attack = false;
	where_to_find = '\0';
	initial_pos.x = 0;
	initial_pos.y = 0;
	
	/** **/
	if (!font.loadFromFile("Cocogoose_trial.otf"))
	{
		std::cerr << "Could not load font!\n";
		exit(1);
	}

	attackText.setString("1");
	defenseText.setString("1");

	attackText.setFont(font);
	defenseText.setFont(font);

	attackText.setCharacterSize((60 * STD_WIDTH) / FULL_WIDTH);
	defenseText.setCharacterSize((60 * STD_WIDTH) / FULL_WIDTH);

	attackText.setFillColor(sf::Color::Red);
	defenseText.setFillColor(sf::Color::Red);
}

void CardSprite::SetCardRect(float width, float height, float pos_w, float pos_h) {

	this->setSize(sf::Vector2f(width, height));
	this->setPosition(sf::Vector2f(pos_w, pos_h));
	this->initial_pos = sf::Vector2f(pos_w, pos_h);
	this->isRect = true;
}

sf::Vector2f CardSprite::get_Initialpos() {

	return this->initial_pos;
}

void CardSprite::SetCardSprite(const std::string& where_to_find) {

	if (where_to_find != "\0") {

		if (!card_texture.loadFromFile(where_to_find)) {

			std::cerr << "Error: Could not open program's data !\n";
			exit(1);
		}
		this->where_to_find = where_to_find;
		this->setTexture(&this->card_texture);
		this->isCard = true;
	}
}

CardSprite::~CardSprite() {
	
	if (card_ptr != nullptr)
	{
		delete card_ptr;
		card_ptr = nullptr;
	}
}

void CardSprite::draw(sf::RenderWindow& window) {

	if (isCard && isRect) {
		window.draw(*this);
		this->setTextPosition(this->getPosition(), this->getSize(), window.getSize());
		if (this->card_ptr != nullptr)
			this->updateText();
		this->attackText.draw(window);
		this->defenseText.draw(window);
	}
}

void CardSprite::copy_content(const CardSprite& obj) {

	if (card_ptr != nullptr)
		delete card_ptr;
	this->createCardPtr();
	if (obj.card_ptr != nullptr)
		(*this->card_ptr) = (*obj.card_ptr);
	this->where_to_find = obj.where_to_find;
	this->isCard = obj.isCard;
	attackText = obj.attackText;
	defenseText = obj.defenseText;
	font = obj.font;
	if (this->isCard == true) // if there is any actual content
		this->SetCardSprite(where_to_find);
}

void CardSprite::change_state() {

	if (ok_highlight == true)
	{
		this->setOutlineThickness(20);
		this->setOutlineColor(sf::Color(0, 102, 51, 74));
	}
	else {
		this->setOutlineThickness(0);
	}
}

void CardSprite::change_attack_state() {

	static bool ok_attack = true;
	if (ok_attack == true)
	{
		this->setOutlineThickness(20);
		this->setOutlineColor(sf::Color(204, 0, 0));
		ok_attack = false;
	}
	else {
		this->setOutlineThickness(0);
		ok_attack = true;
	}
}

void CardSprite::setTextPosition(float x, float y)
{
	attackText.setPosition(x + 8.0f, y + 265.0f);
	defenseText.setPosition(x + 195.0f, y + 265.0f);
}

void CardSprite::setTextPosition(sf::Vector2f v)
{
	attackText.setPosition(v.x + 8.0f, v.y + 265.0f);
	defenseText.setPosition(v.x + 195.0f, v.y + 265.0f);
}

void CardSprite::setTextPosition(sf::Vector2f position, sf::Vector2f size, sf::Vector2u windowSize)
{
	attackText.setPosition(position.x + windowSize.x * 0.005f, (position.y + size.y) - windowSize.y * 0.05f);

	int def = card_ptr->getDefense();
	if (def >= 1 && def <= 9)
	{
		defenseText.setPosition(position.x + windowSize.x * 0.096f, (position.y + size.y) - windowSize.y * 0.05f);
	}
	else if (def >= 10 && def <= 99)
	{
		defenseText.setPosition(position.x + windowSize.x * 0.082f, (position.y + size.y) - windowSize.y * 0.05f);
	}
	else if (def >= 100 && def <= 999)
	{
		defenseText.setPosition(position.x + windowSize.x * 0.068f, (position.y + size.y) - windowSize.y * 0.05f);
	}
	else if (def >= 1000 && def <= 9999)
	{
		defenseText.setPosition(position.x + windowSize.x * 0.068f, (position.y + size.y) - windowSize.y * 0.05f);
	}
	else
	{
		defenseText.setPosition(position.x + windowSize.x * 0.068f, (position.y + size.y) - windowSize.y * 0.05f);
		//in orice alt caz
	}

	updateText();

}

void CardSprite::updateText()
{
	attackText.setString(std::to_string(card_ptr->getAttack()));
	defenseText.setString(std::to_string(card_ptr->getDefense()));
}

Card * CardSprite::getCardPtr()
{
	return card_ptr;
}

void CardSprite::setCardPtr(Card * cp)
{
	card_ptr = cp;
}

void CardSprite::createCardPtr()
{
	card_ptr = new Card;
}

std::string CardSprite::getWhereToFind()
{
	return where_to_find;
}