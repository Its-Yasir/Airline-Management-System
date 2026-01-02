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

		printSkyBlue("Chose an option from the below(1-5): \n");
		std::cout << "1. Manage Users =>\n";
		std::cout << "2. Manage Flight Inventory =>\n";
		std::cout << "3. View Reservation Reports =>\n";
		std::cout << "4. Show Analytic =>\n";
		printError("5. <= Exit\n");
		std::cin >> choice;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			choice = 0;
		}

		if (choice < 1 || choice > 6) {
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
	showLoading("Loading Users Data");
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
	std::string inputIDClean = cleanString(userDetail.id);
	for (int i = 0; i < loadedCount; i++) {
		if (allUserDetails[i].id == inputIDClean) {
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

//This function to confirm deletion of user
bool confirmDeleteUser(int& noOfUsers, std::string userId, User* users, int& noOfBalanceUsers, UserBalance* userBalances){
	bool isValid = false;
	std::string errorMessage = "";
	char confirmation;
	do {
		std::cout << "Are you sure you want to delete User ID: " << userId << "? (y/n): ";
		std::cin >> confirmation;
		if (confirmation == 'y' || confirmation == 'Y') {
			isValid = true;
			return isValid;
			break;
		}
		else if (confirmation == 'n' || confirmation == 'N') {
			return false;
		}
		else {
			isValid = false;
			errorMessage = "[INVAID_INPUT]: Please enter 'y' for yes or 'n' for no.\n";
		}
	} while (!isValid);
}

//This function deleted user from file and update users and user balances arrays
void deleteUser(
	int& noOfUsers,
	User*& users,
	int& noOfBalanceUsers,
	UserBalance*& userBalances,
	std::string userId,
	Flight* flights,
	int& noOfFlights,
	SelectedFlight* userbookings
) {
	// Create temp array and copy all users except the one to delete
	User* tempArrUsers = new User[noOfUsers - 1];
	int tempIndex = 0;
	for (int i = 0; i < noOfUsers; i++) {
		if (!(userId == users[i].userID)) {
			tempArrUsers[tempIndex] = users[i];
			tempIndex++;
		}
	}

	delete[] users;
	users = tempArrUsers;
	noOfUsers--;

	std::ofstream savePassengersFile("database/passengers.txt");
	if (!savePassengersFile.is_open()) {
		printError("There was an error while saving updated passengers file.\n");
	}
	else {
		for (int i = 0; i < noOfUsers; i++) {
			savePassengersFile << users[i].userID << " " << users[i].password << "\n";
		}
		savePassengersFile.close();
		printSuccess("Passengers file has been updated with new Password!\n");
	}

	// Create temp array and copy all user balances except the one to delete
	UserBalance* tempUserBalanceArr = new UserBalance[noOfBalanceUsers - 1];
	tempIndex = 0;
	for (int i = 0; i < noOfBalanceUsers; i++) {
		if (!(userId == userBalances[i].userId)) {
			tempUserBalanceArr[tempIndex] = userBalances[i];
			tempIndex++;
		}
	}

	delete[] userBalances;
	userBalances = tempUserBalanceArr;
	noOfBalanceUsers--;

	std::ofstream saveUserBalanceFile("database/users-balance.txt");
	if (!saveUserBalanceFile.is_open()) {
		printError("There was an error while saving updated users-balance file.\n");
	}
	else {
		for (int i = 0; i < noOfBalanceUsers; i++) {
			saveUserBalanceFile << userBalances[i].userId << " " << userBalances[i].balance << "\n";
		}
		saveUserBalanceFile.close();
		printSuccess("Users-balance file has been updated with new Password!\n");
	}


	UsersDetails* allUserDetails = new UsersDetails[noOfUsers];

	std::ifstream loadUserDetailsFile("database/users-extra-data.txt");
	if (!loadUserDetailsFile.is_open())
		printError("There was an error while loading users-extra-data.txt file.\n");
	else {
		std::string line;
		int count = 0;
		while (std::getline(loadUserDetailsFile, line)) {
			std::stringstream ss(line);
			std::string username, userID, address, city, province, country, phone, passport, balance, password;

			// Read all fields first
			std::getline(ss, username, '|');
			std::getline(ss, userID, '|');
			std::getline(ss, address, '|');
			std::getline(ss, city, '|');
			std::getline(ss, province, '|');
			std::getline(ss, country, '|');
			std::getline(ss, phone, '|');
			std::getline(ss, passport, '|');
			std::getline(ss, password, '|');
			std::getline(ss, balance, '|');

			// Only add to array if it's not the user to delete
			if(userID != userId) {
				allUserDetails[count] = {
					username,
					userID,
					address,
					city,
					province,
					country,
					phone,
					passport,
					password,
					std::stoll(balance)
				};
				count++;
			}
		}
		loadUserDetailsFile.close();
	}

	std::ofstream saveUserDetailsFile("database/users-extra-data.txt");
	if(!saveUserDetailsFile.is_open()) {
		printError("There was an error while saving updated user-details file.\n");
	}
	else {
		for(int i = 0; i < noOfUsers; i++) {
			saveUserDetailsFile <<
				allUserDetails[i].userName << "|"
				<< allUserDetails[i].id << "|"
				<< allUserDetails[i].address << "|"
				<< allUserDetails[i].city << "|"
				<< allUserDetails[i].province << "|"
				<< allUserDetails[i].country << "|"
				<< allUserDetails[i].contact << "|"
				<< allUserDetails[i].passport << "|"
				<< allUserDetails[i].password << "|"
				<< allUserDetails[i].balance << "\n";
		}
		saveUserDetailsFile.close();
		printSuccess("User-details file has been updated with new Password!\n");
	}
	
	delete[] allUserDetails;
}

//Function to remove a user
void removeUser(int& noOfUsers, User*& users, int& noOfBalanceUsers, UserBalance*& userBalances, Flight* flights, int& noOfFlights, SelectedFlight* userbookings){
	bool isValid = false;
	std::string userId;
	std::string errorMessage = "";
	do{
		if (!isValid) {
			if(!errorMessage.empty()){
				printError(errorMessage);
			}
		}
		displayUsersWithIDs(users, noOfUsers);
		std::cout << "Enter User ID to remove: ";
		std::cin >> userId;
		if (isUserIDExists(userId)) {
			isValid = true;
			break;
		} else {
			errorMessage = "User ID does not exist!\n";
			isValid = false;
		}
	} while (!isValid);

	if (confirmDeleteUser(noOfUsers, userId, users, noOfBalanceUsers, userBalances)) {
		deleteUser(noOfUsers, users, noOfBalanceUsers, userBalances, userId, flights, noOfFlights, userbookings);
	}
	else {
		printSuccess("User deletion canceled.\n");
		std::cout << "Press any key to exit!\n";
		return;
	}

}

//Function to manage users
void manageUsers(int& noOfBalanceUsers, User*& users, int& noOfUsers, UserBalance*& userBalances, Flight* flights, int noOfFlights, SelectedFlight* userbookings) {
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
	case 4:
		removeUser(noOfUsers, users, noOfBalanceUsers, userBalances, flights, noOfFlights, userbookings);
		break;
	default:
		break;
	}
}

//Function to print add flight header
void printAddFlightHeader(Flight flight) {
	printHeader();
	printBlue("--------------- ADD NEW FLIGHT ---------------\n\n");
	printSkyBlue("Enter -1 at any point to cancel adding a new flight.\n");
	if (!flight.id.empty()) {
		printBlue("Flight ID: " + flight.id + "\n");
	}
	if(!flight.origin.empty()) {
		printBlue("Origin City: " + flight.origin + "\n");
	}
	if(!flight.destination.empty()) {
		printBlue("Departure City: " + flight.destination+ "\n");
	}
	if (!flight.depTime.empty()) {
		printBlue("Departure Time: " + flight.depTime+ "\n");
	}
	if (!flight.arrTime.empty()) {
		printBlue("Arrival Time: " + flight.arrTime+ "\n");
	}
	if (flight.seatsEco != -1) {
		printBlue("Seats for Economy Class: " + std::to_string(flight.seatsEco) + "\n");
	}
	if (flight.seatsBus != -1) {
		printBlue("Seats for Business Class: " + std::to_string(flight.seatsBus) + "\n");
	}
	if (flight.seatsFirst!= -1) {
		printBlue("Seats for First Class: " + std::to_string(flight.seatsFirst) + "\n");
	}
	if(flight.priceEco != -1) {
		printBlue("Price for Economy Class: " + std::to_string(flight.priceEco) + "\n");
	}
	if(flight.priceBus != -1) {
		printBlue("Price for Business Class: " + std::to_string(flight.priceBus) + "\n");
	}
	if(flight.priceFirst != -1) {
		printBlue("Price for First Class: " + std::to_string(flight.priceFirst) + "\n");
	}
	if (flight.refund != -1) {
		printBlue("Refund percentage(%) : " + std::to_string(flight.refund) + "\n");
	}

}

// This function checks wether a flight ID already exists
bool isFlightIDExists(std::string flightID) {
	std::ifstream loadFlightsFile("database/flights.txt");
	if (!loadFlightsFile.is_open()) {
		printError("There was an error while loading flights file.\n");
		return false;
	}
	else {
		std::string line;
		while (std::getline(loadFlightsFile, line)) {
			std::stringstream sss(line);
			std::string id;
			std::getline(sss, id, ' ');
			if (id == flightID) {
				loadFlightsFile.close();
				return true;
			}
		}
		loadFlightsFile.close();
		return false;
	}
}

//Function to input flight details required to add a new flight
Flight getAllInputsForNewFlight(Flight flight, int detailsTaken) {
	bool isValid = false;
	std::string errorMessage = "";
	std::string inputTaken;
	long long numbericInputs = 0;
	switch (detailsTaken) {
	case 1:
		do {
			printAddFlightHeader(flight);
			if (!isValid) {
				if (!errorMessage.empty()) {
					printError(errorMessage);
				}
			}
			std::cout << "Enter Flight ID: ";
			std::getline(std::cin >> std::ws, inputTaken);
			if (inputTaken == "-1") {
				return flight;
			}
			if (inputTaken.empty()) {
				errorMessage = "[ERROR]: Flight ID cannot be empty!\n";
				isValid = false;
			}
			else if (inputTaken.length() < 4) {
				errorMessage = "[ERROR]: Flight ID must be at least 4 characters long!\n";
				isValid = false;
			}
			else if (isFlightIDExists(inputTaken)) {
				errorMessage = "[ERROR]: Flight ID already exists!\n";
				isValid = false;
			}
			else {
				isValid = true;
				flight.id = inputTaken;
				return flight;
				break;
			}
		} while (!isValid);
		break;
	case 2:
		do {
			printAddFlightHeader(flight);
			if (!isValid) {
				if (!errorMessage.empty()) {
					printError(errorMessage);
				}
			}
			std::cout << "Enter Origin City: ";
			std::getline(std::cin >> std::ws, inputTaken);
			if (inputTaken == "-1") {
				return flight;
			}
			if (inputTaken.empty()) {
				errorMessage = "[ERROR]: Origin City cannot be empty!\n";
				isValid = false;
			}
			else if (inputTaken.length() < 5) {
				errorMessage = "[ERROR]: Origin City must be at least 5 characters long!\n";
				isValid = false;
			}
			else {
				isValid = true;
				flight.origin = inputTaken;
				return flight;
				break;
			}
		} while (!isValid);
		break;
	case 3:
		do {
			printAddFlightHeader(flight);
			if (!isValid) {
				if (!errorMessage.empty()) {
					printError(errorMessage);
				}
			}
			std::cout << "Enter Destination: ";
			std::getline(std::cin >> std::ws, inputTaken);
			if (inputTaken == "-1") {
				return flight;
			}
			if (inputTaken.empty()) {
				errorMessage = "[ERROR]: Destination cannot be empty!\n";
				isValid = false;
			}
			else if (inputTaken.length() < 3) {
				errorMessage = "[ERROR]: Destination must be at least 3 characters long!\n";
				isValid = false;
			}
			else {
				isValid = true;
				flight.destination = inputTaken;
				return flight;
				break;
			}
		} while (!isValid);
		break;
	case 4:
		do {
			printAddFlightHeader(flight);
			if (!isValid) {
				if (!errorMessage.empty()) {
					printError(errorMessage);
				}
			}
			printYellow("Format 12Dec-02:00PM\n");
			std::cout << "Enter Departure Time: ";
			std::getline(std::cin >> std::ws, inputTaken);
			if (inputTaken == "-1") {
				return flight;
			}
			if (inputTaken.empty()) {
				errorMessage = "[ERROR]: Departure Time cannot be empty!\n";
				isValid = false;
			}
			else if (inputTaken.length() < 5) {
				errorMessage = "[ERROR]: Departure Time must be at least 5 characters long!\n";
				isValid = false;
			}
			else {
				isValid = true;
				flight.depTime = inputTaken;
				return flight;
				break;
			}
		} while (!isValid);
		break;
	case 5:
		do {
			printAddFlightHeader(flight);
			if (!isValid) {
				if (!errorMessage.empty()) {
					printError(errorMessage);
				}
			}
			printYellow("Format 12Dec-02:00PM\n");
			std::cout << "Enter Arrival Time: ";
			std::getline(std::cin >> std::ws, inputTaken);
			if (inputTaken == "-1") {
				return flight;
			}
			if (!(std::cin >> numbericInputs)) {
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				errorMessage = "[ERROR]: Invalid input! Please enter a numeric value.\n";
				isValid = false;
			}
			else if (numbericInputs == -1) {
				return flight;
			}
			else if (inputTaken.length() < 5) {
				errorMessage = "[ERROR]: Arrival Time must be at least 5 characters long!\n";
				isValid = false;
			}
			else {
				isValid = true;
				flight.arrTime= inputTaken;
				return flight;
				break;
			}
		} while (!isValid);
		break;
	case 6:
		do {
			printAddFlightHeader(flight);
			if (!isValid) {
				if (!errorMessage.empty()) {
					printError(errorMessage);
				}
			}
			std::cout << "Enter Fare for Economy Class: ";
			std::cin >> numbericInputs;
			if (!(std::cin >> numbericInputs)) {
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				errorMessage = "[ERROR]: Invalid input! Please enter a numeric value.\n";
				isValid = false;
			}
			else if (numbericInputs == -1) {
				return flight;
			}
			else if (numbericInputs < 10000) {
				errorMessage = "[ERROR]: Fare for Economy Class cannot be less than 10000!\n";
				isValid = false;
			}
			else {
				isValid = true;
				flight.priceEco = numbericInputs;
				return flight;
				break;
			}
		} while (!isValid);
		break;
	case 7:
		do {
			printAddFlightHeader(flight);
			if (!isValid) {
				if (!errorMessage.empty()) {
					printError(errorMessage);
				}
			}
			std::cout << "Enter Fare for Business Class: ";
			std::cin >> numbericInputs;
			if (!(std::cin >> numbericInputs)) {
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				errorMessage = "[ERROR]: Invalid input! Please enter a numeric value.\n";
				isValid = false;
			}
			else if (numbericInputs == -1) {
				return flight;
			}
			else if (numbericInputs < 15000) {
				errorMessage = "[ERROR]: Fare for Business Class cannot be less than 15000!\n";
				isValid = false;
			}
			else {
				isValid = true;
				flight.priceBus = numbericInputs;
				return flight;
				break;
			}
		} while (!isValid);
		break;
	case 8:
		do {
			printAddFlightHeader(flight);
			if (!isValid) {
				if (!errorMessage.empty()) {
					printError(errorMessage);
				}
			}
			std::cout << "Enter Fare for First Class: ";
			std::cin >> numbericInputs;
			if (!(std::cin >> numbericInputs)) {
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				errorMessage = "[ERROR]: Invalid input! Please enter a numeric value.\n";
				isValid = false;
			}
			else if (numbericInputs == -1) {
				return flight;
			}
			else if (numbericInputs < 20000) {
				errorMessage = "[ERROR]: Fare for First Class cannot be less than 20000!\n";
				isValid = false;
			}
			else {
				isValid = true;
				flight.priceFirst = numbericInputs;
				return flight;
				break;
			}
		} while (!isValid);
		break;
	case 9:
		do {
			printAddFlightHeader(flight);
			if (!isValid) {
				if (!errorMessage.empty()) {
					printError(errorMessage);
				}
			}
			std::cout << "Enter Seats for Economy Class: ";
			std::cin >> numbericInputs;
			if (!(std::cin >> numbericInputs)) {
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				errorMessage = "[ERROR]: Invalid input! Please enter a numeric value.\n";
				isValid = false;
			}
			else if (numbericInputs == -1) {
				return flight;
			}
			else if (numbericInputs > 450) {
				errorMessage = "[ERROR]: Seats for Economy Class cannot be more than 450!\n";
				isValid = false;
			}
			else {
				isValid = true;
				flight.seatsEco = int(numbericInputs);
				return flight;
				break;
			}
		} while (!isValid);
		break;
	case 10:
		do {
			printAddFlightHeader(flight);
			if (!isValid) {
				if (!errorMessage.empty()) {
					printError(errorMessage);
				}
			}
			std::cout << "Enter Seats for Business Class: ";
			std::cin >> numbericInputs;
			if (!(std::cin >> numbericInputs)) {
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				errorMessage = "[ERROR]: Invalid input! Please enter a numeric value.\n";
				isValid = false;
			}
			else if (numbericInputs == -1) {
				return flight;
			}
			else if (numbericInputs > 60) {
				errorMessage = "[ERROR]: Seats for Business Class cannot be more than 60!\n";
				isValid = false;
			}
			else {
				isValid = true;
				flight.seatsBus = int(numbericInputs);
				return flight;
				break;
			}
		} while (!isValid);
		break;
	case 11:
		do {
			printAddFlightHeader(flight);
			if (!isValid) {
				if (!errorMessage.empty()) {
					printError(errorMessage);
				}
			}
			std::cout << "Enter Seats for First Class: ";
			std::cin >> numbericInputs;
			if (!(std::cin >> numbericInputs)) {
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				errorMessage = "[ERROR]: Invalid input! Please enter a numeric value.\n";
				isValid = false;
			}
			else if (numbericInputs == -1) {
				return flight;
			}
			else if (numbericInputs > 16) {
				errorMessage = "[ERROR]: Seats for First Class cannot be more than 16!\n";
				isValid = false;
			}
			else {
				isValid = true;
				flight.seatsFirst = int(numbericInputs);
				return flight;
				break;
			}
		} while (!isValid);
		break;
	case 12:
		do {
			printAddFlightHeader(flight);
			if (!isValid) {
				if (!errorMessage.empty()) {
					printError(errorMessage);
				}
			}
			std::cout << "Enter Refund for this flight: ";
			std::cin >> numbericInputs;
			if (!(std::cin >> numbericInputs)) {
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				errorMessage = "[ERROR]: Invalid input! Please enter a numeric value.\n";
				isValid = false;
			}
			else if (numbericInputs == -1) {
				return flight;
			}
			else if (numbericInputs > 100) {
				errorMessage = "[ERROR]: Refund cannot be more than 100%!\n";
				isValid = false;
			}else if( numbericInputs < 0 ){
				errorMessage = "[ERROR]: Refund cannot be less than 0%!\n";
				isValid = false;
			}
			else {
				isValid = true;
				flight.refund = int(numbericInputs);
				return flight;
				break;
			}
		} while (!isValid);
		break;
	default:
		break;
	}
	return flight;
}

//This function adds a new flight in file
bool addFlightToFile(Flight newFlight) {
	std::ofstream loadFlightsFile("database/flights.txt", std::ios::app);

	if (!loadFlightsFile.is_open()) {
		printError("[ERROR]: Unable to open file!");
		return false;
	}

	loadFlightsFile << newFlight.id << " "
		<< newFlight.origin << " "
		<< newFlight.destination << " "
		<< newFlight.depTime << " "
		<< newFlight.arrTime << " "
		<< newFlight.seatsEco << " "
		<< newFlight.seatsBus << " "
		<< newFlight.seatsFirst << " "
		<< newFlight.priceEco << " "
		<< newFlight.priceBus << " "
		<< newFlight.priceFirst << " "
		<< newFlight.refund << "\n";
	loadFlightsFile.close();
	return true;
}

//This function will update flights file
bool updateFlightToFile(Flight* flights, Flight flight, int noOfFlights) {
	std::ofstream loadFlightsFile("database/flights.txt", std::ios::out);
	if (!loadFlightsFile.is_open()) {
		printError("[ERROR]: Unable to open file!");
		return false;
	}
	for (int i = 0; i < noOfFlights; i++) {
		if (flights[i].id == flight.id) {
			flights[i] = flight;
			break;
		}
	}
	for (int i = 0; i < noOfFlights; i++) {
		loadFlightsFile << flights[i].id << " "
			<< flights[i].origin << " "
			<< flights[i].destination << " "
			<< flights[i].depTime << " "
			<< flights[i].arrTime << " "
			<< flights[i].seatsEco << " "
			<< flights[i].seatsBus << " "
			<< flights[i].seatsFirst << " "
			<< flights[i].priceEco << " "
			<< flights[i].priceBus << " "
			<< flights[i].priceFirst << " "
			<< flights[i].refund << "\n";
	}
	loadFlightsFile.close();
	return true;
}

//This function inputs a choice that tells that what thing should be edited
int inputChoiceForFlightEdit(Flight flight) {
	bool isValid = false;
	std::string errorMessage = "";
	int choice = 0;
	do {
		printHeader();
		printBlue("----------------- FLIGHT DETAILS -----------------\n");
		std::cout<<"1. Departure Time           : "<<flight.depTime<<"\n";
		std::cout<<"2. Arrival Time             : "<<flight.arrTime<<"\n";
		std::cout<<"3. Seats for Economy Class  : "<<flight.seatsEco<<"\n";
		std::cout<<"4. Seats for Business Class : "<<flight.seatsBus<<"\n";
		std::cout<<"5. Seats for First Class    : "<<flight.seatsFirst<<"\n";
		std::cout<<"6. Price for Economy Class  : "<<flight.priceEco<<"\n";
		std::cout<<"7. Price for Business Class : "<<flight.priceBus<<"\n";
		std::cout<<"8. Price for First Class    : "<<flight.priceFirst<<"\n";
		std::cout<<"9. Refund                   : "<<flight.refund<<"\n";
		if (!isValid) {
			if (!errorMessage.empty()) {
				printError(errorMessage);
			}
		}
		std::cout<<"Enter your choice: ";
		choice = getValidInteger(1,9,isValid);

	} while (!isValid);
	return choice;
}

//This function changes a field of flight based on choice
Flight editFlightField(Flight flight, int choice) {
	bool isValid = false;
	std::string errorMessage = "";
	std::string inputTaken;
	long long numericInput = 0;
	switch (choice) {
	case 1:
		do {
			printHeader();
			printSkyBlue("Current Departure Time: " + flight.depTime + "\n");
			if (!isValid) {
				if (!errorMessage.empty()) {
					printError(errorMessage);
				}
			}
			std::cout << "Enter new Departure Time: ";
			std::cin >> inputTaken;
			if (!inputTaken.empty()) {
				flight.depTime= inputTaken;
				isValid = true;
				return flight;
				break;
			}
			else {
				errorMessage = "[ERROR]: Departure time cannot be empty!\n";
				isValid = false;
			}
		} while (!isValid);
		return flight;
		break;
	case 2:
		do {
			printHeader();
			printSkyBlue("Current Arrival Time: " + flight.arrTime+ "\n");
			if (!isValid) {
				if (!errorMessage.empty()) {
					printError(errorMessage);
				}
			}
			std::cout << "Enter new Arrival Time: ";
			std::cin >> inputTaken;
			if (!inputTaken.empty()) {
				flight.arrTime= inputTaken;
				isValid = true;
				return flight;
				break;
				
			}
			else {
				errorMessage = "[ERROR]: Arrival Time cannot be empty!\n";
				isValid = false;
			}
		} while (!isValid);
		return flight;
		break;
	case 3:
		do {
			printHeader();
			printSkyBlue("Current Seats for Economy Class: " + std::to_string(flight.seatsEco) + "\n");
			if (!isValid) {
				if (!errorMessage.empty()) {
					printError(errorMessage);
				}
			}
			std::cout << "Enter new Seats for Economy: ";
			numericInput = getValidInteger(1, 450, isValid);
			flight.seatsEco = int(numericInput);
			isValid = true;
			return flight;
			break;
		} while (!isValid);
		return flight;
		break;
	case 4:
		do {
			printHeader();
			printSkyBlue("Current Seats for Business Class: " + std::to_string(flight.seatsBus) + "\n");
			if (!isValid) {
				if (!errorMessage.empty()) {
					printError(errorMessage);
				}
			}
			std::cout << "Enter new Seats for Business Class: ";
			numericInput = getValidInteger(1, 60, isValid);
			flight.seatsBus = int(numericInput);
			isValid = true;
			return flight;
			break;
		} while (!isValid);
		return flight;
		break;
	case 5:
		do {
			printHeader();
			printSkyBlue("Current Seats for First Class: " + std::to_string(flight.seatsFirst) + "\n");
			if (!isValid) {
				if (!errorMessage.empty()) {
					printError(errorMessage);
				}
			}
			std::cout << "Enter new Seats for First Class: ";
			numericInput = getValidInteger(1, 16, isValid);
			flight.seatsFirst = int(numericInput);
			isValid = true;
			return flight;
			break;
		} while (!isValid);
		return flight;
		break;
	case 6:
		do {
			printHeader();
			printSkyBlue("Current Fare for Economy Class: " + std::to_string(flight.priceEco) + "\n");
			if (!isValid) {
				if (!errorMessage.empty()) {
					printError(errorMessage);
				}
			}
			std::cout << "Enter new Fare for Economy Class: ";
			numericInput = getValidInteger(10000, 1000000000, isValid);
			flight.priceEco = numericInput;
			isValid = true;
			return flight;
			break;
		} while (!isValid);
		return flight;
		break;
	case 7:
		do {
			printHeader();
			printSkyBlue("Current Fare for Business Class: " + std::to_string(flight.priceBus) + "\n");
			if (!isValid) {
				if (!errorMessage.empty()) {
					printError(errorMessage);
				}
			}
			std::cout << "Enter new Fare for Business Class: ";
			numericInput = getValidInteger(15000, 1000000000, isValid);
			flight.priceBus = numericInput;
			isValid = true;
			return flight;
			break;
		} while (!isValid);
		return flight;
		break;
	case 8:
		do {
			printHeader();
			printSkyBlue("Current Fare for First Class: " + std::to_string(flight.priceFirst) + "\n");
			if (!isValid) {
				if (!errorMessage.empty()) {
					printError(errorMessage);
				}
			}
			std::cout << "Enter new Fare for First Class: ";
			numericInput = getValidInteger(30000, 1000000000, isValid);
			flight.priceFirst = numericInput;
			isValid = true;
			return flight;
			break;
		} while (!isValid);
		return flight;
		break;
	case 9:
		do {
			printHeader();
			printSkyBlue("Current Refund Percentage: " + std::to_string(flight.refund) + "%\n");
			if (!isValid) {
				if (!errorMessage.empty()) {
					printError(errorMessage);
				}
			}
			std::cout << "Enter new Refund %: ";
			numericInput = getValidInteger(1, 100, isValid);
			flight.priceEco = int(numericInput);
			isValid = true;
			return flight;
			break;
		} while (!isValid);
		return flight;
		break;
	default:
		break;
	}
	return flight;
}

//This function is used to edit a fligt details
void editFlight(Flight*& flights, int noOfFlights) {
	bool isValid = false;
	Flight selectedFlight;
	std::string errorMessage = "";
	int choice = 0;
	std::string inputId = "";
	do {
		printHeader();
		viewAvailableFlights(flights, noOfFlights);
		if (!isValid) {
			if (!errorMessage.empty()) {
				printError(errorMessage);
			}
		}
		printBlue("Enter an ID of flight ot proceed: \n");
		std::cin >> inputId;
		for (int i = 0; i < noOfFlights; i++) {
			if (flights[i].id == inputId) {
				isValid = true;
				selectedFlight = flights[i];
				break;
			}

			if (!isValid) {
				errorMessage = "[INVALID_INPUT]: Flight ID not found!\n";
			}
		}
	} while (!isValid);

	if (isValid) {
		choice = inputChoiceForFlightEdit(selectedFlight);
	}

	selectedFlight = editFlightField(selectedFlight, choice);

	if (updateFlightToFile(flights, selectedFlight, noOfFlights)) {
		printSuccess("Flights has been updated in system!\n");
	}
	else {
		printError("[ERROR]: While updating flights file!\n");
	}
}

//This function is used to add a new Flight
void addFlight(Flight*& flights, int& noOfFlights) {
	Flight newFlight = { "", "", "", "", "", -1, -1, -1, -1, -1, -1, -1 };
	int inputs = 12;
	for(int i = 1; i <= inputs; i++) {
		newFlight = getAllInputsForNewFlight(newFlight, i);
	}
	if (addFlightToFile(newFlight)) {
		printSuccess("Flights has been added to system!\n");
		noOfFlights++;
		flights = loadFlights(noOfFlights);
		printYellow("Press any key to exit!\n");
	}
	else {
		printError("[ERROR]: While updating flights file!\n");
	}

}

//This functione  delete flight from file
bool removeFlightFromFile(std::string flightID, Flight* flights, int& noOfFlights) {
	std::ofstream updateFlightsFile("database/flights.txt", std::ios::out);
	if(!updateFlightsFile.is_open()) {
		printError("[ERROR]: Unable to open file!");
		return false;
	}
	else {
		for (int i = 0; i < noOfFlights; i++) {
			if (flights[i].id != flightID) {
				updateFlightsFile << flights[i].id << " "
					<< flights[i].origin << " "
					<< flights[i].destination << " "
					<< flights[i].depTime << " "
					<< flights[i].arrTime << " "
					<< flights[i].seatsEco << " "
					<< flights[i].seatsBus << " "
					<< flights[i].seatsFirst << " "
					<< flights[i].priceEco << " "
					<< flights[i].priceBus << " "
					<< flights[i].priceFirst << " "
					<< flights[i].refund << "\n";
			}
		}
		updateFlightsFile.close();	
		noOfFlights--;
		flights = loadFlights(noOfFlights);
		return true;
	}
}

// this function is used to remove a flight
void removeFlight(Flight*& flights, int& noOfFlights) {
	Flight selectedFlight = { "", "", "", "", "", -1, -1, -1, -1, -1, -1, -1 };
	bool isValid = false;
	std::string errorMessage = "";
	char choice = 'n';
	std::string inputId = "";
	do {
		printHeader();
		viewAvailableFlights(flights, noOfFlights);
		if (!isValid) {
			if (!errorMessage.empty()) {
				printError(errorMessage);
			}
		}
		printBlue("Enter an ID of flight to remove: \n");
		std::cin >> inputId;
		for (int i = 0; i < noOfFlights; i++) {
			if (flights[i].id == inputId) {
				isValid = true;
				selectedFlight = flights[i];
				break;
			}

			if (!isValid) {
				errorMessage = "[INVALID_INPUT]: Flight ID not found!\n";
			}
		}
	} while (!isValid);

	if (isValid) {
		isValid = false;
		errorMessage = "";
		do {
			printHeader();
			printBlue("-------------------- FLIGHT DETAILS -------------------\n\n");
			std::cout << "Flight ID                : " << selectedFlight.id << "\n";
			std::cout << "Flight Source            : " << selectedFlight.origin << "\n";
			std::cout << "Flight Destination       : " << selectedFlight.destination << "\n";
			std::cout << "Arrival Time             : " << selectedFlight.arrTime << "\n";
			std::cout << "Departure Time           : " << selectedFlight.depTime << "\n";
			std::cout << "Seats for Economy Class  : " << selectedFlight.seatsEco << "\n";
			std::cout << "Seats for Business Class : " << selectedFlight.seatsBus << "\n";
			std::cout << "Seats for First Class    : " << selectedFlight.seatsFirst << "\n";
			std::cout << "Economy Class Fare       : " << selectedFlight.priceEco << "\n";
			std::cout << "Business Class Fare      : " << selectedFlight.priceBus << "\n";
			std::cout << "First Class Fare         : " << selectedFlight.priceFirst << "\n";
			std::cout << "Refund Percentage        : " << selectedFlight.refund << "\n";
			if (!isValid) {
				if (!errorMessage.empty()) {
					printError(errorMessage);
				}
			}
			printYellow("Are you sure you want to delete this flight?(y/n)\n");
			std::cin >> choice;
			if (choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N') {
				if (choice == 'y' || choice == 'Y') {
					isValid = true;
					break;
				}
				else if (choice == 'n' || choice == 'N') {
					isValid = true;
					break;
				}
			}
			else {
				errorMessage = "[INVALID_INPUT]: Press y or n!\n";
			}
		} while (!isValid);
	}

	if (isValid) {
		if (choice == 'y' || choice == 'Y') {
			if (removeFlightFromFile(selectedFlight.id, flights, noOfFlights)) {
				printSuccess("Flight has been removed from system!\n");
			}
			else {
				printError("[ERROR]: While removing flight from file!\n");
			}
		}else if(choice == 'n' || choice == 'N') {
			printSuccess("Flight removal canceled.\n");
			std::cout << "Press any key to exit!\n";
			return;
		}
	}
}

//Function to view current bookings
void printBookingsTableHeaderForAdmin() {
	std::string cCyan = "\033[1;36m";
	std::string cYellow = "\033[1;33m";
	std::string cReset = "\033[0m";

	printHeader();

	std::cout << cYellow << "=====================================================================================================================================" << cReset << std::endl;

	std::cout << cYellow << "|" << cReset;
	std::cout << cCyan << "Index" << cReset;
	std::cout << cYellow << "|" << cReset;
	std::cout << cCyan << "User-ID     " << cReset;
	std::cout << cYellow << "|" << cReset;
	std::cout << cCyan << "Flight-ID" << cReset;
	std::cout << cYellow << "|" << cReset;
	std::cout << cCyan << "Origin    " << cReset;
	std::cout << cYellow << " |" << cReset;
	std::cout << cCyan << "Destination " << cReset;
	std::cout << cYellow << " |" << cReset;
	std::cout << cCyan << "Depart Time  " << cReset;
	std::cout << cYellow << " |" << cReset;
	std::cout << cCyan << "Arrival Time " << cReset;
	std::cout << cYellow << " |" << cReset;
	std::cout << cCyan << " Price  " << cReset;
	std::cout << cYellow << " |" << cReset;
	std::cout << cCyan << "Class    " << cReset;
	std::cout << cYellow << " |" << cReset;
	std::cout << cCyan << "Seats" << cReset;
	std::cout << cYellow << " |" << cReset;
	std::cout << cCyan << "Refund %" << cReset;
	std::cout << cYellow << " |" << cReset;

	std::cout << std::endl;
	std::cout << cYellow << "=====================================================================================================================================" << cReset << std::endl;
}

//This function display bookings for admin with index
void viewReservationsForAdmin(SelectedFlight* bookings, int size) {
	if (size == 0) {
		printError("There are no Boookings found!\n");
		return;
	}
	printBookingsTableHeaderForAdmin();
	const int wID = 10;
	const int wCity = 12;
	const int wTime = 14;
	const int wPrice = 10;
	const int wSeat = 7;
	std::string cYellow = "\033[1;33m";
	std::string cReset = "\033[0m";
	for (int i = 0; i < size; i++) {
		std::cout << cYellow << "|" << cReset;


		std::cout << std::left << std::setw(4) << i + 1 << cYellow << " |" << cReset;
		std::cout << std::left << std::setw(11) << bookings[i].userId << cYellow << " |" << cReset;
		std::cout << std::left << std::setw(8) << bookings[i].id << cYellow << " |" << cReset;
		std::cout << std::left << std::setw(10) << bookings[i].origin << cYellow << " |" << cReset;
		std::cout << std::left << std::setw(wCity) << bookings[i].destination << cYellow << " |" << cReset;
		std::cout << std::left << std::setw(13) << bookings[i].depTime << cYellow << " |" << cReset;
		std::cout << std::left << std::setw(13) << bookings[i].arrTime << cYellow << " |" << cReset;


		std::cout << std::left << std::setw(8) << bookings[i].price << cYellow << " |" << cReset;
		std::cout << std::left << std::setw(9) << bookings[i].classSelected << cYellow << " |" << cReset;


		std::cout << std::left << std::setw(6) << std::to_string(bookings[i].seats) << cYellow << "|" << cReset;


		std::cout << std::left << std::setw(8) << std::to_string(bookings[i].refund) + "%" << cYellow << " |" << cReset;

		std::cout << std::endl;
		std::cout << "-------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
	}
}

void removeBookingUsingIndex(SelectedFlight*& bookings, int& noOfFlights) {
	bool isValid = false;
	std::string errorMessage = "";
	int choice = 0;
	do {
		printHeader();
		printBlue("--------------- REMOVE BOOKING USING INDEX ---------------\n\n");
		if (!isValid) {
			if (!errorMessage.empty()) {
				printError(errorMessage);
			}
		}
		viewReservationsForAdmin(bookings, noOfFlights);
		if (noOfFlights == 0) {
			printYellow("Press any key to exit!\n");
			return;
		}
		std::cout << "Enter the index of the booking to remove: ";
		choice = getValidInteger(0, noOfFlights, isValid);	
	} while (!isValid);

	if (isValid) {
		if (removeBookingFromFileUsingIndex(--choice, bookings, noOfFlights)) {
			printSuccess("Booking has been removed from system!\n");
		}
		else {
			printError("[ERROR]: While removing booking from file!\n");
		}
	}
}

bool removeBookingFromFileUsingIndex(int bookingIndex, SelectedFlight*& bookings, int& noOfBookings) {
	if (noOfBookings <= 0 || bookingIndex < 0 || bookingIndex >= noOfBookings) {
		return false;
	}

	if (noOfBookings == 1) {
		delete[] bookings;
		bookings = nullptr;
		noOfBookings = 0;

		std::ofstream updateBookingsFile("database/bookings.txt", std::ios::trunc);
		updateBookingsFile.close();
		return true;
	}

	int newCount = noOfBookings - 1;

	SelectedFlight* newArrayOfBookings = nullptr;
	newArrayOfBookings = new SelectedFlight[newCount];
	int count = 0;
	for (int i = 0; i < noOfBookings; i++) {
		if (i != bookingIndex) {
			if(count < noOfBookings) {
				newArrayOfBookings[count] = bookings[i];
				count++;
			}
		}
	}
	delete[] bookings;
	bookings = newArrayOfBookings;
	noOfBookings--;

	std::ofstream updateBookingsFile("database/bookings.txt");
	if(updateBookingsFile.is_open()){
		for (int i = 0; i < noOfBookings; i++) {
			updateBookingsFile << bookings[i].userId << " "
							 << bookings[i].id << " "
							 << bookings[i].origin << " "
							 << bookings[i].destination << " "
							 << bookings[i].depTime << " "
							 << bookings[i].arrTime << " "
							 << bookings[i].classSelected << " "
							 << bookings[i].price << " "	
							 << bookings[i].refund << " "	
							 << bookings[i].seats << "\n";
		}
		updateBookingsFile.close();
	}
	else{
		return false;
	}
	return true;
}

bool isUserIDExistsInBookings(std::string userId, int noOfBookings, SelectedFlight* bookings){
	for(int i = 0; i < noOfBookings; i++){
		if(bookings[i].userId == userId){
			return true;
		}
	}
	return false;
}

bool deleteBookingsFromFileUsingUserId(std::string userId, SelectedFlight* bookings, int& noOfBookings){
	if(noOfBookings <= 0 || userId.empty()){
		return false;
	}

	if(noOfBookings == 1){
		delete[] bookings;
		bookings = nullptr;
		noOfBookings = 0;

		std::ofstream updateBookingsFile("database/bookings.txt", std::ios::trunc);
		updateBookingsFile.close();
		return true;
	}
	
	SelectedFlight* newBookingsArray = nullptr;

	int newBookingsCount = 0;
	for(int i = 0; i < noOfBookings; i++){
		if(bookings[i].userId != userId){
			newBookingsCount++;
		}
	}
	
	newBookingsArray = new SelectedFlight[newBookingsCount];
	int count = 0;
	for(int i = 0; i < noOfBookings; i++){
		if(bookings[i].userId != userId){
			if (count < newBookingsCount) {
				newBookingsArray[count] = bookings[i];
				count++;
			}
		}
	}
	delete[] bookings;
	bookings = newBookingsArray;
	noOfBookings = newBookingsCount;
	
	std::ofstream updateBookingsFile("database/bookings.txt");
	if(updateBookingsFile.is_open()){
		for(int i = 0; i < noOfBookings; i++){
			updateBookingsFile << bookings[i].userId << " "
							 << bookings[i].id << " "
							 << bookings[i].origin << " "
							 << bookings[i].destination << " "
							 << bookings[i].depTime << " "
							 << bookings[i].arrTime << " "
							 << bookings[i].classSelected << " "
							 << bookings[i].price << " "	
							 << bookings[i].refund << " "	
							 << bookings[i].seats << "\n";
		}
		updateBookingsFile.close();
	}
	else{
		return false;
	}
	return true;
}

void removeBookingUsingUserID(SelectedFlight*& bookings, int& noOfBookings){
	bool isValid = false;
	std::string errorMessage = "";
	std::string userId = "";
	
	do{
		printHeader();
		printBlue("--------------- REMOVE BOOKING USING USER ID ---------------\n\n");
		viewReservationsForAdmin(bookings, noOfBookings);
		if (!isValid) {
			if (!errorMessage.empty()) {
				printError(errorMessage);
			}
		}
		std::cout << "Enter the user ID of the booking to remove: ";
		std::cin >> userId;
		isValid = isUserIDExistsInBookings(userId, noOfBookings, bookings);
		if(!isValid){
			errorMessage = "[ERROR]: User ID does not exist!\n";
		}
	}while(!isValid);

	if (isValid) {
		if (deleteBookingsFromFileUsingUserId(userId, bookings, noOfBookings)) {
			printSuccess("Booking(s) has been removed from system!\n");
		}
		else {
			printError("[ERROR]: While removing booking(s) from file!\n");
		}
	}
}

//This function removes Bookings
void removeBooking( SelectedFlight*& bookings, int& noOfBookings ){
	bool isValid = false;
	std::string errorMessage = "";

	do {
		printHeader();
		printBlue("--------------- REMOVE BOOKING ---------------\n\n");
		if (!isValid) {
			if (!errorMessage.empty()) {
				printError(errorMessage);
			}
		}
		std::cout<<"Chose one of the following menu: \n";
		std::cout<<"  1. Remove Booking Using Index\n";
		std::cout<<"  2. Remove Booking Using User ID\n";
		printError("  3. <= Exit to Admin Menu\n\n");
		
		int choice = getValidInteger(1, 3, isValid);
		
		switch(choice){
			case 1:
				removeBookingUsingIndex(bookings, noOfBookings);
				break;
			case 2:
				removeBookingUsingUserID(bookings, noOfBookings);
				break;
			default:
				break;
		}
		
	} while (!isValid);
	
}

void manageFlights(Flight*& flights, int& noOfFlights, SelectedFlight*& bookings, int& noOfBookings) {
	bool isValid = false;
	int choice = 0;
	std::string errorMessage = "";

	do {
		printHeader();
		printBlue("--------------- MANAGE FLIGHTS & BOOKINGS ---------------\n\n");
		if (!isValid) {
			if (!errorMessage.empty()) {
				printError(errorMessage);
			}
		}
		std::cout << "  1. Add Flight\n";
		std::cout << "  2. Edit Flight\n";
		std::cout << "  3. Remove Flight\n";
		std::cout << "  4. Remove Booking\n";
		std::cout << "  5. View All Flights\n";
		printError("  6. <= Exit to Admin Menu\n\n");
		std::cout << "Enter your choice (1-6): ";
		choice = getValidInteger(1, 6, isValid);
	} while (!isValid);

	switch (choice) {
	case 1:
		addFlight(flights, noOfFlights);
		break;
	case 2:
		editFlight(flights, noOfFlights);
		break;
	case 3:
		removeFlight(flights, noOfFlights);
		break;
	case 4:
		removeBooking(bookings, noOfBookings);
		break;
	case 5:
		printHeader();
		viewAvailableFlights(flights, noOfFlights);
		printYellow("Press any key to exit!\n");
		break;
	case 6:
		break;
	default:
		break;
	}
	
}

void viewReservationReportsAdmin(User* users, UserBalance* userBalance, int size) {
	bool isValid = false;
	std::string errorMessage = "";
	std::string inputId;
	do{
		displayUsersWithIDs(users, size);
		if (!isValid) {
			if (!errorMessage.empty()) {
				printError(errorMessage);
			}
		}
		std::cout << "Enter the user ID of the user to view their reservations: ";
		std::cin >> inputId;
		isValid = isUserIDExists(inputId);
		if(!isValid){
			errorMessage = "[ERROR]: User ID does not exist!\n";
		}
	}while(!isValid);

	if(isValid){
		generateUserReservationReport(inputId, size);
	}
}
