#ifndef _MAZE_H_
#define _MAZE_H_

#include <string> 	// std::string
#include <vector>	// std::vector
#include <random>	// std::default_random_engine, std::uniform_int_distribution

#include "cell.h" // Cell

class Maze 
{
	public:
		//== Types aliases
		using MazeType = std::vector< std::vector<Cell> >;

		//== Members
		size_t num_rows;	//<! Num of rows in the maze
		size_t num_cols;	//<! Num of collumns

		MazeType m_maze;	//<! Maze structure definition, [vector of vectors of Cells]

		//== Special Members
		Maze(const MazeType &); 	// Main constructor
		~Maze() = default;

		//== Public methods
		Cell get_begin();		//<! Returns the start marker
		Cell create_a_apple();	//<! Creates a apple

};

#endif
