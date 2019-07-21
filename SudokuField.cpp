#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <random>
#include <stdexcept>
#include <chrono>
#include <iterator>
#include "SudokuField.h"

SudokuField::SudokuField() {
	Initialize();
}

SudokuField::SudokuField(const SudokuField& in) {
	Initialize();
	CopyValues(in);
}

SudokuField& SudokuField::operator = (const SudokuField& in) {
	// check assignment to itself
	if (this == &in) {
		return *this;
	}
	CopyValues(in);
	return *this;
}

// This is only for debug needs
SudokuField& SudokuField::operator = (const std::string& in) {
	const char *data = in.c_str();
	const unsigned zero = static_cast<unsigned>('0');

	for (auto &element: m_elements) {
		if (*data < '0' || *data > '9') {
			throw std::runtime_error("SudokuField::operator = (const std::string& in) incorrect input string");
		}
		unsigned number = static_cast<unsigned>(*data) - zero;
		element.m_value = number;
		++data;
	}
	return *this;
}

bool SudokuField::operator == (const SudokuField &in) const {

	for (const auto &element : m_elements) {
		auto res = std::find(std::begin(in.m_elements), std::end(in.m_elements), element);
		if (res == in.m_elements.end()) {
			return false;
		}
	}
	return true;
}

void SudokuField::MakeSpaces(const SudokuMode &mode) {

	std::cout << "SudokuField::MakeSpaces() is running.\n";

	static std::random_device randomDevice;
	static std::mt19937 randomGenerator(randomDevice());
	unsigned elementsCounter = 0, min, max;
	SudokuField originalField = *this;

	// chose min max elements count regarding sudoku mode
	switch(mode) {
	case SudokuMode::easy:
		min = SUDOKU_EASY_MODE_MIN;
		max = SUDOKU_EASY_MODE_MAX;
		break;
	case SudokuMode::medium:
		min = SUDOKU_MEDIUM_MODE_MIN;
		max = SUDOKU_MEDIUM_MODE_MAX;
		break;
	case SudokuMode::hard:
		min = SUDOKU_HARD_MODE_MIN;
		max = SUDOKU_HARD_MODE_MAX;
		break;
	default:
		// no way
		throw std::runtime_error("SudokuField::RemoveElements() incorrect mode");
		break;
	}

	std::uniform_int_distribution<> dis(min, max);
	elementsCounter = dis(randomGenerator);

	// make and shuffle vector with indexes
	std::vector<unsigned> ids;
	ids.reserve(SUDOKU_ELEMENTS_NUMBER);
	for (unsigned i = 0; i < SUDOKU_ELEMENTS_NUMBER; ++i) {
		ids.push_back(i);
	}
	// shuffle ids
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(ids.begin(), ids.end(), std::default_random_engine(seed));

	unsigned spacesCounter = SUDOKU_ELEMENTS_NUMBER - elementsCounter;
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// make empties
// the core of the task is here
	unsigned i = 0, spaces = 0;
	for (; i < SUDOKU_ELEMENTS_NUMBER && spaces < spacesCounter; ++i) {
		// make a copy of a value
		unsigned oldValue = m_elements.at(ids.at(i)).m_value;
		// assign zero to a random element on the field
		m_elements.at(ids.at(i)).m_value = 0;
		// check if there are many collisions
		unsigned solutionsCounter = this->HasCollisions();
		if (solutionsCounter > 1) {
			m_elements.at(ids.at(i)).m_value = oldValue;
		}
		else {
			++spaces;
		}
	}

	// check if the difficult mode is reached
	if (spaces < SUDOKU_ELEMENTS_NUMBER - max) {
		*this = originalField;
		MakeSpaces(mode);
	}
}

unsigned SudokuField::HasCollisions() {
	SudokuField tempField(*this);
	tempField.HasCollisionsHelper(0);
	return tempField.m_collisionsCounter;
}

unsigned SudokuField::GetAvailableElementsCount() const {
	unsigned counter = std::count_if(m_elements.cbegin(), m_elements.cend(),
			[](const SudokuElement &in) { return in.m_value > 0;});
	return counter;
}

void SudokuField::PrintField() const {
	std::cout << "-------------------------\n";

	for(unsigned i = 0; i < SUDOKU_FIELD_SIZE; ++i) {
		std::cout << "| ";

		for(unsigned j = 0; j < SUDOKU_FIELD_SIZE; ++j) {
			auto index = i * SUDOKU_FIELD_SIZE + j;
			auto value = m_elements.at(index).m_value;

			if (value > 0)  {
				std::cout << value << " ";
			} else {
				std::cout << "  ";
			}

			if (j % SUDOKU_BLOCK_SIZE == SUDOKU_BLOCK_SIZE - 1) {
				std::cout << "| ";
			}
		}
		if (i % SUDOKU_BLOCK_SIZE == SUDOKU_BLOCK_SIZE - 1) {
			std::cout << "\n-------------------------";
		}
		std::cout << '\n';
	}
}

void SudokuField::PrintDifference(const SudokuField& in) const {
	if (*this == in) {
		std::cout << "\nFields are identical.\n";
		PrintField();
		return;
	}

	std::cout << "\nTwo fields difference:\n";

	std::cout << "----------------------------------\n";

	for(unsigned i = 0; i < SUDOKU_FIELD_SIZE; ++i) {
		std::cout << "| ";

		for(unsigned j = 0; j < SUDOKU_FIELD_SIZE; ++j) {
			auto index = i * SUDOKU_FIELD_SIZE + j;
			auto value = m_elements.at(index).m_value;

			auto secondValue = in.m_elements.at(index).m_value;

			if (value > 0)  {
				if (value != secondValue) {
					std::cout << value << "d ";
				}
				else {
					std::cout << value << "  ";
				}
			} else {
				if (value != secondValue) {
					std::cout << "d  ";
				}
				else {
					std::cout << "   ";
				}
			}

			if (j % SUDOKU_BLOCK_SIZE == SUDOKU_BLOCK_SIZE - 1) {
				std::cout << "| ";
			}
		}
		if (i % SUDOKU_BLOCK_SIZE == SUDOKU_BLOCK_SIZE - 1) {
			std::cout << "\n----------------------------------";
		}
		std::cout << '\n';
	}
}

