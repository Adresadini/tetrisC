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

void Game::VisualInterface()
{
	sf::RenderWindow window(sf::VideoMode(m_board.GetWidth() * (sizeOfBlokLine + 1), m_board.GetHeight() * (sizeOfBlokLine + 1)), "Tetris++",
		sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
	sf::RectangleShape shape(sf::Vector2(sizeOfBlokLine, sizeOfBlokLine));

	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == evnt.Closed)
			{
				window.close();
			}

		}
		window.clear();
		float linePosition = -(sizeOfBlokLine);
		for (uint16_t line = 0; line < m_board.GetHeight(); line++)
		{
			linePosition += sizeOfBlokLine + 1;
			float columnPosition = -(sizeOfBlokLine);
			for (uint16_t column = 0; column < m_board.GetHeight(); column++)
			{
				columnPosition += sizeOfBlokLine + 1;
				shape.setPosition(columnPosition, linePosition);
				window.draw(shape);
			}
		}
		window.display();
	}
}
