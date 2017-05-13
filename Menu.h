#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <vector>
#include <string>
#include "GameObject.h"
#include <cstdarg>
#define UNDEF -1
#define BUFF_SIZE 101

namespace Theta {

	class Menu : public GameObject {

	private:
		unsigned int selectedItemIndex;
		sf::Font font;
		std::vector<sf::Text> menu;
	public:
		Menu(float, float, unsigned int, ...);
		~Menu();

		void MoveUp();
		void MoveDown();
		void ShowWaiting();
		void changePoints(int);
		void draw(sf::RenderWindow& window);
		unsigned int collide(sf::Vector2i mouse_pos) const;
		unsigned int getSelectedItem() const {
			return this->selectedItemIndex;
		}
		void setSelectedItem(unsigned int indx);
	};
}
#endif // MENU_H

