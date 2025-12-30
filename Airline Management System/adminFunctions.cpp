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

//Manage Users Menu
int showManageUsersMenu() {
	int choice;
	bool isValid = true;
	do {
		printHeader();
		if (!isValid) {
			printError("[INVALID_INPUT]: Press 1, 2, 3, 4, or 5\n");
		}
		printSkyBlue("Chose an option from the below(1-5): \n");
		std::cout << "1. View Users =>\n";
		std::cout << "2. Edit Users Details =>\n";
		std::cout << "3. Add User =>\n";
		std::cout << "4. Remove User =>\n";
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

//Find balance for a specific username
std::string getBalanceForUser(std::string userId, int size) {
	std::ifstream balanceFile("database/users-balance.txt");
	if (!balanceFile.is_open()) {
		printError("Could not open users-balance.txt file.");
		return "0";
	}
	int count = 0;
	std::string line, user, balance;
	while (count < size && balanceFile
		>> user
		>> balance) {
		count++;
		if(user == userId) {
			balanceFile.close();
			return balance;
		}
	}
	return "0";
}

//View All Userrs
void viewAllUsersData(int noOfBalanceUsers) {
	std::ifstream file("database/users-extra-data.txt");
	if (!file.is_open()) {
		printError("There was an error while opening users-extra-data.txt");
		return;
	}

	std::string line;
	int count = 1;

	printBlue("==========================================");
	printYellow("           ALL USERS DETAILES                    ");
	printBlue("==========================================");

	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string username, userId, address, city, province, country, phone, passport;


		std::getline(ss, username, '|');
		std::getline(ss, userId, '|');
		std::getline(ss, address, '|');
		std::getline(ss, city, '|');
		std::getline(ss, province, '|');
		std::getline(ss, country, '|');
		std::getline(ss, phone, '|');
		std::getline(ss, passport, '|');


		std::string balance = getBalanceForUser(userId, noOfBalanceUsers);

		printBlue("--------------------------------------------------------");
		std::string header = " [" + std::to_string(count) + "] User: " + username;
		printYellow(header);
		printBlue("--------------------------------------------------------\n");

		printSkyBlue(" Address:   ");
		std::cout << address << std::endl;

		printSkyBlue(" City:      ");
		std::cout << city << std::endl;

		printSkyBlue(" Province:  ");
		std::cout << province << std::endl;

		printSkyBlue(" Country:   ");
		std::cout << country << std::endl;

		printSkyBlue(" Contact:   ");
		std::cout << phone << std::endl;

		printSkyBlue(" Passport:  ");
		std::cout << passport << std::endl;

		printSkyBlue(" Balance:   ");
		printSuccess("PKR " + balance);

		std::cout << std::endl;
		count++;
	}

	printBlue("==================================================\n");
	printSuccess(" End of Users\n");
	printBlue("==================================================\n");

	file.close();
}

void manageUsers(int noOfBalanceUsers) {
	int choice = showManageUsersMenu();
	switch (choice)
	{
		case 1:
		viewAllUsersData(noOfBalanceUsers);
		break;
	default:
		break;
	}
}

void manageFlights() {
	printSuccess("Flights managed Successfully");
}

void viewReservationReportsAdmin() {
	printSuccess("Reports generated successfully by admin");
}