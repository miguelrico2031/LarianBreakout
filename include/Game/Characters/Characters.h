#pragma once
#include <filesystem>
#include <array>
#include <string>

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
		unsigned int CooldownDuration;
		std::filesystem::path PaddleTexturePath;
		std::filesystem::path ProjectileTexturePath;
		std::filesystem::path SymbolTexturePath;
		std::filesystem::path HUDSymbolTexturePath;
		std::string TitleText;
		std::string DescriptionText;
		std::string Tutorial;
	};

	inline const Data FighterData
	{
		.Character = Type::Fighter,
		.MaxAbilityUses = 4,
		.CooldownDuration = 12,
		.PaddleTexturePath = "assets/FighterShield.png",
		.ProjectileTexturePath = "assets/FighterSword.png",
		.SymbolTexturePath = "assets/FighterSymbolNC.png",
		.HUDSymbolTexturePath = "assets/FighterSymbol.png",
		.TitleText = "FIGHTER",
		.DescriptionText = "Throws a sword that\n" "damages Dragon Scales.",
		.Tutorial = "LEFT and RIGHT keys\n" "to move.\n" "Destroy all the\n" "Scales to defeat\n" "the dragon."

	};

	inline const Data WizardData
	{
		.Character = Type::Wizard,
		.MaxAbilityUses = 2,
		.CooldownDuration = 18,
		.PaddleTexturePath = "assets/WizardHat.png",
		.ProjectileTexturePath = "assets/FireBall1.png",
		.SymbolTexturePath = "assets/WizardSymbolNC.png",
		.HUDSymbolTexturePath = "assets/WizardSymbol.png",
		.TitleText = "WIZARD",
		.DescriptionText = "Casts a large Fire\n" "Ball that can strike\n" "several Dragon Scales.",
		.Tutorial = "SPACE or NUMBER 1234 keys\n" "to switch character."
	};

	inline const Data PaladinData
	{
		.Character = Type::Paladin,
		.MaxAbilityUses = 1,
		.CooldownDuration = 20,
		.PaddleTexturePath = "assets/PaladinShield.png",
		.ProjectileTexturePath = "assets/PaladinSword.png",
		.SymbolTexturePath = "assets/PaladinSymbolNC.png",
		.HUDSymbolTexturePath = "assets/PaladinSymbol.png",
		.TitleText = "PALADIN",
		.DescriptionText = "",
		.Tutorial = ""
	};

	inline const Data BardData
	{
		.Character = Type::Bard,
		.MaxAbilityUses = 2,
		.CooldownDuration = 30,
		.PaddleTexturePath = "assets/Beer.png",
		.ProjectileTexturePath = "assets/BardLyre.png",
		.SymbolTexturePath = "assets/BardSymbolNC.png",
		.HUDSymbolTexturePath = "assets/BardSymbol.png",
		.TitleText = "BARD",
		.DescriptionText = "",
		.Tutorial = ""
	};

	inline const std::array<Data, 4> Characters
	{
		FighterData, WizardData, PaladinData, BardData
	};
}
