#pragma once
#include <Core/Manager.h>
#include <functional>
#include <vector>

namespace Core
{
	class AsyncManager : public Manager
	{
	public:
		AsyncManager(Scene* scene) : Manager(scene) {}
		virtual void update(float dt) override;
		void invokeIn(std::function<void()> callback, float seconds);
	private:
		struct Callback
		{
			std::function<void()> Func;
			float Seconds;
		};
	private:
		std::vector<Callback> m_callbacks;
	};
}