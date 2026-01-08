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
		std::cout << "1. Book FLights =>\n";
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

void generateFileForUsersExtraInfo() {
	std::string filePath = "database/users-extra-data.txt";
	std::ofstream outFile(filePath);

	if (outFile.is_open()) {

		outFile << "Yasir Ali|yasir_ali|House 12-A, Street 5, Johar Town|Lahore|Punjab|Pakistan|+923001234567|PK-8829102|yas_123_@|1434000" << std::endl;
		outFile << "Roshan Haider|roshan_haider|88 West Broadway, Apt 402|Vancouver|British Columbia|Canada|+16045550199|CA-9912388|ros_345_#|4500000" << std::endl;

		outFile.close();
		std::cout << "File generated successfully inside 'databse' folder." << std::endl;
	}
	else {
		printError("Unable to create file. Please ensure the folder 'databse' exists.");
	}
}

bool passengerLogin(User arr[], int a, std::string& userID) {
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
					userID = inputUserId;
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

SelectedFlight handleClassSeatsInput(Flight selectedFlight) {
	bool isValidClass = false;
	bool isValidClassSeats = false;
	long long totalPrice = 0;
	int noOfseats = 0;
	std::string classSelected = "";
	std::string errorMessage = "";
	do {
		printHeader();
		printBlue("------ FLIGHT DETAILS ------\n");
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
			std::cout << selectedFlight.seatsFirst<< std::endl;
		}
		else {
			printError("FULL\n");
		}
		std::cout << "Refund PErcentage: " << selectedFlight.refund << "%" << std::endl;
		if (!isValidClassSeats) {
			if (!errorMessage.empty()) {
				printError(errorMessage);
			}
		}
		std::cout << "Choose class to book 1(Economy) / 2(Business)/ 3(First): ";
		int classChoice;
		std::cin >> classChoice;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			errorMessage = "[INVALID_INPUT]: Please enter a number.\n";
			isValidClassSeats = false;
			continue;
		}
		std::cout << "Choose number of seats: ";
		int seatsInput;
		int seatsAvailable = 0;
		std::cin >> seatsInput;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			errorMessage = "[INVALID_INPUT]: Please enter a valid number of seats.\n";
			isValidClassSeats = false;
			continue;
		}
		if (classChoice > 0 && classChoice < 4) {
			if (classChoice == 1) {
				if (selectedFlight.seatsEco > 0) {
					isValidClass = true;
					seatsAvailable = selectedFlight.seatsEco;
					classSelected = "Economy";
					totalPrice = 1;
				}
				else {
					isValidClass = false;
					errorMessage = "This Class if Full.\n";
				}
			}else if (classChoice == 2) {
				if (selectedFlight.seatsBus > 0) {
					isValidClass = true;
					seatsAvailable = selectedFlight.seatsBus;
					classSelected = "Business";
					totalPrice = 2;
				}
				else {
					isValidClass = false;
					errorMessage = "This Class if Full.\n";
				}
			}else if (classChoice == 3) {
				if (selectedFlight.seatsFirst > 0) {
					isValidClass = true;
					seatsAvailable = selectedFlight.seatsFirst;
					classSelected = "First";
					totalPrice = 3;
				}
				else {
					isValidClass = false;
					errorMessage = "This Class if Full.\n";
				}
			}

			if (isValidClass) {
				if (!(seatsInput <= seatsAvailable)) {
					errorMessage = "[INVALID_INPUT]: Number of seats in more than this class has.\n";
				}
				else if (seatsInput < 1) {
					errorMessage = "[INVALID_INPUT]: Chose a number greated than zero.\n";
				}
				else {
					noOfseats = seatsInput;
					if (totalPrice == 1) {
						totalPrice = noOfseats* selectedFlight.priceEco;
					}else if (totalPrice == 2) {
						totalPrice = noOfseats* selectedFlight.priceBus;
					}else if (totalPrice == 3) {
						totalPrice = noOfseats* selectedFlight.priceFirst;
					}
					isValidClassSeats = true;
					break;
				}
			}
		}
		else {
			isValidClassSeats = false;
			errorMessage = "[INVALID_INPUT]: Press 1,2 or 3 for selecting class.\n";
		}

	} while (!isValidClassSeats);

		SelectedFlight sec;
		sec.id = selectedFlight.id;
		sec.origin = selectedFlight.origin;
		sec.destination = selectedFlight.destination;
		sec.depTime = selectedFlight.depTime;
		sec.arrTime = selectedFlight.arrTime;
		sec.classSelected = classSelected;
		sec.refund = selectedFlight.refund;
		sec.price = totalPrice;
		sec.seats = noOfseats;

		return sec;
}

