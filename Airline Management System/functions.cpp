#include "functions.h"
#include "models.h"

void printError(std::string message) {
	std::cout << "\033[1;31m" << message << "\033[0m" << std::endl;
}

void printSuccess(std::string message) {
	std::cout << "\033[1;32m" << message << "\033[0m" << std::endl;
}

void printHeader() {
	std::string colorCyan = "\033[1;36m";
	std::string colorYellow = "\033[1;33m";
	std::string colorReset = "\033[0m";

	std::cout << colorYellow << "===================================================================================================================" << colorReset << std::endl;
	std::cout << colorCyan <<   "=                                        AIRLINE RESERVATION MANAGEMENT SYSTEM                                    =" << colorReset << std::endl;
	std::cout << colorYellow << "===================================================================================================================" << colorReset << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
}

User* loadUsers(int& size) {
	std::ifstream passengersFile("database/passengers.txt");
	if (!passengersFile.is_open()) {
		printError("There was an error while opening the file.");
		return nullptr;
	}
	else{
		std::string line;
		while (std::getline(passengersFile, line)) {
			if(!line.empty()){
				size++;
			}
	}
		//printSuccess("No. of users found: " + std::to_string(size));

		passengersFile.clear();
		passengersFile.seekg(0, std::ios::beg);
		User* userArray = new User[size];
		int count = 0;
		while (count < size && passengersFile >> userArray[count].userID >> userArray[count].password) {
			count++;
		}

		passengersFile.close();
		return userArray;
	}

}

