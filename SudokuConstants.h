#pragma once

const unsigned SUDOKU_FIELD_SIZE = 9;
const unsigned SUDOKU_ELEMENTS_NUMBER = SUDOKU_FIELD_SIZE * SUDOKU_FIELD_SIZE;
const unsigned SUDOKU_BLOCK_SIZE = 3;
const unsigned ALL_POSSIBLE_VALUES[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

enum class SudokuMode {easy, medium, hard};
const unsigned SUDOKU_EASY_MODE_MIN = 30;
const unsigned SUDOKU_EASY_MODE_MAX = 35;
const unsigned SUDOKU_MEDIUM_MODE_MIN = 25;
const unsigned SUDOKU_MEDIUM_MODE_MAX = 30;
const unsigned SUDOKU_HARD_MODE_MIN = 20;
const unsigned SUDOKU_HARD_MODE_MAX = 25;
