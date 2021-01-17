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

		TEST_METHOD(SetName)
		{
			Player player;
			player.SetName("Player");
			Assert::AreEqual(player.GetName(),(std::string)"Player");
		}

		TEST_METHOD(SetScore)
		{
			Player player;
			player.SetScore(120);
			Assert::AreEqual(player.GetScore(), (uint16_t)120);
		}
	};
}