#pragma once
#include "Event.h"


namespace Events 
{
	class MouseScrollEvent : public Event 
	{
	private:
		double m_XOffset;
		double m_YOffset;
	public:
		MouseScrollEvent(double xOffset, double yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset)
		{}
		
		inline double GetXOffset() const { return m_XOffset; }
		inline double GetYOffset() const { return m_YOffset; }

		EVENT_CLASS_TYPE(MouseScrollEvent)
	};
}