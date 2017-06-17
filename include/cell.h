#ifndef _CELL_H_
#define _CELL_H_

enum turn_t { NONE, UP, RIGHT, DOWN, LEFT };

class Cell {
	public:
		//== Enumerators
		enum CellType {
			SPACE = 0,			//<! Free space		' '
			WALL,				//<! Blocked wall	'#'
			INVISIBLE_WALL,		//<! Invisible wall	'-'
			APPLE,				//<! Apple		'$'
			BEGIN,				//<! Begin '*'
			SNAKE_BODY,			//<! Snake's body	'o'
			SNAKE_HEAD,			//<! Snake's head	'@'
			INVALID
		};

		//== Members
		int x;
		int y;
		turn_t last_turn;
		bool marked;

		CellType cell_type;

		//== Special Members
		Cell(int, int, char);
		//== Public interface
		bool is_type(CellType);
	private:
		//== Private members
		CellType identify_cell_type(char);
};


#endif
