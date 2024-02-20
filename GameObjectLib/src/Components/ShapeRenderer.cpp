#include "Components/ShapeRenderer.h"
#include "SFML/Graphics/Shape.hpp"

ShapeRenderer::ShapeRenderer()
{
	shape = new sf::RectangleShape();
}

ShapeRenderer::~ShapeRenderer()
{
	delete shape;
	shape = nullptr;
}

void ShapeRenderer::Render(sf::RenderWindow* _window)
{
	Component::Render(_window);

	const auto position = GetOwner()->GetPosition();
	shape->setPosition(position.x, position.y);
	shape->setSize(sf::Vector2f(150.f, 200.f));
	shape->setFillColor(color);

	_window->draw(*shape);
}

void SpriteRenderer::Render(sf::RenderWindow* _window)
{
	Component::Render(_window);

	const auto position = GetOwner()->GetPosition();
	Sprite.setPosition(position.x, position.y);
	Sprite.setRotation(GetOwner()->GetRotation());

	_window->draw(Sprite);
}

void SpriteRenderer::setTexture(std::string link) 
{
	texture.loadFromFile(link);
	Sprite = sf::Sprite(texture);
}