#include "stdafx.h"
#include "CppUnitTest.h"
#include "WindowManager.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EngineTestSuite
{		

	using namespace EngineCore;

	TEST_CLASS(WindowManagerTests) {
	public:
		
		TEST_METHOD(WindowCreationTest) {
			WindowManager test("Test", 600, 800);

			Assert::IsNotNull(test.getWindow().get());
		}
		TEST_METHOD(BufferSwapTest) {
			WindowManager test("Test", 600, 800);
			test.SwapBuffers();

			//It didn't crash.
			Assert::AreEqual(1, 1);
		}
	};
}