#pragma once
#include <string>
#include <vector>

#include "Maths/Vector2.h"
#include "Components/Component.h"

class Component;

class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;

	std::string GetName() const { return name; }
	Maths::Vector2<float> GetPosition() const { return position; }
	float GetRotation() const { return rotation; }
	Maths::Vector2<float> GetSize() const { return size; }

	void SetName(const std::string& _name) { name = _name; }
	void SetPosition(const Maths::Vector2<float>& _position) { position = _position; }
	void SetRotation(float _rotation) { rotation = _rotation; }
	void GetSize(const Maths::Vector2<float>& _size) { size = _size; }

	void AddComponent(Component* _component);

	template<typename T>
	T* CreateComponent()
	{
		T* component = new T();
		component->SetOwner(this);
		components.push_back(component);
		return component;
	}

	template<typename T>
	T* GetComponent()
	{
		for (Component* component : components) {
			T* typedComponent = dynamic_cast<T*>(component);
			if (typedComponent != nullptr) {
				return typedComponent;
			}
		}
		return nullptr;
	}

	void RemoveComponent(Component* _component);
	void Update() const;
	void Render(sf::RenderWindow* _window) const;

private:
	std::string name = "GameObject";
	Maths::Vector2<float> position = Maths::Vector2f::Zero;
	float rotation = 0.f;
	Maths::Vector2<float> size = Maths::Vector2f::Zero;
	std::vector<Component*> components;
};
