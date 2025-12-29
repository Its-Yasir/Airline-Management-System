#include <stdlib.h>
#include <iomanip>

#include "functions.h"
#include "models.h"


UserBalance* loadBalanceForUsers(int& size) {
	size = 0;
	std::ifstream userBalanceFile("database/users-balance.txt");
	if(!userBalanceFile.is_open()) {
		printError("[ERROR]: There was an error while opening the user balance file.");
		return nullptr;
	}
	else {
		std::string line;
		while (std::getline(userBalanceFile, line)) {
			if (!line.empty()) {
				size++;
			}
		}
		userBalanceFile.clear();
		userBalanceFile.seekg(0, std::ios::beg);
		UserBalance* userBalanceArray = new UserBalance[size];
		int count = 0;
		while (count < size && userBalanceFile >> userBalanceArray[count].userId >> userBalanceArray[count].balance) {
			count++;
		}
		userBalanceFile.close();
		return userBalanceArray;
	}
}

void SaveBalanceForUsers(UserBalance arr[], int size) {
	std::ofstream userBalanceFile("database/users-balance.txt");
	if (!userBalanceFile.is_open()) {
		printError("[ERROR]: There was an error while opening the user balance file for saving.");
	}
	else {
		for (int i = 0; i < size; i++) {
			userBalanceFile << arr[i].userId << " " << arr[i].balance << "\n";
		}
		printSuccess("Your balance has been updated!\n");
		userBalanceFile.close();
	}
}

UserBalance* DeductBalanceForUser(std::string userId, long long amount, UserBalance arr[], int size, bool& isAmountOk) {
	bool userFound = false;

	for (int i = 0; i < size; i++) {
		if (arr[i].userId == userId) {
			userFound = true;

			if (arr[i].balance >= amount) {
				arr[i].balance -= amount;
				printSuccess("Amount deducted successfully from your balance!\n");
				printSkyBlue("Your New Balance is: " + std::to_string(arr[i].balance) + "/- PKR\n");
				isAmountOk = true;
			}
			else {
				printError("[ERROR]: Insufficient balance! Transaction Failed.\n");
				printYellow("Your Current Balance is: " + std::to_string(arr[i].balance) + "/- PKR\n");
				isAmountOk = false;
			}
			break;
		}
	}
	if (!userFound) {
		printError("[ERROR]: User ID not found in Balance Database. Contact Admin.\n");
		isAmountOk = false;
	}

	return arr;
}

void displayFlightHeader() {
	std::string cCyan = "\033[1;36m";
	std::string cYellow = "\033[1;33m";
	std::string cReset = "\033[0m";

	std::cout << cYellow << "=====================================================================================================================================" << cReset << std::endl;

	std::cout << cYellow << "|" << cReset;
	std::cout << cCyan << "Flight-ID" << cReset;
	std::cout << cYellow << " |" << cReset;
	std::cout << cCyan << "Origin     " << cReset;
	std::cout << cYellow << " |" << cReset;
	std::cout << cCyan << "Destination" << cReset;
	std::cout << cYellow << " |" << cReset;
	std::cout << cCyan << "Depart Time  " << cReset;
	std::cout << cYellow << " |" << cReset;
	std::cout << cCyan << "Arrival Time " << cReset;
	std::cout << cYellow << " |" << cReset;
	std::cout << cCyan << "Price(E)" << cReset;
	std::cout << cYellow << " |" << cReset;
	std::cout << cCyan << "Price(B)" << cReset;
	std::cout << cYellow << " |" << cReset;
	std::cout << cCyan << "Price(F)" << cReset;
	std::cout << cYellow << " |" << cReset;
	std::cout << cCyan << "Refund" << cReset;
	std::cout << cYellow << " |" << cReset;
	std::cout << cCyan << "Seats(E)" << cReset;
	std::cout << cYellow << "|" << cReset;
	std::cout << cCyan << "Seats(B)" << cReset;
	std::cout << cYellow << "|" << cReset;
	std::cout << cCyan << "Seats(F)" << cReset;
	std::cout << cYellow << "|" << cReset;

	std::cout << std::endl;
	std::cout << cYellow << "=====================================================================================================================================" << cReset << std::endl;
}

