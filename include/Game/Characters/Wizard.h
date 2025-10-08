#pragma once
#include <Game/Characters/Character.h>

class Wizard : public Character
{
public:
	Wizard(Core::GameObject* gameObject)
		: Character(gameObject, "assets/WizardHat.png", "assets/FireBall.png") {
	}

	virtual Character::Characters getCharacter() const override { return Characters::Fighter; }

	virtual void initialize(int indexInParty) override;
	virtual void onProjectilePaddleCollision() override;
	virtual void onProjectileScaleCollision(Scale* scale) override;
private:
	float m_fireBallOverlapRadius;
};