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
	constexpr float PADDING_TOP = 8.f;
	constexpr float PADDING_LEFT = 8.f;
	constexpr float PADDING_RIGHT = 8.f;
	constexpr float PADDING_BOTTOM = 0.f;
}

namespace SCALES
{
	constexpr unsigned int SCALES_PER_ODD_ROW = 10;
	constexpr unsigned int START_X = 0;
	constexpr unsigned int START_Y = 11;
	constexpr int START_Z = 20;
	constexpr float DOWN_DISPLACEMENT = 5.f / 8.f;
	constexpr float COLLISION_RADIUS = 8.f;
}

namespace PADDLE
{
	constexpr float SPEED = 100.f;
	constexpr int Y_POS = 108;
	constexpr int Z = 80;
	constexpr int COLLISION_HEIGHT = 3;
	constexpr float COLLISION_DISABLED_SECONDS = .25f;
}

namespace PROJECTILE
{
	constexpr float START_SPEED = 70.f;
	constexpr float START_APERTURE = .5f;
	constexpr int Y_POS = 90;
	constexpr int Z = 90;
	constexpr float MAX_BOUNCE_ANGLE = 70.f;
}

namespace UI
{
	constexpr float PANEL_START_X = 4;
	constexpr float PANEL_START_Y = 116;
	constexpr float PANEL_Z = 200;
	constexpr float PANEL_PADDING = 0; 
	//these are relative to the panel top left corner nad the bar top left corner
	constexpr float PANEL_COOLDOWN_BAR_X = 32;
	constexpr float PANEL_COOLDOWN_BAR_Y = 5;
	constexpr float USE_X = 27;
	constexpr float FIRST_USE_Y = 4;
	constexpr float USE_PADDING = 2;
}

namespace SMITE
{
	constexpr float HITBOX_WIDTH = 8;
}