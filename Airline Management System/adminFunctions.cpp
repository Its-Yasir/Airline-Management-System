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
			printError("[INVALID_INPUT]: Press 1, 2, 3, or 4\n");
		}

		printSkyBlue("Chose an option from the below(1-4): \n");
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
	printHeader();
	printBlue("==========================================");
	printYellow("           ALL USERS DETAILES                    ");
	printBlue("==========================================\n");

	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string username, userId, address, city, province, country, phone, passport, balance, password;


		std::getline(ss, username, '|');
		std::getline(ss, userId, '|');
		std::getline(ss, address, '|');
		std::getline(ss, city, '|');
		std::getline(ss, province, '|');
		std::getline(ss, country, '|');
		std::getline(ss, phone, '|');
		std::getline(ss, passport, '|');
		std::getline(ss, password, '|');
		std::getline(ss, balance, '|');


		printBlue("--------------------------------------------------------");
		std::string header = " [" + std::to_string(count) + "] User: " + username;
		printYellow(header);
		printBlue(" --------------------------------------------------------\n");

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

		printSkyBlue(" Pasword:   ");
		printSuccess(password + "\n");

		std::cout << std::endl;
		count++;
	}

	printBlue("==================================================\n");
	printSuccess(" End of Users\n");
	printBlue("==================================================\n");

	file.close();
}

//Get Users List containing IDs only
void displayUsersWithIDs(User* users, int noOfUsers) {
	printHeader();
	printYellow("List of users: \n");
	for (int i = 0; i < noOfUsers; i++) {
		printBlue("\t" + users[i].userID + "\n");
	}
}

//Update Users Extra data file
void updateUserDetailsFile(UsersDetails userDetail) {
	std::ifstream countFile("database/users-extra-data.txt");
	int actualCount = 0;
	std::string tempLine;
	if (countFile.is_open()) {
		while (std::getline(countFile, tempLine)) {
			if (!tempLine.empty()) actualCount++;
		}
		countFile.close();
	}

	int maxCapacity = actualCount + 1;
	UsersDetails* allUserDetails = new UsersDetails[maxCapacity];

	std::ifstream loadFile("database/users-extra-data.txt");
	int loadedCount = 0;

	if (loadFile.is_open()) {
		std::string line;
		while (loadedCount < actualCount && std::getline(loadFile, line)) {
			if (line.empty()) continue;

			std::stringstream ss(line);
			std::string uName, uId, uAddr, uCity, uProv, uCount, uPhone, uPass, uPwd, uBal;

			std::getline(ss, uName, '|');
			std::getline(ss, uId, '|');
			std::getline(ss, uAddr, '|');
			std::getline(ss, uCity, '|');
			std::getline(ss, uProv, '|');
			std::getline(ss, uCount, '|');
			std::getline(ss, uPhone, '|');
			std::getline(ss, uPass, '|');
			std::getline(ss, uPwd, '|');
			std::getline(ss, uBal, '|');

			allUserDetails[loadedCount].userName = uName;
			allUserDetails[loadedCount].id = uId;
			allUserDetails[loadedCount].address = uAddr;
			allUserDetails[loadedCount].city = uCity;
			allUserDetails[loadedCount].province = uProv;
			allUserDetails[loadedCount].country = uCount;
			allUserDetails[loadedCount].contact = uPhone;
			allUserDetails[loadedCount].passport = uPass;
			allUserDetails[loadedCount].password = uPwd;
			try { allUserDetails[loadedCount].balance = std::stoll(uBal); }
			catch (...) { allUserDetails[loadedCount].balance = 0; }

			loadedCount++;
		}
		loadFile.close();
	}


	bool found = false;
	for (int i = 0; i < loadedCount; i++) {
		if (allUserDetails[i].id == userDetail.id) {
			allUserDetails[i] = userDetail; // Update existing
			found = true;
			break;
		}
	}

	if (!found) {
		allUserDetails[loadedCount] = userDetail;
		loadedCount++;
	}


	std::ofstream saveFile("database/users-extra-data.txt");
	if (saveFile.is_open()) {
		for (int i = 0; i < loadedCount; i++) {
			saveFile
				<< allUserDetails[i].userName + "|"
				<< allUserDetails[i].id + "|"
				<< allUserDetails[i].address + "|"
				<< allUserDetails[i].city + "|"
				<< allUserDetails[i].province + "|"
				<< allUserDetails[i].country + "|"
				<< allUserDetails[i].contact + "|"
				<< allUserDetails[i].passport + "|"
				<< allUserDetails[i].password + "|"
				<< allUserDetails[i].balance << "\n";
		}
		printSuccess("File updated successfully!\n");
		saveFile.close();
	}
	else {
		printError("Error saving file!\n");
	}

	delete[] allUserDetails;
}

