#include "TetrisPiece.h"
TetrisPiece::TetrisPiece(Board::Position pos, uint8_t pieceType)
	:m_position(pos)
{
	if (pieceType >= NumberOfPieces)
		throw "Wrong piece type";
	for (auto block : m_pieceType[pieceType])
		m_piece[block] = pieceType + 1;
}

void TetrisPiece::MoveLeft(Board& board)
{
	uint8_t iterator = 0;
	for (uint8_t line = m_position.first; line < m_position.first + kHeight; line++)
		for (uint8_t column = m_position.second; column < m_position.second + kWidth; column++)
		{
			if (m_piece[iterator] && column -1 <0)
				return;
			iterator++;
		}
	Delete(board);
	m_position.second--;
	Draw(board);
}

void TetrisPiece::MoveDown(Board &board)
{
	uint8_t iterator = 0;
	for (uint8_t line = m_position.first; line < m_position.first + kHeight; line++)
		for (uint8_t column = m_position.second; column < m_position.second + kWidth; column++)
		{
			if (m_piece[iterator] && line + 1 >= board.getHeight())
				return;
			iterator++;
		}
	Delete(board);
	m_position.first++;
	Draw(board);
}

void TetrisPiece::MoveRight(Board& board)
{
	uint8_t iterator = 0;
	for (uint8_t line = m_position.first; line < m_position.first + kHeight; line++)
		for (uint8_t column = m_position.second; column < m_position.second + kWidth; column++)
		{
			if (m_piece[iterator] && column+1>= board.getWidth())
				return;
			iterator++;
		}
	Delete(board);
	m_position.second++;
	Draw(board);
}

void TetrisPiece::Draw(Board& board)
{
	uint8_t iterator = 0;
	for (uint8_t line = m_position.first; line < m_position.first + kHeight; line++)
		for (uint8_t column = m_position.second; column < m_position.second + kWidth; column++)
		{
			if (m_piece[iterator])
				board[{line, column}] = m_piece[iterator];
			iterator++;
		}
}

void TetrisPiece::Delete(Board& board)
{
	uint8_t iterator = 0;
	for (uint8_t line = m_position.first; line < m_position.first + kHeight; line++)
		for (uint8_t column = m_position.second; column < m_position.second + kWidth; column++)
		{
			if (m_piece[iterator])
				board[{line, column}] = std::nullopt;
			iterator++;
		}
}
