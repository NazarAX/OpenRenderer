#pragma once
#include "Event.h"

namespace Events 
{
	class KeyEvent : public Event
	{
	private:
		int m_Key;
		int m_Action;
	public:
		KeyEvent(int key, int action) : m_Key(key), m_Action(action) {}

		inline int GetKey() const { return m_Key; }
		inline int GetAction() const { return m_Action;}

		EVENT_CLASS_TYPE(KeyEvent)
	};
}