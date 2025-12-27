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
		printError("[ERROR]: There was an error while opening the file.");
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

User* loadAdmins(int& size) {
	std::ifstream adminsFile("database/admins.txt");
	if (!adminsFile.is_open()) {
		printError("[ERROR]: There was an error while opening the admins file.");
		return nullptr;
	}
	else {
		std::string line;
		while (std::getline(adminsFile, line)) {
			if (!line.empty()) {
				size++;
			}
		}

		adminsFile.clear();
		adminsFile.seekg(0, std::ios::beg);
		User* adminArray = new User[size];
		int count = 0;
		while (count < size && adminsFile >> adminArray[count].userID >> adminArray[count].password) {
			count++;
		}

		adminsFile.close();
		return adminArray;
	}

}

void createAdminFile() {
	std::ofstream adminFileCreate("database/admins.txt");
	if (!adminFileCreate.is_open()) {
		printError("[ERROR]: There was as error while creating the admins file!\n");
	}
	else {
		adminFileCreate << "hassan_raza_15 @dmin_has_123" << std::endl;
		adminFileCreate << "ahmad_faraz_911 @dmin_ahm_890" << std::endl;
		adminFileCreate.close();
	}
}

int showMenu() {
	int choice;
	bool isValid = true;
	do {
		printHeader();
		if (!isValid) {
			printError("[INVALID_INPUT]: Press 1, 2 or 3\n");
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
					errrorMessage = "[INVALID_INPUT]: Password is incorrect!\n";
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
		printBlue("Admin Login: \n");
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
			errrorMessage = "[ERROR]: Admin ID not found!\n";
		}
	} while (!isAuthentic);

	return isAuthentic;
}

int showUserMenu() {
	int choice;
	bool isValid = true;
	do {
		printHeader();
		if (!isValid) {
			printError("[INVALID_INPUT]: Press 1, 2, 3, 4 or 5\n");
		}

		printSkyBlue("Chose an option from the below(1-5): \n");
		std::cout << "1. Book FLighrs =>\n";
		std::cout << "2. Cancel Reservations =>\n";
		std::cout << "3. View Available Flights =>\n";
		std::cout << "4. Genrerate Bookign Reports =>\n";
		printError("5. <= Exit\n");
		std::cin >> choice;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			choice = 0;
		}

		if (choice < 1 || choice > 5) {
			isValid = false;
		}
		else {
			isValid = true;
		}

	} while (!isValid);

	return choice;
}

int showAdminMenu() {
	int choice;
	bool isValid = true;
	do {
		printHeader();
		if (!isValid) {
			printError("[INVALID_INPUT]: Press 1, 2, 3, 4, or 5\n");
		}

		printSkyBlue("Chose an option from the below(1-5): \n");
		std::cout << "1. Manage Pasengers =>\n";
		std::cout << "2. Manage Users =>\n";
		std::cout << "3. Manage Flight Inventory =>\n";
		std::cout << "4. View Reservation Reports =>\n";
		printError("5. <= Exit\n");
		std::cin >> choice;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			choice = 0;
		}

		if (choice < 1 || choice > 5) {
			isValid = false;
		}
		else {
			isValid = true;
		}

	} while (!isValid);

	return choice;
}

void bookFlights() {
	printSuccess("Flights Booked Successfuly!");
}

void cancelReservations() {
	printSuccess("Reservations canceled Successfuly!");
}

void viewAvailableFlights() {
	printSuccess("Available flights viewed successfully!");
}

void generateUserReservationReport() {
	printSuccess("Report Genrated Successfully!");
}

void managePassengers() {
	printSuccess("Passengers managed Successfully!");
}

void manageUsers() {
	printSuccess("User managed successfully!");
}

void manageFlights() {
	printSuccess("Flights managed Successfully");
}

void viewReservationReportsAdmin() {
	printSuccess( "Reports generated successfully by admin");
}