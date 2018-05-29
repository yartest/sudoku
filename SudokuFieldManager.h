#pragma once

#include "SudokuField.h"

class SudokuFieldManager {
	SudokuField 	m_startingField;
	SudokuField 	m_workingField;
	SudokuMode		m_mode 				= SudokuMode::medium;

	SudokuFieldManager() = default;
	~SudokuFieldManager() = default;

public:
	static SudokuFieldManager& GetInstance() {
		static SudokuFieldManager instance;
		return instance;
	}

	void AskUserAndCheckMode();
	void GenerateField();
	void UnitTests();
private:
	void UnitTest(const unsigned n, const SudokuMode mode);
	std::string ConvertModeToString(const SudokuMode mode) const;
};// class SudokuFieldManager
