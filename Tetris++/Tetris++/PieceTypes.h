#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
class PieceTypes
{
public:
	enum class scaleType { Normal, Special, Line };

public:
	static const size_t PiecesSize = 4;

public:
	PieceTypes(const std::string& filename);
	std::array<uint16_t, PiecesSize> GetPiece(const uint8_t&) const;
	scaleType GetScale(const uint8_t&) const;
	size_t GetNumberOfPieces() const;

private:
	size_t m_numberOfPieces;
	std::vector<std::array<uint16_t, PiecesSize>> m_pieceType;
	std::vector<scaleType> m_scaleType;
};