//Function to find if another user exists with same userID
bool isUserIDExists(std::string userId) {
	std::ifstream usersFile("database/passengers.txt");
	if(!usersFile.is_open()) {
		printError("There was an error while opening the file!\n");
		return false;
	}
	else {
		std::string line;
		while (std::getline(usersFile, line)) {
			std::stringstream ss(line);
			std::string id, password;
			std::getline(ss, id, ' ');
			std::getline(ss, password, ' ');
			if(id == userId) {
				usersFile.close();
				return true;
			}
		}
		usersFile.close();
	}
	return false;
}


//Function to update passengers file when userID is changed
void updatePassengersFile(std::string newUserId, std::string oldUserId, User users[], int noOfUsers) {
	for(int i = 0; i < noOfUsers; i++) {
		if(users[i].userID == oldUserId) {
			users[i].userID = newUserId;
			break;
		}
	}

	std::ofstream savePassengersFile("database/passengers.txt");
	if (!savePassengersFile.is_open()) {
		printError("There was an error while saving updated passengers file.\n");
	}
	else {
		for (int i = 0; i < noOfUsers; i++) {
			savePassengersFile << users[i].userID << " " << users[i].password << "\n";
		}
		printSuccess("Passengers file has been updated with new User ID!\n");
		savePassengersFile.close();
	}
}

//Get Info for One User
UsersDetails getDetailsForOneUser(std::string userId, int noOfBalanceUsers, User myUsers[], int noOfUsers) {
	UsersDetails userDetails = { "", "", "", "", "", "", "", "", "", 0 };

	bool foundInLogin = false;
	for (int i = 0; i < noOfUsers; i++) {
		if (myUsers[i].userID == userId) {
			userDetails.password = myUsers[i].password;
			userDetails.id = userId;
			foundInLogin = true;
			break;
		}
	}

	if (!foundInLogin) return userDetails;

	std::ifstream usersExtraDataFile("database/users-extra-data.txt");
	if (!usersExtraDataFile.is_open()) {
		printError("Warning: users-extra-data.txt not found. Returning partial info.\n");
		return userDetails;
	}

	std::string line;
	while (std::getline(usersExtraDataFile, line)) {
		if (line.empty()) continue;

		std::stringstream ss(line);
		std::string username, userIdFormFile, address, city, province, country, phone, passport, password, balanceStr;

		std::getline(ss, username, '|');
		std::getline(ss, userIdFormFile, '|');

		if (userIdFormFile == userId) {
			std::getline(ss, address, '|');
			std::getline(ss, city, '|');
			std::getline(ss, province, '|');
			std::getline(ss, country, '|');
			std::getline(ss, phone, '|');
			std::getline(ss, passport, '|');
			std::getline(ss, password, '|');
			std::getline(ss, balanceStr, '|');

			userDetails.userName = username;
			userDetails.address = address;
			userDetails.city = city;
			userDetails.province = province;
			userDetails.country = country;
			userDetails.contact = phone;
			userDetails.passport = passport;

			try {
				if (!balanceStr.empty()) {
					userDetails.balance = std::stoll(balanceStr);
				}
				else {
					std::string bal = getBalanceForUser(userId, noOfBalanceUsers);
					userDetails.balance = std::stoll(bal);
				}
			}
			catch (...) {
				userDetails.balance = 0;
			}

			usersExtraDataFile.close();
			return userDetails;
		}
	}

	usersExtraDataFile.close();
	return userDetails;
}

