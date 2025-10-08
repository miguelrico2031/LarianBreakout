#pragma once
#include <Game/Characters/Character.h>

class Fighter : public Character
{
public:
	Fighter(Core::GameObject* gameObject) 
		: Character(gameObject, "assets/FighterShield.png", "assets/SwordProjectile.png") {}

	virtual Character::Characters getCharacter() const override { return Characters::Fighter; }

	virtual void onProjectilePaddleCollision() override;
	virtual void onProjectileScaleCollision(Scale* scale) override;
};