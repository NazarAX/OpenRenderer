#pragma once

#include <string>
#include <functional>

namespace Events
{
	

	class Event 
	{
		friend class EventDispatcher;
	public:
		enum class EventType
		{
			MouseMovedEvent,
			MouseButtonEvent,
			KeyEvent,
			WindowResizeEvent,
			WindowCloseEvent,
			MouseScrollEvent
		};
	public:
		virtual EventType GetType() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string GetInfo() const { return GetName(); }
	private:
		bool m_Handled;

	};

	

#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }


//-------------------------------------------- Dispatcher -----------------------------------------------

	class EventDispatcher
	{
		template<typename T> using EventFn = std::function<bool(T&)>;
	private:
		Event& m_Event;
	public:
		EventDispatcher(Event& e) : m_Event(e) {}


		template<typename T>
		bool Dispatch(EventFn<T> function)
		{
			if (m_Event.GetType() == T::GetStaticType()) 
			{
				m_Event.m_Handled = function(*(T*)&m_Event);
				return true;
			}

			return false;
		}
	};
}