//This funtion will change the UserDetails object and return an updated one
UsersDetails getUserDetailsAfterChange(UsersDetails det, int type) {
	std::string inputTaken;
	std::string errorMessage = "";
	long long amountInput = 0;
	bool isFound = false;
	bool isValid = false;
	switch (type) {
		case 1:
			errorMessage = "";
			isValid = false;
			do {
				printHeader();
				if (!isValid) {
					if (!errorMessage.empty()) {
						printError(errorMessage);
					}
				}
				printBlue("Current Username: " + det.userName + "\n");
				printSkyBlue("Enter 0 to exit without changing any data\n");
				std::cout << "Enter new Username: ";
				std::getline(std::cin >> std::ws, inputTaken);
				if(inputTaken.find_first_not_of(' ') != std::string::npos) {
					if (inputTaken.length() > 3) {
						if(inputTaken == "0") {
							isValid = true;
							return det;
						}
						else {
							det.userName = inputTaken;
							isValid = true;
							return det;
						}
					}
					else {
						isValid = false;
						errorMessage = "[INVALID_INPUT]: Username must be at least 4 characters long!\n";
					}
				}
				else {
					isValid = false;
					errorMessage = "[INVALID_INPUT]: Username cannot be empty or spaces only!\n";
				}
			} while (!isValid);
			return det;
			break;
		case 2:
			isValid = false;
			errorMessage = "";
			do {
				printHeader();
				if (!isFound) {
					if (!errorMessage.empty()) {
						printError(errorMessage);
					}
				}
				printSkyBlue("Enter 0 to exit without changing any data\n");
				std::cout << "Enter new User ID: ";
				std::getline(std::cin >> std::ws, inputTaken);
				if(inputTaken == "0") {
					isValid = true;
					return det;
				}
				else {
					if (inputTaken.length() >= 5) {
						if (!isUserIDExists(inputTaken)) {
							det.id = inputTaken;
							isFound = true;
							isValid = true;
						}
						else {
							isFound = false;
							errorMessage = "[INVALID_INPUT]: This User ID already exists! Try another one.\n";
						}
					}
					else {
						isFound = false;
						errorMessage = "[INVALID_INPUT]: User ID must be at least 5 characters long!\n";
					}
				}
			} while (!isFound || !isValid);
			return det;
			break;
		case 3:
			isValid = false;
			errorMessage = "";
			do {
				printHeader();
				if (!isValid) {
					if (!errorMessage.empty()) {
						printError(errorMessage);
					}
				}
				printBlue("Current Address: " + det.address + "\n");
				printSkyBlue("Enter 0 to exit without changing any data\n");
				std::cout << "Enter new Address: ";
				std::getline(std::cin >> std::ws, inputTaken);
				if(inputTaken == "0") {
					isValid = true;
					return det;
				}
				else {
					if (inputTaken.length() >= 10) {
						det.address = inputTaken;
						isValid = true;
					}
					else {
						isValid = false;
						errorMessage = "[INVALID_INPUT]: Address must be at least 10 characters long!\n";
					}
				}
			} while (!isValid);
			return det;
			break;
		case 4:
			isValid = false;
			errorMessage = "";
			do {
				printHeader();
				if (!isValid) {
					if (!errorMessage.empty()) {
						printError(errorMessage);
					}
				}
				printBlue("Current City: " + det.city + "\n");
				printSkyBlue("Enter 0 to exit without changing any data\n");
				std::cout << "Enter new City: ";
				std::getline(std::cin >> std::ws, inputTaken);
				if(inputTaken == "0") {
					isValid = true;
					return det;
				}
				else {
					if (inputTaken.length() >= 3) {
						det.city = inputTaken;
						isValid = true;
					}
					else {
						isValid = false;
						errorMessage = "[INVALID_INPUT]: City must be at least 3 characters long!\n";
					}
				}
			} while (!isValid);
			return det;
			break;
		case 5:
			isValid = false;
			errorMessage = "";
			do {
				printHeader();
				if (!isValid) {
					if (!errorMessage.empty()) {
						printError(errorMessage);
					}
				}
				printBlue("Current Province: " + det.province + "\n");
				printSkyBlue("Enter 0 to exit without changing any data\n");
				std::cout << "Enter new Province: ";
				std::getline(std::cin >> std::ws, inputTaken);
				if(inputTaken == "0") {
					isValid = true;
					return det;
				}
				else {
					if (inputTaken.length() >= 3) {
						det.province = inputTaken;
						isValid = true;
					}
					else {
						isValid = false;
						errorMessage = "[INVALID_INPUT]: Province must be at least 3 characters long!\n";
					}
				}
			} while (!isValid);
			return det;
			break;
		case 6:
			isValid = false;
			errorMessage = "";
			do {
				printHeader();
				if (!isValid) {
					if (!errorMessage.empty()) {
						printError(errorMessage);
					}
				}
				printBlue("Current Country: " + det.country + "\n");
				printSkyBlue("Enter 0 to exit without changing any data\n");
				std::cout << "Enter new Country: ";
				std::getline(std::cin >> std::ws, inputTaken);
				if(inputTaken == "0") {
					isValid = true;
					return det;
				}
				else {
					if (inputTaken.length() >= 3) {
						det.country = inputTaken;
						isValid = true;
					}
					else {
						isValid = false;
						errorMessage = "[INVALID_INPUT]: Country must be at least 3 characters long!\n";
					}
				}
			} while (!isValid);
			return det;
			break;
		case 7:
			isValid = false;
			errorMessage = "";
			do {
				printHeader();
				if (!isValid) {
					if (!errorMessage.empty()) {
						printError(errorMessage);
					}
				}
				printBlue("Current Contact: " + det.contact + "\n");
				printSkyBlue("Enter 0 to exit without changing any data\n");
				std::cout << "Enter new Contact: ";
				std::getline(std::cin >> std::ws, inputTaken);
				if(inputTaken == "0") {
					isValid = true;
					return det;
				}
				else {
					if (inputTaken.length() >= 10) {
						det.contact = inputTaken;
						isValid = true;
					}
					else {
						isValid = false;
						errorMessage = "[INVALID_INPUT]: Contact must be at least 10 characters long!\n";
					}
				}
			} while (!isValid);
			return det;
			break;

		case 8:
			isValid = false;
			errorMessage = "";
			do {
				printHeader();
				if (!isValid) {
					if (!errorMessage.empty()) {
						printError(errorMessage);
					}
				}
				printBlue("Current Passport NO#: " + det.passport + "\n");
				printSkyBlue("Enter 0 to exit without changing any data\n");
				std::cout << "Enter new Passport NO#: ";
				std::getline(std::cin >> std::ws, inputTaken);
				if(inputTaken == "0") {
					isValid = true;
					return det;
				}
				else {
					if (inputTaken.length() >= 8) {
						det.passport = inputTaken;
						isValid = true;
					}
					else {
						isValid = false;
						errorMessage = "[INVALID_INPUT]: Passport NO# must be at least 8 characters long!\n";
					}
				}
			} while (!isValid);
			return det;
			break;
		case 9:
			isValid = false;
			errorMessage = "";
			do {
				printHeader();
				if (!isValid) {
					if (!errorMessage.empty()) {
						printError(errorMessage);
					}
				}
				printBlue("Current Password: " + det.password + "\n");
				printSkyBlue("Enter 0 to exit without changing any data\n");
				std::cout << "Enter new Password: ";
				std::getline(std::cin >> std::ws, inputTaken);
				if(inputTaken == "0") {
					isValid = true;
					return det;
				}
				else {
					if (inputTaken.length() >= 6) {
						det.password = inputTaken;
						isValid = true;
					}
					else {
						isValid = false;
						errorMessage = "[INVALID_INPUT]: Password must be at least 6 characters long!\n";
					}
				}
			} while (!isValid);
			return det;
			break;
		case 10:
			isValid = false;
			errorMessage = "";
			do {
				printHeader();
				if(!isValid) {
					if (!errorMessage.empty()) {
						printError(errorMessage);
					}
				}
				printBlue("Current Balance: " + std::to_string(det.balance) + "\n");
				printSkyBlue("Enter 0 to exit without changing any data\n");
				std::cout << "Enter new Balance: ";
				std::cin >> inputTaken;
				if(inputTaken == "0") {
					isValid = true;
					return det;
				}
				else {
					try {
						amountInput = std::stoll(inputTaken);
						if(amountInput >= 0) {
							det.balance = amountInput;
							isValid = true;
						}
						else {
							isValid = false;
							errorMessage = "[INVALID_INPUT]: Balance cannot be negative!\n";
						}
					}
					catch (std::invalid_argument&) {
						isValid = false;
						errorMessage = "[INVALID_INPUT]: Please enter a valid numeric value for balance!\n";
					}
					catch (std::out_of_range&) {
						isValid = false;
						errorMessage = "[INVALID_INPUT]: The entered balance is out of range!\n";
					}
				}
			} while (!isValid);
			return det;
			break;

		default:
			return det;
			break;
	}
}

