#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED
#include "SFML\Graphics.hpp"
#include "GameObject.h"
#include "CardZone.h"

namespace Theta {

	/** Table - Theta class that represents the table of the game **/

	class Table : public GameObject, public sf::RectangleShape {

	private:
		sf::Texture table_texture;
	public:
		Table(float width, float height);
		~Table();
		///
		CardZone player_hand;
		CardZone player_table;
		CardZone enemy_table;
		void draw(sf::RenderWindow& window);
		void setRectTexture(const std::string&);
	};
}

#endif // !TABLE_H_INCLUDED