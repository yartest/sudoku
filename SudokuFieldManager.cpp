#include <iostream>
#include "SudokuFieldManager.h"

void SudokuFieldManager::AskUserAndCheckMode() {
	unsigned modeNumber = 0;
	std::cout << "\nEasy mode \"1\": 30 - 35 available numbers.\n";
	std::cout << "Medium mode \"2\": 20 - 30 available numbers (by default).\n";
	std::cout << "Hard mode \"3\": 20 - 25 available numbers.\n";
	std::cout << "Input sudoku mode: ";
	std::cin >> modeNumber;

	switch (modeNumber) {
	case 1:
		std::cout << "Easy mode is chosen.\n";
		m_mode = SudokuMode::easy;
		break;
	case 3:
		std::cout << "Hard mode is chosen.\n";
		m_mode = SudokuMode::hard;
		break;
	default:
		m_mode = SudokuMode::medium;
		std::cout << "Medium mode is chosen.\n";
		break;
	}
}

void SudokuFieldManager::GenerateField() {
	// make a starting field
	m_startingField.GenerateField(true);
	std::cout << "\nStart field:\n";
	m_startingField.PrintField();

	// make a copy field and put spaces inside
	m_workingField = m_startingField;
	m_workingField.MakeSpaces(m_mode);
	std::cout << "\nWork field(" << m_workingField.GetAvailableElementsCount() << "):\n";;
	m_workingField.PrintField();

	// solve the sudoku
	std::cout << "\nResult field:";
	m_workingField.GenerateField(false);
	m_workingField.PrintDifference(m_startingField);
}

void SudokuFieldManager::UnitTests() {
	const unsigned timesNumber = 10;
	UnitTest(timesNumber, SudokuMode::easy);
	UnitTest(timesNumber, SudokuMode::medium);
	UnitTest(timesNumber, SudokuMode::hard);

	std::cout << "\n All unit tests completed successfully.";
}

void SudokuFieldManager::UnitTest(const unsigned timesNumber, const SudokuMode mode) {

	SudokuField fieldWithSpaces;

	m_mode = mode;
	for (unsigned i = 1; i <= timesNumber; ++i) {
		std::cout << ConvertModeToString(m_mode) << " mode, testId: " << i << " is running" << '\n';
		m_startingField.GenerateField(true);
		m_workingField = m_startingField;
		m_workingField.MakeSpaces(m_mode);
		fieldWithSpaces = m_workingField;
		m_workingField.GenerateField(false);
		if (m_workingField == m_startingField) {
			std::cout << ConvertModeToString(m_mode) << " mode, testId: " << i << " is finished" << '\n';
		}
		else {
			std::cerr << ConvertModeToString(m_mode) << " mode, testId: " << i << " is failed" << '\n';
			std::cerr << "original:\n";
			std::cerr << m_startingField.ConvertToString() << '\n';
			std::cerr << "spaces:\n";
			std::cerr << fieldWithSpaces.ConvertToString() << '\n';
			std::cerr << "result:\n";
			std::cerr << m_workingField.ConvertToString() << '\n';
			throw std::runtime_error("SudokuField::UnitTest() failed");
			return;
		}
	}
}

std::string SudokuFieldManager::ConvertModeToString(const SudokuMode mode) const {
	switch(mode) {
	case SudokuMode::easy:
		return std::string("easy");
		break;
	case SudokuMode::medium:
		return std::string("medium");
		break;
	case SudokuMode::hard:
		return std::string("hard");
		break;
	default:
		// no way
		throw std::runtime_error("SudokuField::ConvertModeToString() incorrect mode");
		break;
	}
}
