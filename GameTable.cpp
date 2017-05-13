#include "ThetaEngine.h"
#include <iostream>

using namespace Theta;

extern std::vector<int> IndxAvailable;
extern CardSprite Player;
extern bool myTurn;

GameTable::GameTable(float width, float height)
{
	this->setPosition(width * 0.75f, 0);
	this->setSize(sf::Vector2f(width * 0.25f, height));
	//this->setTextureRect(sf::IntRect(0, 500, 1000, 1000));
	if (!texture.loadFromFile("gametabletexture_deckalmostfull.png"))
	{
		std::cout << "Could not load texture!\n";
	}

	this->setTexture(&texture);

	if (!font.loadFromFile("Cocogoose_trial.otf"))
	{
		std::cout << "Could not load font!\n";
	}

	nrCardsLeft.setFont(font);
	ExitButton.setFont(font);
	currentMana.setFont(font);
	EndTurnButton.setFont(font);

	ExitButton.setString("Exit");
	EndTurnButton.setString("End turn");

	nrCardsLeft.setCharacterSize((40 * Window::getHandle().getSize().x) / FULL_WIDTH);
	ExitButton.setCharacterSize((40 * Window::getHandle().getSize().x) / FULL_WIDTH);
	currentMana.setCharacterSize((40 * Window::getHandle().getSize().x) / FULL_WIDTH);
	EndTurnButton.setCharacterSize((60 * Window::getHandle().getSize().x) / FULL_WIDTH);

	nrCardsLeft.setFillColor(sf::Color::Red);
	ExitButton.setFillColor(sf::Color::Red);
	currentMana.setFillColor(sf::Color::Red);
	EndTurnButton.setFillColor(sf::Color::Red);

	nrCardsLeft.setPosition(width * 0.84f, height * 0.65f);
	ExitButton.setPosition(width * 0.954f, 0);
	currentMana.setPosition(width * 0.92f, height * 0.84f);
	EndTurnButton.setPosition(width * 0.80f, height * 0.30f);
}

GameTable::~GameTable()
{

}

sf::FloatRect GameTable::getExitButtonGlobalBounds()
{
	return ExitButton.getGlobalBounds();
}

sf::FloatRect GameTable::getEndTurnButtonGlobalBounds()
{
	return EndTurnButton.getGlobalBounds();
}

void GameTable::update()
{
	if (myTurn)
		EndTurnButton.setFillColor(sf::Color::Green);
	else
		EndTurnButton.setFillColor(sf::Color::Red);

	currentMana.setString(std::to_string(Player.getCardPtr()->getMana()));
	nrCardsLeft.setString(std::to_string(IndxAvailable.size()));
}

void GameTable::draw(sf::RenderWindow& window)
{
	window.draw(*this);
	this->update();
	this->nrCardsLeft.draw(window);
	this->currentMana.draw(window);
	window.draw(this->EndTurnButton);
	window.draw(this->ExitButton);
}
