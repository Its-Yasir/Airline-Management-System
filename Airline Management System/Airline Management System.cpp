#include <iostream>
#include <stdlib.h>
#include <conio.h>

#include "functions.h"
#include "userFunctions.h"
#include "models.h"
#include "adminFunctions.h"

int main()
{
    int totalUsers = 0;
	int totalUsersWithBalance = 0;
    int totalAdmins = 0;
    int totalFlight = 0;
    int noOfBookingsForCurrentUser = 0;
	int totalBookings = 0;
    std::string userID = "";
    User loggedInAdmin = { "", "" };



    std::string currentlyLoggenIn = "";
    User* Admins = loadAdmins(totalAdmins);
    User* myUsers = loadUsers(totalUsers);
	Flight* availableFlight = nullptr;
    availableFlight = loadFlights(totalFlight);
    SelectedFlight* bookingsForUser = nullptr;
	SelectedFlight* allBookings = loadBookings(totalBookings);
    UserBalance* userBalances = nullptr;
	userBalances = loadBalanceForUsers(totalUsersWithBalance);


    while (true) {
        SelectedFlight sec;
        int choice = showMenu();
        if (choice == 3) {
            break;
        }
        else if (choice == 1) {
            if (adminLogin(Admins, totalAdmins, loggedInAdmin)) {
                currentlyLoggenIn = "admin";
            }
        }
        else if (choice == 2) {
            if (passengerLogin(myUsers, totalUsers, userID)) {
                currentlyLoggenIn = "user";
                if (bookingsForUser != nullptr) delete[] bookingsForUser;
                bookingsForUser = getBookingsByUserId(userID, noOfBookingsForCurrentUser);
            }
        }

        if (currentlyLoggenIn == "user") {
            while (true) {
                int userChoice = showUserMenu();
                if (userChoice == 5) {
                    break;
                }

                switch (userChoice) {
                    case 1: 
                        sec = bookFlights(availableFlight, totalFlight, userID, userBalances, totalUsersWithBalance, totalFlight ); 
                        if (sec.id != "0") {
                            saveBookingToFile(sec, userID);
                        }
                        else {
                            printError("Your booing has been cancelled!\n");
                        }
                        printYellow("Press any key to exit!\n");
                        (void)_getch();
                        break;
                    case 2: 
                        if (bookingsForUser != nullptr) delete[] bookingsForUser;
                        bookingsForUser = getBookingsByUserId(userID, noOfBookingsForCurrentUser);
                        cancelReservations(bookingsForUser, noOfBookingsForCurrentUser, userID);
                        if (availableFlight != nullptr) delete[] availableFlight;
                        availableFlight = loadFlights(totalFlight);
                        if (availableFlight != nullptr) delete[] availableFlight;
                        userBalances = loadBalanceForUsers(totalUsersWithBalance);
                        (void)_getch();
                        break;
                    case 3: 
						printSuccess("*E = Economy, B = Business, F = First Class* \n");
						printBlue("Press any key to return to the menu...\n");
                        viewAvailableFlights(availableFlight, totalFlight); 
                        (void)_getch();
                        break;
                    case 4:
                        generateUserReservationReport(userID, noOfBookingsForCurrentUser); 
                        (void)_getch(); 
                        break;
                }
            }
        }
        else if (currentlyLoggenIn == "admin") {
            while (true) {
                int adminChoice = showAdminMenu();

                if (adminChoice == 6) {
                    break;
                }


                switch (adminChoice) {
                case 1: manageUsers(totalUsersWithBalance, myUsers, totalUsers, userBalances, availableFlight, totalFlight, bookingsForUser ); (void)_getch(); break;
                case 2: manageFlights(availableFlight, totalFlight, allBookings, totalBookings  ); (void)_getch(); break;
                case 3: viewReservationReportsAdmin(myUsers, userBalances, totalUsers); (void)_getch(); break;
                case 4: viewAnalytics(totalFlight, totalBookings, myUsers, allBookings, totalUsers); (void)_getch(); break;
                case 5: changePassword(loggedInAdmin, Admins, totalAdmins); (void)_getch(); break;
                }
            }
        }
    }


    delete[] userBalances;
    delete[] allBookings;
    delete[] bookingsForUser;
    delete[] availableFlight;
    delete[] myUsers;
    delete[] Admins;
	std::cout << "Thanks for using our Airline Management System. Press any key to exit...";
    (void)_getch();
    return 0;
}
