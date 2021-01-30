#include "pch.h"
#include "CppUnitTest.h"

#include "Player.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TetrisTests
{
	TEST_CLASS(PlayerTests)
	{
	public:

		TEST_METHOD(PlayerConstructor)
		{
			Player player("Player");
			Assert::IsTrue(player.GetName() == "Player");
			Assert::IsTrue(player.GetScore() == 0);
		}

		TEST_METHOD(PlayerSetName)
		{
			Player player;
			player.SetInfo("Player");
			Assert::IsTrue(player.GetName() == "Player");
		}

		TEST_METHOD(PlayerSetScore)
		{
			Player player;
			player.AddScore(120);
			Assert::IsTrue(player.GetScore() == 120);
		}

		TEST_METHOD(PlayerToString)
		{
			Player player("Player");
			Assert::IsTrue(player.PlayerToString() == "Player 0");
		}
	};
}