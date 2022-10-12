#include "Level.h"

std::vector<char> Level::get_board() const
{
	return board;
}

int Level::get_rows()
{
	return 12;
}

int Level::get_columns()
{
	return (board.size() / get_rows());
}
