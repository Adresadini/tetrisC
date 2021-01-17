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
			Player player("Player", 120);
			Assert::IsTrue(player.GetName() == "Player" && player.GetScore() == 120);
		}

		TEST_METHOD(PlayerOneAndTwoDifferent)
		{
			Player player1("Player", 120);
			Player player2("Player", 120, true);
			Assert::AreNotEqual(player1, player2);
		}

		TEST_METHOD(PlayerSetName)
		{
			Player player;
			player.SetName("Player");
			Assert::AreEqual(player.GetName(),(std::string)"Player");
		}

		TEST_METHOD(PlayerSetScore)
		{
			Player player;
			player.SetScore(120);
			Assert::AreEqual(player.GetScore(), (uint16_t)120);
		}

		TEST_METHOD(PlayerToString)
		{
			Player player("Player", 120);
			Assert::AreEqual(player.PlayerToString(),(std::string)"Player 120");
		}
	};
}