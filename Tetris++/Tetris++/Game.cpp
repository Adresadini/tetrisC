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
	int iteratii = 0; // O sa inlocuim asta cu threads
	while (!m_gameOver)
	{
		
		try {
			m_board.DeleteCompleteLines();
			// TO DO: optimize this function : Delete Complet Lines
			std::cout << m_board;
			m_CurrentPiece->MovePiece(m_board, m_gameOver);
			Board::Position piecePosition = m_CurrentPiece->GetPosition();
			m_CurrentPiece->MoveDown(m_board);
			if (m_CurrentPiece->GetPosition().first == piecePosition.first)
			{
				delete m_CurrentPiece;
				m_CurrentPiece = new TetrisPiece(m_pos, m_types);
			}
			if (iteratii == 5)
			{
				m_hole.Disappear(m_board);
				m_hole.Spawn(m_board, *m_CurrentPiece);
				iteratii = 0;
			}
			Sleep(250);
			system("CLS");
			iteratii++;
		}
		catch (const char* errorMessage)
		{
			std::cout << errorMessage;
		}
	}
	std::cout << "Game Over!";
}
