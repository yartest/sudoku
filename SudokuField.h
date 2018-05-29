#pragma once

#include <vector>
#include <string>
#include <memory>
#include "SudokuElement.h"

// SudokuField contains all elements on the field

class SudokuField {
	std::vector<std::shared_ptr<SudokuElement> > 	m_elements;
	unsigned 										m_collisionsCounter = 0;

public:
	SudokuField();
	SudokuField(const SudokuField& in);
	SudokuField& operator = (const SudokuField& in);
	// This is only for debug needs
	SudokuField& operator = (const std::string& in);
	SudokuField(SudokuField&&) = delete;
	SudokuField& operator = (SudokuField&&) = delete;
	~SudokuField() = default;

	// compare two fields
	bool operator == (const SudokuField &in) const;

	// Generate sudoku field
	void GenerateField(bool generate) {
		GenerateFieldBackTracking(0, generate);
	}
	// Remove elements regarding choosen mode
	void MakeSpaces(const SudokuMode &mode);
	// Return number of solutions (collisions) for the current field
	unsigned HasCollisions();
	// Get available elements counter.
	unsigned GetAvailableElementsCount() const;
	// Print the sudoku field
	void PrintField() const;
	// Print the difference of the two fields
	void PrintDifference(const SudokuField& in) const;
	// Convert to string
	std::string ConvertToString() const;

private:
	// at the first time create all elements
	void Initialize();
	// Copy values from one filed to another
	void CopyValues(const SudokuField &in);
	// Get element by index inside the vector
	std::shared_ptr<SudokuElement> GetElementByIndex(unsigned index) const ;
	// Get element by position on the field
	std::shared_ptr<SudokuElement> GetElementByPosition(const unsigned i, const unsigned j) const;
	// Recursive function that uses brute force to generate or solve sudoku field
	bool GenerateFieldBackTracking(unsigned elementId, bool generate);
	// Check all possible solutions (collisions)
	bool HasCollisionsHelper(unsigned elementId);
};// struct SudokuField {
