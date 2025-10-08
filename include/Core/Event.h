#pragma once
#include <functional>
#include <vector>
#include <algorithm>

namespace Core
{
	template<typename... Args>
	class Event
	{
	public:
		using Callback = std::function<void(Args...)>;
		using ObserverID = size_t;
		struct Observer
		{
			ObserverID id;
			Callback callback;
		};

		ObserverID subscribe(const Callback& callback)
		{
			auto id = m_lastID++;
			m_observers.push_back({ id, callback });
			return id;
		}

		void unsubscribe(ObserverID id)
		{
			auto it = std::remove_if(m_observers.begin(), m_observers.end(),
				[id](const Observer& obs) { return obs.id == id; });
			m_observers.erase(it, m_observers.end());
		}

		void invoke(Args... args)
		{
			for (Observer& obs : m_observers)
			{
				if (obs.callback) obs.callback(args...);
			}
		}

		void clear()
		{
			m_observers.clear();
		}

	private:
		ObserverID m_lastID = 0;
		std::vector<Observer> m_observers;
	};
}