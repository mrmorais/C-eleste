#ifndef _MAZE_READER_H_
#define _MAZE_READER_H_

#include <vector>	// std::vector
#include <string>	// std::string
#include <fstream>	// File management
#include <utility>	// std::pair

#include "maze.h"
#include "cell.h"

class MazeReader
{
	using Dimension = std::pair<int, int>;

	private:
		std::fstream m_fstream;		//<! File stream
		std::string m_file_path;	//<! File location

		//== Private methods
		void read_word(std::string::const_iterator &, const std::string::const_iterator &, std::string &);
		Dimension parse_dimension(const std::string &);					// Transform a line in maze information (height x width)
		std::vector<Cell> parse_cells(const std::string &, int, int);	// Transform a line in maze's cells vector
	public:
		//== Special Methods
		MazeReader(std::string); // Main constructor
		//== Public interface
		std::vector<Maze> read_mazes();
};

#endif
