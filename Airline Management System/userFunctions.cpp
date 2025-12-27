#include "userFunctions.h"
#include "functions.h"

User* loadUsers(int& size) {
	std::ifstream passengersFile("database/passengers.txt");
	if (!passengersFile.is_open()) {
		printError("[ERROR]: There was an error while opening the file.");
		return nullptr;
	}
	else {
		std::string line;
		while (std::getline(passengersFile, line)) {
			if (!line.empty()) {
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

void bookFlights(Flight arr[], int size) {
	bool isValid = false;
	std::string message = "";
	Flight selectedFlight = { "", "", "", "", "", 0, 0, 0, 0, 0, 0 };
	do {
		printHeader();
		viewAvailableFlights(arr, size);
		if (!isValid) {
			if (!message.empty()) {
				printError(message);
			}
		}
		printBlue("Enter Flight ID to proceed: \n");
		std::string inputID;
		std::cin >> inputID;
		for (int i = 0; i < size; i++) {
			if (arr[i].id == inputID) {
				selectedFlight = arr[i];
				isValid = true;
				break;
			}
		}
		if (!isValid) {
			message = "[ERROR]: Flight ID not found! Please try again.\n";
		}
	} while (!isValid);

	if (isValid) {
		bool isValidClassSeats = false;
		do {
			printHeader();
			printBlue("Flight Details: \n");
			std::cout << "Flight ID: " << selectedFlight.id << std::endl;
			std::cout << "Origin: " << selectedFlight.origin << std::endl;
			std::cout << "Destination: " << selectedFlight.destination << std::endl;
			std::cout << "Departure Time: " << selectedFlight.depTime << std::endl;
			std::cout << "Arrival Time: " << selectedFlight.arrTime << std::endl;
			std::cout << "Price of Ticket Per Seat (Economy): " << selectedFlight.priceEco << std::endl;
			std::cout << "Price of Ticket Per Seat (Business): " << selectedFlight.priceBus << std::endl;
			std::cout << "Price of Ticket Per Seat (First Class): " << selectedFlight.priceFirst << std::endl;
			std::cout << "Number of seats available (Economy): ";
			if (selectedFlight.seatsEco > 0) {
				std::cout << selectedFlight.seatsEco << std::endl;
			}
			else {
				printError("FULL\n");
			}
			std::cout << "Number of seats available (Business): ";
			if (selectedFlight.seatsBus > 0) {
				std::cout << selectedFlight.seatsBus << std::endl;
			}
			else {
				printError("FULL\n");
			}
			std::cout << "Number of seats available (First): ";
			if (selectedFlight.seatsFirst > 0) {
				std::cout << selectedFlight.seatsBus << std::endl;
			}
			else {
				printError("FULL\n");
			}
			std::cout << "Choose class to book (1(Economy) / 2(Business)/ 3(First)): ";
			int classChoice;
			std::cin >> classChoice;

		} while (!isValidClassSeats);
	}

}

void cancelReservations() {
	printSuccess("Reservations canceled Successfuly!");
}

void viewAvailableFlights(Flight arr[], int size) {
	displayFlightHeader();
	const int wID = 9;
	const int wCity = 11;
	const int wTime = 13;
	const int wPrice = 9;
	const int wSeat = 8;
	std::string cYellow = "\033[1;33m";
	std::string cReset = "\033[0m";
	for (int i = 0; i < size; i++) {
		std::cout << cYellow << "|" << cReset;


		std::cout << std::left << std::setw(wID) << arr[i].id << cYellow << " |" << cReset;
		std::cout << std::left << std::setw(wCity) << arr[i].origin << cYellow << " |" << cReset;
		std::cout << std::left << std::setw(wCity) << arr[i].destination << cYellow << " |" << cReset;
		std::cout << std::left << std::setw(wTime) << arr[i].depTime << cYellow << " |" << cReset;
		std::cout << std::left << std::setw(wTime) << arr[i].arrTime << cYellow << " |" << cReset;


		std::cout << std::left << std::setw(wPrice) << arr[i].priceEco << cYellow << " |" << cReset;
		std::cout << std::left << std::setw(wPrice) << arr[i].priceBus << cYellow << " |" << cReset;
		std::cout << std::left << std::setw(wPrice) << arr[i].priceFirst << cYellow << " |" << cReset;


		std::cout << std::left << std::setw(wSeat) << arr[i].seatsEco << cYellow << " |" << cReset;
		std::cout << std::left << std::setw(wSeat) << arr[i].seatsBus << cYellow << " |" << cReset;
		std::cout << std::left << std::setw(wSeat) << arr[i].seatsFirst << cYellow << " |" << cReset;

		std::cout << std::endl;
		std::cout << "-----------------------------------------------------------------------------------------------------------------------------------" << std::endl;
	}
}

void generateUserReservationReport() {
	printSuccess("Report Genrated Successfully!");
}


