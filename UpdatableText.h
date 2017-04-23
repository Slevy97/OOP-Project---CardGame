#ifndef UPDATABLE_TEXT_H_INCLUDED
#define UPDATABLE_TEXT_H_INCLUDED

#include "SFML\Graphics.hpp"
#include "GameObject.h"

namespace Theta {

	class UpdatableText : public GameObject, public sf::Text
	{
		public:
			UpdatableText();
			~UpdatableText();
			void draw(sf::RenderWindow& window);
	};

}

#endif // !UPDATABLE_TEXT_H_INCLUDED