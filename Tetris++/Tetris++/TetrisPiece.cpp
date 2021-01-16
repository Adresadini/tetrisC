#include "TetrisPiece.h"
#include <random>
#include <conio.h>

TetrisPiece::TetrisPiece(const Board::Position& pos, const PieceTypes& types,const bool& isPlayerTwo)
	:m_position(pos)
{
	std::random_device random;
	std::uniform_int_distribution<uint16_t> pieceDistribution(0, types.GetNumberOfPieces() - 1);
	uint8_t randomPiece = pieceDistribution(random);
	pieceType = randomPiece + 1;

	if (isPlayerTwo)
		pieceType += 20;

	for (auto block : types.GetPiece(randomPiece))
		m_piece[block] = pieceType;
	m_scaleType = types.GetScale(randomPiece);
}

void TetrisPiece::MoveLeft(Board& board)
{
	if (m_set)
		m_set = !m_set;
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
				if (line > 0)
				{
					if (line + 1 >= board.GetHeight() || board[{line + 1, column}] && board[{line + 1, column}] != 0)
					{
						m_set = true;
						RemovePart(iterator);
						if (!IsEmpty())
							m_set = false;
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
	if (m_set)
		m_set = !m_set;
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
				if (board[{line, column}] && board[{line, column}] != 0 && board[{line, column}].value() % 10 != aux[iterator].value() % 10)
					return;
			}
		}
	Delete(board);
	std::swap(aux, m_piece);
	std::swap(auxPos, m_position);
	m_vertical = !m_vertical;
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
	for (int8_t line = auxPos.first; line < auxPos.first + (signed)kHeight; line++)
		for (int8_t column = auxPos.second; column < auxPos.second + (signed)kWidth; column++)
		{
			iterator = (line - auxPos.first) * kWidth + column - auxPos.second;
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
				if (board[{line, column}] && board[{line, column}] != 0 && board[{line, column}].value() % 10 != aux[iterator].value() % 10)
					return;
			}
		}
	Delete(board);
	std::swap(aux, m_piece);
	std::swap(auxPos, m_position);
	m_vertical = !m_vertical;
	Draw(board);
}

void TetrisPiece::Scale(Board& board)
{
	if (m_disableScaling || m_position.first < 0)
		return;
	std::array<std::optional<uint8_t>, TetrisPiece::kSize> aux = m_piece;
	Board::Position auxPos = m_position;
	if (!m_scaled)
	{
		if (m_scaleType != PieceTypes::scaleType::Line)
			FillBorders(aux);
		if (m_scaleType != PieceTypes::scaleType::Normal)
			FixMiddle(aux);
		for (int8_t line = auxPos.first; line < auxPos.first + (signed)kHeight; line++)
			for (int8_t column = auxPos.second; column < auxPos.second + (signed)kWidth; column++)
			{
				uint8_t iterator = (line - auxPos.first) * kWidth + column - auxPos.second;
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
				uint8_t iterator = (line - auxPos.first) * kWidth + column - auxPos.second;
				if (aux[iterator])
				{
					if (board[{line, column}] && board[{line, column}] != 0 && board[{line, column}].value() % 10 != aux[iterator].value() % 10)
						return;
				}
			}
	}
	else
		ScaleDown(aux);
	m_scaled = !m_scaled;
	Delete(board);
	m_piece = aux;
	m_position = auxPos;
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
				{
					m_piece[iterator] = std::nullopt;
					board[{line, column}] = 0;
					if (IsEmpty())
						m_set = true;
					m_disableScaling = true;
				}
				else
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
	return m_set;
}


void TetrisPiece::DropDown(Board& board)
{
	Delete(board);
	while (!m_set)
		MoveDown(board);
	Draw(board);
}

bool TetrisPiece::IsEmpty() const
{
	for (int8_t column = 0; column < kWidth; column++)
		for (int8_t line = kHeight - 1; line >= 0; line--)
		{
			int8_t iterator = line * kWidth + column;
			if (m_piece[iterator])
				return false;
		}
	return true;
}

