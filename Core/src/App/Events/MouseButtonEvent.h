#pragma once
#include "Event.h"


namespace Events 
{
	class MouseButtonEvent : public Event
	{
	private:
		int m_Button;
		int m_Action;
	public:
		MouseButtonEvent(int button, int action)
			:
			m_Button(button), m_Action(action)
		{}

		inline int GetButton() const { return m_Button; }
		inline int GetAction() const { return m_Action; }

		EVENT_CLASS_TYPE(MouseButtonEvent)
	};
}