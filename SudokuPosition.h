#pragma once

#include "SudokuConstants.h"

// SudokuPosition contains coordinates inside
// SudokuPosition{i, j}
//
//			  | 0 | 1 | 2 | . | j | . |N-1|
//			-------------------------------
//			0 |   |   |   |   |   |   |   |
//			-------------------------------
//			1 |   |   |   |   |   |   |   |
//			-------------------------------
//			. |   |   |   |   |   |   |   |
//			-------------------------------
//			i |   |   |   |   | E |   |   |
//			-------------------------------
//			. |   |   |   |   |   |   |   |
//			-------------------------------
//		   N-1|   |   |   |   |   |   |   |
//			-------------------------------

struct SudokuPosition {
	unsigned i = 0;
	unsigned j = 0;

	SudokuPosition(unsigned first, unsigned second):i{first}, j{second}{}

	bool operator == (const SudokuPosition &in) const {
		return i == in.i && j == in.j;
	}

	// hash function for unordered_set
	// it presumes that every sudoku row (column) doesn't have more than 256 elements
	std::size_t operator () (const SudokuPosition &in) const {
		return (in.i << 8) | in.j;
	}

	SudokuPosition() = default;
	SudokuPosition(const SudokuPosition&) = default;
	SudokuPosition& operator = (const SudokuPosition&) = default;
	SudokuPosition(SudokuPosition&&) = default;
	SudokuPosition& operator = (SudokuPosition&&) = default;
	~SudokuPosition() = default;

}; // struct SudokuPosition {