SelectedFlight bookFlights(Flight arr[], int size, std::string userId, UserBalance* balanceArr, int sizeOfBalanceUsers, int flightSize) {
	SelectedFlight sec;
	bool isValid = false;
	std::string message = "";
	Flight selectedFlight = { "", "", "", "", "", 0, 0, 0, 0, 0, 0, 0 };
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
		sec = handleClassSeatsInput(selectedFlight);
	}
	if (handleFinalBookFlight(sec, userId, balanceArr, sizeOfBalanceUsers, arr, flightSize)) {
		return sec;
	}
	else {
		sec.id = "0";
		return sec;
	}

}

bool handleFinalBookFlight(SelectedFlight sec, std::string userId, UserBalance* arr, int size, Flight flightArr[], int flightSize) {
	char choice;
	bool isValid = false;
	std::string errorMessage = "";
	do {
		printHeader();
		printBlue("------ BOOKING SUMMARY ------\n");
		std::cout << "ID:              " << sec.id << std::endl;
		std::cout << "From:            " << sec.origin << std::endl;
		std::cout << "To:              " << sec.destination << std::endl;
		std::cout << "Departure Time:  " << sec.depTime << std::endl;
		std::cout << "Arrival Time:    " << sec.arrTime << std::endl;
		std::cout << "Class Selected:  " << sec.classSelected << std::endl;
		std::cout << "Number of seats: " << sec.seats << std::endl;
		std::cout << "Total Price:     " << sec.price << std::endl << std::endl;
		std::cout << "Refund Percentage:     " << sec.refund << "%" << std::endl << std::endl;
		if (!isValid) {
			if (!errorMessage.empty()) {
				printError(errorMessage);
			}
		}
		printSkyBlue("Are you sure you want to confirm this booking?(y/n): ");
		std::cin >> choice;
		bool isAmountOk = false;
		choice = std::tolower(choice);
		if (choice == 'y' || choice == 'n') {
			if (choice == 'y') {
				DeductBalanceForUser(userId, sec.price, arr, size, isAmountOk);
				if (isAmountOk) {
					SaveBalanceForUsers(arr, size);
					return true;
				}
				else {
					return false;
				}
			}
			else if (choice == 'n') {
				return false;
			}

			isValid = true;
			break;
		}
		else {
			errorMessage = "[INVALID_INPUT]: Press y or n.\n";
			isValid = false;
		}
	} while (!isValid);



}

void printBookingsTableHeader() {
	std::string cCyan = "\033[1;36m";
	std::string cYellow = "\033[1;33m";
	std::string cReset = "\033[0m";

	printHeader();

	std::cout << cYellow << "=====================================================================================================================================" << cReset << std::endl;

	std::cout << cYellow << "|" << cReset;
	std::cout << cCyan << " Flight-ID" << cReset;
	std::cout << cYellow << " |" << cReset;
	std::cout << cCyan << " Origin     " << cReset;
	std::cout << cYellow << " |" << cReset;
	std::cout << cCyan << " Destination  " << cReset;
	std::cout << cYellow << " |" << cReset;
	std::cout << cCyan << " Depart Time  " << cReset;
	std::cout << cYellow << " |" << cReset;
	std::cout << cCyan << " Arrival Time " << cReset;
	std::cout << cYellow << " |" << cReset;
	std::cout << cCyan << " Price  " << cReset;
	std::cout << cYellow << " |" << cReset;
	std::cout << cCyan << " Class    " << cReset;
	std::cout << cYellow << " |" << cReset;
	std::cout << cCyan << " Seats    " << cReset;
	std::cout << cYellow << " |" << cReset;
	std::cout << cCyan << " Refund %" << cReset;
	std::cout << cYellow << " |" << cReset;

	std::cout << std::endl;
	std::cout << cYellow << "=====================================================================================================================================" << cReset << std::endl;
}

