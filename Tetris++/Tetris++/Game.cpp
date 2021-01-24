#include "Game.h"
#include "SfmlButton.h"
#include <chrono>

Game::Game(const uint16_t& width, const uint16_t& height, std::string filename)
	: m_types(filename), m_boardWidth(width), m_boardHeight(height)
{
	m_gameOver = false;
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
				{
					window.close();
					SingleplayerLogic();
				}

				if (buttonMultiPlayerTeam.isPressed())
				{
					window.close();
					MultiplayerTeamLogic();
				}
				if (buttonMultiplayerVersus.isPressed())
				{
					window.close();
					MultiplayerVersusLogic();
				}

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



void setBlock(const std::optional<uint8_t> block, sf::RectangleShape& shape)
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

void Game::DisplayBoard(sf::RenderWindow& window, const Board& board) const
{
	sf::RectangleShape shape(sf::Vector2(sizeOfBlockLine, sizeOfBlockLine));

	float linePosition = -(sizeOfBlockLine);
	for (uint16_t line = 0; line < board.GetHeight(); line++)
	{
		linePosition += sizeOfBlockLine + 1;
		float columnPosition = -(sizeOfBlockLine);
		for (uint16_t column = 0; column < board.GetWidth(); column++)
		{
			columnPosition += sizeOfBlockLine + 1;
			shape.setPosition(columnPosition, linePosition);
			setBlock(board[{line, column}], shape);
			window.draw(shape);
		}
	}
	window.display();
}

void Game::CheckTopLine(const Board& board)
{
	for (int8_t column = 0; column < board.GetWidth(); column++)
		if (board[{0, column}])
			m_gameOver = true;
}


void Game::SingleplayerLogic() 

{


	Board board(m_boardWidth, m_boardHeight, 0);

	sf::RenderWindow window(sf::VideoMode(board.GetWidth() * (sizeOfBlockLine + 1), board.GetHeight() * (sizeOfBlockLine + 1)), "Tetris++",
		sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);

	Board::Position m_startPosition = { -2, board.GetWidth() / 2 - 2 };
	auto startTime = std::chrono::high_resolution_clock::now();
	std::unique_ptr<RandomSquare> randomSquare(new RandomSquare(board));
	std::unique_ptr<TetrisPiece> currentPiece(new TetrisPiece(m_startPosition, m_types));
	Player player1("Player1");  //For Testing purposes

	m_hole.Spawn(board);

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
				player1.MovePiece(evnt, *currentPiece, board);
				break;
			}
		window.clear(sf::Color::White);
		DisplayBoard(window, board);
		if (currentPiece->IsSet())
		{
			m_hole.Disappear(board);
			player1.AddScore(currentPiece->DeleteCompleteLines(board));
			CheckTopLine(board);
			randomSquare.reset(new RandomSquare(board));
			DisplayBoard(window, board);
			while (!randomSquare->isSet())
			{
				window.clear(sf::Color::White);
				DisplayBoard(window, board);
				randomSquare->MoveDown(board);
				Sleep(5);
				window.display();
			}
			player1.AddScore(randomSquare->DeleteColmpleteLine(board));
			currentPiece.reset(new TetrisPiece(m_startPosition, m_types));
			m_hole.Spawn(board);
		}
		currentPiece->MoveDown(board);
		if (m_level < 10)
			if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - startTime).count() > 30 * (m_level + 1))
				m_level++;
		Sleep(500 - m_level * 50);
		window.display();
	}
	window.close();
	m_level = 0;
	ShowMenu();
}

