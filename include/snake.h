#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <list> 	// std::list

#include "cell.h"
#include "iara.h"

class Snake
{
	private:
		//== Private members
		std::list<Cell> m_snake; // The snake's head + body
		bool colision(const Cell &);
		Cell previous_head;
	public:
		Snake(const Cell &); // Default constructor
		//== Public members
		bool move(const MazeSolver::IARA::Direction &);
		Cell get_head() const;
		std::list<Cell> get_snake() const;
		void move_resize(const MazeSolver::IARA::Direction &);
};

#endif
