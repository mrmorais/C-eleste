#include "celeste.h"
#include <iostream>

/// Constructor
Celeste::Celeste()
	: m_celeste({0, 0, Cell::INVALID}), // Initialize a "null" snake head
	  m_apple({0, 0, Cell::INVALID})	// Initialize a "null" apple
{ /* empty */ }

/// Make an apple and then solve the maze
void Celeste::make_round(const Cell & initial_position)
{
	// Generates an apple in the maze
	m_apple = m_mazes[m_status_board.curr_maze].create_a_apple();
	std::cout << "Apple in " << m_apple.x << m_apple.y << "\n";

	solve_maze(initial_position);
}

void Celeste::solve_maze(const Cell & initial_position)
{
	MazeSolver::IARA maze_solver = MazeSolver::IARA();
	maze_solver.set_board(m_mazes[m_status_board.curr_maze].m_maze);

	auto curr_position = MazeSolver::IARA::Position(initial_position.y, initial_position.x); // Copy the snake head to solve path
	maze_solver.set_curr_position(curr_position);

	while (not (curr_position.line == m_apple.y and curr_position.column == m_apple.x)) {
		curr_position = maze_solver.advance_one();
	}

	m_directions = maze_solver.get_directions();
}

/// Merge maze + apple
Maze Celeste::merge()
{
	Maze merged_maze = m_mazes[m_status_board.curr_maze];

	merged_maze.m_maze[m_apple.y][m_apple.x] = m_apple;
	return merged_maze;
}

/// Read the mazes from a file and init the snake
void Celeste::initialize(std::string file_path)
{
	MazeReader mr = MazeReader(file_path);
	m_mazes = mr.read_mazes();
	m_status_board = {m_mazes.size(), -1, 5, 0}; // 5 is the number of lifes
	m_num_apples = 0;
}

/// Update the game structure
Container Celeste::step()
{
	std::cout << "++++++++++++++++++++++++++++++ \n";
	std::cout << ">>> NUM OF MAZES:" << m_mazes.size() << "\n";
	std::cout << ">>> CURRENT MAZE:" << m_status_board.curr_maze << "\n";
	std::cout << ">>> APPLES IN MAZE:" << m_status_board.points % 2 << "\n";
	std::cout << ">>> APPLES: " << m_status_board.points << "\n";
	std::cout << ">> LIFES: " << m_status_board.lifes << "\n";
	std::cout << ">>> DIRECTIONS: "<< m_directions.size()<< "\n";

	if (m_directions.empty()) {
		// This is the first maze
		// Update the curr_maze, because its starts -1
		m_status_board.curr_maze++;

		if (m_status_board.curr_maze == m_mazes.size()) {
			return {m_status_board, merge(), m_celeste, Container::WIN};
		}

		Cell snk_head = m_mazes[m_status_board.curr_maze].get_begin(); // Determines the start
		//if (snk_head == Cell::INVALID); TODO does not exists a beginning marker
		m_celeste = Snake(snk_head); // Instanciate a new Celeste shshshhh

		make_round(snk_head);
	} else {
		// Celeste needs to walk
		
		MazeSolver::IARA::Direction last_dir;
		if (not m_celeste.move(m_directions.front())) {
			last_dir = m_directions.front();
			Cell head = m_celeste.get_head(); 

			Cell up = m_mazes[m_status_board.curr_maze].m_maze[head.y - 1][head.x];
			Cell right = m_mazes[m_status_board.curr_maze].m_maze[head.y][head.x + 1];
			Cell down = m_mazes[m_status_board.curr_maze].m_maze[head.y + 1][head.x];
			Cell left = m_mazes[m_status_board.curr_maze].m_maze[head.y][head.x - 1];

			bool saved = false;

			if (not up.is_type(Cell::WALL)) {
				if (m_celeste.move({turn_t::UP})) {
					saved = true;
					solve_maze(m_celeste.get_head());
					last_dir = {turn_t::UP};
				}
			}
			if (not right.is_type(Cell::WALL) and not saved) {
				if (m_celeste.move({turn_t::RIGHT})) {
					saved = true;
					solve_maze(m_celeste.get_head());
					last_dir = {turn_t::RIGHT};
				}
			}
			if (not down.is_type(Cell::WALL) and not saved) {
				if (m_celeste.move({turn_t::DOWN})) {
					saved = true;
					solve_maze(m_celeste.get_head());
					last_dir ={turn_t::DOWN};
				}
			}
			if (not left.is_type(Cell::WALL) and not saved) {
				if (m_celeste.move({turn_t::LEFT})) {
					saved = true;
					solve_maze(m_celeste.get_head());
					last_dir = {turn_t::LEFT};
				}
			}
			if (not saved) {
				// No céu tem pão? E morreu. Sss... (x.x) R.I.P Celeste 2017-2017
				if (m_status_board.lifes > 0) {
					m_status_board.lifes--;

					Cell snk_head = m_mazes[m_status_board.curr_maze].get_begin(); // Determines the start
					m_celeste = Snake(snk_head); // Instanciate a new Celeste shshshhh

					make_round(snk_head);
				} else {
					return {m_status_board, merge(), m_celeste, Container::FAIL};
				}
			}
			return { m_status_board, merge(), m_celeste, Container::NORMAL };
		}

		m_directions.pop_front();

		if (m_directions.empty()) {
			// Gotcha an apple
			std::cout << "--- GOTCHA A APPLE\n";
			m_num_apples++;
			m_status_board.points++;
			m_celeste.move_resize(last_dir);
			if (m_num_apples == 3) {
				// That means that is a new round starting
				m_status_board.curr_maze++;
				m_num_apples = 0;
				// Checks if there is no more mazes in database
				if (m_status_board.curr_maze + 1 == m_mazes.size())
					return {m_status_board, merge(), m_celeste, Container::WIN};
				Cell snk_head = m_mazes[m_status_board.curr_maze].get_begin(); // Determines the start
				m_celeste = Snake(snk_head); // Instanciate a new Celeste shshshhh
			}
			make_round(m_celeste.get_head()); // Start a new round
		}
	}
	return { m_status_board, merge(), m_celeste, Container::NORMAL };
}