//Function to edit a field and save changes in file
void editAField(std::string userId, UsersDetails det, int type, int noOfBalanceUsers, User users[]) {
	std::ofstream savePassengersFile;
	switch (type) {
		case 1:
			det = getUserDetailsAfterChange(det, 1);
			updateUserDetailsFile(det);
			break;
		case 2:
			det = getUserDetailsAfterChange(det, 2);
			updateUserDetailsFile(det);
			updatePassengersFile(det.id, userId, users, noOfBalanceUsers);
			break;
		case 3:
			det = getUserDetailsAfterChange(det, 3);
			updateUserDetailsFile(det);
			break;
		case 4:
			det = getUserDetailsAfterChange(det, 4);
			updateUserDetailsFile(det);
			break;
		case 5:
			det = getUserDetailsAfterChange(det, 5);
			updateUserDetailsFile(det);
			break;
		case 6:
			det = getUserDetailsAfterChange(det, 6);
			updateUserDetailsFile(det);
			break;
		case 7:
			det = getUserDetailsAfterChange(det, 7);
			updateUserDetailsFile(det);
			break;
		case 8:
			det = getUserDetailsAfterChange(det, 8);
			updateUserDetailsFile(det);
			break;
		case 9:
			det = getUserDetailsAfterChange(det, 9);
			updateUserDetailsFile(det);
			for (int i = 0; i < noOfBalanceUsers; i++) {
				if (users[i].userID == det.id) {
					users[i].password = det.password;
					break;
				}
			}
			savePassengersFile.open("database/passengers.txt");
			if (!savePassengersFile.is_open()) {
				printError("There was an error while saving updated passengers file.\n");
			}
			else {
				for (int i = 0; i < noOfBalanceUsers; i++) {
					savePassengersFile << users[i].userID << " " << users[i].password << "\n";
				}
				printSuccess("Passengers file has been updated with new Password!\n");
				savePassengersFile.close();
			}
			break;

		case 10:
			det = getUserDetailsAfterChange(det, 10);
			updateUserDetailsFile(det);
			break;
		default:
			break;
	}
}

