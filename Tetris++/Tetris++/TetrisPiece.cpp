#include "TetrisPiece.h"
#include <random>
#include <conio.h>

TetrisPiece::TetrisPiece(const Board::Position& pos, const PieceTypes& types)
	:m_position(pos)
{
	std::random_device random;
	std::uniform_int_distribution<uint16_t> pieceDistribution(0, types.GetNumberOfPieces() - 1);
	uint8_t randomPiece = pieceDistribution(random);

	for (auto block : types.GetPiece(randomPiece))
		m_piece[block] = randomPiece + 1;

}

void TetrisPiece::MoveLeft(Board& board)
{
	uint8_t iterator = 0;
	for (int8_t line = m_position.first; line < m_position.first + (signed)kHeight; line++)
		for (int8_t column = m_position.second; column < m_position.second + (signed)kWidth; column++)
		{
			iterator = (line - m_position.first) * kWidth + column - m_position.second;
			if (m_piece[iterator])
			{
				if (line >= 0)
				{
					if (column - 1 < 0 || board[{line, column - 1}] && board[{line, column - 1}] != 0)
						return;
					else
					{
						break;
					}
				}
			}
		}
	Delete(board);
	m_position.second--;
	Draw(board);
}

void TetrisPiece::MoveDown(Board& board)
{
	uint8_t iterator = kSize - 1;
	for (int8_t column = m_position.second + (signed)kWidth - 1; column >= m_position.second; column--)
		for (int8_t line = m_position.first + (signed)kHeight - 1; line >= m_position.first; line--)
		{
			iterator = (line - m_position.first) * kWidth + column - m_position.second;
			if (m_piece[iterator])
			{
				if (line >= 0)
				{
					if (line + 1 >= board.GetHeight() || board[{line + 1, column}] && board[{line + 1, column}] != 0)
					{
						set = true;
						return;
					}
					else
					{
						break;
					}
				}

			}
		}
	Delete(board);
	m_position.first++;
	Draw(board);
}

void TetrisPiece::MoveRight(Board& board)
{
	uint8_t iterator;
	for (int8_t line = m_position.first + (signed)kHeight - 1; line >= m_position.first; line--)
		for (int8_t column = m_position.second + (signed)kWidth - 1; column >= m_position.second; column--)
		{
			iterator = (line - m_position.first) * kWidth + column - m_position.second;
			if (m_piece[iterator])
			{
				if (line >= 0)
				{
					if (column + 1 >= board.GetWidth() || board[{line, column + 1}] && board[{line, column + 1}] != 0)
						return;
					else
					{
						break;
					}
				}
			}
		}
	Delete(board);
	m_position.second++;
	Draw(board);
}

void TetrisPiece::RotateLeft(Board& board)
{
	if (m_position.first < 0)
		return;
	std::array<std::optional<uint8_t>, TetrisPiece::kSize> aux;
	Board::Position auxPos = m_position;
	uint8_t iterator = 0;
	for (int8_t column = kWidth - 1; column >= 0; column--)
		for (int8_t line = 0; line < kHeight; line++)
		{
			aux[iterator] = m_piece[line * kWidth + column];
			iterator++;
		}
	for (int8_t line = m_position.first; line < m_position.first + (signed)kHeight; line++)
		for (int8_t column = m_position.second; column < m_position.second + (signed)kWidth; column++)
		{
			iterator = (line - m_position.first) * kWidth + column - m_position.second;
			if (aux[iterator])
			{
				if (column >= board.GetWidth())
					auxPos.second--;
				if (column < 0)
					auxPos.second += 2;
				if (line >= board.GetHeight())
					auxPos.first--;
			}
		}
	for (int8_t line = auxPos.first; line < auxPos.first + (signed)kHeight; line++)
		for (int8_t column = auxPos.second; column < auxPos.second + (signed)kWidth; column++)
		{
			iterator = (line - auxPos.first) * kWidth + column - auxPos.second;
			if (aux[iterator])
			{
				if (board[{line, column}] && board[{line, column}] != 0 && board[{line, column}] != aux[iterator])
					return;
			}
		}
	Delete(board);
	std::swap(aux, m_piece);
	std::swap(auxPos, m_position);
	Draw(board);
}

void TetrisPiece::RotateRight(Board& board)
{
	if (m_position.first < 0)
		return;
	std::array<std::optional<uint8_t>, TetrisPiece::kSize> aux;
	Board::Position auxPos = m_position;
	uint8_t iterator = 0;
	for (int8_t column = 0; column < kWidth; column++)
		for (int8_t line = kHeight - 1; line >= 0; line--)
		{
			aux[iterator] = m_piece[line * kWidth + column];
			iterator++;
		}
	for (int8_t line = m_position.first; line < m_position.first + (signed)kHeight; line++)
		for (int8_t column = m_position.second; column < m_position.second + (signed)kWidth; column++)
		{
			iterator = (line - m_position.first) * kWidth + column - m_position.second;
			if (aux[iterator])
			{
				if (column >= board.GetWidth())
					auxPos.second--;
				if (column < 0)
					auxPos.second += 2;
				if (line >= board.GetHeight())
					auxPos.first--;
			}
		}
	for (int8_t line = auxPos.first; line < auxPos.first + (signed)kHeight; line++)
		for (int8_t column = auxPos.second; column < auxPos.second + (signed)kWidth; column++)
		{
			iterator = (line - auxPos.first) * kWidth + column - auxPos.second;
			if (aux[iterator])
			{
				if (board[{line, column}] && board[{line, column}] != 0 && board[{line, column}] != aux[iterator])
					return;
			}
		}
	Delete(board);
	std::swap(aux, m_piece);
	std::swap(auxPos, m_position);
	Draw(board);
}

void TetrisPiece::Draw(Board& board)
{
	uint8_t iterator;
	for (int8_t line = m_position.first; line < m_position.first + (signed)kHeight; line++)
		for (int8_t column = m_position.second; column < m_position.second + (signed)kWidth; column++)
		{
			iterator = (line - m_position.first) * kWidth + column - m_position.second;
			if (line >= 0 && m_piece[iterator])
			{
				if (board[{line, column}] == 0)
					m_piece[iterator] = std::nullopt;
				board[{line, column}] = m_piece[iterator];
			}
		}
}

void TetrisPiece::Delete(Board& board) const
{
	uint8_t iterator;
	for (int8_t line = m_position.first; line < m_position.first + (signed)kHeight; line++)
		for (int8_t column = m_position.second; column < m_position.second + (signed)kWidth; column++)
		{
			iterator = (line - m_position.first) * kWidth + column - m_position.second;
			if (m_piece[iterator] && line >= 0)
				board[{line, column}] = std::nullopt;
		}
}

size_t TetrisPiece::GetKHeight() const
{
	return kHeight;
}

size_t TetrisPiece::GetKWidth() const
{
	return kWidth;
}

Board::Position TetrisPiece::GetPosition() const
{
	return m_position;
}

bool TetrisPiece::IsSet() const
{
	return set;
}

void TetrisPiece::MovePiece(Board& board, bool gameOver)
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			MoveLeft(board);
			break;
		case 'd':
			MoveRight(board);
			break;
		case 's':
			MoveDown(board);
			break;
		case 'q':
			RotateLeft(board);
			break;
		case'e':
			RotateRight(board);
			break;
		case 27:
			gameOver = true;
			break;
		}
		system("CLS");
		std::cout << board;
	}
	
}

void TetrisPiece::ResetPieceElement(Board::Position position)
{
	m_piece[(position.first - m_position.first) * kWidth +
		position.second - m_position.second] = std::nullopt;
}