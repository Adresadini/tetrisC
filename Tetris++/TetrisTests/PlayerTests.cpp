#include "pch.h"
#include "CppUnitTest.h"

#include "..\Tetris++\Player.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TetrisTests
{
	TEST_CLASS(PlayerTests)
	{
	public:

		TEST_METHOD(PlayerOneAndTwoDifference)
		{
			Player p1("Player", 120);
			Player p2("Player", 120, true);
			Assert::AreNotEqual(p1, p2);
		}
	};
}