//Edit Users Details
void editUserDetails(User* users, int noOfUsers, int noOfBalanceUsers) {
	bool isValid = false;
	std::string userId;
	std::string errorMessage = "";
	do {
		displayUsersWithIDs(users, noOfUsers);
		if (!isValid) {
			if (!errorMessage.empty()) {
				printError(errorMessage);
			}
		}
		std::cout << "Enter ID of the user you want to change: ";
		std::cin >> userId;
		for (int i = 0; i < noOfUsers; i++) {
			if (userId == users[i].userID) {
				isValid = true;
				break;
			}
		}
		if (!isValid) {
			errorMessage = "[INVALID_INPUT]: This ID does not exist!\n";
		}
	} while (!isValid);

	UsersDetails userDetails = getDetailsForOneUser(userId, noOfBalanceUsers, users, noOfUsers);

	if (userDetails.userName.empty()) {
		printError("Warning: No detailed data found for this user.\n");
		printSkyBlue("You are about to create new data for User ID: " + userId + "\n");
		userDetails.id = userId;
		if (userDetails.password.empty()) {
			userDetails.password = "pass123";
		}
		userDetails.userName = "New User";
		userDetails.address = "Not Set";
		userDetails.city = "Not Set";
		userDetails.province = "Not Set";
		userDetails.country = "Not Set";
		userDetails.contact = "Not Set";
		userDetails.passport = "Not Set";
		userDetails.balance = 0;
		updateUserDetailsFile(userDetails);
		printSuccess("New user details created with default values. You can edit them now.\n");
	}

	isValid = false;
	errorMessage = "";
	int changeCoice = 0;
	do {
		printHeader();
		printBlue("-------------- USER DETAILS --------------\n");
		std::cout << "\t1. UserName:     " + userDetails.userName << std::endl;
		std::cout << "\t2. ID:           " + userDetails.id << std::endl;
		std::cout << "\t3. Address:      " + userDetails.address << std::endl;
		std::cout << "\t4. City:         " + userDetails.city << std::endl;
		std::cout << "\t5. Province:     " + userDetails.province << std::endl;
		std::cout << "\t6. Country:      " + userDetails.country << std::endl;
		std::cout << "\t7. Contact:      " + userDetails.contact << std::endl;
		std::cout << "\t8. Passport NO#: " + userDetails.passport << std::endl;
		std::cout << "\t9. Password:     " + userDetails.password << std::endl;
		std::cout << "\t10. Balance:     " + std::to_string(userDetails.balance) << std::endl;
		std::cout << "Enter a number to change/edit that thing (1-10): ";
		changeCoice = getValidInteger(1, 10, isValid);
	} while (!isValid);

	editAField(userId, userDetails, changeCoice, noOfBalanceUsers, users);
}

//Function to show header while creating a new user
void viewCreateNewUserHeader(UsersDetails newUserDetails, int detailsTaken) {
	printHeader();
	printSuccess("--------------- ADDING A NEW USER ---------------\n\n");
	printSkyBlue("Enter 0 at any point to cancel adding a new user.\n");
	printBlue("Details you have entered so far: " + std::to_string(detailsTaken) + "/10\n");
	if (!newUserDetails.userName.empty()) {
		printBlue("\tUsername: " + newUserDetails.userName + "\n");
	}
	if (!newUserDetails.id.empty()) {
		printBlue("\tUser ID: " + newUserDetails.id + "\n");
	}
	if (!newUserDetails.address.empty()) {
		printBlue("\tAddress: " + newUserDetails.address + "\n");
	}
	if (!newUserDetails.city.empty()) {
		printBlue("\tCity: " + newUserDetails.city + "\n");
	}
	if (!newUserDetails.province.empty()) {
		printBlue("\tProvince: " + newUserDetails.province + "\n");
	}
	if (!newUserDetails.country.empty()) {
		printBlue("\tCountry: " + newUserDetails.country + "\n");
	}
	if (!newUserDetails.contact.empty()) {
		printBlue("\tContact: " + newUserDetails.contact + "\n");
	}
	if (!newUserDetails.passport.empty()) {
		printBlue("\tPassport NO#: " + newUserDetails.passport + "\n");
	}
	if (!newUserDetails.password.empty()) {
		printBlue("\tPassword: " + newUserDetails.password + "\n");
	}
	if (newUserDetails.balance != 0) {
		printBlue("\tBalance: " + std::to_string(newUserDetails.balance) + "\n");
	}
}

