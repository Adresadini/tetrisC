#include "pch.h"
#include "CppUnitTest.h"

#include "Board.h"
#include "Board.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TetrisTests
{
	TEST_CLASS(BoardTests)
	{
	public:

		TEST_METHOD(BoardConstructor)
		{
			Board board(10, 30, false);
			Assert::IsTrue(board.GetWidth() == 10);
			Assert::IsTrue(board.GetHeight() == 30);
		}

		TEST_METHOD(GetAtOneOne)
		{
			Board board(10, 30, false);
			Board::Position position{ 1,1 };
			Assert::IsFalse(board[position].has_value());
		}

		TEST_METHOD(GetAtMinusOneOne)
		{
			Board board(10, 30, false);
			Board::Position position{ -1,1 };
			Assert::ExpectException<const char*>([&]() {
				board[position];
				});
		}

		TEST_METHOD(GetAtMinusOneOneConst)
		{
			const Board board(10, 30, false);
			Board::Position position{ -1,1 };
			Assert::ExpectException<std::out_of_range>([&]() {
				board[position];
				});
		}

		TEST_METHOD(GetAtOneMinusOne)
		{
			Board board(10, 30, false);
			Board::Position position{ 1,-1 };
			Assert::ExpectException<const char*>([&]() {
				board[position];
				});
		}

		TEST_METHOD(GetAtOneMinusOneConst)
		{
			const Board board(10, 30, false);
			Board::Position position{ 1,-1 };
			Assert::ExpectException<std::out_of_range>([&]() {
				board[position];
				});
		}
	};
}