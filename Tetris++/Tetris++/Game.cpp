#include "Game.h"
#include "SfmlButton.h"
#include "TextBox.h"
#include "SFML/Audio.hpp"
#include <chrono>

Game::Game(std::string filename)
	: m_types(filename)
{
	m_gameOver = false;
}

void configureText(sf::Text& text, const sf::Font& font)
{
	text.setFont(font);
	text.setCharacterSize(40);
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
}


bool dataValidation(sf::Text& errorMessage, const std::string& name1, const std::string& name2,
	const std::string& width, const std::string& height, const bool& multiplayer)
{
	if (name1.size() < 4)
	{
		errorMessage.setString("Player name too small!");
		return false;
	}
	if (name2.size() < 4 && multiplayer)
	{
		errorMessage.setString("Player2 name too small!");
		return false;
	}
	if (width.empty())
	{
		errorMessage.setString("Width  Text Box is Empty!");
		return false;
	}
	if (height.empty())
	{
		errorMessage.setString("Height  Text Box is Empty!");
		return false;
	}
	if (std::stoi(width) <= 4)
	{
		errorMessage.setString("Width too small!");
		return false;
	}
	if (std::stoi(width) > 9)
	{
		errorMessage.setString("Width to Big!");
		return false;
	}
	if (std::stoi(height) > 27)
	{
		errorMessage.setString("Height to Big!");
		return false;
	}
	if (std::stoi(height) < std::stoi(width) * 3)
	{
		errorMessage.setString("Height Must be bigger than Width * 3!\n We suggest you to put " +
			std::to_string(std::stoi(width) * 3));
		return false;
	}
	return true;
}

void Game::ShowSinglePlayerSettings(sf::RenderWindow& window, const sf::Font& font)
{
	sf::Text nameText;
	configureText(nameText, font);
	nameText.setPosition(sf::Vector2f(window.getSize().x / 2 - 150, 50));
	nameText.setString("Player Name:");

	TextBox nameTexBox(window.getSize().x / 2 - 150,
		100,
		300, 50, font, "Player",
		sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta);


	sf::Text widthText;
	configureText(widthText, font);
	widthText.setPosition(sf::Vector2f(window.getSize().x / 2 - 150, 300));
	widthText.setString("Select tabel width:");

	TextBox widthTextBox(window.getSize().x / 2 - 150,
		350,
		300, 50, font, "9",
		sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta);



	sf::Text heightText;
	configureText(heightText, font);
	heightText.setPosition(sf::Vector2f(window.getSize().x / 2 - 150, 550));
	heightText.setString("Select tabel height:");


	TextBox heightTextBox(window.getSize().x / 2 - 150,
		600,
		300, 50, font, "27"
		, sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta);


	SfmlButton playButton(window.getSize().x / 2 - 150,
		750
		, 300, 50, font, "Play",
		sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta);



	sf::Font errorFont;
	if (!errorFont.loadFromFile("images/Font.ttf"))
		Sleep(10);
	sf::Text errorText("", errorFont, 35);
	errorText.setFillColor(sf::Color::Red);
	errorText.setPosition(sf::Vector2f(20, window.getSize().y - 100));

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
				nameTexBox.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
				widthTextBox.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
				heightTextBox.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
				playButton.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

				if (nameTexBox.IsPressed())
				{
					widthTextBox.SetIsSelected(false);
					heightTextBox.SetIsSelected(false);
				}

				if (widthTextBox.IsPressed())
				{
					nameTexBox.SetIsSelected(false);
					heightTextBox.SetIsSelected(false);
				}

				if (heightTextBox.IsPressed())
				{
					widthTextBox.SetIsSelected(false);
					nameTexBox.SetIsSelected(false);
				}

				if (playButton.IsPressed())
				{
					if (dataValidation(errorText, nameTexBox.GetText(), "",
						widthTextBox.GetText(), heightTextBox.GetText(), false))
					{
						window.close();
						SingleplayerLogic(nameTexBox.GetText(), std::stoi(widthTextBox.GetText()), std::stoi(heightTextBox.GetText()));
					}
				}

				break;
			case sf::Event::KeyPressed:
				if (nameTexBox.GetIsSelected())
					nameTexBox.UpdateText(event, false);

				if (widthTextBox.GetIsSelected())
					widthTextBox.UpdateText(event, true);

				if (heightTextBox.GetIsSelected())
					heightTextBox.UpdateText(event, true);

				break;
			}

		playButton.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		nameTexBox.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		widthTextBox.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		heightTextBox.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

		window.clear();

		window.draw(nameText);
		nameTexBox.Render(window);


		window.draw(widthText);
		widthTextBox.Render(window);


		window.draw(heightText);
		heightTextBox.Render(window);

		playButton.Render(window);

		window.draw(errorText);

		window.display();
	}


}

