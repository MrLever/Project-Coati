#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/event_system/Event.h"
#include "core/input/definitions/MouseInput.h"

namespace core {
	class MouseButtonEvent : public Event {
		ENABLE_RTTI(MouseButtonEvent)

	public:
		/** The input this event is reporting */
		MouseInput Input;

		/**
		 * Constructor
		 */
		MouseButtonEvent(MouseInput& input);

	};
}

