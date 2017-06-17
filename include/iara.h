#ifndef _IARA_H_
#define _IARA_H_

#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <ostream>
#include <stack>
#include <list>

#include "cell.h"

namespace MazeSolver {
	class IARA
	{
		public: 
			struct Direction
			{
				enum turn_t turn;
				int line;
				int column;

				Direction( turn_t t_ = NONE )
					: turn( t_ )
				{
					line = 0;
					column = 0;
					if( t_ == UP ) line -= 1;
					else if( t_ == DOWN ) line += 1;
					else if( t_ == LEFT ) column -= 1;
					else if( t_ == RIGHT ) column += 1;
				}

				friend bool operator ==( Direction &lhs_, turn_t rhs_ )
				{
					return lhs_.turn == rhs_;
				}
			};

			struct Position
			{
				int line;
				int column;

				Position( size_t l_ = 0, size_t c_ = 0 )
					: line( l_ )
					  , column ( c_ )
				{ /* empty */ }

				friend Position operator+( const Position &position_, const Direction &direction_ )
				{
					auto temp = position_;
					return Position( temp.line + direction_.line,
							temp.column += direction_.column );
				}
			};

			//==> Alias
			using board_t = std::vector< std::vector< Cell > >;
			using path_t = std::stack< Position >;
			using directions_t = std::list< Direction >;

		private:
			board_t m_board;            // <! A matriz containing NxM cells.
			Position m_curr_pos;        // <! The beginning position of Maze.
			path_t m_way;               // <! A stack with the path of positions.
			directions_t m_directions;  // <! A list with the directions from begin to end.

		public:
			//===> CONSTRUCTOR
			IARA() = default;

			//===> AUXILIARIES
			bool is_outside( const Position &position_ );
			bool is_blocked( const Position &position_, const Direction &direction_ );
			bool is_marked( const Position &position_, const Direction &direction_ );
			void next_turn( turn_t &last_turn_ );

			//===> MODIFIERS
			void mark_cell( const Position &position_ );
			void unmark_cell( const Position &position_ );
			void set_board( const board_t &board_ );
			void set_curr_position(const Position &);

			//===> FUNCTIONALS
			Position advance_one( void );
			size_t get_steps_quantity( void );
			directions_t get_directions( void );
	};

};


#endif
