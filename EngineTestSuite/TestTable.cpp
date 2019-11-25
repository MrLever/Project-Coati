//STD Headers

//Library Headers
#include "CppUnitTest.h"

//Void Engine Headers
#include "Table.h"
#include "Name.h"
#include "ColliderComponent.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace utils;

namespace EngineUtilitiesTests {

	TEST_CLASS(TableTests) {
	public:
		TEST_METHOD(TableArrayInexOperatorTest) {
			Table<int, int, int> table;

			table[1][1] = 2;
			Assert::AreEqual(2, table[1][1]);
		}

		TEST_METHOD(TableFindTest) {
			Table<int, int, int> table;
			Assert::IsNull(table.Find(1, 1));

			table.Insert(1, 1, 164);
			Assert::AreEqual(164, table[1][1]);

			
			Assert::AreEqual(164, *table.Find(1, 1));
		}

		TEST_METHOD(TableEraseTest) {
			Table<int, int, int> table;
			table[1][1] = 100;
			Assert::AreEqual(100, *table.Find(1, 1));

			table.Erase(1, 1);

			Assert::IsNull(table.Find(1, 1));
		}

		TEST_METHOD(AdvancedTemplateParameterTest) {
			Table<
				utils::Name, 
				utils::Name, 
				std::function<bool(core::ColliderComponent*, core::ColliderComponent*)>
			> table;

			utils::Name i("i");
			utils::Name j("j");
			auto lambda = [](core::ColliderComponent*, core::ColliderComponent*) {
				return true;
			};

			table[i][j] = lambda;

			Assert::IsTrue(table[i][j](nullptr, nullptr));

		}
	};
};