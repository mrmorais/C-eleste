#include "maze.h"
#include <iostream>

/// Constructor
Maze::Maze(const MazeType & maze_input_)
	: m_maze(maze_input_)
{
	num_rows = maze_input_.size();
	num_cols = maze_input_[0].size();
}

/// Retuns the cell with start marker
Cell Maze::get_begin()
{
	for (auto i(0u); i < num_rows; i++) {
		for (auto j(0u); j < num_cols; j++) {
			if (m_maze[i][j].is_type(Cell::BEGIN))
				return m_maze[i][j];
		}
	}
	return {0, 0, Cell::INVALID};
}

/// Creates a apple
Cell Maze::create_a_apple()
{
	Cell apple(0, 1, Cell::INVALID);

	// Randomic engines + distributions
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> random_row(0, num_rows - 1);
	std::uniform_int_distribution<int> random_col(0, num_cols - 1);


	while (	apple.is_type(Cell::INVALID)
			or apple.is_type(Cell::WALL)
			or apple.is_type(Cell::INVISIBLE_WALL)) /* TODO There's a bug here. It's necessary to 
														verifies if the position is a snake */
	{
		int row = random_row(rng);
		int col = random_col(rng);
		apple = m_maze[row][col];
		std::cout << "Generated: x = " << apple.x << " y = " << apple.y <<" \n";

	}

	apple.cell_type = Cell::APPLE;
	return apple;
}
