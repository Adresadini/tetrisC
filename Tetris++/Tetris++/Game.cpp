#include "Game.h"
#include "SfmlButton.h"


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

void Game::ShowMenu()
{

	::ShowWindow(::GetConsoleWindow(), SW_HIDE); //Hides console

	sf::RenderWindow window(sf::VideoMode(800, 900), "Tetris++",
		sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);

	sf::Font font;

	if (!font.loadFromFile("images/Fun Games Demo/Fun Games.ttf"))
		Sleep(10);

	sf::Text text;
	text.setFont(font);
	text.setString("Selectati tipul de joc:");
	text.setCharacterSize(40);
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
	text.setPosition(sf::Vector2f(window.getSize().x / 5, window.getSize().y / 5));

	SfmlButton buttonSinglePlayer(window.getSize().x / 2 - 150,
		window.getSize().y / 3
		, 300, 50, font, "Single Player",
		sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta);


	SfmlButton buttonMultiPlayerTeam(window.getSize().x / 2 - 150,
		window.getSize().y / 3 + 150,
		300, 50, font, "MultiPlayer Team",
		sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta);

	SfmlButton buttonMultiplayerVersus(window.getSize().x / 2 - 150,
		window.getSize().y / 3 + 300,
		300, 50, font, "MultiPlayer Versus"
		, sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				buttonSinglePlayer.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
				buttonMultiPlayerTeam.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
				buttonMultiplayerVersus.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

				if (buttonSinglePlayer.isPressed())
					SingleplayerLogic(window);

				if (buttonMultiPlayerTeam.isPressed())
					MultiplayerTeamLogic(window);

				if (buttonMultiplayerVersus.isPressed())
					MultiplayerVersusLogic(window);

				break;
			}

		buttonSinglePlayer.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		buttonMultiPlayerTeam.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		buttonMultiplayerVersus.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

		window.clear();

		buttonSinglePlayer.Render(window);
		buttonMultiPlayerTeam.Render(window);
		buttonMultiplayerVersus.Render(window);

		window.draw(text);
		window.display();
	}

}

void Game::VisualInterface()
{
	ShowMenu();

	::ShowWindow(::GetConsoleWindow(), SW_HIDE); //Hides console

	sf::RenderWindow window(sf::VideoMode(m_board.GetWidth() * (sizeOfBlockLine + 1), m_board.GetHeight() * (sizeOfBlockLine + 1)), "Tetris++",
		sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);

	/*if (m_multiplayer)
		MultiplayerVersusLogic(window);
	else
		SingleplayerLogic(window);*/
}



void setBlock(std::optional<uint8_t> block, sf::RectangleShape& shape)
{
	if (block == std::nullopt)
	{
		shape.setFillColor(sf::Color::Black);
		return;
	}
	if (block.value() < 20)
		switch (block.value() % 10)
		{
		case 0:
			shape.setFillColor(sf::Color::White);
			break;
		case 1:
			shape.setFillColor(sf::Color(26, 255, 255));
			break;
		case 2:
			shape.setFillColor(sf::Color(255, 0, 0));
			break;
		case 3:
			shape.setFillColor(sf::Color(51, 204, 51));
			break;
		case 4:
			shape.setFillColor(sf::Color(255, 153, 0));
			break;
		case 5:
			shape.setFillColor(sf::Color(0, 0, 255));
			break;
		case 6:
			shape.setFillColor(sf::Color(255, 255, 0));
			break;
		case 7:
			shape.setFillColor(sf::Color(204, 0, 204));
			break;
		}
	else
		switch (block.value() % 10)
		{
		case 0:
			shape.setFillColor(sf::Color::White);
			break;
		case 1:
			shape.setFillColor(sf::Color(0, 128, 128));
			break;
		case 2:
			shape.setFillColor(sf::Color(204, 0, 153));
			break;
		case 3:
			shape.setFillColor(sf::Color(51, 102, 0));
			break;
		case 4:
			shape.setFillColor(sf::Color(153, 102, 51));
			break;
		case 5:
			shape.setFillColor(sf::Color(115, 0, 230));
			break;
		case 6:
			shape.setFillColor(sf::Color(255, 153, 102));
			break;
		case 7:
			shape.setFillColor(sf::Color(153, 51, 51));
			break;
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
	TetrisPiece* playerTwoPiece = new TetrisPiece(m_startPositionPlayer2, m_types, true);

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
			playerTwoPiece = new TetrisPiece(m_startPositionPlayer2, m_types, true);
		}

		playerOnePiece->MoveDown(m_board);
		playerTwoPiece->MoveDown(m_board);
		Sleep(m_speed);
		window.display();
	}


}

void Game::MultiplayerVersusLogic(sf::RenderWindow& window)
{
	TetrisPiece* playerOnePiece = new TetrisPiece(m_startPositionPlayer1, m_types);
	TetrisPiece* playerTwoPiece = new TetrisPiece(m_startPositionPlayer2, m_types, true);

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

		if (playerOnePiece->IsSet())
		{
			m_hole.Disappear(m_board);
			playerOnePiece->DeleteCompletLinesAndColumns(m_board, false);
			if (playerTwoPiece->IsSet())
				CheckTopLine();
			delete playerOnePiece;

			playerOnePiece = new TetrisPiece(m_startPositionPlayer1, m_types);
			m_hole.Spawn(m_board);
		}
		if (playerTwoPiece->IsSet())
		{
			m_hole.Disappear(m_board);
			playerTwoPiece->DeleteCompletLinesAndColumns(m_board, true);
			if (playerOnePiece->IsSet())
				CheckTopLine();
			delete playerTwoPiece;
			playerTwoPiece = new TetrisPiece(m_startPositionPlayer2, m_types, true);
			m_hole.Spawn(m_board);
		}

		playerOnePiece->MoveDown(m_board);
		playerTwoPiece->MoveDown(m_board);
		Sleep(m_speed);
		window.display();
	}

}


