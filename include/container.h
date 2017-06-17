#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include "status_board.h" // it's necessary a status board that will travel with the container
#include "snake.h"

/*
 *	The container is usefull, its encapsulates a current game status and a
 *	information that describes the status of the game, such as Failed, success,
 *	wrong input file, etc.
 */

//== Container to transmission
struct Container {
	StatusBoard m_status_board;	//<! Status board
	Maze m_maze;				//<! Current Maze
	Snake m_snake;				//<! Snake snapshot
	
	enum GameStatus {
		NORMAL=0,
		WIN,				//<! Thrown when celeste win the all mazes
		FAIL				//<! Thrown when celeste fail
	};

	GameStatus m_game_status;
};


#endif
