#include "Components/SquareCollider.h"

bool SquareCollider::IsColliding(const SquareCollider& _colliderA, const SquareCollider& _colliderB)
{
	const Maths::Vector2f positionA = _colliderA.GetOwner()->GetPosition();
	const Maths::Vector2f positionB = _colliderB.GetOwner()->GetPosition();
	return (positionA.x < positionB.x + _colliderB.GetWidth() && positionA.x + _colliderA.GetWidth() > positionB.x && positionA.y < positionB.y + _colliderB.GetHeight() && positionA.y + _colliderA.GetHeight() > positionB.y);
}