//This function check if function is exited or not
bool checkBreakFunction(int detailsTaken, UsersDetails newUserDetails) {
	switch (detailsTaken) {
	case 0:
		if (newUserDetails.userName == "") {
			printError("You canceled the creation of new User!\n");
			printYellow("Press any ket to exit!\n");
			return true;
		}
		else {
			return false;
		}
		break;
	case 1:
		if (newUserDetails.id == "") {
			printError("You canceled the creation of new User!\n");
			printYellow("Press any ket to exit!\n");
			return true;
		}
		else {
			return false;
		}
		break;
	case 2:
		if (newUserDetails.address == "") {
			printError("You canceled the creation of new User!\n");
			printYellow("Press any ket to exit!\n");
			return true;
		}
		else {
			return false;
		}
		break;
	case 3:
		if (newUserDetails.city == "") {
			printError("You canceled the creation of new User!\n");
			printYellow("Press any ket to exit!\n");
			return true;
		}
		else {
			return false;
		}
		break;
	case 4:
		if (newUserDetails.province == "") {
			printError("You canceled the creation of new User!\n");
			printYellow("Press any ket to exit!\n");
			return true;
		}
		else {
			return false;
		}
		break;
	case 5:
		if (newUserDetails.country == "") {
			printError("You canceled the creation of new User!\n");
			printYellow("Press any ket to exit!\n");
			return true;
		}
		else {
			return false;
		}
		break;
	case 6:
		if (newUserDetails.contact == "") {
			printError("You canceled the creation of new User!\n");
			printYellow("Press any ket to exit!\n");
			return true;
		}
		else {
			return false;
		}
		break;
	case 7:
		if (newUserDetails.passport == "") {
			printError("You canceled the creation of new User!\n");
			printYellow("Press any ket to exit!\n");
			return true;
		}
		else {
			return false;
		}
		break;
	case 8:
		if (newUserDetails.password == "") {
			printError("You canceled the creation of new User!\n");
			printYellow("Press any ket to exit!\n");
			return true;
		}
		else {
			return false;
		}
		break;
	case 9:
		if (newUserDetails.balance == 0) {
			printError("You canceled the creation of new User!\n");
			printYellow("Press any ket to exit!\n");
			return true;
		}
		else {
			return false;
		}
		break;
	default:
		return false;
		break;
	}
}

