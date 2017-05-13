#ifndef CARD_SPRITE_H_INCLUDED
#define CARD_SPRITE_H_INCLUDED
#include "GameObject.h"
#include "SFML\Graphics.hpp"
#include <string>
#include "Card.h"
#include "UpdatableText.h"

namespace Theta {

	class GameManager;
	class EventManager;
	class InputManager;
	class NetworkManager;

	/** CardSprite - Theta class for representing the cards in the game **/
	class CardSprite : public GameObject, public sf::RectangleShape {

	private:
		Card* card_ptr; /** it keeps track of the card that is connected to **/
		sf::Texture card_texture; /** it loads the image of the card **/
		std::string where_to_find;
		bool isCard;
		bool isRect;
		bool ok_highlight;
		bool is_ready_for_attack;
		sf::Vector2f initial_pos;

		/** **/
		UpdatableText attackText;
		UpdatableText defenseText;
		sf::Font font;

	public:
		CardSprite();
		void SetCardRect(float width, float height, float pos_w, float pos_h); /** it builds the rectangle shape for the card **/
		void SetCardSprite(const std::string& where_to_find); /** it loads the content **/
		~CardSprite();
		void draw(sf::RenderWindow& window); /** it needs to be both a Card and a Rect in order to be drawn **/
		void copy_content(const CardSprite&); /** it copies the content from another card **/
		void change_state(); /** it changes the state of being or not highlighted **/
		void change_attack_state();
		sf::Vector2f get_Initialpos();

		/** **/
		void setTextPosition(float x, float y);
		void setTextPosition(sf::Vector2f v);
		void setTextPosition(sf::Vector2f position, sf::Vector2f size, sf::Vector2u windowSize);
		void updateText();

		Card * getCardPtr();
		void setCardPtr(Card * cp);
		void createCardPtr();
		std::string getWhereToFind();

		/** All the managers are friends of CardSprite and can freely look inside the class **/
		friend class GameManager;
		friend class EventManager;
		friend class InputManager;
		friend class NetworkManager;
	};
}

#endif // CARD_SPRITE_H_INCLUDED