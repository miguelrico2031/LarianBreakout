#pragma once

namespace Core
{
	class GameObject;

	class Behavior //behavior that is attached to a sprite
	{
	public:
		Behavior(GameObject* gameObject) : m_gameObject(gameObject) {}
		virtual void start() {}
		virtual void update(float dt) {}
		virtual void onDestroy() {}
		GameObject* getGameObject() const { return m_gameObject; }
	protected:
		GameObject* m_gameObject;
	};
}