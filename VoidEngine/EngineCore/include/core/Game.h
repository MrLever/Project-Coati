#pragma once

//STD Headers
#include <chrono>
#include <memory>
#include <queue>

//Library Headers

//Void Engine Headers
#include "utils/configuration/Configurable.h"
#include "utils/configuration/Configuration.h"
#include "utils/threading/ThreadPool.h"
#include "utils/resource/ResourceAllocator.h"
#include "utils/Logger.h"

#include "core/Window.h"
#include "core/audio/AudioManager.h"
#include "core/event_system/EventBus.h"
#include "core/event_system/EventBusNode.h"
#include "core/event_system/events/WindowClosedEvent.h"
#include "core/input/InputManager.h"
#include "core/physics/PhysicsEngine.h"
#include "core/rendering/Renderer.h"
#include "core/event_system/events/PauseGameEvent.h"
#include "core/event_system/events/InputActionEvent.h"

namespace core {
	/**
	 * @class Game 
	 * @brief Framework that defines what a game is in the Void Engine
	 */
	class Game {
		using Timer = std::chrono::high_resolution_clock;

	public:
		/**
		 * Constructor
		 * @param name The game's name
		 */
		Game(const std::string& configFile);

		/**
		 * Destructor
		 */
		~Game();

	private:
		/**
		 * Set's up game engine enviornment
		 */
		void Initialize();

		/**
		 * Runs the game simulation
		 */
		void ExecuteGameLoop();
		
		/**
		 * Instructs the game to update the entities in it's simulation
		 */
		void Update(float deltaTime);
		
		/**
		 * Tracks the game's frame rate.
		 * @param timeSinceLastFrame Time since the last frame, in seconds
		 */
		void UpdateFramerate(double timeSinceLastFrame);

		/**
		 * Allows the game to react to WindowClosedEvents
		 */
		void HandleWindowClosed(WindowClosedEvent* event);
		
		/**
		 * Allows the game to react to PauseGameEvents
		 */
		void PauseGame(PauseGameEvent* event);

		/**
		 * Set the game's current level
		 * @param newLevelPath path to the new level's data file
		 */
		void SetLevel(const std::string& newLevelPath);

		/** The game's current level */
		std::shared_ptr<Scene> scene;
		
		/** A Handle to the Engine's thread pool */
		std::shared_ptr<utils::ThreadPool> threadPool;

		/** Resource Manager for the engine's config files */
		utils::ResourceAllocator<utils::Configuration> configCache;

		utils::Configuration engineConfig;

		/** Engine's central event bus */
		std::shared_ptr<EventBus> eventBus;

		/** A handle to the game's display */
		std::shared_ptr<Window> window;

		/** Pointer to the game's Input Manager*/
		std::shared_ptr<InputManager> inputManager;

		/** Pointer to physics subsystem */
		std::shared_ptr<PhysicsEngine> physicsEngine;
		
		/** Pointer to the game's Audio Manger */
		std::unique_ptr<AudioManager> audioManager;

		/** Flag to determine when the game loop should terminate */
		bool isTerminated;

		/** Flag to query whether the game is paused */
		bool isPaused;

		/**
		 * Helper class to connect Game to the event bus
		 */
		class GameEventBusNode : public EventBusNode {
		public:
			/**
			 * Constructor
			 */
			GameEventBusNode(EventBus* bus, Game* owner) 
				: EventBusNode(bus), Owner(owner) {

			}

			/**
			 * Function to dispatch events to Game
			 */
			virtual void ReceiveEvent(Event* event) {
				EventDispatcher dispatcher(event);
				
				dispatcher.Dispatch<WindowClosedEvent>(
					[this](WindowClosedEvent* windowEvent) {
						Owner->HandleWindowClosed(windowEvent);
					}
				);

				dispatcher.Dispatch<InputActionEvent>(
					[this](InputActionEvent* event) {
						auto action = event->action;
						if (action.Action == "PauseGame" && action.Type == ActionType::PRESSED) {
							PublishEvent(new PauseGameEvent());
						}
					}
				);

				dispatcher.Dispatch<PauseGameEvent>(
					[this](PauseGameEvent* pauseEvent) {
						Owner->PauseGame(pauseEvent);
					}
				);

			}

			/**
			 * Allows EventBus to query the node's subscription, and filter events accordingly
			 */
			unsigned GetSubscription() override {
				static const unsigned char ALL_FLAG = -1;
				static const unsigned char RAW_INPUT_FLAG = static_cast<unsigned char>(EventCategory::RAW_INPUT);

				//Accept all events except raw input flags
				return ALL_FLAG ^ RAW_INPUT_FLAG;
			}

			Game* Owner;
		};

		std::unique_ptr<GameEventBusNode> m_CentralBusNode;

	};

}