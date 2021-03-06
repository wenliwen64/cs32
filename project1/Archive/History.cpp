#include "History.h"
#include "globals.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols) {
	m_rows = nRows;
	m_cols = nCols;
	for (int i = 0; i < m_rows; i++)
		for (int j = 0; j < m_cols; j++)
			m_grid[i][j] = 0;
}

bool History::record(int r, int c) {//TODO justify the rc
	if (r > m_rows || c > m_cols || r <= 0 || c <= 0)
		return false;
	else {
		m_grid[r - 1][c - 1]++;
		if (m_grid[r - 1][c - 1] >= 26)
			m_grid[r - 1][c - 1] = 26;
		return true;
	}
}

void History::display() const
{
	// Position (row,col) in the arena coordinate system is represented in
	// the array element grid[row-1][col-1]
	char grid[MAXROWS][MAXCOLS];
	int r, c;

	// Fill the grid with dots
	for (r = 0; r < m_rows; r++) {
		for (c = 0; c < m_cols; c++) {
			if (m_grid[r][c] == 0)
				grid[r][c] = '.';
			else
				grid[r][c] = m_grid[r][c] + 'A' - 1;
		}
	}

	// Draw the grid
	clearScreen();
	for (r = 0; r < m_rows; r++)
	{
		for (c = 0; c < m_cols; c++)
			cout << grid[r][c];
		cout << endl;
	}
	cout << endl;
	/*
	cout << "There are " << robotCount() << " robots remaining." << endl;
	if (m_player == nullptr)
	cout << "There is no player." << endl;
	else
	{
	if (m_player->age() > 0)
	cout << "The player has lasted " << m_player->age() << " steps." << endl;
	if (m_player->isDead())
	cout << "The player is dead." << endl;
	}
	*/
}