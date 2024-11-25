#pragma once
#include "Event.h"

namespace Events 
{
	class WindowCloseEvent : public Event 
	{
	public:
		EVENT_CLASS_TYPE(WindowCloseEvent)
	};
}