#include "TetrisPiece.h"
void Rotation(std::optional<uint8_t>& a, std::optional<uint8_t>& b, std::optional<uint8_t>& c, std::optional<uint8_t>& d)
{
	std::swap(a, b);
	std::swap(b, c);
	std::swap(c, d);
}
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
			if (m_piece[iterator] && column - 1 < 0)
				return;
			iterator++;
		}
	Delete(board);
	m_position.second--;
	Draw(board);
}

void TetrisPiece::MoveDown(Board& board)
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
			if (m_piece[iterator] && column + 1 >= board.getWidth())
				return;
			iterator++;
		}
	Delete(board);
	m_position.second++;
	Draw(board);
}

void TetrisPiece::RotateLeft(Board& board)
{
	std::array<std::optional<uint8_t>, TetrisPiece::kSize> aux;
	uint8_t iterator = 0;
	for (int column = kWidth - 1; column >= 0; column--)
		for (int line = 0; line < kHeight; line++)
		{
			aux[iterator] = m_piece[line * kWidth + column];
			iterator++;
		}

	Delete(board);
	std::swap(aux, m_piece);
	Draw(board);
}

void TetrisPiece::RotateRight(Board& board)
{
	std::array<std::optional<uint8_t>, TetrisPiece::kSize> aux;
	uint8_t iterator = 0;
	for (int column = 0; column < kWidth; column++)
		for (int line = kHeight - 1; line >= 0; line--)
		{
			aux[iterator] = m_piece[line * kWidth + column];
			iterator++;
		}

	Delete(board);
	std::swap(aux, m_piece);
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

size_t TetrisPiece::getKHeight()
{
	return kHeight;
}

size_t TetrisPiece::getKWidth()
{
	return kWidth;
}

Board::Position TetrisPiece::getPosition()
{
	return m_position;
}
