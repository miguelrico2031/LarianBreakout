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
			ObserverID ID;
			Callback Callback;
		};

		ObserverID subscribe(const Callback& Callback)
		{
			auto ID = m_lastID++;
			m_observers.push_back({ ID, Callback });
			return ID;
		}

		void unsubscribe(ObserverID ID)
		{
			auto it = std::remove_if(m_observers.begin(), m_observers.end(),
				[ID](const Observer& obs) { return obs.ID == ID; });
			m_observers.erase(it, m_observers.end());
		}

		void invoke(Args... args)
		{
			for (Observer& obs : m_observers)
			{
				if (obs.Callback) obs.Callback(args...);
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