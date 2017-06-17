#include "snake.h"

Snake::Snake(const Cell & head_)
	: previous_head(0, 0, Cell::INVALID)
{
	m_snake.push_back(head_);
}

bool Snake::colision(const Cell & cell_)
{
	for (auto bd_ : m_snake) {
		if (cell_.x == bd_.x and cell_.y == bd_.y)
			return true;
	}
	return false;
}

bool Snake::move(const MazeSolver::IARA::Direction &direction_ )
{
	m_snake.front().cell_type = Cell::SNAKE_BODY;

	Cell new_head = Cell( m_snake.front().x + direction_.column
						, m_snake.front().y + direction_.line
						, '@' );

	if((new_head.x == previous_head.x and new_head.y == previous_head.y) or colision(new_head)) 
		return false;

	previous_head = m_snake.front();
	m_snake.push_front( new_head );
	m_snake.pop_back();

	return true;
}

Cell Snake::get_head() const
{
	return m_snake.front();
}

std::list<Cell> Snake::get_snake() const
{
	return m_snake;
}

void Snake::move_resize(const MazeSolver::IARA::Direction & direction_)
{
	m_snake.front().cell_type = Cell::SNAKE_BODY;
	Cell new_head = Cell( m_snake.front().x + direction_.column
						, m_snake.front().y + direction_.line
						, '@' );
	m_snake.push_front( new_head );
}
