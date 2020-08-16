#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;

int sudokuTable[9][9];
bool sudoku(int sudokuTable[9][9], int i, int j);

//Makes array2 equal array1
void copyArray(int array1[9][9], int array2[9][9]);

//True if x value is not present in row
bool rows(int i, int x);

//True if x value is not present in column
bool columns(int j, int x);

//True if x value is not present in square
bool square(int i, int j, int x);

int main() {

	bool done = false;
	const char* fileName = "Sudoku.txt";
	ifstream in(fileName);
	if (!in.is_open()) {
		cout << "Problem with Sudoku file\n";
		return 0;
	}

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			//Reads sudoku table value
			in >> sudokuTable[i][j];
		}
	}
	in.close();

	sudoku(sudokuTable, 0, 0);

}

void copyArray(int array1[9][9], int array2[9][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			array2[i][j] = array1[i][j];
		}
	}
}

bool sudoku(int sudokuTable[9][9], int i, int j) {

	int copy[9][9];
	int row = i;
	int col = j;

	//Make a copy of original sudoku table
	copyArray(sudokuTable, copy);

	if (sudokuTable[row][col] == 0) {
		for (int x = 1; x < 10; x++) {
			// True if x is not in rows, columns or square
			if (rows(row, x) and columns(col, x) and square(row, col, x)) {
				sudokuTable[row][col] = x;

				if (col == 8 and row == 8) {
					cout << "The sudoku is solved: ";
					cout << "\n\n\n";
					for (int i = 0; i < 9; i++) {
						for (int j = 0; j < 9; j++)
							cout << sudokuTable[i][j] << " ";
						cout << endl;
					}
					return true;
				}

				else if (col == 8) {
					row++;
					col = 0;
				}
				else {
					col++;
				}

				sudoku(sudokuTable, row, col);
				if (col == 0) {
					col = 8;
					row--;
				}
				else
					col--;
			}
		}
		//Go back to original table
		copyArray(copy, sudokuTable);
		exit;
	}

	else {
		if (col == 8 and row == 8) {
			cout << "The sudoku is solved: ";
			cout << "\n\n\n";
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++)
					cout << sudokuTable[i][j] << " ";
					cout << endl;
			}
			return true;
		}

		else if (col == 8) {
			row++;
			col = 0;
		}
		else {
			col++;
		}

		sudoku(sudokuTable, row, col);
		if (col == 0) {
			col = 8;
			row--;
		}
		else
			col--;
		exit;
	}
}

bool rows(int i, int x) {
	for (int a = 0; a < 9; a++) {
		if (sudokuTable[i][a] == x)
			return false;
	}
	return true;
}

bool columns(int j, int x) {
	for (int a = 0; a < 9; a++) {
		if (sudokuTable[a][j] == x)
			return false;
	}
	return true;
}

bool square(int i, int j, int x) {
	int row = ceil((i + 1) / 3.);
	int column = ceil((j + 1) / 3.);
	for (int a = (row - 1) * 3; a < ((row - 1) * 3 + 3); a++)
		for (int b = (column - 1) * 3; b < ((column - 1) * 3 + 3); b++)
			if (sudokuTable[a][b] == x)
				return false;
	return true;

}