void TetrisPiece::DeleteCompleteLines(Board& board)
{
	for (int line = m_position.first; line < m_position.first + (signed)kHeight && line < board.GetHeight(); line++)
		if (board.VerifyIfLineIsComplete(line))
			board.DeleteAndReplaceLine(line);

}

void TetrisPiece::SetPieceForPlayerTwo()
{
	pieceType += 20;
}

void TetrisPiece::FillBorders(std::array<std::optional<uint8_t>, TetrisPiece::kSize>& aux)
{
	for (int8_t column = 1; column < (signed)kWidth - 1; column++) //fills horizontal borders
	{
		if (aux[kWidth + column])
			if (aux[column] != pieceType && aux[column - 1] != pieceType && aux[column + 1] != pieceType)
				aux[column] = 10 + pieceType;
		if (aux[(kHeight - 2) * kWidth + column])
			if (aux[(kHeight - 1) * kWidth + column] != pieceType && aux[(kHeight - 1) * kWidth + column - 1] != pieceType && aux[(kHeight - 1) * kWidth + column + 1] != pieceType)
				aux[(kHeight - 1) * kWidth + column] = 10 + pieceType;
	}

	for (int8_t line = 1; line < (signed)kHeight - 1; line++) //fills vertical borders
	{
		if (aux[line * kWidth + kWidth - 2])
			if (aux[line * kWidth + kWidth - 1] != pieceType && aux[(line - 1) * kWidth + kWidth - 1] != pieceType && aux[(line + 1) * kWidth + kWidth - 1] != pieceType)
				aux[line * kWidth + kWidth - 1] = 10 + pieceType;
		if (aux[line * kWidth + 1])
			if (aux[line * kWidth] != pieceType && aux[(line - 1) * kWidth] != pieceType && aux[(line + 1) * kWidth] != pieceType)
				aux[line * kWidth] = 10 + pieceType;
	}

	if (aux[1] && aux[kWidth])   //fills corners
		aux[0] = 10 + pieceType;
	if (aux[kWidth - 2] && aux[2 * kWidth - 1])
		aux[kWidth - 1] = 10 + pieceType;
	if (aux[(kHeight - 1) * kWidth - 1] && aux[kHeight * kWidth - 2])
		aux[kHeight * kWidth - 1] = 10 + pieceType;
	if (aux[kHeight * (kWidth - 2)] && aux[kHeight * (kWidth - 1) + 1])
		aux[kHeight * (kWidth - 1)] = 10 + pieceType;

}

void TetrisPiece::FixMiddle(std::array<std::optional<uint8_t>, TetrisPiece::kSize>& aux)
{
	if (m_vertical)
		for (int8_t column = 1; column < kWidth - 1; column++)
			for (int8_t line = 0; line < kHeight; line++)
			{
				if (!aux[line * kWidth + column])
					aux[line * kWidth + column] = 10 + pieceType;
			}
	else
		for (int8_t column = 0; column < kWidth; column++)
			for (int8_t line = 1; line < kHeight - 1; line++)
			{
				if (!aux[line * kWidth + column])
					aux[line * kWidth + column] = 10 + pieceType;
			}
}

void TetrisPiece::ScaleDown(std::array<std::optional<uint8_t>, TetrisPiece::kSize>& aux)
{
	for (int8_t block = 0; block < kSize; block++)
		if (aux[block] == 10 + pieceType)
		{
			aux[block] = std::nullopt;
		}
}

void TetrisPiece::RemovePart(const uint8_t& block)
{
	m_piece[block] = std::nullopt;
	if (block - 1 < kSize && m_piece[block - 1] && block % kWidth > (block - 1) % kWidth)
		RemovePart(block - 1);
	if (block + 1 < kSize && m_piece[block + 1] && block % kWidth < (block + 1) % kWidth)
		RemovePart(block + 1);
	if (block - kWidth < kSize && m_piece[block - kWidth])
		RemovePart(block - kWidth);
	if (block + kWidth < kSize && m_piece[block + kWidth])
		RemovePart(block + kWidth);
}
