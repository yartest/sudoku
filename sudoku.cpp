#include <iostream>
#include <stdexcept>
#include "SudokuFieldManager.h"

int main() {
	try {
		//SudokuFieldManager::GetInstance().AskUserAndCheckMode();
		//SudokuFieldManager::GetInstance().GenerateField();

		SudokuFieldManager::GetInstance().UnitTests();
		if (true) {
			SudokuField test1, test2;
			test1 = std::string("792431568654987321381256947869325174473619285215874639926148753538792416147563892");
			test1.PrintField();
			test2 = std::string("090431500054000000301006900809000074400610280210000030006048050000700406000063000");
			test2.PrintField();
			unsigned collisions = test2.HasCollisions();
			std::cout << "collisions: " << collisions << '\n';
			test2.GenerateField(false);
			test2.PrintDifference(test1);
		}

	}
	catch (std::exception &e) {
		std::cerr << " main(): an exception has been caught " << e.what() << '\n';
	}
	catch (...) {
		std::cerr << "main(): unknown exception has been caught" << '\n';
	}
	return 0;
}
