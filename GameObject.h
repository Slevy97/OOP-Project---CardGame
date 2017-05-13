#ifndef GAME_OBJECT_H_INCLUDED
#define GAME_OBJECT_H_INCLUDED
#include "SFML\Graphics.hpp"

namespace Theta {

	/** GameObject - Theta class that represents an interface for the objects in the game
	that need to be drawn **/

	class GameObject {

	public:
		virtual void draw(sf::RenderWindow& window) = 0;
		virtual ~GameObject() {}
	};
}

#endif // !GAME_OBJECT_H_INCLUDED
