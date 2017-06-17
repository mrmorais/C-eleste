#ifndef _STATUS_BOARD_
#define _STATUS_BOARD_

/*
 * The status board contains all relevant information that 
 * resumes all the current game situations, such as, how many lifes
 * and point our snake gotcha, or which maze is the snake in?
 */

//== StructsBoard
struct StatusBoard {
	size_t num_mazes;	//<! Total num of mazes
	int curr_maze;	//<! Actual running maze
	int lifes;		//<! Lives remaining - starts with 5
	int points; 	//<! Num of apples collected
};

#endif
