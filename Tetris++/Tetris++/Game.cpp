#include "Game.h"

Game::Game(const uint16_t& width, const uint16_t& height, const bool& multiPlayer, std::string filename)
	:m_board(width, height, multiPlayer), m_types(filename)
{
	m_gameOver = false;
	m_currentPiece = new TetrisPiece(POS, m_types);
}

void Game::Run()
{
	m_hole.Spawn(m_board, *m_currentPiece);
	while (!m_gameOver)
	{
		try {
			std::cout << m_board;
			m_currentPiece->MovePiece(m_board, m_gameOver);
			//Board::Position piecePosition = m_CurrentPiece->GetPosition();
			m_currentPiece->MoveDown(m_board);
			if (m_currentPiece->IsSet())
			{
				CheckTopLine();
				delete m_currentPiece;
				m_currentPiece = new TetrisPiece(POS, m_types);
				m_hole.Disappear(m_board);
				m_board.DeleteCompleteLines();			// TO DO: optimize this function : Delete Complet Lines
				m_hole.Spawn(m_board, *m_currentPiece);
			}
			Sleep(50);
			system("CLS");
		}
		catch (const char* errorMessage)
		{
			std::cout << errorMessage;
		}
	}
	system("CLS");
	std::cout << "Game Over!";
}

void Game::CheckTopLine()
{
	for (int8_t column = 0; column < m_board.GetWidth(); column++)
		if (m_board[{0, column}])
			m_gameOver = true;
}
