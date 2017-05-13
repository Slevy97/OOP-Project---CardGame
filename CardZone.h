#ifndef CARD_ZONE_H_INCLUDED
#define CARD_ZONE_H_INCLUDED

#include "GameObject.h"
#include "SFML\Graphics.hpp"
#include "CardSprite.h"
#define NR_MAX_CARDS 6

namespace Theta {
	
	class GameManager;
	class EventManager;
	class InputManager;
	class NetworkManager;

	/** CardZone - Theta class for representing the area in which the cards are kept in the game.
	It behaves like a container for the cards **/

	class CardZone : public GameObject, public sf::RectangleShape {

	private:
		CardSprite PH_CARDS[NR_MAX_CARDS + 1]; // the container for the CardSprite objects
		unsigned int nr_cards; // the number of cards kept in the container
		sf::Texture cardzone_texture;
	public:
		CardZone(float width, float height, float wp, float hp);
		~CardZone() {}
		void draw(sf::RenderWindow& window);
		void add_card(const std::string&); // function that adds a card in the CardZone
		void add_card(const CardSprite& obj);
		void add_card(int index);
		void copy_card(CardZone*, unsigned int); //function that copies the content of a card from another CardZone and adds it to the actual one
		void erase_card(unsigned int indx); // function that erases a card from the CardZone from a specific position 
		bool isFull(); // checks if the container is full
		void setRectColor(const sf::Color&);
		void setRectTexture(const std::string&);

		int getNrCards();
		CardSprite & getCard(int index);
		void setCard(int index, CardSprite cardSprite);
		/** **/
		/** All the managers are friends of CardZone and can freely look inside the class **/
		friend class GameManager;
		friend class EventManager;
		friend class InputManager;
		friend class NetworkManager;
	};

}


#endif // !CARD_ZONE_H_INCLUDED
