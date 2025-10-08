#pragma once

namespace sf
{
	class Event;
}
namespace Core
{
	class Scene;
	class Manager //manager that only has an instance per scene
	{
	public:
		Manager(Scene* scene) : m_scene(scene) {}
		virtual void start() {}
		virtual void update(float dt) {}
		virtual void onEvent(const sf::Event* event) {}
		Scene* getScene() const { return m_scene; }
	protected:
		Scene* m_scene;
	};
}