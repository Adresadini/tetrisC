#include "Game.h"

Game::Game(const uint16_t& width, const uint16_t& height, const bool& multiPlayer, std::string filename)
	:m_board(width, height, multiPlayer), m_types(filename), m_multiplayer(multiPlayer)
{
	m_gameOver = false;
	m_startPositionPlayer1 = { -2,  width / 2 - 2 };
	if (multiPlayer)
	{
		m_startPositionPlayer2 = { -2, m_board.GetWidth() / 4 * 3 };
	}
}

void Game::VisualInterface()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE); //Hides console

	sf::RenderWindow window(sf::VideoMode(m_board.GetWidth() * (sizeOfBlockLine + 1), m_board.GetHeight() * (sizeOfBlockLine + 1)), "Tetris++",
		sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);

	if (m_multiplayer)
		MultiplayerTeamLogic(window);
	else
		SingleplayerLogic(window);




}



void setBlock(std::optional<uint8_t> block, sf::RectangleShape& shape)
{
	if (block == std::nullopt)
	{
		shape.setFillColor(sf::Color::Black);
	}
	else
	{
		if (block == 0)
			shape.setFillColor(sf::Color::White);
		if (block.value() % 10 == 1)
			shape.setFillColor(sf::Color::Blue);
		if (block.value() % 10 == 2)
			shape.setFillColor(sf::Color::Red);
		if (block.value() % 10 == 3)
			shape.setFillColor(sf::Color::Green);
		if (block.value() % 10 == 4)
			shape.setFillColor(sf::Color::Yellow);
		if (block.value() % 10 == 5)
			shape.setFillColor(sf::Color::Magenta);
		if (block.value() % 10 == 6)
			shape.setFillColor(sf::Color::Cyan);
		if (block.value() % 10 == 7)
			shape.setFillColor(sf::Color(11, 24, 90));
	}
}

void Game::DisplayBoard(sf::RenderWindow& window)
{
	sf::RectangleShape shape(sf::Vector2(sizeOfBlockLine, sizeOfBlockLine));

	float linePosition = -(sizeOfBlockLine);
	for (uint16_t line = 0; line < m_board.GetHeight(); line++)
	{
		linePosition += sizeOfBlockLine + 1;
		float columnPosition = -(sizeOfBlockLine);
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
void Game::CheckTopLine()
{
	for (int8_t column = 0; column < m_board.GetWidth(); column++)
		if (m_board[{0, column}])
			m_gameOver = true;
}


void Game::SingleplayerLogic(sf::RenderWindow& window)
{
	TetrisPiece* currentPiece = new TetrisPiece(m_startPositionPlayer1, m_types);
	Player player1("Player1", 0);  //For Testing purposes
	m_hole.Spawn(m_board);
	while (window.isOpen() && !m_gameOver)
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (evnt.key.code == sf::Keyboard::Escape)
				{
					m_gameOver = true;
					break;
				}
				player1.MovePiece(evnt, *currentPiece, m_board);
				break;
			}
		window.clear(sf::Color::White);
		DisplayBoard(window);
		if (currentPiece->IsSet())
		{
			m_hole.Disappear(m_board);
			currentPiece->DeleteCompleteLines(m_board);
			CheckTopLine();
			delete currentPiece;
			delete m_square;
			m_square = new RandomSquare(m_board);
			DisplayBoard(window);
			while (!m_square->isSet())
			{
				window.clear(sf::Color::White);
				DisplayBoard(window);
				m_square->MoveDown(m_board);
				Sleep(5);

				window.display();
			}
			m_square->DeleteColmpletLine(m_board);
			currentPiece = new TetrisPiece(m_startPositionPlayer1, m_types);
			m_hole.Spawn(m_board);
		}
		currentPiece->MoveDown(m_board);
		Sleep(m_speed);
		window.display();
	}
}

void Game::MultiplayerTeamLogic(sf::RenderWindow& window)
{
	TetrisPiece* playerOnePiece = new TetrisPiece(m_startPositionPlayer1, m_types);
	TetrisPiece* playerTwoPiece = new TetrisPiece(m_startPositionPlayer2, m_types);


	Player player1("Player1", 0);
	Player player2("Player2", 0, true);


	m_hole.Spawn(m_board);
	while (window.isOpen() && !m_gameOver)
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (evnt.key.code == sf::Keyboard::Escape)
				{
					m_gameOver = true;
					break;
				}
				player1.MovePiece(evnt, *playerOnePiece, m_board);
				player2.MovePiece(evnt, *playerTwoPiece, m_board);
				break;
			}
		window.clear(sf::Color::White);
		DisplayBoard(window);

		// TO DO: baga Logica pt RandomSquare

		if (playerOnePiece->IsSet())
		{
			m_hole.Disappear(m_board);
			playerOnePiece->DeleteCompleteLines(m_board);
			if (playerTwoPiece->IsSet())
				CheckTopLine();
			delete playerOnePiece;

			playerOnePiece = new TetrisPiece(m_startPositionPlayer1, m_types);
			m_hole.Spawn(m_board);
		}
		if (playerTwoPiece->IsSet())
		{
			playerTwoPiece->DeleteCompleteLines(m_board);
			if (playerOnePiece->IsSet())
				CheckTopLine();
			delete playerTwoPiece;
			playerTwoPiece = new TetrisPiece(m_startPositionPlayer2, m_types);
		}

		playerOnePiece->MoveDown(m_board);
		playerTwoPiece->MoveDown(m_board);
		Sleep(m_speed);
		window.display();
	}


}

