#include "UpdatableText.h"

using namespace Theta;

UpdatableText::UpdatableText()
{

}


UpdatableText::~UpdatableText() {}

void UpdatableText::draw(sf::RenderWindow& window)
{
	window.draw(*this);
}