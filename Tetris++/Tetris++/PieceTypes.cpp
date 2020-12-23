#include "PieceTypes.h"

PieceTypes::PieceTypes(const std::string& filename)
{
	std::ifstream in(filename);
	in >> m_numberOfPieces;
	std::array<uint16_t, PiecesSize> pieceType;
	uint16_t blockNumber;
	std::string scale;
	for (uint8_t piece = 0; piece < m_numberOfPieces; piece++)
	{
		for (uint8_t block = 0; block < PiecesSize; block++)
		{
			in >> blockNumber;
			pieceType.at(block) = blockNumber;
		}
		m_pieceType.push_back(pieceType);
		in >> scale;
		if (scale == "Line")
			m_scaleType.push_back(scaleType::Line);
		else if(scale=="Normal")
			m_scaleType.push_back(scaleType::Normal);
		else if(scale=="Special")
			m_scaleType.push_back(scaleType::Special);
	}
}

size_t PieceTypes::GetNumberOfPieces() const
{
	return m_numberOfPieces;
}

std::array<uint16_t, PieceTypes::PiecesSize> PieceTypes::GetPiece(const uint8_t& number) const
{
	return m_pieceType.at(number);
}

PieceTypes::scaleType PieceTypes::GetScale(const uint8_t& number) const
{
	return m_scaleType.at(number);
}
