#include "SudokuElement.h"

void SudokuElement::SetPosition(const SudokuPosition &inPos) {
	m_pos = inPos;
	SetRelatedElements();
}

void SudokuElement::SetRelatedElements () {

	for (unsigned i = 0; i < SUDOKU_FIELD_SIZE; ++i) {
		// set column neighbors
		m_relatedElements.insert({i, m_pos.j});
		// set row neighbors
		m_relatedElements.insert({m_pos.i, i});
	}

	unsigned yStartId = (m_pos.i / SUDOKU_BLOCK_SIZE) * SUDOKU_BLOCK_SIZE;
	unsigned xStartId = (m_pos.j / SUDOKU_BLOCK_SIZE) * SUDOKU_BLOCK_SIZE;
	unsigned yEndId = yStartId + SUDOKU_BLOCK_SIZE - 1;
	unsigned xEndId = xStartId + SUDOKU_BLOCK_SIZE - 1;

	// set block neighbors
	for (unsigned i = yStartId; i <= yEndId; ++i) {
		for (unsigned j = xStartId; j <= xEndId; ++j) {
			m_relatedElements.insert({i, j});
		}
	}
}
