#include "game.h"
#include <iostream>
#include <chrono>
#include <thread>

Game::Game()
	: mWindow(sf::VideoMode( WINDOW_WIDTH, WINDOW_HEIGHT ), "Celeste by IARA"),
	  mBoard()
{
	snake_textures[DIR_UP].loadFromFile("asset/snk_head_u.png");
	snake_textures[DIR_RIGHT].loadFromFile("asset/snk_head_r.png");
	snake_textures[DIR_DOWN].loadFromFile("asset/snk_head_d.png");
	snake_textures[DIR_LEFT].loadFromFile("asset/snk_head_l.png");

	mTextures[1].loadFromFile("asset/snk_tail_r.png");
	mTextures[2].loadFromFile("asset/snk_tail_d.png");
	mTextures[4].loadFromFile("asset/snk_tail_l.png");
	mTextures[8].loadFromFile("asset/snk_tail_u.png");

	mTextures[3].loadFromFile("asset/snk_curve_r_d.png");
	mTextures[9].loadFromFile("asset/snk_curve_r_u.png");
	mTextures[6].loadFromFile("asset/snk_curve_l_d.png");
	mTextures[12].loadFromFile("asset/snk_curve_l_u.png");

	mTextures[5].loadFromFile("asset/snk_body_h.png");
	mTextures[10].loadFromFile("asset/snk_body_v.png");

	mTextures[108].loadFromFile("asset/snk_head_d.png");
	mTextures[104].loadFromFile("asset/snk_head_r.png");
	mTextures[102].loadFromFile("asset/snk_head_u.png");
	mTextures[101].loadFromFile("asset/snk_head_l.png");
	mTextures[100].loadFromFile("asset/ball_head.png");

	mTextures[201].loadFromFile("asset/board.png");
	mTextures[300].loadFromFile("asset/stone.png");
	mTextures[400].loadFromFile("asset/apple.png");
	mTextures[500].loadFromFile("asset/grass.png");

	mBoard.setTexture(mTextures[201]);
	mBoard.setPosition(640.0f, 0.0f);

	// Initialize Celeste
	m_celeste.initialize("data/levels.txt");
}

void Game::run()
{
	/*std::vector< std::vector <Cell> > scene = {
	   	{ Cell(0, 0, '@')}
	};*/
	bool won = false;
	Container result = m_celeste.step();
	while (mWindow.isOpen()) {
		processEvents();

		if (not won)
			result = m_celeste.step();

		if (result.m_game_status == Container::NORMAL) {
			mountScene(result.m_maze.m_maze, result.m_snake);
		}
		if (result.m_game_status == Container::FAIL) {
			std::cout << "<<<< MORREU BICHO >>>>\n";
		}
		if (result.m_game_status == Container::WIN) {
			std::cout << "<<<< GANHOU >>>>\n";
			won = true;
		}

		m_status_board = result.m_status_board;

		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event)) {
		switch(event.type) {
			case sf::Event::Closed:
				mWindow.close();
				break;
		}
	}
}

void Game::render()
{
	sf::Sprite background(mTextures[500]);

	mWindow.clear(); // 640, 480
	for (auto w(0); w < WINDOW_WIDTH / 40; w++) {
		for (auto h(0); h < WINDOW_HEIGHT / 40; h++) {
			background.setPosition(w * 40, h * 40);
			mWindow.draw(background);
		}
	}

	mWindow.draw(mBoard);

	for (auto element : mElements) {
		mWindow.draw(element);
	}

	for (auto element : mSnake) {
		mWindow.draw(element);
	}
	
	render_status();

	mWindow.display();
}

void Game::render_status()
{
	sf::Font NotoSans;
	NotoSans.loadFromFile("asset/fonts/NotoSans.ttc");

	sf::Text text;
	text.setFont(NotoSans);
	text.setCharacterSize(20);
	text.setColor(sf::Color::Black);

	text.setString(std::to_string(m_status_board.points));
	text.setPosition(720.f, 290.f);
	mWindow.draw(text);

	text.setString(std::to_string(m_status_board.lifes));
	text.setPosition(720.f, 334.f);
	mWindow.draw(text);

	std::string level = std::to_string(m_status_board.curr_maze + 1) + "/" + std::to_string(m_status_board.num_mazes);
	text.setString(level);
	text.setPosition(720.f, 378.f);
	mWindow.draw(text);
}

int chair_relation(const Cell &first, const Cell & second) {
	int sprite_val = 0;

	// TOP relation
	if ((first.y - 1 == second.y) and (first.x == second.x)) {
		std::cout << "TOP RELATION \n";
		sprite_val += 8;
	}

	// LEFT relation
	if ((first.y == second.y) and (first.x - 1 == second.x)) {
		std::cout << "LEFT RELATION \n";
		sprite_val += 4;
	}

	// DOWN relation
	if ((first.y + 1 == second.y) and (first.x == second.x)) {
		std::cout << "DOWN RELATION \n";
		sprite_val += 2;
	}

	// RIGHT relation
	if ((first.y  == second.y) and (first.x + 1 == second.x)) {
		std::cout << "RIGHT RELATION \n";
		sprite_val += 1;
	}

	std::cout << "Sprite val : "<< sprite_val << "\n";

	return sprite_val;
}

void Game::mountScene(std::vector< std::vector<Cell> > cells, const Snake & snake_) {
	/// Clear everybody
	mSnake.clear();
	mElements.clear();

	// Look in all cells
	Cell current_cell = Cell(0, 0, 'A');
	for (auto i(0); i < cells.size(); i++) {
		for (auto j(0); j < cells[i].size(); j++) {
			current_cell = cells[i][j];
			sf::Sprite spr;
			if (current_cell.is_type(Cell::WALL)) {
				spr.setTexture(mTextures[300]);
				spr.setPosition(current_cell.x * 40, current_cell.y * 40);
			}
			if (current_cell.is_type(Cell::APPLE)) {
				spr.setTexture(mTextures[400]);
				spr.setPosition(current_cell.x * 40, current_cell.y * 40);
			}
			if (current_cell.is_type(Cell::SPACE)) {
				spr.setTexture(mTextures[500]); // Grass
				spr.setPosition(current_cell.x * 40, current_cell.y * 40);
			}

			mElements.push_back(spr);
		}
	}

	std::vector<Cell> temp;

	auto snk_ = snake_.get_snake();
	for (auto el : snk_) {
		temp.push_back(el);
	}

	for (auto i(0); i < temp.size(); i++) {
		sf::Sprite sp_;
		int chair_r = 0;
		if (i == 0) { // HEAD
			chair_r += 100;
			if (temp.size() > 1)
				chair_r += chair_relation(temp[i], temp[i+1]);
		} else {
			chair_r += chair_relation(temp[i], temp[i-1]);
			if (i + 1 < temp.size())
				chair_r += chair_relation(temp[i], temp[i+1]);
		}
		sp_.setTexture(mTextures[chair_r]);
		sp_.setPosition(temp[i].x * 40, temp[i].y * 40);
		mSnake.push_back(sp_);
	}

}

