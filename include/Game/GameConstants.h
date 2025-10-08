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
	constexpr unsigned int SCALES_PER_EVEN_ROW = 10;
	constexpr unsigned int START_X = 0;
	constexpr unsigned int START_Y = 30;
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
	constexpr int Y_POS = 90;
	constexpr int Z = 90;
}