#include "Components/Component.h"

Component::Component(GameObject* owner)
{
	this->owner = owner;
}

void Component::Update() {}

void Component::Render(sf::RenderWindow* _window) {}
