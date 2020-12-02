#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
class PieceTypes
{
public:
	static const size_t PiecesSize = 4;

public:
	PieceTypes(std::string filename);
	std::array<uint16_t, PiecesSize> GetPiece(uint8_t&) const;
	size_t GetNumberOfPieces() const;

private:
	size_t m_numberOfPieces;
	std::vector<std::array<uint16_t, PiecesSize>> m_pieceType;
};

