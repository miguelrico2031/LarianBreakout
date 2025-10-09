#pragma once
#include <filesystem>


namespace Characters
{

	enum class Type
	{
		None = 0,
		Fighter,
		Wizard,
		Paladin,
		Bard
	};

	struct Data
	{
		Type Character;
		unsigned int MaxAbilityUses;
		float CooldownDuration;
		std::filesystem::path PaddleTexturePath;
		std::filesystem::path ProjectileTexturePath;
		std::filesystem::path SymbolTexturePath;
	};

	inline const Data FighterData
	{
		.Character = Type::Fighter,
		.MaxAbilityUses = 4,
		.CooldownDuration = 12.f,
		.PaddleTexturePath = "assets/FighterShield.png",
		.ProjectileTexturePath = "assets/FighterSword.png",
		.SymbolTexturePath = "assets/FighterSymbol.png"
	};

	inline const Data WizardData
	{
		.Character = Type::Wizard,
		.MaxAbilityUses = 2,
		.CooldownDuration = 18.f,
		.PaddleTexturePath = "assets/WizardHat.png",
		.ProjectileTexturePath = "assets/FireBall1.png",
		.SymbolTexturePath = "assets/WizardSymbol.png"
	};

	inline const Data PaladinData
	{
		.Character = Type::Paladin,
		.MaxAbilityUses = 1,
		.CooldownDuration = 20.f,
		.PaddleTexturePath = "assets/PaladinShield.png",
		.ProjectileTexturePath = "assets/PaladinSword.png",
		.SymbolTexturePath = "assets/PaladinSymbol.png"
	};

	inline const Data BardData
	{
		.Character = Type::Bard,
		.MaxAbilityUses = 2,
		.CooldownDuration = 30.f,
		.PaddleTexturePath = "assets/Beer.png",
		.ProjectileTexturePath = "assets/BardLyre.png",
		.SymbolTexturePath = "assets/BardSymbol.png"
	};
}