void viewReservations(SelectedFlight* bookings, int size) {
	printBookingsTableHeader();
	const int wID = 10;
	const int wCity = 12;
	const int wTime = 14;
	const int wPrice = 10;
	const int wSeat = 7;
	std::string cYellow = "\033[1;33m";
	std::string cReset = "\033[0m";
	showLoading("Loading Reservations");
	for (int i = 0; i < size; i++) {
		std::cout << cYellow << "|" << cReset;


		std::cout << std::left << std::setw(wID) << bookings[i].id << cYellow << " |" << cReset;
		std::cout << std::left << std::setw(wCity) << bookings[i].origin << cYellow << " |" << cReset;
		std::cout << std::left << std::setw(wCity + 2) << bookings[i].destination << cYellow << " |" << cReset;
		std::cout << std::left << std::setw(wTime) << bookings[i].depTime << cYellow << " |" << cReset;
		std::cout << std::left << std::setw(wTime) << bookings[i].arrTime << cYellow << " |" << cReset;


		std::cout << std::left << std::setw(8) << bookings[i].price << cYellow << " |" << cReset;
		std::cout << std::left << std::setw(wPrice) << bookings[i].classSelected << cYellow << " |" << cReset;


		std::cout << std::left << std::setw(11) << std::to_string(bookings[i].seats) << cYellow << "|" << cReset;


		std::cout << std::left << std::setw(9) << std::to_string(bookings[i].refund) + "%" << cYellow << " |" << cReset;

		std::cout << std::endl;
		std::cout << "-------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
	}
}

void cancelReservations(SelectedFlight* bookings, int size, std::string userId) {
	bool isValid = false;
	long long getBack;
	std::string message = "";
	SelectedFlight selectedFlight = { "", "", "", "", "", "", "", 0, 0, 0 };
	do {
		viewReservations(bookings, size);
		if (!isValid) {
			if (!message.empty()) {
				printError(message);
			}
		}
		printBlue("Enter Flight ID to cancel it: \n");
		std::string inputID;
		std::cin >> inputID;
		for (int i = 0; i < size; i++) {
			if (bookings[i].id == inputID) {
				selectedFlight = bookings[i];
				isValid = true;
				break;
			}
		}
		if (!isValid) {
			message = "[ERROR]: Flight ID not found! Please try again.\n";
		}
	} while (!isValid);

	if (isValid) {
		printHeader();
		printBlue("----------- RESERVATION SUMMARY -----------\n\n");
		std::cout << "Flight ID     : " << selectedFlight.id << std::endl;
		std::cout << "Origin        : " << selectedFlight.origin << std::endl;
		std::cout << "Destination   : " << selectedFlight.destination << std::endl;
		std::cout << "Departue Time : " << selectedFlight.depTime << std::endl;
		std::cout << "Arrival Time  : " << selectedFlight.arrTime << std::endl;
		std::cout << "Price         : " << selectedFlight.price << std::endl;
		std::cout << "Class         : " << selectedFlight.classSelected << std::endl;
		std::cout << "Seats         : " << selectedFlight.seats << std::endl;
		std::cout << "Refund        : " << std::to_string(selectedFlight.refund) + "%" << std::endl << std::endl;
		getBack = selectedFlight.price * selectedFlight.refund / 100;
		if (getBack == 0) {
			std::cout << "Money You Get Back : ";
			printError(std::to_string(getBack) + "/- PKR\n");
		}
		else if (selectedFlight.refund == 100) {
			std::cout << "Money You Get Back : ";
			printSuccess(std::to_string(getBack) + "/- PKR\n\n");

		}
		else {
			std::cout << "Money You Get Back : ";
			printSkyBlue(std::to_string(getBack) + "/- PKR\n\n");
		}
	}
	char choice; 
	bool isValidConfirmation = false;
	std::string errorMessage = "";
	do {
		if (!isValidConfirmation) {
			if (!errorMessage.empty()) {
				printError(errorMessage);
			}
		}
		printBlue("Are you sure you want to cancel the reservation? (y/n): ");
		std::cin >> choice;
		if (choice == 'y' || choice == 'n') {
			if (choice == 'n') {
				printSuccess("Reservation is not canceled!\n");
				printYellow("Press any key to exit!\n");
				(void)_getch();
			}
			else if (choice == 'y') {
				if (getBack != 0) {
					updateBalance(getBack, userId, 2);
				}
				updateBookings(userId, selectedFlight.id);
				updateFlightFile(selectedFlight.id, selectedFlight.classSelected, selectedFlight.seats);
				printSuccess("Reservation canceled successfully!\n");
				isValidConfirmation = true;
				break;
			}

			isValidConfirmation = true;
			break;
		}
		else {
			errorMessage = "[INVALID_INPUT]: Press y or n\n";
			isValidConfirmation = false;
		}
	} while (!isValidConfirmation);
}

void viewAvailableFlights(Flight arr[], int size) {
	showLoading("Loading Flights");
	displayFlightHeader();
	const int wID = 9;
	const int wCity = 11;
	const int wTime = 13;
	const int wPrice = 8;
	const int wSeat = 7;
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


		std::cout << std::left << std::setw(7) << std::to_string(arr[i].refund) + "%" << cYellow << "|" << cReset;


		std::cout << std::left << std::setw(wSeat) << arr[i].seatsEco << cYellow << " |" << cReset;
		std::cout << std::left << std::setw(wSeat) << arr[i].seatsBus << cYellow << " |" << cReset;
		std::cout << std::left << std::setw(wSeat) << arr[i].seatsFirst << cYellow << " |" << cReset;

		std::cout << std::endl;
		std::cout << "-------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
	}
}

