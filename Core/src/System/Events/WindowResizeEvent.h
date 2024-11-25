#pragma once
#include "Event.h"


namespace Events 
{
	class WindowResizeEvent : public Event
	{
	private:
		int m_Width;
		int m_Height;
	public:
		WindowResizeEvent(int width, int height) 
			: m_Width(width), m_Height(height)
		{}

		inline int GetHeight() { return m_Height; }
		inline int GetWidth() { return m_Width; }

		EVENT_CLASS_TYPE(WindowResizeEvent)
	};
}