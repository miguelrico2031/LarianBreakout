#include <Core/AsyncManager.h>

namespace Core
{

	void AsyncManager::update(float dt)
	{
		for (auto& callback : m_callbacks)
		{
			callback.Seconds -= dt;
		}
		std::erase_if(m_callbacks, [](Callback& cb)
			{
				if (cb.Seconds <= 0.f)
				{
					cb.Func();
					return true;
				}
				return false;
			});
	}

	void AsyncManager::invokeIn(std::function<void()> callback, float seconds)
	{
		m_callbacks.push_back({ std::move(callback), seconds });
	}
}
