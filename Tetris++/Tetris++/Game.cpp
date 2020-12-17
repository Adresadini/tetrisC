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
				m_board.DeleteCompleteLines();			// TO DO: optimize this function : Delete Complete Lines
				m_hole.Spawn(m_board, *m_currentPiece);
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
	sf::RenderWindow window(sf::VideoMode(m_board.GetWidth() * (sizeOfBlockLine + 1), m_board.GetHeight() * (sizeOfBlockLine + 1)), "Tetris++",
		sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
	sf::RectangleShape shape(sf::Vector2(sizeOfBlockLine, sizeOfBlockLine));

	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
			if (evnt.type == sf::Event::Closed)
				window.close();

		window.clear(sf::Color::White);

		DisplayBoard(window);
		if (m_CurrentPiece->IsSet())
		{
			delete m_CurrentPiece;
			m_CurrentPiece = new TetrisPiece(POS, m_types);
		}
		m_CurrentPiece->MoveDown(m_board);
		Sleep(250);

		window.display();

	}
}

	void setBlock(std::optional<uint8_t> block, sf::RectangleShape & shape)
	{
		if (block == std::nullopt)
			shape.setFillColor(sf::Color::Black);
		if (block == 0)
			shape.setFillColor(sf::Color::White);
		if (block == 1)
			shape.setFillColor(sf::Color::Blue);
		if (block == 2)
			shape.setFillColor(sf::Color::Red);
		if (block == 3)
			shape.setFillColor(sf::Color::Green);
		if (block == 4)
			shape.setFillColor(sf::Color::Yellow);
		if (block == 5)
			shape.setFillColor(sf::Color::Magenta);
		if (block == 6)
			shape.setFillColor(sf::Color::Cyan);

	}

	void Game::DisplayBoard(sf::RenderWindow & window)
	{
		sf::RectangleShape shape(sf::Vector2(sizeOfBlokLine, sizeOfBlokLine));

		float linePosition = -(sizeOfBlokLine);
		for (uint16_t line = 0; line < m_board.GetHeight(); line++)
		{
			linePosition += sizeOfBlokLine + 1;
			float columnPosition = -(sizeOfBlokLine);
			for (uint16_t column = 0; column < m_board.GetWidth(); column++)
			{
				columnPosition += sizeOfBlockLine + 1;
				shape.setPosition(columnPosition, linePosition);
				setBlock(m_board[{line, column}], shape);
				window.draw(shape);
			}
		}
		window.display();
	}
}

void Game::CheckTopLine()
{
	for (int8_t column = 0; column < m_board.GetWidth(); column++)
		if (m_board[{0, column}])
			m_gameOver = true;
}
