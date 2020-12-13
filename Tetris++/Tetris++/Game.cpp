#include "Game.h"

Game::Game(const uint16_t& width, const uint16_t& height, const bool& multiPlayer, std::string filename)
	:m_board(width, height, multiPlayer), m_types(filename)
{
	m_pos = { -2,1 };
	m_gameOver = false;
	m_CurrentPiece = new TetrisPiece(m_pos, m_types);
}

void Game::Run()
{

	while (!m_gameOver)
	{
		try {
			std::cout << m_board;
			m_CurrentPiece->movePiece(m_board, m_gameOver);
			Board::Position piecePosition = m_CurrentPiece->GetPosition();
			m_CurrentPiece->MoveDown(m_board);
			if (m_CurrentPiece->GetPosition().first == piecePosition.first)
			{
				delete m_CurrentPiece;
				m_CurrentPiece = new TetrisPiece(m_pos, m_types);
			}
			Sleep(250);
			system("CLS");
		}
		catch (const char* errorMessage)
		{
			std::cout << errorMessage;
		}
	}
	std::cout << "Game Over!";
}