void Game::ShowMultiPlayerSettings(sf::RenderWindow& window, const sf::Font& font)
{
	sf::Text nameTextPlayer1;
	configureText(nameTextPlayer1, font);
	nameTextPlayer1.setPosition(sf::Vector2f(window.getSize().x / 2 - 150, 50));
	nameTextPlayer1.setString("Player1 Name:");

	TextBox nameTexBoxPlayer1(window.getSize().x / 2 - 150,
		100,
		300, 50, font, "Player1",
		sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta);


	sf::Text nameTextPlayer2;
	configureText(nameTextPlayer2, font);
	nameTextPlayer2.setPosition(sf::Vector2f(window.getSize().x / 2 - 150, 200));
	nameTextPlayer2.setString("Player2 Name:");

	TextBox nameTexBoxPlayer2(window.getSize().x / 2 - 150,
		250,
		300, 50, font, "Player2",
		sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta);


	sf::Text widthText;
	configureText(widthText, font);
	widthText.setPosition(sf::Vector2f(window.getSize().x / 2 - 150, 350));
	widthText.setString("Select tabel width:");

	TextBox widthTextBox(window.getSize().x / 2 - 150,
		400,
		300, 50, font, "9",
		sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta);



	sf::Text heightText;
	configureText(heightText, font);
	heightText.setPosition(sf::Vector2f(window.getSize().x / 2 - 150, 500));
	heightText.setString("Select tabel height:");


	TextBox heightTextBox(window.getSize().x / 2 - 150,
		550,
		300, 50, font, "27"
		, sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta);


	SfmlButton playButtonTeam(window.getSize().x / 2 - 150,
		675
		, 300, 50, font, "Play as Team",
		sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta);

	SfmlButton playButtonVersus(window.getSize().x / 2 - 150,
		775
		, 300, 50, font, "Play Versus",
		sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta);


	sf::Font errorFont;
	if (!errorFont.loadFromFile("images/Font.ttf"))
		Sleep(10);
	sf::Text errorText("", errorFont, 35);
	errorText.setFillColor(sf::Color::Red);
	errorText.setPosition(sf::Vector2f(20, window.getSize().y - 100));

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
				nameTexBoxPlayer1.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
				nameTexBoxPlayer2.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
				widthTextBox.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
				heightTextBox.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
				playButtonTeam.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
				playButtonVersus.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

				if (nameTexBoxPlayer1.IsPressed())
				{
					nameTexBoxPlayer2.SetIsSelected(false);
					widthTextBox.SetIsSelected(false);
					heightTextBox.SetIsSelected(false);
				}

				if (nameTexBoxPlayer2.IsPressed())
				{
					nameTexBoxPlayer1.SetIsSelected(false);
					widthTextBox.SetIsSelected(false);
					heightTextBox.SetIsSelected(false);
				}

				if (widthTextBox.IsPressed())
				{
					nameTexBoxPlayer1.SetIsSelected(false);
					nameTexBoxPlayer2.SetIsSelected(false);
					heightTextBox.SetIsSelected(false);
				}

				if (heightTextBox.IsPressed())
				{
					nameTexBoxPlayer1.SetIsSelected(false);
					nameTexBoxPlayer2.SetIsSelected(false);
					widthTextBox.SetIsSelected(false);
				}

				if (playButtonTeam.IsPressed())
				{
					if (dataValidation(errorText, nameTexBoxPlayer1.GetText(), nameTexBoxPlayer2.GetText(),
						widthTextBox.GetText(), heightTextBox.GetText(), true))
					{
						window.close();
						MultiplayerTeamLogic(nameTexBoxPlayer1.GetText(), nameTexBoxPlayer1.GetText(),
							std::stoi(widthTextBox.GetText()), std::stoi(heightTextBox.GetText()));
					}
				}

				if (playButtonVersus.IsPressed())
				{
					if (dataValidation(errorText, nameTexBoxPlayer1.GetText(), nameTexBoxPlayer2.GetText(),
						widthTextBox.GetText(), heightTextBox.GetText(), true))
					{
						window.close();
						MultiplayerVersusLogic(nameTexBoxPlayer1.GetText(), nameTexBoxPlayer1.GetText(),
							std::stoi(widthTextBox.GetText()), std::stoi(heightTextBox.GetText()));
					}
				}

				break;
			case sf::Event::KeyPressed:
				if (nameTexBoxPlayer1.GetIsSelected())
					nameTexBoxPlayer1.UpdateText(event, false);

				if (nameTexBoxPlayer2.GetIsSelected())
					nameTexBoxPlayer2.UpdateText(event, false);

				if (widthTextBox.GetIsSelected())
					widthTextBox.UpdateText(event, true);

				if (heightTextBox.GetIsSelected())
					heightTextBox.UpdateText(event, true);

				break;
			}

		playButtonTeam.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		playButtonVersus.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		nameTexBoxPlayer1.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		nameTexBoxPlayer2.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		widthTextBox.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		heightTextBox.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

		window.clear();

		window.draw(nameTextPlayer1);
		nameTexBoxPlayer1.Render(window);

		window.draw(nameTextPlayer2);
		nameTexBoxPlayer2.Render(window);


		window.draw(widthText);
		widthTextBox.Render(window);


		window.draw(heightText);
		heightTextBox.Render(window);

		playButtonTeam.Render(window);

		playButtonVersus.Render(window);

		window.draw(errorText);

		window.display();
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

	sf::SoundBuffer music;
	music.loadFromFile("images/mainTheme.ogg");
	m_sound.setBuffer(music);
	m_sound.play();
	m_sound.setLoop(true);
	m_sound.setVolume(5);

	sf::Texture texture;
	texture.loadFromFile("images/background2.png");
	sf::Sprite sprite;
	sf::Vector2u size = texture.getSize();
	sprite.setTexture(texture);
	sprite.setOrigin(size.x / 100 - 8, size.y / 100 - 9);

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


	SfmlButton buttonMultiPlayer(window.getSize().x / 2 - 150,
		window.getSize().y / 3 + 150,
		300, 50, font, "MultiPlayer",
		sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta);


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
				buttonMultiPlayer.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

				if (buttonSinglePlayer.IsPressed())
				{
					ShowSinglePlayerSettings(window, font);
				}

				if (buttonMultiPlayer.IsPressed())
				{
					ShowMultiPlayerSettings(window, font);
				}


				break;
			}

		buttonSinglePlayer.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		buttonMultiPlayer.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

		window.clear();
		window.draw(sprite);
		buttonSinglePlayer.Render(window);
		buttonMultiPlayer.Render(window);


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


	//add a window to display the current piece
	//add a window to display the score
}

