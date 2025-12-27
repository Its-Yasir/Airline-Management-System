#include <stdlib.h>

#include "functions.h"
#include "models.h"

void printError(std::string message) {
	std::cout << "\033[1;31m" << message << "\033[0m";
}

void printBlue(std::string message) {
	std::cout << "\033[1;34m" << message << "\033[0m";
}

void printSkyBlue(std::string message) {
	std::cout << "\033[1;36m" << message << "\033[0m";
}

void printSuccess(std::string message) {
	std::cout << "\033[1;32m" << message << "\033[0m";
}

void printHeader() {
	system("CLS");
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

int showMenu() {
	int choice;
	bool isValid = true;
	do {
		printHeader();
		if (!isValid) {
			printError("[ERROR]: Invalid input, Press 1, 2 or 3\n");
		}

		std::cout << "Chose an option from the below(1-3): \n";
		std::cout << "1. Login as admin\n";
		std::cout << "2. Login as passenger\n";
		printError("3. Exit\n");
		std::cin >> choice;

		if (std::cin.fail()) { 
			std::cin.clear(); 
			std::cin.ignore(1000, '\n'); 
			choice = 0; 
		}

		if (choice < 1 || choice > 3) {
			isValid = false;
		}
		else {
			isValid = true;
		}

	} while (!isValid);

	return choice;
}

bool passengerLogin(User arr[], int a) {
	bool isAuthentic = false;
	std::string inputUserId;
	std::string inputPass;
	std::string errrorMessage = "";
	do {
		printHeader();
		printBlue("Passenger Login: \n");
		if (!errrorMessage.empty()) {
			printError(errrorMessage);
		}
		std::cout << "Enter Username: ";
		std::cin >> inputUserId;
		std::cout << "Enter Password: ";
		std::cin >> inputPass;
		bool idFound = false;
		for (int i = 0; i < a; i++) {
			if (arr[i].userID == inputUserId) {
				idFound = true;
				if (arr[i].password == inputPass) {
					isAuthentic = true;
					errrorMessage = "";
					break;
				}
				else {
					errrorMessage = "[ERROR]: Password is incorrect!\n";
					break;
				}
			}
		}
		if (!idFound) {
			errrorMessage = "[ERROR]: User ID not found!\n";
		}
	} while (!isAuthentic);

	return isAuthentic;
}

bool adminLogin(User arr[], int a) {
	bool isAuthentic = false;
	std::string inputAdminId;
	std::string inputPass;
	std::string errrorMessage = "";
	do {
		printHeader();
		printBlue("Passenger Login: \n");
		if (!errrorMessage.empty()) {
			printError(errrorMessage);
		}
		std::cout << "Enter Admin ID: ";
		std::cin >> inputAdminId;
		std::cout << "Enter Password: ";
		std::cin >> inputPass;
		bool idFound = false;
		for (int i = 0; i < a; i++) {
			if (arr[i].userID == inputAdminId) {
				idFound = true;
				if (arr[i].password == inputPass) {
					isAuthentic = true;
					errrorMessage = "";
					break;
				}
				else {
					errrorMessage = "[ERROR]: Password is incorrect!\n";
					break;
				}
			}
		}
		if (!idFound) {
			errrorMessage = "[ERROR]: User ID not found!\n";
		}
	} while (!isAuthentic);

	return isAuthentic;
}

