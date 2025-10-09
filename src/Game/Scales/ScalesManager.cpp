#include <Game/Scales/ScalesManager.h>
#include <Game/Scales/Scale.h>
#include <Core/GameObject.h>
#include <Core/Scene.h>
#include <Core/Game.h>


void ScalesManager::start()
{
	m_scaleDestroyKey = Core::Animator::registerAnimation({
		"assets/Scale1.png",
		"assets/Scale2.png",
		"assets/Scale3.png",
		"assets/Scale4.png",
		"assets/Scale5.png",
		"assets/Scale6.png",
		});
}

void ScalesManager::spawnScales(int ScaleRows)
{
	m_rowsBounds.resize(ScaleRows);

	auto dimensions = m_scene->getGame()->getDimensions();
	auto scaleSize = m_scalesTexture.getSize();

	sf::Vector2u start = { SCALES::START_X, SCALES::START_Y };

	for (int row = 0; row < ScaleRows; row++)
	{
		//new empty array
		m_scaleRows.push_back({});
		ScaleRow& scaleRow = m_scaleRows.back();
		int index = 0;

		//initial coords calculations
		float startX = start.x + scaleSize.x * (row % 2 == 0 ? 1 : .5f);
		float y = start.y + scaleSize.x * row * SCALES::DOWN_DISPLACEMENT;
		float z = SCALES::START_Z - row;

		const unsigned int nScales = row % 2 == 0
			? SCALES::SCALES_PER_ODD_ROW - 1
			: SCALES::SCALES_PER_ODD_ROW;

		//get the row's bounding box
		Core::Collision::AABB aabb
		{
			.Min{startX - scaleSize.x / 2.f, y - scaleSize.y / 2.f},
			.Max{startX - scaleSize.x / 2.f + nScales * scaleSize.x, y + scaleSize.y / 2.f}
		};
		m_rowsBounds[row] = aabb;

		
		//spawn all the scales of a row
		for (float x = startX; x <= dimensions.x - scaleSize.x * .5f; x += scaleSize.x)
		{
			Core::GameObject& scaleGO = m_scene->createSpriteGameObject(m_scalesTexture, z);
			unsigned int col = index++;
			scaleGO.getSprite()->setPosition({ x, y });
			auto& scale = scaleGO.addBehavior<Scale>(row, col);
			scaleGO.addBehavior<Core::Animator>();
			scaleRow[col] = &scale; //add the scale to the array to keep track of it
		}

#ifndef NDEBUG //debug visually the AABBs
		//auto debugRect = std::make_unique<sf::RectangleShape>(aabb.Max - aabb.Min);
		//debugRect->setPosition(aabb.Min);
		//debugRect->setFillColor({ 0, 0, 0, 0 });
		//debugRect->setOutlineColor(sf::Color::Blue);
		//debugRect->setOutlineThickness(1);
		//scaleRow[0]->getGameObject()->DebugShapes.push_back(std::move(debugRect));
#endif
	}
}


Scale* ScalesManager::checkCollision(const Core::Collision::AABB& aabb) const
{
	//from the bottom to the top, because the objects that collide with the scales usually come from the bottom
	for (int row = m_scaleRows.size() - 1; row >= 0; row--)
	{
		const ScaleRow& scaleRow = m_scaleRows[row];
		const auto& rowAabb = m_rowsBounds[row];
		if (!Core::Collision::isColliding(aabb, rowAabb))
		{
			continue;
		}
		//we know the aabb is overlapping the current row so it could be colliding with one scale
		for(int col = 0; col < scaleRow.size(); col++)
		{
			Scale* scale = scaleRow[col];
			if (scale == nullptr) //destroyed or non existent scale
			{
				continue;
			}
			Core::Collision::Circle scaleCircle
			{
				.Center = scale->getGameObject()->getSprite()->getPosition(),
				.Radius = SCALES::COLLISION_RADIUS
			};
			if (Core::Collision::isColliding(aabb, scaleCircle))
			{
				return scale;
			}
		}
	}
	return nullptr;
}

Scale* ScalesManager::checkCollision(const Core::Collision::Circle& circle) const
{
	for (int row = m_scaleRows.size() - 1; row >= 0; row--)
	{
		const ScaleRow& scaleRow = m_scaleRows[row];
		const auto& rowAabb = m_rowsBounds[row];
		if (!Core::Collision::isColliding(rowAabb, circle))
		{
			continue;
		}
		for (int col = 0; col < scaleRow.size(); col++)
		{
			Scale* scale = scaleRow[col];
			if (scale == nullptr)
			{
				continue;
			}
			Core::Collision::Circle scaleCircle
			{
				.Center = scale->getGameObject()->getSprite()->getPosition(),
				.Radius = SCALES::COLLISION_RADIUS
			};
			if (Core::Collision::isColliding(circle, scaleCircle))
			{
				return scale;
			}
		}
	}
	return nullptr;
}

std::vector<Scale*> ScalesManager::checkCollisionAll(const Core::Collision::AABB& aabb)
{
	std::vector<Scale*> scales;
	for (int row = m_scaleRows.size() - 1; row >= 0; row--)
	{
		const ScaleRow& scaleRow = m_scaleRows[row];
		const auto& rowAabb = m_rowsBounds[row];
		if (!Core::Collision::isColliding(rowAabb, aabb))
		{
			continue;
		}
		for (int col = 0; col < scaleRow.size(); col++)
		{
			Scale* scale = scaleRow[col];
			if (scale == nullptr)
			{
				continue;
			}
			Core::Collision::Circle scaleCircle
			{
				.Center = scale->getGameObject()->getSprite()->getPosition(),
				.Radius = SCALES::COLLISION_RADIUS
			};
			if (Core::Collision::isColliding(aabb, scaleCircle))
			{
				scales.push_back(scale);
			}
		}
	}
	return scales;
}

std::vector<Scale*> ScalesManager::checkCollisionAll(const Core::Collision::Circle& circle)
{
	std::vector<Scale*> scales;
	for (int row = m_scaleRows.size() - 1; row >= 0; row--)
	{
		const ScaleRow& scaleRow = m_scaleRows[row];
		const auto& rowAabb = m_rowsBounds[row];
		if (!Core::Collision::isColliding(rowAabb, circle))
		{
			continue;
		}
		for (int col = 0; col < scaleRow.size(); col++)
		{
			Scale* scale = scaleRow[col];
			if (scale == nullptr)
			{
				continue;
			}
			Core::Collision::Circle scaleCircle
			{
				.Center = scale->getGameObject()->getSprite()->getPosition(),
				.Radius = SCALES::COLLISION_RADIUS
			};
			if (Core::Collision::isColliding(circle, scaleCircle))
			{
				scales.push_back(scale);
			}
		}
	}
	return scales;
}


void ScalesManager::destroyScale(Scale* scale)
{
	m_scaleRows[scale->Row][scale->Col] = nullptr;
	scale->getGameObject()->getBehavior<Core::Animator>()->playAnimationOnce(m_scaleDestroyKey, 15.f,
		[this, scale]() {m_scene->destroyGameObject(scale->getGameObject()); });
	
}


