#include "maze_reader.h"
#include <iostream>

//== Private methods

void MazeReader::read_word(std::string::const_iterator & it, const std::string::const_iterator & end, std::string & word)
{
	// skip white spaces or tabs
	while (*it == 9 or *it == ' ')
		it++;

	for (/* empty */; it != end; it++) {
		if (*it == 9 or *it == ' ') break; // If it is a whitespace or tab, the word ends
		word += *it;
	}
}

/// Gets a line and transform it in a pair<width, height>
MazeReader::Dimension MazeReader::parse_dimension(const std::string & line)
{
	std::string num_buff = "";
	std::string::const_iterator curr_char = line.cbegin();

	// Read the width
	read_word(curr_char, line.cend(), num_buff);
	int width = stoi(num_buff);

	num_buff = "";

	// Read the heigth
	read_word(curr_char, line.cend(), num_buff);
	int height = stoi(num_buff);
	
	return std::make_pair(width, height);

}

/// Gets a line and transform it in a vector of Cells
std::vector<Cell> MazeReader::parse_cells(const std::string & line, int curr_row, int num_cols)
{
	//if (line.size() < num_cols) // TODO throw a error here
	std::vector<Cell> line_of_cells;	// vector with parsed cells
	for (auto i(0); i < num_cols; i++) {
		line_of_cells.push_back(Cell(i, curr_row, line[i]));
	}
	return line_of_cells;
}

//== Special Methods

/// Main constructor
MazeReader::MazeReader(std::string file_path)
	: m_file_path(file_path)
{
	m_fstream.open(m_file_path);
	// if (!m_fstream.is_open()) TODO throw a error here
	m_fstream.close();
}

//== Public interface

/// Reads all mazes from a file
std::vector<Maze> MazeReader::read_mazes()
{
	std::cout << ">>>\tStart read maze file \n";
	m_fstream.open(m_file_path);

	// Buffer rows
	std::string buffer = "";
	int rows = 0;
	int	curr_row = 0;
	int num_cols = 0;

	std::vector<Maze> mazes_vector;
	Maze::MazeType tmp_maze;

	while (std::getline(m_fstream, buffer)) {
		// The first row should say "WIDTH HEIGHT"
		if (rows == 0) {
			std::cout << "\tRead maze infos \n";
			Dimension dim = parse_dimension(buffer);
			std::cout <<"\tMaze dimensions = " << std::get<0>(dim) << "r " << std::get<1>(dim) << "c\n";

			rows = std::get<0>(dim); // Sets rows as first dimension, because we want to read 
			num_cols = std::get<1>(dim); // Stores the num of cols
			curr_row = 0;

			if (tmp_maze.size() > 0) {
				mazes_vector.push_back(Maze(tmp_maze));
				tmp_maze.clear();
			}
		} else {
			// It is a line with Cells elements
			tmp_maze.push_back(parse_cells(buffer, curr_row, num_cols));
			rows--;
			curr_row++;
			std::cout << "Curr line : " << curr_row << "\n";
		}
	}

	m_fstream.close();
	return mazes_vector;
};
