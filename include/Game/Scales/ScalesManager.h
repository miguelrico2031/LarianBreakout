#pragma once
#include <Core/Manager.h>
#include <Core/Collision.h>
#include <Core/Event.h>
#include <Game/GameConstants.h>
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>

namespace Core
{
	class GameObject;
}
class Scale;
class ScalesManager : public Core::Manager
{
public:
	ScalesManager(Core::Scene* scene)
		: Manager(scene), m_scalesTexture("assets/Scale.png") {}

	void spawnScales(int rows);
	Scale* checkCollision(const Core::Collision::AABB& aabb) const;
	Scale* checkCollision(const Core::Collision::Circle& circle) const;
	std::vector<Scale*>checkCollisionAll(const Core::Collision::Circle& circle);
	void destroyScale(Scale* scale);
private:
	sf::Texture m_scalesTexture;
	using ScaleRow = std::array<Scale*, SCALES::SCALES_PER_EVEN_ROW>;
	//this is a vector of arrays, modeling a grid.
	//odd rows initially contain N scales. Even rows contain N-1 scales
	//and all of those scales are offsetted in the x axis by scale width / 2
	//so the grid forms an hexagonal pattern.
	std::vector<ScaleRow> m_scaleRows;
	//vector containing an AABB per row that is the row's bounds
	//used to avoid checking collisions with a row if the other object is outside its bounds
	std::vector<Core::Collision::AABB> m_rowsBounds;
};