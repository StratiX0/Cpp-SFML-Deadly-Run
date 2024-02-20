#include "Scene.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Components/ShapeRenderer.h"
#include "Components/SquareCollider.h"

void Scene::Update()
{
	for (GameObject* const& gameObject : gameObjects)
	{
		gameObject->Update();
	}
}

void Scene::Render(sf::RenderWindow* _window)
{
	for (GameObject* const& gameObject : gameObjects)
	{
		gameObject->Render(_window);
	}
}

GameObject* Scene::CreateGameObject(const std::string& _name)
{
	auto gameObject = new GameObject();
	gameObject->SetName(_name);
	gameObjects.push_back(gameObject);
	return gameObject;
}

GameObject* Scene::CreateDummyGameObject(const std::string& name, float positionX, float positionY, const sf::Color color)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(positionX, positionY));

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetWidth(20.f);
	squareCollider->SetHeight(20.f);

	ShapeRenderer* shapeRenderer = gameObject->CreateComponent<ShapeRenderer>();
	shapeRenderer->SetColor(color);

	return gameObject;
}

GameObject* Scene::CreateMainGameObject(const std::string& name, float positionX, float positionY, float width, float height, const sf::Color color, std::string asset)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(positionX, positionY));

	SpriteRenderer* shapeRenderer = gameObject->CreateComponent<SpriteRenderer>();
	shapeRenderer->SetColor(color);
	shapeRenderer->setTexture(asset);

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetWidth(shapeRenderer->texture.getSize().x);
	squareCollider->SetHeight(shapeRenderer->texture.getSize().y);
	shapeRenderer->Sprite.setScale(width, height);

	return gameObject;
}
