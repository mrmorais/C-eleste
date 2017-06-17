#include "cell.h"
#include <iostream>

/// Constructor
Cell::Cell(int x_, int y_, char char_ct_)
	: x(x_),
	  y(y_)
{
	last_turn = turn_t::NONE;
	cell_type = identify_cell_type(char_ct_);
}

bool Cell::is_type(CellType ct_)
{
	return (ct_ == cell_type);
}

/// Identifies the CellType of a char
Cell::CellType Cell::identify_cell_type(char char_ct_)
{
	CellType ct;
	switch(char_ct_)
	{
		case ' ':
			ct = SPACE;
			break;
		case '#':
			ct = WALL;
			break;
		case '-':
			ct = INVISIBLE_WALL;
			break;
		case '$':
			ct = APPLE;
			break;
		case 'o':
			ct = SNAKE_BODY;
			break;
		case '@':
			ct = SNAKE_HEAD;
			break;
		case '*':
			ct = BEGIN;
			break;
		default:
			ct = INVALID;
			break;
	}
	return ct;
}
