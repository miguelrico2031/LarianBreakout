#pragma once
#include <filesystem>


namespace Characters
{

	enum class Type
	{
		None = 0,
		Fighter,
		Wizard
	};

	struct Data
	{
		Type Character;
		unsigned int MaxAbilityUses;
		float CooldownDuration;
		std::filesystem::path PaddleTexturePath;
		std::filesystem::path ProjectileTexturePath;
	};

	inline const Data FighterData
	{
		.Character = Type::Fighter,
		.MaxAbilityUses = 4,
		.CooldownDuration = 8.f,
		.PaddleTexturePath = "assets/FighterShield.png",
		.ProjectileTexturePath = "assets/SwordProjectile.png"
	};

	inline const Data WizardData
	{
		.Character = Type::Wizard,
		.MaxAbilityUses = 2,
		.CooldownDuration = 12.f,
		.PaddleTexturePath = "assets/WizardHat.png",
		.ProjectileTexturePath = "assets/FireBall.png"
	};
}