void Game::MultiplayerTeamLogic()
{

	Board board(m_boardWidth, m_boardHeight, 1);

	sf::RenderWindow window(sf::VideoMode(board.GetWidth() * (sizeOfBlockLine + 1), board.GetHeight() * (sizeOfBlockLine + 1)), "Tetris++",
		sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);

	Board::Position m_startPositionPlayer1 = { -2, m_boardWidth / 2 - 2 };
	Board::Position m_startPositionPlayer2 = { -2, board.GetWidth() / 4 * 3 };
	auto startTime = std::chrono::high_resolution_clock::now();
	std::unique_ptr<TetrisPiece> playerOnePiece(new TetrisPiece(m_startPositionPlayer1, m_types));
	std::unique_ptr<TetrisPiece> playerTwoPiece(new TetrisPiece(m_startPositionPlayer2, m_types, true));

	Player player1("Player1");
	Player player2("Player2", true);

	m_hole.Spawn(board);
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
				player1.MovePiece(evnt, *playerOnePiece, board);
				player2.MovePiece(evnt, *playerTwoPiece, board);
				break;
			}
		window.clear(sf::Color::White);
		DisplayBoard(window, board);

		if (playerOnePiece->IsSet())
		{
			m_hole.Disappear(board);
			player1.AddScore(playerOnePiece->DeleteCompleteLines(board));
			if (playerTwoPiece->IsSet())
				CheckTopLine(board);

			playerOnePiece.reset(new TetrisPiece(m_startPositionPlayer1, m_types));
			m_hole.Spawn(board);
		}
		if (playerTwoPiece->IsSet())
		{
			player1.AddScore(playerTwoPiece->DeleteCompleteLines(board));
			if (playerOnePiece->IsSet())
				CheckTopLine(board);
			playerTwoPiece.reset(new TetrisPiece(m_startPositionPlayer2, m_types, true));
		}

		playerOnePiece->MoveDown(board);
		playerTwoPiece->MoveDown(board);
		if (m_level < 10)
			if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - startTime).count() > 30 * (m_level + 1))
				m_level++;
		Sleep(500 - m_level * 50);
		window.display();
	}
	window.close();
	m_level = 0;
	ShowMenu();
}

void Game::MultiplayerVersusLogic()
{

	Board board(m_boardWidth, m_boardHeight, 1);

	sf::RenderWindow window(sf::VideoMode(board.GetWidth() * (sizeOfBlockLine + 1), board.GetHeight() * (sizeOfBlockLine + 1)), "Tetris++",
		sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);

	Board::Position m_startPositionPlayer1 = { -2, m_boardWidth / 2 - 2 };
	Board::Position m_startPositionPlayer2 = { -2, board.GetWidth() / 4 * 3 };
	auto startTime = std::chrono::high_resolution_clock::now();
	std::unique_ptr<TetrisPiece> playerOnePiece(new TetrisPiece(m_startPositionPlayer1, m_types));
	std::unique_ptr<TetrisPiece> playerTwoPiece(new TetrisPiece(m_startPositionPlayer2, m_types, true));

	Player player1("Player1");
	Player player2("Player2", true);


	m_hole.Spawn(board);
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
				player1.MovePiece(evnt, *playerOnePiece, board);
				player2.MovePiece(evnt, *playerTwoPiece, board);
				break;
			}
		window.clear(sf::Color::White);
		DisplayBoard(window, board);

		if (playerOnePiece->IsSet())
		{
			m_hole.Disappear(board);
			player1.AddScore(playerOnePiece->DeleteCompleteLinesAndColumns(board, false));
			if (playerTwoPiece->IsSet())
				CheckTopLine(board);

			playerOnePiece.reset(new TetrisPiece(m_startPositionPlayer1, m_types));
			m_hole.Spawn(board);
		}
		if (playerTwoPiece->IsSet())
		{
			m_hole.Disappear(board);
			player2.AddScore(playerTwoPiece->DeleteCompleteLinesAndColumns(board, true));
			if (playerOnePiece->IsSet())
				CheckTopLine(board);
			playerTwoPiece.reset(new TetrisPiece(m_startPositionPlayer2, m_types, true));
			m_hole.Spawn(board);
		}
		playerOnePiece->MoveDown(board);
		playerTwoPiece->MoveDown(board);
		if (m_level < 10)
			if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - startTime).count() > 30 * (m_level + 1))
				m_level++;
		Sleep(500 - m_level * 50);
		window.display();
	}
	window.close();
	m_level = 0;
	ShowMenu();
}