void updateBalance(long long amount, std::string userId, int op) {
	std::ifstream loadUserBalanceFile("database/users-balance.txt");

	if (!loadUserBalanceFile.is_open()) {
		printError("[ERROR]: Could not open balance file!\n");
		return;
	}

	int noOfRecords = 0;
	std::string line;
	while (std::getline(loadUserBalanceFile, line)) {
		if (!line.empty()) {
			noOfRecords++;
		}
	}


	UserBalance* allUSersBalanceRecords = new UserBalance[noOfRecords];

	loadUserBalanceFile.clear(); 
	loadUserBalanceFile.seekg(0, std::ios::beg); 


	int i = 0;
	while (i < noOfRecords && loadUserBalanceFile >> allUSersBalanceRecords[i].userId >> allUSersBalanceRecords[i].balance) {
		i++;
	}
	loadUserBalanceFile.close();


	bool found = false;
	for (int k = 0; k < noOfRecords; k++) {
		if (allUSersBalanceRecords[k].userId == userId) {
			found = true;
			if (op > 0) {
				allUSersBalanceRecords[k].balance += amount;
				printSuccess("Refund added to wallet successfully!\n");
			}
			else if (op < 0) {
				if (allUSersBalanceRecords[k].balance >= amount) {
					allUSersBalanceRecords[k].balance -= amount;
					printSuccess("Payment deducted successfully!\n");
				}
				else {
					printError("[ERROR]: Insufficient Balance!\n");
				}
			}
			break;
		}
	}

	if (!found) {
		printError("[ERROR]: User ID not found in balance records.\n");
	}


	std::ofstream saveFile("database/users-balance.txt"); 
	if (saveFile.is_open()) {
		for (int k = 0; k < noOfRecords; k++) {
			saveFile << allUSersBalanceRecords[k].userId << " " << allUSersBalanceRecords[k].balance << std::endl;
		}
		saveFile.close();
	}
	else {
		printError("[ERROR]: Could not save updated balance!\n");
	}


	delete[] allUSersBalanceRecords;
}

void updateBookings(std::string userId, std::string flightId) {
	int noOfRecords = 0;
	SelectedFlight* bookingsArray = nullptr;

	std::ifstream loadBookingsFile("database/bookings.txt");
	if (!loadBookingsFile.is_open()) {
		printError("There was an error while opening the bookings file.\n");
		return;
	}


	std::string line;
	while (std::getline(loadBookingsFile, line)) {
		if (!line.empty()) noOfRecords++;
	}


	loadBookingsFile.clear();
	loadBookingsFile.seekg(0, std::ios::beg);

	bookingsArray = new SelectedFlight[noOfRecords];
	int count = 0;


	while (count < noOfRecords && loadBookingsFile
		>> bookingsArray[count].userId
		>> bookingsArray[count].id
		>> bookingsArray[count].origin
		>> bookingsArray[count].destination
		>> bookingsArray[count].depTime
		>> bookingsArray[count].arrTime
		>> bookingsArray[count].classSelected
		>> bookingsArray[count].price
		>> bookingsArray[count].refund
		>> bookingsArray[count].seats
		) {
		count++;
	}
	loadBookingsFile.close();


	std::ofstream createNewBookingsFile("database/bookings.txt");
	if (!createNewBookingsFile.is_open()) {
		printError("There was an error while opening the bookings file for updating.\n");
	}
	else {
		for (int i = 0; i < noOfRecords; i++) {

			if (!(bookingsArray[i].userId == userId && bookingsArray[i].id == flightId)) {
				createNewBookingsFile
					<< bookingsArray[i].userId << " "
					<< bookingsArray[i].id << " "
					<< bookingsArray[i].origin << " "
					<< bookingsArray[i].destination << " "
					<< bookingsArray[i].depTime << " "
					<< bookingsArray[i].arrTime << " "
					<< bookingsArray[i].classSelected << " "
					<< bookingsArray[i].price << " "
					<< bookingsArray[i].refund << " "
					<< bookingsArray[i].seats << "\n";
			}
		}
		createNewBookingsFile.close();
	}

	delete[] bookingsArray;
}

