#ifndef _CELESTE_H_
#define _CELESTE_H_

#include <iostream> // size_t
#include <vector> // std::vector

//#include "maze.h"
#include "maze_reader.h"
#include "container.h" 
#include "status_board.h"
#include "snake.h"
#include "iara.h"
#include "cell.h"

class Celeste
{
	using Direction = MazeSolver::IARA::Direction;

	private:
		//== Private members
		Snake m_celeste;					//<! Dear Celeste
		StatusBoard m_status_board;			//<! Informations about the game
		std::vector<Maze> m_mazes;			//<! All my mazes
		std::list<Direction> m_directions;	//<! Directions to take
		Cell m_apple;						//<! Apple
		int m_num_apples;

		//== Private functions
		void make_round(const Cell &);
		void solve_maze(const Cell &);
		Maze merge();

	public:
		//== Special Members
		Celeste();
		void initialize(std::string);	// <! Initialize the game structure

		//== Game functions
		Container step();		//<! Give a next step in the game (looking if is time to walk/uplevel/die/etc)
		
};

#endif
