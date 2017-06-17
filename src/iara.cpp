#include "iara.h"

using namespace MazeSolver;

/*
 * @brief Analyzes whether the assumed position to be played is blocked.
 */
bool IARA::is_blocked( const Position &position_, const Direction &direction_ )
{
    auto next_step = position_ + direction_;
    return (m_board[next_step.line][next_step.column].is_type(Cell::WALL)
		    or m_board[next_step.line][next_step.column].is_type(Cell::INVISIBLE_WALL)	
            or direction_.turn == turn_t::NONE);
}

/*
 * @brief Sets the current cell as marked.
 */
void IARA::mark_cell( const Position &position_ )
{
    m_board[position_.line][position_.column].marked = true;
}

/*
 * @brief Sets the current cell as not marked.
 */
void IARA::unmark_cell( const Position &position_ )
{
    m_board[position_.line][position_.column].marked = false;
}

/*
 * @brief Analyzes whether the assumed position to be played is marked.
 */
bool IARA::is_marked( const Position &position_, const Direction &direction_ )
{
    auto next_step = position_ + direction_;
    return m_board[next_step.line][next_step.column].marked == true;
}

/*
 * @brief According to the inputted file path, fills the matrix with the values (chars).
 */
void IARA::set_board( const board_t &board_ )
{
    m_board = board_;
}

void IARA::set_curr_position(const Position & position_)
{
	m_curr_pos = position_;
	m_way.push(m_curr_pos);
}

/*
 * @brief Decides where is the next step is to take in the Maze.
 */
IARA::Position IARA::advance_one( void )
{
    turn_t last_turn_temp = m_board[m_curr_pos.line][m_curr_pos.column].last_turn;
    auto temp_can_advance(false);

    while( last_turn_temp != turn_t::LEFT )
    {
        next_turn ( last_turn_temp );
        if( ( is_blocked( m_curr_pos, last_turn_temp ) ) or ( is_marked( m_curr_pos, last_turn_temp ) ) )
        {
            temp_can_advance = false;
        }
        else
        {
            temp_can_advance = true;
            break;
        }
    }

    if( temp_can_advance == false ){   
        if( m_board[m_curr_pos.line][m_curr_pos.column].is_type(Cell::SNAKE_HEAD) )
        {
            std::cout << ">>> IARA without an end!\n";
            exit(0);
        }
        else
        {
            unmark_cell( m_curr_pos );
            m_curr_pos = m_way.top();
            m_way.pop();
            m_directions.pop_back();
            return m_curr_pos;
        }
    }
    m_way.push( m_curr_pos );
    m_directions.push_back( last_turn_temp );
    mark_cell( m_curr_pos );
    m_board[m_curr_pos.line][m_curr_pos.column].last_turn = last_turn_temp;
    m_curr_pos = m_curr_pos + last_turn_temp;
    
    return m_curr_pos;
}

/*
 * @brief The turns follow a way. And this function decides it.
 */
void IARA::next_turn( turn_t &last_turn_ )
{
    if( last_turn_ == turn_t::NONE ) last_turn_ = turn_t::UP;
    else if( last_turn_ == turn_t::UP ) last_turn_ = turn_t::RIGHT;
    else if( last_turn_ == turn_t::RIGHT ) last_turn_ = turn_t::DOWN;
    else if( last_turn_ == turn_t::DOWN ) last_turn_ = turn_t::LEFT;
    else last_turn_ = turn_t::LEFT;
}

/*
 * @brief Returns the length of path represented by the stack.
 */
size_t IARA::get_steps_quantity( void )
{
    return m_way.size();
}

/*
 * @brief Returns the length of path represented by the stack.
 */
std::list< IARA::Direction > IARA::get_directions( void )
{
    return m_directions;
}
