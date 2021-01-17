#include "pch.h"
#include "CppUnitTest.h"

#include "Board.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TetrisTests
{
	TEST_CLASS(BoardTests)
	{
	public:

		TEST_METHOD(BoardConstructor)
		{
			Board board(10, 20, false);
			Assert::IsTrue(board.GetWidth() == 10);
			Assert::IsTrue(board.GetHeight() == 20);
		}

		TEST_METHOD(GetAtOneOne)
		{
			Board board(10, 20, false);
			Board::Position position{ 1,1 };
			Assert::IsFalse(board[position].has_value());
		}
	};
}