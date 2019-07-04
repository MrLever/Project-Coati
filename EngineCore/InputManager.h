#pragma once
//STD Headers
#include <memory>
#include <unordered_map>
#include <unordered_set>

//Library Headers

//Coati Headers
#include "MessageBusNode.h"
#include "KeyboardInput.h"
#include "Keybindings.h"
#include "InputInterfaceManager.h"


namespace EngineCore {

	//Forward Class declarations
	class MessageBus;
	class InputEvent;


	class InputManager {
	private:
		//Private class members
		Keybindings Bindings;
		std::shared_ptr<InputInterfaceManager> PlayerInterface;

	public:
		//CTORS
		InputManager(
			std::shared_ptr<MessageBus> bus, 
			std::shared_ptr<InputInterfaceManager> playerInterface
		);
		~InputManager() = default;

	private:
		//Private member functions
		void LoadKeybindings();

		void HandleKeyboard();
		void HandleMouse();
		void HandleGamepad();

	public:
		//Public member functions
		void HandleInput();
	};

}