#pragma once

#include <unordered_set>
#include "SudokuPosition.h"

// SudokuElement
// m_pos				- own position
// m_value 				- own value
// m_relatedElements 	- positions of all related elements to the current one
struct SudokuElement {
public:
	SudokuPosition 										m_pos;
	unsigned 											m_value = 0;
	std::unordered_set<SudokuPosition, SudokuPosition> 	m_relatedElements;

	void SetPosition(const SudokuPosition &inPos);

	bool operator == (const SudokuElement &in) const
	{ return m_pos == in.m_pos && m_value == in.m_value; }

private:
	void SetRelatedElements ();

};// struct SudokuElement {