//Function to input all inputs for new user
UsersDetails getAllInputsForNewUser(UsersDetails newUserDetails, int detailsTaken) {
	bool isValid = false;
	std::string errorMessage = "";
	std::string inputTaken;
	long long balance;
	switch (detailsTaken) {
	case 0:
		do {
			viewCreateNewUserHeader(newUserDetails, detailsTaken);
			if(!isValid){
				if(!errorMessage.empty()){
					printError(errorMessage);
				}
			}
			std::cout << "Enter Username: ";
			std::getline(std::cin >> std::ws, inputTaken);
			if(inputTaken == "0"){
				return newUserDetails;
			}
			if(inputTaken.empty()) {
				errorMessage = "[ERROR]: Username cannot be empty!\n";
				isValid = false;
			}else if(inputTaken.length() <5) {
				errorMessage = "[ERROR]: Username must be at least 5 characters long!\n";
				isValid = false;
			}else {
				isValid = true;
				newUserDetails.userName = inputTaken;
				return newUserDetails;
				break;
			}
		} while (!isValid);
		break;
	case 1:
		do {
			viewCreateNewUserHeader(newUserDetails, detailsTaken);
			if(!isValid){
				if(!errorMessage.empty()){
					printError(errorMessage);
				}
			}
			std::cout << "Enter User ID: ";
			std::getline(std::cin >> std::ws, inputTaken);
			if(inputTaken == "0"){
				return newUserDetails;
			}
			if(inputTaken.empty()) {
				errorMessage = "[ERROR]: User ID cannot be empty!\n";
				isValid = false;
			}else if(inputTaken.length() <5) {
				errorMessage = "[ERROR]: User ID must be at least 5 characters long!\n";
				isValid = false;
			}else if(isUserIDExists(inputTaken)) {
				errorMessage = "[ERROR]: User ID already exists!\n";
				isValid = false;
			}else {
				isValid = true;
				newUserDetails.id = inputTaken;
				return newUserDetails;
				break;
			}
		} while (!isValid);
		break;
	case 2:
		do {
			viewCreateNewUserHeader(newUserDetails, detailsTaken);
			if(!isValid){
				if(!errorMessage.empty()){
					printError(errorMessage);
				}
			}
			std::cout << "Enter Address: ";
			std::getline(std::cin >> std::ws, inputTaken);
			if(inputTaken == "0"){
				return newUserDetails;
			}
			if(inputTaken.empty()) {
				errorMessage = "[ERROR]: Address cannot be empty!\n";
				isValid = false;
			}else if(inputTaken.length() <10) {
				errorMessage = "[ERROR]: Address must be at least 10 characters long!\n";
				isValid = false;
			}else {
				isValid = true;
				newUserDetails.address = inputTaken;
				return newUserDetails;
				break;
			}
		} while (!isValid);
		break;
	case 3:
		do {
			viewCreateNewUserHeader(newUserDetails, detailsTaken);
			if(!isValid){
				if(!errorMessage.empty()){
					printError(errorMessage);
				}
			}
			std::cout << "Enter City: ";	
			std::getline(std::cin >> std::ws, inputTaken);	
			if(inputTaken == "0"){
				return newUserDetails;
			}
			if(inputTaken.empty()) {
				errorMessage = "[ERROR]: City cannot be empty!\n";
				isValid = false;
			}else if(inputTaken.length() <5) {
				errorMessage = "[ERROR]: City must be at least 5 characters long!\n";
				isValid = false;
			}else {
				isValid = true;
				newUserDetails.city = inputTaken;
				return newUserDetails;
				break;
			}
		} while (!isValid);
		break;
	case 4:
		do {
			viewCreateNewUserHeader(newUserDetails, detailsTaken);
			if(!isValid){
				if(!errorMessage.empty()){
					printError(errorMessage);
				}
			}
			std::cout << "Enter Province: ";
			std::getline(std::cin >> std::ws, inputTaken);
			if(inputTaken == "0"){
				return newUserDetails;
			}
			if(inputTaken.empty()) {
				errorMessage = "[ERROR]: Province cannot be empty!\n";
				isValid = false;
			}else if(inputTaken.length() <5) {
				errorMessage = "[ERROR]: Province must be at least 5 characters long!\n";
				isValid = false;
			}else {
				isValid = true;
				newUserDetails.province = inputTaken;
				return newUserDetails;
				break;
			}
		} while (!isValid);
		break;
	case 5:
		do {
			viewCreateNewUserHeader(newUserDetails, detailsTaken);
			if(!isValid){
				if(!errorMessage.empty()){
					printError(errorMessage);
				}
			}
			std::cout << "Enter Country: ";
			std::getline(std::cin >> std::ws, inputTaken);
			if(inputTaken == "0"){
				return newUserDetails;
			}
			if(inputTaken.empty()) {
				errorMessage = "[ERROR]: Country cannot be empty!\n";
				isValid = false;
			}else if(inputTaken.length() <5) {
				errorMessage = "[ERROR]: Country must be at least 5 characters long!\n";
				isValid = false;
			}else {
				isValid = true;
				newUserDetails.country = inputTaken;
				return newUserDetails;
				break;
			}
		} while (!isValid);
		break;
	case 6:
		do {
			viewCreateNewUserHeader(newUserDetails, detailsTaken);
			if(!isValid){
				if(!errorMessage.empty()){
					printError(errorMessage);
				}
			}
			std::cout << "Enter Contact: ";
			std::getline(std::cin >> std::ws, inputTaken);
			if(inputTaken == "0"){
				return newUserDetails;
			}
			if(inputTaken.empty()) {
				errorMessage = "[ERROR]: Contact cannot be empty!\n";
				isValid = false;
			}else if(inputTaken.length() <10) {
				errorMessage = "[ERROR]: Contact must be at least 10 characters long!\n";
				isValid = false;
			}else {
				isValid = true;
				newUserDetails.contact = inputTaken;
				return newUserDetails;
				break;
			}
		} while (!isValid);
		break;
	case 7:
		do {
			viewCreateNewUserHeader(newUserDetails, detailsTaken);
			if(!isValid){
				if(!errorMessage.empty()){
					printError(errorMessage);
				}
			}
			std::cout << "Enter Passport NO#: ";
			std::getline(std::cin >> std::ws, inputTaken);	
			if(inputTaken == "0"){
				return newUserDetails;
			}
			if(inputTaken.empty()) {
				errorMessage = "[ERROR]: Passport NO# cannot be empty!\n";
				isValid = false;
			}else if(inputTaken.length() <5) {
				errorMessage = "[ERROR]: Passport NO# must be at least 5 characters long!\n";
				isValid = false;
			}else {
				isValid = true;
				newUserDetails.passport = inputTaken;
				return newUserDetails;
				break;
			}
		} while (!isValid);
		break;
	case 8:
		do {
			viewCreateNewUserHeader(newUserDetails, detailsTaken);
			if(!isValid){
				if(!errorMessage.empty()){
					printError(errorMessage);
				}
			}
			std::cout << "Enter Password: ";
			std::getline(std::cin >> std::ws, inputTaken);
			if(inputTaken == "0"){
				return newUserDetails;
			}
			if(inputTaken.empty()) {
				errorMessage = "[ERROR]: Password cannot be empty!\n";
				isValid = false;
			}else if(inputTaken.length() <5) {
				errorMessage = "[ERROR]: Password must be at least 5 characters long!\n";
				isValid = false;
			}else {
				isValid = true;
				newUserDetails.password = inputTaken;
				return newUserDetails;
				break;
			}
		} while (!isValid);
		break;
	case 9:
		do {
			viewCreateNewUserHeader(newUserDetails, detailsTaken);
			if(!isValid){
				if(!errorMessage.empty()){
					printError(errorMessage);
				}
			}
			std::cout << "Enter Balance: ";
			if(std::cin>>balance){
				if(balance < 0) {
					errorMessage = "[ERROR]: Balance cannot be negative!\n";
					isValid = false;
				}else {
					isValid = true;
					newUserDetails.balance = balance;
					return newUserDetails;
					break;
				}
			}else{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				errorMessage = "[ERROR]: Balance must be a numeric value!\n";
				isValid = false;
			}

		} while (!isValid);
		break;
	default:
		break;
	}
	return newUserDetails;
}

