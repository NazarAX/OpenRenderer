#pragma once
#include "Event.h"

namespace Events 
{
	class MouseMovedEvent : public Event
	{
	private:
		double m_X;
		double m_Y;
	public:
		MouseMovedEvent(double x, double y)
			: m_X(x), m_Y(y)
		{}

		inline double GetPrevX() { return s_PrevX; }
		inline double GetPrevY() { return s_PrevY; }

		inline double GetDeltaX() { return GetX() - GetPrevX(); }
		inline double GetDeltaY() { return GetY() - GetPrevY(); }

		inline double GetX() { return m_X; }
		inline double GetY() { return m_Y; }


		static double s_PrevX;
		static double s_PrevY;

		EVENT_CLASS_TYPE(MouseMovedEvent)
	};
}