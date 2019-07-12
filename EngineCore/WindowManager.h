#pragma once
//STD Headers
#include <iostream>
#include <memory>
#include <string>

//Library Headers
#include "glad/glad.h"
#include "GLFW/glfw3.h"

//Coati Headers
#include "InputInterfaceManager.h"
#include "EngineUtilities.h"


namespace EngineCore {

	class WindowManager {

	private:
		//Private class members
		std::shared_ptr<GLFWwindow> Window;
		std::string GameName;
		std::shared_ptr<InputInterfaceManager> PlayerInterface;

		int WindowWidth;
		int WindowHeight;

		static WindowManager* CurrWindowManager;

		static const int OPENGL_MAJOR = 4;
		static const int OPENGL_MINOR = 5;

	public:
		//CTORS
		WindowManager(std::string gameName, int windowWidth, int windowHeight);
		~WindowManager();

	private:
		//Private member functions
		void InitGLFW();
		void InitGLAD();

	public:
		//Public member functions
		std::shared_ptr<GLFWwindow> getWindow();

		void SwapBuffers();
		bool WindowTerminated();

		std::shared_ptr<InputInterfaceManager> GetInputInterface();

		//Static Functions
		static void DeleteWindow(GLFWwindow* window) {
			glfwDestroyWindow(window);
		}

		static void ReportWindowError(int error, const char* description) {
			std::cerr << "Error: " << description << std::endl;
		}

		static void ResizeFrameBuffer(GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);

			CurrWindowManager->WindowWidth = width;
			CurrWindowManager->WindowHeight = height;
		}

		static void KeyboardInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
			//Get time stamp for KeyBoardInput
			auto timeStamp = EngineUtils::GetGameTime();

			//Create Coati KeyboardInput
			KeyboardInputPtr input = std::make_shared<KeyboardInput>(
				static_cast<KeyboardButton>(key), 
				static_cast<ButtonState>(action), 
				timeStamp
			);
			
			//Report Input to Input Interface for later polling.
			CurrWindowManager->PlayerInterface->ReportKeyboardInput(input);

		}

		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
			//Get time stamp for MouseButton event
			auto timeStamp = EngineUtils::GetGameTime();
			
			//Create Coati MouseInput
			MouseInputPtr input = std::make_shared<MouseInput>(
				static_cast<MouseButton>(button),
				static_cast<ButtonState>(action),
				timeStamp
			);

			//Report input to InputInterface
			CurrWindowManager->PlayerInterface->ReportMouseKeyInput(input);
		}

		static void MousePositionCallback(GLFWwindow* window, double xPos, double yPos) {
			CurrWindowManager->PlayerInterface->ReportMousePosition(xPos, yPos);
		}
	};

}