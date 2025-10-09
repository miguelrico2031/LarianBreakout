#pragma once
#include <Game/Characters/Character.h>

class Wizard : public Character
{
public:
	Wizard(Core::GameObject* gameObject)
		: Character(gameObject, Characters::WizardData) {}

	virtual void initialize(int indexInParty) override;
	virtual void onScaleCollidedWithThisProjectile(Scale* scale) override;
private:
	float m_fireBallOverlapRadius;
};