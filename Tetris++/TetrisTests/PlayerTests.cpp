#include "pch.h"
#include "CppUnitTest.h"

#include "Player.h"
#include "Player.cpp"
#include "TetrisPiece.cpp"
#include "PieceTypes.cpp"

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

		TEST_METHOD(PlayerSetInfo)
		{
			Player player("Player");
			player.SetInfo(250, 160, 4);
			Assert::IsTrue(player.GetHighScore() == 250);
			Assert::IsTrue(player.GetAverageScore() == 160);
			Assert::IsTrue(player.GetScoreCount() == 4);
		}

		TEST_METHOD(PlayerToString)
		{
			Player player("Player");
			Assert::IsTrue(player.PlayerToString() == "Player 0");
		}

		TEST_METHOD(PlayerAddScore)
		{
			Player player("Player");
			player.AddScore(10);
			Assert::IsTrue(player.GetScore() == 10);
		}
	};
}