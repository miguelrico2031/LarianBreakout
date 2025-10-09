#pragma once
#include <Game/Characters/Character.h>

class Bard : public Character
{
public:
	Bard(Core::GameObject* gameObject)
		: Character(gameObject, Characters::BardData) {
	}

	virtual void initialize(int indexInParty) override;
	virtual void onPaddleCollidedWithThisProjectile(Paddle* paddle, Character* owner) override;
	//erase the base class behavior so it doesn't change the lyre to a fire projectile
	virtual void onScaleCollidedWithThisProjectile(Scale* scale) override {}
};