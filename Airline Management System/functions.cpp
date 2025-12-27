#include <stdlib.h>
#include <iomanip>

#include "functions.h"
#include "models.h"

void printError(std::string message) {
	std::cout << "\033[1;31m" << message << "\033[0m";
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

Flight* loadFlights(int& size) {
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

void createFlightsFile() {
	std::ofstream creatingFlightsFile("database/flights.txt");
	if (!creatingFlightsFile.is_open()) {
		printError("[ERROR]: While creating flights file!\n");
	}
	else {
		//Format I am using
		//ID ORIGIN DESTINATION DEPARTURE ARRIVAL EcoPRICE BusPRICE FirstPRICE EcoSEATS BusSEATS FirstSEATS
		creatingFlightsFile << "PK-101 Lahore Istanbul 12Dec-08:00AM 12Dec-02:00PM 150000 450000 900000 60 20 8" << std::endl;
		creatingFlightsFile << "PK-102 Karachi Dubai 13Dec-10:00AM 13Dec-01:00PM 80000 160000 300000 50 30 5" << std::endl;
		creatingFlightsFile << "PK-205 Islamabad London 14Dec-03:00AM 14Dec-01:00PM 280000 600000 1200000 100 25 10" << std::endl;
		creatingFlightsFile << "PK-050 Lahore Karachi 15Dec-06:00PM 15Dec-08:00PM 25000 55000 0 120 15 0" << std::endl;
		creatingFlightsFile << "PK-301 Islamabad Jeddah 16Dec-05:00AM 16Dec-09:00AM 190000 400000 750000 80 20 10" << std::endl;
		creatingFlightsFile << "PK-404 Peshawar Doha 17Dec-11:00PM 18Dec-02:00AM 110000 250000 500000 60 15 5" << std::endl;
		creatingFlightsFile << "PK-701 Karachi New_York 19Dec-02:00AM 19Dec-06:00PM 350000 850000 1800000 150 40 12" << std::endl;
		creatingFlightsFile << "PK-010 Lahore Islamabad 20Dec-09:00AM 20Dec-10:00AM 18000 35000 0 40 10 0" << std::endl;
		creatingFlightsFile << "PK-110 Sialkot Dubai 21Dec-04:00PM 21Dec-07:00PM 85000 170000 320000 55 20 0" << std::endl;
		creatingFlightsFile << "PK-555 Islamabad Beijing 22Dec-07:00AM 22Dec-03:00PM 220000 480000 800000 70 20 6" << std::endl;
		std::cout << "File created Successfully!";
		creatingFlightsFile.close();
	}
}

SelectedFlight* loadBookings(int& size) {
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
			<< sec.seats << "\n"
			;
		printSuccess("Flight has been booked successfully!\n");
		loadBookingFileForSave.close();
	}
}

SelectedFlight* getBookingsByUserId(std::string userId, int& count) {
	int size = 0;
	SelectedFlight* loadedBookings = loadBookings(size);
	for (int i = 0; i < size; i++) {
		if (loadedBookings[i].userId == userId) {
			count++;
		}
	}
	SelectedFlight* bookingsForUser = new SelectedFlight[count];
	int temp = 0;
	for (int i = 0; i < size; i++) {
		if (loadedBookings[i].userId == userId && temp < count) {
			bookingsForUser[temp] = loadedBookings[i];
			temp++;
		}
	}

	delete[] loadedBookings;
	return bookingsForUser;
}

void createBookingFile() {
	std::ofstream creatingBookingFile("database/bookings.txt");

	if (!creatingBookingFile.is_open()) {
		printError("[ERROR]: While Creating Bookings File\n");
	}
	else {
		creatingBookingFile << "yasir_ali PK-110 Lahore Dubai 12Dec-08:00PM 13Dec-05:00PM Business 1000000 2\n";
		creatingBookingFile << "roshan_ali PK-102 Karachi Dubai 12Dec-08:00PM 13Dec-05:00PM First 2000000 1\n";

		creatingBookingFile.close();
	}
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