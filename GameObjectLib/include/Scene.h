#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "GameObject.h"

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	void Update();
	void Render(sf::RenderWindow* _window);

	GameObject* CreateGameObject(const std::string& _name);

	GameObject* CreateDummyGameObject(const std::string& name, float positionX, float positionY, const sf::Color color);

	GameObject* CreateMainGameObject(const std::string& name, float positionX, float positionY, float width, float height, const sf::Color color, std::string asset);

private:
	std::vector<GameObject*> gameObjects;
};