//Function to add a new user
void addUser(int& noOfUsers, User*& users, int& noOfBalanceUsers, UserBalance*& userBalances) {
	UsersDetails newUserDetails = { "", "", "", "", "", "", "", "", "", 0 };
	int detailsTaken = 0;
	for (detailsTaken; detailsTaken < 10; detailsTaken++) {
		newUserDetails = getAllInputsForNewUser(newUserDetails, detailsTaken);
		if (checkBreakFunction(detailsTaken, newUserDetails)) {
			break;
		}
	}
	if(detailsTaken == 10) {
		int originalNoOfUsers = noOfBalanceUsers;
		
		std::ofstream savePassengersFile;
		savePassengersFile.open("database/passengers.txt");
		if (!savePassengersFile.is_open()) {
			printError("There was an error while saving updated passengers file.\n");
		}
		else {
			for (int i = 0; i < originalNoOfUsers; i++) {
				savePassengersFile << users[i].userID << " " << users[i].password << "\n";
			}
			savePassengersFile << newUserDetails.id << " " << newUserDetails.password << "\n";
			printSuccess("Passengers file has been updated with new Password!\n");
			savePassengersFile.close();
		}

		std::ofstream saveUserBalanceFile("database/users-balance.txt");
		if(!saveUserBalanceFile.is_open()) {
			printError("There was an error while saving updated users-balance file.\n");
		}
		else {
			for(int i = 0; i < originalNoOfUsers; i++) {
				saveUserBalanceFile << userBalances[i].userId << " " << userBalances[i].balance << "\n";
			}
			saveUserBalanceFile << newUserDetails.id << " " << newUserDetails.balance << "\n";
			printSuccess("Users-balance file has been updated with new Password!\n");
			saveUserBalanceFile.close();
		}

		updateUserDetailsFile(newUserDetails);
		
		User* newUsersArray = new User[noOfUsers + 1];
        for(int i=0; i<noOfUsers; i++) newUsersArray[i] = users[i];
        newUsersArray[noOfUsers].userID = newUserDetails.id;
        newUsersArray[noOfUsers].password = newUserDetails.password;
        delete[] users;
        users = newUsersArray;
        noOfUsers++;


        UserBalance* newBalArray = new UserBalance[noOfBalanceUsers + 1];
        for(int i=0; i<noOfBalanceUsers; i++) newBalArray[i] = userBalances[i];
        newBalArray[noOfBalanceUsers].userId = newUserDetails.id;
        newBalArray[noOfBalanceUsers].balance = newUserDetails.balance;
        delete[] userBalances;
        userBalances = newBalArray;
        noOfBalanceUsers++;

        printSuccess("User added successfully to System!\n");
	}
}

//Function to manage users
void manageUsers(int& noOfBalanceUsers, User*& users, int& noOfUsers, UserBalance*& userBalances) {
	int choice = showManageUsersMenu();
	switch (choice)
	{
	case 1:
		viewAllUsersData(noOfBalanceUsers);
		break;
	case 2:
		editUserDetails(users, noOfUsers, noOfBalanceUsers);
		break;
	case 3:
		addUser(noOfUsers, users, noOfBalanceUsers, userBalances);
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