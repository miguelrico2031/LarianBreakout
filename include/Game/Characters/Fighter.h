#pragma once
#include <Game/Characters/Character.h>

class Fighter : public Character
{
public:
	Fighter(Core::GameObject* gameObject) 
		: Character(gameObject, Characters::FighterData) {}

	virtual void initialize(int indexInParty) override;
};