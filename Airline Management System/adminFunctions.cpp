#include "adminFunctions.h"


//Admin Login Function
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

//Function to show Admin Menu
int showAdminMenu() {
	int choice;
	bool isValid = true;
	do {
		printHeader();
		if (!isValid) {
			printError("[INVALID_INPUT]: Press 1, 2, 3, 4, or 5\n");
		}

		printSkyBlue("Chose an option from the below(1-5): \n");
		std::cout << "1. Manage Users =>\n";
		std::cout << "2. Manage Flight Inventory =>\n";
		std::cout << "3. View Reservation Reports =>\n";
		printError("4. <= Exit\n");
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

//Create Admins file
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

//Load Admins from file
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

void manageUsers() {
	printSuccess("User managed successfully!");
}

void manageFlights() {
	printSuccess("Flights managed Successfully");
}

void viewReservationReportsAdmin() {
	printSuccess("Reports generated successfully by admin");
}