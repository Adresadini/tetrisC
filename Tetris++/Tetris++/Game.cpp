#include "Game.h"

Game::Game(const uint16_t& width, const uint16_t& height, const bool& multiPlayer, std::string filename)
	:m_board(width, height, multiPlayer), m_types(filename)
{
	m_gameOver = false;
	m_CurrentPiece = new TetrisPiece(POS, m_types);
}

void Game::Run()
{
	m_hole.Spawn(m_board, *m_CurrentPiece);
	while (!m_gameOver)
	{
		try {
			
			std::cout << m_board;
			m_CurrentPiece->MovePiece(m_board, m_gameOver);
			//Board::Position piecePosition = m_CurrentPiece->GetPosition();
			m_CurrentPiece->MoveDown(m_board);
			if (m_CurrentPiece->IsSet())
			{
				delete m_CurrentPiece;
				m_CurrentPiece = new TetrisPiece(POS, m_types);
				m_hole.Disappear(m_board);
				m_board.DeleteCompleteLines();			// TO DO: optimize this function : Delete Complet Lines
				m_hole.Spawn(m_board, *m_CurrentPiece);
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
