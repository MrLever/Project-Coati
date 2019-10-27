#pragma once
//STD Headers
#include <unordered_map>

//Library Headers

//Void Engine Headers
#include "JsonResource.h"
#include "InputAction.h"
#include "KeyboardInput.h"
#include "MouseInput.h"
#include "GamepadInput.h"

namespace core {

	class ControlLayout : public utils::JsonResource {
	public:
		/**
		 * Constructor
		 */
		ControlLayout(const std::string& filePath);

	private:
		std::unordered_map<KeyboardInput, InputAction> KeyboardBindings;
		std::unordered_map<MouseInput, InputAction> MouseBindings;
		std::unordered_map<GamepadInput, InputAction> GamepadBindings;
		//std::unordered_map<InputAxis, InputAction>
	};
}