void updateFlightFile(std::string flightId, std::string clasS, int seats) {
	int noOfFlights = 0;
	Flight* flightsArray = nullptr;
	std::ifstream updateFlightsFile("database/flights.txt");
	if (!updateFlightsFile.is_open()) {
		printError("[ERROR]: While opening flights file!\n");
	}
	else {
		std::string line;
		while (std::getline(updateFlightsFile, line)) {
			if (!line.empty()) {
				noOfFlights++;
			}
		}
		updateFlightsFile.clear();
		updateFlightsFile.seekg(0, std::ios::beg);
		flightsArray = new Flight[noOfFlights];
		int count = 0;
		while (count < noOfFlights && updateFlightsFile
			>> flightsArray[count].id
			>> flightsArray[count].origin
			>> flightsArray[count].destination
			>> flightsArray[count].depTime
			>> flightsArray[count].arrTime
			>> flightsArray[count].priceEco
			>> flightsArray[count].priceBus
			>> flightsArray[count].priceFirst
			>> flightsArray[count].seatsEco
			>> flightsArray[count].seatsBus
			>> flightsArray[count].seatsFirst
			>> flightsArray[count].refund
			) {
			count++;
		}
		updateFlightsFile.close();
		for (int j = 0; j < noOfFlights; j++) {
			if (flightsArray[j].id == flightId) {
				if (clasS == "Economy") {
					flightsArray[j].seatsEco += seats;
				}
				else if (clasS == "Business") {
					flightsArray[j].seatsBus += seats;
				}
				else if (clasS == "First") {
					flightsArray[j].seatsFirst += seats;
				}
				break;
			}
		}
	}

	std::ofstream saveUpdatedFlightsFile("database/flights.txt");
	if (!saveUpdatedFlightsFile.is_open()) {
		printError("There was an error while saving updated flights file.\n");
	}
	else {
		for (int i = 0; i < noOfFlights; i++) {
			saveUpdatedFlightsFile
				<< flightsArray[i].id << " "
				<< flightsArray[i].origin << " "
				<< flightsArray[i].destination << " "
				<< flightsArray[i].depTime << " "
				<< flightsArray[i].arrTime << " "
				<< flightsArray[i].priceEco << " "
				<< flightsArray[i].priceBus << " "
				<< flightsArray[i].priceFirst << " "
				<< flightsArray[i].seatsEco << " "
				<< flightsArray[i].seatsBus << " "
				<< flightsArray[i].seatsFirst << " "
				<< flightsArray[i].refund << "\n";
		}
		saveUpdatedFlightsFile.close();
	}

}

void printError(std::string message) {
	std::cout << "\033[1;31m" << message << "\033[0m";
}

void printBlue(std::string message) {
	std::cout << "\033[1;34m" << message << "\033[0m";
}

void printYellow(std::string text) {
	std::cout << "\033[1;33m" << text << "\033[0m";
}