void Game::CheckTopLine(const Board& board)
{
	for (int8_t column = 0; column < board.GetWidth(); column++)
		if (board[{0, column}])
			m_gameOver = true;

	if (m_gameOver == true)
	{
		sf::RenderWindow window(sf::VideoMode(400, 500), "Game Over", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
		sf::Font font;

		if (!font.loadFromFile("images/Fun Games Demo/Fun Games.ttf"))
			Sleep(10);

		sf::Texture texture;
		texture.loadFromFile("images/gameOver1.jpg");
		sf::Sprite sprite;
		sf::Vector2u size = texture.getSize();
		sprite.setTexture(texture);
		sprite.setOrigin(size.x / 50 - 8, size.y / 50 - 8);

		SfmlButton buttonGameOver(window.getSize().x / 2 - 150, window.getSize().y / 3, 300, 50, font, "Return to main menu", sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta);

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
					buttonGameOver.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
					if (buttonGameOver.IsPressed())
					{
						window.close();
						ShowMenu();
					}
					break;
				}

			buttonGameOver.Update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
			window.clear();
			window.draw(sprite);
			buttonGameOver.Render(window);
			window.display();
		}
	}

	//open a window to show game over + button to go back to menu / exit
}


void Game::SingleplayerLogic(const std::string& playerName, const int& boardWidth, const int& boardHeight)
{
	Board board(static_cast<uint16_t>(boardWidth), static_cast<uint16_t>(boardHeight), false);

	sf::RenderWindow window(sf::VideoMode(board.GetWidth() * (sizeOfBlockLine + 1), board.GetHeight() * (sizeOfBlockLine + 1)), "Tetris++",
		sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);

	Board::Position m_startPosition = { -2, board.GetWidth() / 2 - 2 };
	auto startTime = std::chrono::high_resolution_clock::now();
	std::unique_ptr<RandomSquare> randomSquare(new RandomSquare(board));
	std::unique_ptr<TetrisPiece> currentPiece(new TetrisPiece(m_startPosition, m_types));
	Player player(playerName);  //For Testing purposes

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
				player.MovePiece(evnt, *currentPiece, board);
				break;
			}
		window.clear(sf::Color::White);
		DisplayBoard(window, board);
		if (currentPiece->IsSet())
		{
			m_hole.Disappear(board);
			player.AddScore(currentPiece->DeleteCompleteLines(board));
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
			player.AddScore(randomSquare->DeleteColmpleteLine(board));
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
	m_sound.stop();
	ShowMenu();
}

