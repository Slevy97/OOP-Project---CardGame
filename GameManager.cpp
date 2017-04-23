#include "ThetaEngine.h"

using namespace Theta;

std::list<GameObject*> GameObjects;
GameObject* moving = nullptr;

GameManager::GameManager() {

}

GameManager GameManager::G_Manager;

void GameManager::draw_game() {

	Window::getHandle().clear();
	for (std::list<GameObject*>::iterator it = GameObjects.begin(); it != GameObjects.end(); it++)
	{
		(*it)->draw(Window::getHandle());
	}
	Window::getHandle().display();
}

void GameManager::add_GameObject(GameObject* obj) {

	GameObjects.push_back(obj);
}

void GameManager::erase_GameObject(GameObject* obj) {

	std::list<GameObject*>::iterator it;
	for (it = GameObjects.begin(); it != GameObjects.end(); it++)
		if ((*it) == obj)
			break;
	if (it != GameObjects.end())
	{
		delete[] * it;
		GameObjects.erase(it);
	}
}

void GameManager::erase_GameObjects() {

	while (!GameObjects.empty())
	{
		delete[] * GameObjects.begin();
		GameObjects.pop_front();
	}
}

void GameManager::change_state() {

	if (Window::getHandle().isFullscreen() == false)
	{
		this->erase_GameObjects();
		Window::getHandle().goFullScreen();
	}
	else
	{
		this->erase_GameObjects();
		Window::getHandle().goStdScreen();
	}
}