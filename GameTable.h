#ifndef GAME_TABLE_H_INCLUDED
#define GAME_TABLE_H_INCLUDED
#include "GameObject.h"
#include "SFML\Graphics.hpp"
#include <string>
#include "UpdatableText.h"

namespace Theta {

	class Card;
	class GameManager;
	class EventManager;
	class InputManager;

	/** GameTable **/
	class GameTable : public GameObject, public sf::RectangleShape {

	private:
		UpdatableText nrCardsLeft;
		UpdatableText currentMana;

		sf::Text EndTurnButton;
		sf::Text ExitButton;
		sf::Texture texture;

		sf::Font font;

	public:
		GameTable(float width, float height);
		~GameTable();

		sf::FloatRect getExitButtonGlobalBounds();
		sf::FloatRect getEndTurnButtonGlobalBounds();

		void update();

		void draw(sf::RenderWindow& window);

		friend class GameManager;
		friend class EventManager;
		friend class InputManager;
	};
}

#endif // !GAME_TABLE_H_INCLUDED