void printBold(std::string text) {
	std::cout << "\033[1;37m" << text << "\033[0m";
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

Flight* loadFlights(int& size) {
	size = 0;
	std::ifstream loadFlightsFile("database/flights.txt");
	if (!loadFlightsFile.is_open()) {
		printError("[ERROR]: While opening flights file!\n");
		return nullptr;
	}
	else {
		std::string line;
		while (std::getline(loadFlightsFile, line)) {
			if (!line.empty()) {
				size++;
			}
		}

		loadFlightsFile.clear();
		loadFlightsFile.seekg(0, std::ios::beg);
		Flight* flightsArray = new Flight[size];
		int count = 0;
		while (count < size && loadFlightsFile
			>> flightsArray[count].id
			>> flightsArray[count].origin
			>> flightsArray[count].destination
			>> flightsArray[count].depTime
			>> flightsArray[count].arrTime
			>> flightsArray[count].priceEco
			>> flightsArray[count].priceBus
			>> flightsArray[count].priceFirst
			>> flightsArray[count].seatsEco
			>> flightsArray[count].seatsBus
			>> flightsArray[count].seatsFirst
			>> flightsArray[count].refund
			) {
			count++;
		}

		loadFlightsFile.close();
		return flightsArray;
	}
}

void createFlightsFile() {
	std::ofstream creatingFlightsFile("database/flights.txt");
	if (!creatingFlightsFile.is_open()) {
		printError("[ERROR]: While creating flights file!\n");
	}
	else {
		//Format I am using
		//ID ORIGIN DESTINATION DEPARTURE ARRIVAL EcoPRICE BusPRICE FirstPRICE EcoSEATS BusSEATS FirstSEATS
		creatingFlightsFile << "PK-101 Lahore Istanbul 12Dec-08:00AM 12Dec-02:00PM 150000 450000 900000 60 20 8 15" << std::endl;
		creatingFlightsFile << "PK-102 Karachi Dubai 13Dec-10:00AM 13Dec-01:00PM 80000 160000 300000 50 30 5 25" << std::endl;
		creatingFlightsFile << "PK-205 Islamabad London 14Dec-03:00AM 14Dec-01:00PM 280000 600000 1200000 100 25 10 0" << std::endl;
		creatingFlightsFile << "PK-050 Lahore Karachi 15Dec-06:00PM 15Dec-08:00PM 25000 55000 0 120 15 0 100" << std::endl;
		creatingFlightsFile << "PK-301 Islamabad Jeddah 16Dec-05:00AM 16Dec-09:00AM 190000 400000 750000 80 20 10 50" << std::endl;
		creatingFlightsFile << "PK-404 Peshawar Doha 17Dec-11:00PM 18Dec-02:00AM 110000 250000 500000 60 15 5 75" << std::endl;
		creatingFlightsFile << "PK-701 Karachi New_York 19Dec-02:00AM 19Dec-06:00PM 350000 850000 1800000 150 40 12 30" << std::endl;
		creatingFlightsFile << "PK-010 Lahore Islamabad 20Dec-09:00AM 20Dec-10:00AM 18000 35000 0 40 10 0 90" << std::endl;
		creatingFlightsFile << "PK-110 Sialkot Dubai 21Dec-04:00PM 21Dec-07:00PM 85000 170000 320000 55 20 0 10" << std::endl;
		creatingFlightsFile << "PK-555 Islamabad Beijing 22Dec-07:00AM 22Dec-03:00PM 220000 480000 800000 70 20 6 0" << std::endl;
		std::cout << "File created Successfully!";
		creatingFlightsFile.close();
	}
}

void updateFlightsFile(Flight arr[], int size, std::string flightID, int seats, std::string clasS) {
	for (int i = 0; i < size; i++) {
		if (flightID == arr[i].id) {
			if (clasS == "Economy") {
				arr[i].seatsEco -= seats;
			}
			else if (clasS == "Business") {
				arr[i].seatsBus -= seats;
			}
			else if (clasS == "First") {
				arr[i].seatsFirst -= seats;
			}
		}
	}

	std::ofstream updateFlightsFile("database/flights.txt");
	if (!updateFlightsFile.is_open()) {
		printError("[ERROR]: While opening file for upadting flights\n");
	}
	else {
		for (int i = 0; i < size; i++) {
			updateFlightsFile
				<< arr[i].id
				<< " "
				<< arr[i].origin
				<< " "
				<< arr[i].destination
				<< " "
				<< arr[i].depTime
				<< " "
				<< arr[i].arrTime
				<< " "
				<< arr[i].priceEco
				<< " "
				<< arr[i].priceBus
				<< " "
				<< arr[i].priceFirst
				<< " "
				<< arr[i].seatsEco
				<< " "
				<< arr[i].seatsBus
				<< " "
				<< arr[i].seatsFirst
				<< " "
				<< arr[i].refund
				<< " "
				<< std::endl;
		}

		updateFlightsFile.close();
	}
}

SelectedFlight* loadBookings(int& size) {
	size = 0;
	std::ifstream loadBookingsFile("database/bookings.txt");
	if (!loadBookingsFile.is_open()) {
		printError("[ERROR]: While opening flights file!\n");
		return nullptr;
	}
	else {
		std::string line;
		while (std::getline(loadBookingsFile, line)) {
			if (!line.empty()) {
				size++;
			}
		}

		loadBookingsFile.clear();
		loadBookingsFile.seekg(0, std::ios::beg);
		SelectedFlight* bookingsArray = new SelectedFlight[size];
		int count = 0;
		while (count < size && loadBookingsFile
			>> bookingsArray[count].userId
			>> bookingsArray[count].id
			>> bookingsArray[count].origin
			>> bookingsArray[count].destination
			>> bookingsArray[count].depTime
			>> bookingsArray[count].arrTime
			>> bookingsArray[count].classSelected
			>> bookingsArray[count].price
			>> bookingsArray[count].refund
			>> bookingsArray[count].seats
			) {
			count++;
		}

		loadBookingsFile.close();
		return bookingsArray;
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

void saveBookingToFile(SelectedFlight sec, std::string userID) {
	sec.userId = userID;

	std::ofstream loadBookingFileForSave("database/bookings.txt", std::ios::app);
	if (!loadBookingFileForSave.is_open()) {
		printError("[ERROR]: While opening bookings file for saving booking\n");
	}
	else {
		loadBookingFileForSave <<
			sec.userId << " "
			<< sec.id << " "
			<< sec.origin << " "
			<< sec.destination << " "
			<< sec.depTime << " "
			<< sec.arrTime << " "
			<< sec.classSelected << " "
			<< sec.price << " "
			<< sec.refund << " "
			<< sec.seats << "\n"
			;
		printSuccess("Flight has been booked successfully!\n");
		loadBookingFileForSave.close();
	}
}

SelectedFlight* getBookingsByUserId(std::string userId, int& count) {
	int totalFileLines = 0;
	count = 0;

	SelectedFlight* loadedBookings = loadBookings(totalFileLines);

	int userBookingCount = 0;
	for (int i = 0; i < totalFileLines; i++) {
		if (loadedBookings[i].userId == userId) {
			userBookingCount++;
		}
	}

	SelectedFlight* bookingsForUser = new SelectedFlight[userBookingCount];
	int temp = 0;

	for (int i = 0; i < totalFileLines; i++) {
		if (loadedBookings[i].userId == userId) {
			bookingsForUser[temp] = loadedBookings[i];
			temp++;
		}
	}

	count = userBookingCount;
	delete[] loadedBookings;
	return bookingsForUser;
}

void createBookingFile() {
	std::ofstream creatingBookingFile("database/bookings.txt");

	if (!creatingBookingFile.is_open()) {
		printError("[ERROR]: While Creating Bookings File\n");
	}
	else {
		creatingBookingFile << "yasir_ali PK-110 Lahore Dubai 12Dec-08:00PM 13Dec-05:00PM Business 1000000 10 2\n";
		creatingBookingFile << "roshan_ali PK-102 Karachi Dubai 12Dec-08:00PM 13Dec-05:00PM First 2000000 20 1\n";

		creatingBookingFile.close();
	}
}