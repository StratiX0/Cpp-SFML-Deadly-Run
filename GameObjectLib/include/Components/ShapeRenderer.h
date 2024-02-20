#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Component.h"

class ShapeRenderer : public Component
{
public:
	ShapeRenderer();
	~ShapeRenderer() override;

	void SetColor(const sf::Color& _color) { color = _color; }

	void Render(sf::RenderWindow* _window) override;

protected:
	sf::Color color = sf::Color::White;
	sf::RectangleShape* shape = nullptr;
};

class SpriteRenderer : public ShapeRenderer
{
public:
	sf::Texture texture;
	sf::Sprite Sprite;

	void setTexture(std::string);
	void Render(sf::RenderWindow* _window) override;
};