void Game::MultiplayerTeamLogic(const std::string& player1Name, const std::string& player2Name, const int& boardWidth, const int& boardHeight)
{

	Board board(boardWidth, boardHeight, 1);

	sf::RenderWindow window(sf::VideoMode(board.GetWidth() * (sizeOfBlockLine + 1), board.GetHeight() * (sizeOfBlockLine + 1)), "Tetris++",
		sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);

	Board::Position m_startPositionPlayer1 = { -2, boardWidth / 2 - 2 };
	Board::Position m_startPositionPlayer2 = { -2, board.GetWidth() / 4 * 3 };
	auto startTime = std::chrono::high_resolution_clock::now();
	std::unique_ptr<TetrisPiece> playerOnePiece(new TetrisPiece(m_startPositionPlayer1, m_types));
	std::unique_ptr<TetrisPiece> playerTwoPiece(new TetrisPiece(m_startPositionPlayer2, m_types, true));

	Player player1(player1Name);
	Player player2(player2Name, true);

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
	m_sound.stop();
	ShowMenu();
}

void Game::MultiplayerVersusLogic(const std::string& player1Name, const std::string& player2Name, const int& boardWidth, const int& boardHeight)
{

	Board board(boardWidth, boardHeight, 1);

	sf::RenderWindow window(sf::VideoMode(board.GetWidth() * (sizeOfBlockLine + 1), board.GetHeight() * (sizeOfBlockLine + 1)), "Tetris++",
		sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);

	Board::Position m_startPositionPlayer1 = { -2, boardWidth / 2 - 2 };
	Board::Position m_startPositionPlayer2 = { -2, board.GetWidth() / 4 * 3 };
	auto startTime = std::chrono::high_resolution_clock::now();
	std::unique_ptr<TetrisPiece> playerOnePiece(new TetrisPiece(m_startPositionPlayer1, m_types));
	std::unique_ptr<TetrisPiece> playerTwoPiece(new TetrisPiece(m_startPositionPlayer2, m_types, true));

	Player player1(player1Name);
	Player player2(player2Name, true);


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
	m_sound.pause();
	ShowMenu();
}