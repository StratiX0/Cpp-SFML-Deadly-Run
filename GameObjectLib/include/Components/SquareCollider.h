#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "Component.h"

class SquareCollider : public Component
{
public:
	SquareCollider() = default;
	~SquareCollider() override = default;

	float width;
	float height;

	float GetWidth() const { return width; }
	float GetHeight() const { return height; }

	void SetWidth(const float _width) { width = _width; }
	void SetHeight(const float _height) { height = _height; }

	static bool IsColliding(const SquareCollider& _colliderA, const SquareCollider& _colliderB);
};