void generateUserReservationReport(std::string userId, int& count) {
	SelectedFlight* bookingsForUser = getBookingsByUserId(userId, count);


	if (count == 0) {
		printHeader();
		showLoading("Loading Reservation Report");
		printError("\n[INFO]: No flight history found for user: " + userId + "\n");
		if (bookingsForUser != nullptr) delete[] bookingsForUser;
		return;
	}


	int totalUsersCount = 0;
	UserBalance* allBalanceForUsers = loadBalanceForUsers(totalUsersCount);


	UserBalance balanceForUser = { "", 0 };
	bool balanceFound = false;


	for (int i = 0; i < totalUsersCount; i++) {
		if (allBalanceForUsers[i].userId == userId) {
			balanceForUser = allBalanceForUsers[i];
			balanceFound = true;
			break;
		}
	}
	
	if (allBalanceForUsers != nullptr) {
		delete[] allBalanceForUsers;
	}


	long long totalSpent = 0;
	int totalSeats = 0;

	int seatsEco = 0, seatsBus = 0, seatsFirst = 0;
	long long spendEco = 0, spendBus = 0, spendFirst = 0;

	for (int i = 0; i < count; i++) {
		totalSpent += bookingsForUser[i].price;
		totalSeats += bookingsForUser[i].seats;

		if (bookingsForUser[i].classSelected == "Economy") {
			seatsEco += bookingsForUser[i].seats;
			spendEco += bookingsForUser[i].price;
		}
		else if (bookingsForUser[i].classSelected == "Business") {
			seatsBus += bookingsForUser[i].seats;
			spendBus += bookingsForUser[i].price;
		}
		else if (bookingsForUser[i].classSelected == "First") {
			seatsFirst += bookingsForUser[i].seats;
			spendFirst += bookingsForUser[i].price;
		}
	}


	std::string highestClass = "None";
	long long highestAmount = 0;

	if (spendEco >= spendBus && spendEco >= spendFirst) {
		highestClass = "Economy";
		highestAmount = spendEco;
	}
	else if (spendBus >= spendEco && spendBus >= spendFirst) {
		highestClass = "Business";
		highestAmount = spendBus;
	}
	else {
		highestClass = "First Class";
		highestAmount = spendFirst;
	}


	printHeader();
	printBlue("\n===========================================================\n");
	printBold("               PERSONAL RESERVATION REPORT                  \n");
	printBlue("===========================================================\n");

	std::cout << " My User ID: " << userId << "\n";
	std::cout << " Total flights I hace booked: " << count << " flight\n\n";

	printYellow("---------------------- SUMMARY ----------------------------\n");
	std::cout << " Total seats I have booked:    " << totalSeats << "\n";
	std::cout << " Total Amount I have Spent:    ";
	printSuccess(std::to_string(totalSpent) + "/- PKR\n");
	std::cout << " My available Balance:      ";
	if (balanceForUser.balance <= 0) {
		printError(std::to_string(balanceForUser.balance) + "/- PKR\n");
	}
	else {
		printSuccess(std::to_string(balanceForUser.balance) + "/- PKR\n");
	}

	std::cout << std::left << std::setw(15) << " Class"
		<< std::left << std::setw(15) << " | Seats"
		<< std::left << std::setw(20) << " | Total Money Spent" << "\n";
	std::cout << " --------------------------------------------------\n";

	std::cout << std::left << std::setw(16) << " Economy"
		<< "| " << std::left << std::setw(13) << seatsEco
		<< "| " << spendEco << "/- PKR\n";

	std::cout << std::left << std::setw(16) << " Business"
		<< "| " << std::left << std::setw(13) << seatsBus
		<< "| " << spendBus << "/- PKR\n";

	std::cout << std::left << std::setw(16) << " First"
		<< "| " << std::left << std::setw(13) << seatsFirst
		<< "| " << spendFirst << "/- PKR\n\n";

	printYellow("---------------------- Most Spent ---------------------------\n");
	std::cout << " Most money I spent on:   ";
	printSkyBlue(highestClass + " (" + std::to_string(highestAmount) + "/- PKR)\n");
	printYellow("-----------------------------------------------------------\n");

	// 8. Final Cleanup
	if (bookingsForUser != nullptr) {
		delete[] bookingsForUser;
	}
}


