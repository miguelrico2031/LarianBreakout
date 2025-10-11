#pragma once
namespace WINDOW
{
	constexpr int WIDTH = 160;
	constexpr int HEIGHT = 144;
	constexpr int SCALE = 4;
	constexpr const char* NAME = "LARIAN TAL";
}

namespace BOUNDS
{
	constexpr float PADDING_TOP = 13.f;
	constexpr float PADDING_LEFT = 8.f;
	constexpr float PADDING_RIGHT = 8.f;
	constexpr float PADDING_BOTTOM = 32.f;
}


namespace SCALES
{
	constexpr unsigned int SCALES_PER_ODD_ROW = 10;
	constexpr unsigned int START_X = 0;
	constexpr unsigned int START_Y = 16;//11;
	constexpr int START_Z = 20;
	constexpr float DOWN_DISPLACEMENT = 5.f / 8.f;
	constexpr float COLLISION_RADIUS = 8.f;
}

namespace PADDLE
{
	constexpr float SPEED = 130.f;
	constexpr int Y_POS = 108;
	constexpr int Z = 80;
	constexpr int COLLISION_HEIGHT = 3;
	constexpr float COLLISION_DISABLED_SECONDS = .25f;
	constexpr float MAX_WIDTH = 22.f;
}

namespace PROJECTILE
{
	constexpr float START_SPEED = 70.f;
	constexpr float START_APERTURE = 45.f;
	constexpr int START_Y = 100;
	constexpr int Z = 90;
	constexpr float MAX_BOUNCE_ANGLE = 70.f;
	constexpr float MIN_BOUND_BOUNCE_Y = .2f;
	constexpr float SPIN_SPEED = 300.f;
}

namespace HUD
{
	constexpr float Z = 200;

	constexpr float PANEL_START_X = 4;
	constexpr float PANEL_START_Y = 116;
	constexpr float PANEL_PADDING = 0; 
	//these are relative to the panel top left corner nad the bar top left corner
	constexpr float PANEL_COOLDOWN_BAR_X = 32;
	constexpr float PANEL_COOLDOWN_BAR_Y = 5;
	constexpr float USE_X = 27;
	constexpr float FIRST_USE_Y = 4;
	constexpr float USE_PADDING = 2;

	constexpr float HEART_START_X = 7.f;
	constexpr float HEART_Y = 3.f;
	constexpr float HEART_PADDING = 3.f;

	constexpr float LOSE_HEART_DURATION = 1.f;

}

namespace FIREBALL
{
	constexpr float COLLIDER_RADIUS_FRACTION = .3f;
}

namespace SMITE
{
	constexpr float HITBOX_WIDTH = 8;
}

namespace VICTORY
{
	constexpr float SLAIN_TEXT_DURATION = 2.f;
	constexpr float INFO_TEXT_DURATION = 6.f;
	constexpr unsigned int SLAIN_TEXT_Y = 15;
	constexpr unsigned int INFO_TEXT_Y = 30;
}

namespace CHARACTERS
{
	constexpr unsigned int TITLE_TEXT_Y = 5;
	constexpr unsigned int DESCRIPTION_TEXT_Y = 70;
	constexpr unsigned int SYMBOL_TEXT_Y = 52;
}