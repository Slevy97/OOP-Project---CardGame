#ifndef FINAL_LAYER_H_INCLUDED
#define FINAL_LAYER_H_INCLUDED
#include "SFML\Graphics.hpp"
#include "GameObject.h"
#include "UpdatableText.h"
#include <string>

namespace Theta {

	/** FinalLayer - Theta class that represents the end of the game **/

	class FinalLayer : public GameObject, public sf::RectangleShape {

	private:
		sf::Texture table_texture;
		UpdatableText finaltext;
		sf::Font font;
	public:
		FinalLayer(float width, float height);
		~FinalLayer();
		///
		void draw(sf::RenderWindow& window);
		void setRectTexture(const std::string&);
		void setString(const std::string&);
	};
}

#endif // !FINAL_LAYER_H_INCLUDED