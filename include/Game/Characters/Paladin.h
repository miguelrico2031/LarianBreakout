#pragma once
#include <Game/Characters/Character.h>
#include <Core/GameObject.h>
#include <Core/Animator.h>

class Paladin : public Character
{
public:
	Paladin(Core::GameObject* gameObject)
		: Character(gameObject, Characters::PaladinData) {}

	virtual void initialize(int indexInParty) override;
protected:
	virtual void useAbility() override;
	void smiteScales();
private:
	sf::Texture m_smiteTex;
	Core::GameObject* m_smite;
	Core::Animator* m_smiteAnimator;
	Core::Animator::Key m_smiteAnimKey;
};