std::string SudokuField::ConvertToString() const {
	std::stringstream ostream;
	for(auto element: m_elements) {
		ostream << element.m_value;
	}
	return ostream.str();
}

void SudokuField::Initialize() {
	// skip it if it is done already
	if (m_elements.size() > 0) {
		return;
	}

	m_elements.reserve(SUDOKU_ELEMENTS_NUMBER);

	for (unsigned i = 0; i < SUDOKU_FIELD_SIZE; ++i) {
		for(unsigned j = 0; j < SUDOKU_FIELD_SIZE; ++j) {
			m_elements.push_back(SudokuElement());
			m_elements.rbegin()->SetPosition({i, j});
		}
	}
}

void SudokuField::CopyValues(const SudokuField &in) {
	size_t size = in.m_elements.size();
	for (unsigned i = 0; i < size; ++i) {
		m_elements.at(i).m_value = in.m_elements.at(i).m_value;
	}
}

SudokuElement SudokuField::GetElementByIndex(unsigned index) const {

	if (index >= SUDOKU_ELEMENTS_NUMBER)
		throw std::runtime_error("SudokuField::GetElementByIndex() incorrect index");

	return m_elements.at(index);
}

SudokuElement SudokuField::GetElementByPosition(const unsigned i, const unsigned j) const {
	unsigned index = i * SUDOKU_FIELD_SIZE + j;
	return GetElementByIndex(index);
}

bool SudokuField::GenerateFieldBackTracking(unsigned elementId, bool generate) {

	auto &element = m_elements.at(elementId);

	if (element.m_value != 0) {
		if (elementId == m_elements.size() - 1) {
			return true;
		}
		return GenerateFieldBackTracking(elementId + 1, generate);
	}

	std::unordered_set<int> currentValues;

	for (const auto &relatedElement : element.m_relatedElements) {
		auto value = this->GetElementByPosition
				(relatedElement.i, relatedElement.j).m_value;
		currentValues.insert(value);
	}

	static const std::vector<unsigned> allPossibleValues(ALL_POSSIBLE_VALUES, ALL_POSSIBLE_VALUES + SUDOKU_FIELD_SIZE);
	std::vector<int> newValues;

// take a value from all possible values
// check if this value is inside the related elements
// if there is no such value ADD it like a possible candidate
	for(const auto &eachPossibleValue : allPossibleValues) {
		auto it = currentValues.find(eachPossibleValue);
		if (it == currentValues.end()) {
			newValues.push_back(eachPossibleValue);
		}
	}

// Random is here:
	if (generate) {
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(newValues.begin(), newValues.end(), std::default_random_engine(seed));
	}

	for (auto &newValue: newValues) {
		element.m_value = newValue;
		if (elementId == m_elements.size() - 1) {
			return true;
		}
		bool result = GenerateFieldBackTracking(elementId + 1, generate);
		if (result) {
			return true;
		}
	}

	element.m_value = 0;
	return false;
}

bool SudokuField::HasCollisionsHelper(unsigned elementId) {

	// proccessing can be skiped if there are 2 collisions already
	if (m_collisionsCounter > 1) {
		return false;
	}

	auto &element = m_elements.at(elementId);
	if (element.m_value != 0) {
		if (elementId == m_elements.size() - 1) {
			++m_collisionsCounter;
			return false;
		}
		return HasCollisionsHelper(elementId + 1);
	}

	std::unordered_set<int> currentValues;

	for (auto &relatedElement : element.m_relatedElements) {
		auto value = GetElementByPosition(relatedElement.i, relatedElement.j).m_value;
		currentValues.insert(value);
	}

	static const std::vector<unsigned> allPossibleValues(ALL_POSSIBLE_VALUES, ALL_POSSIBLE_VALUES + SUDOKU_FIELD_SIZE);
	std::vector<int> newValues;

// take a value from all possible values
// check if this value is inside the related elements
// ADD it like a possible candidate if there is no such a value
	for(const auto &eachPossibleValue : allPossibleValues) {
		auto it = currentValues.find(eachPossibleValue);
		if (it == currentValues.end()) {
			newValues.push_back(eachPossibleValue);
		}
	}

	//if (newValues.empty()) {
	//	std::cout << "\nelementId: " << elementId << '\n';
	//	std::cout << "empty\n";
	//}

	for (const auto &newValue: newValues) {
		//std::cout << "\nelementId: " << elementId << '\n';
		//std::copy(newValues.cbegin(), newValues.cend(), std::ostream_iterator<unsigned>(std::cout , " : "));
		//std::cout << '\n';
		//std::cout << "value: " << newValue << '\n';

		// proccessing can be skipped if there are 2 collisions already
		if (m_collisionsCounter > 1) {
			return false;
		}
		element.m_value = newValue;
		if (elementId == m_elements.size() - 1) {
			++m_collisionsCounter;
			element.m_value = 0;
			return false;
		}
		HasCollisionsHelper(elementId + 1);
	}

	element.m_value = 0;
	return false;
}

