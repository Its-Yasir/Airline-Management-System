#include <iostream>
#include <stdlib.h>
#include <conio.h>

#include "functions.h"
#include "models.h"

int main()
{
    int totalUsers = 0;
    int totalAdmins = 0;
    int totalFlight = 0;

    std::string currentlyLoggenIn = "";

    User* Admins = loadAdmins(totalAdmins);
    User* myUsers = loadUsers(totalUsers);
    Flight* availableFlight = loadFlights(totalFlight);

    while (true) {
        int choice = showMenu();
        if (choice == 3) {
            break;
        }
        else if (choice == 1) {
            if (adminLogin(Admins, totalAdmins)) {
                currentlyLoggenIn = "admin";
            }
        }
        else if (choice == 2) {
            if (passengerLogin(myUsers, totalUsers)) {
                currentlyLoggenIn = "user";
            }
        }

        if (currentlyLoggenIn == "user") {
            while (true) {
                int userChoice = showUserMenu();
                if (userChoice == 5) {
                    break;
                }

                switch (userChoice) {
                    case 1: bookFlights(); _getch(); break;
                    case 2: cancelReservations(); _getch(); break;
                    case 3: viewAvailableFlights(availableFlight, totalFlight); _getch(); break;
                    case 4: generateUserReservationReport(); _getch(); break;
                }
            }
        }
        else if (currentlyLoggenIn == "admin") {
            while (true) {
                int adminChoice = showAdminMenu();

                if (adminChoice == 5) {
                    break;
                }


                switch (adminChoice) {
                case 1: managePassengers(); _getch(); break;
                case 2: manageUsers(); _getch(); break;
                case 3: manageFlights(); _getch(); break;
                case 4: viewReservationReportsAdmin(); _getch(); break;
                }
            }
        }

    }


    delete[] availableFlight;
    delete[] myUsers;
    delete[] Admins;
	std::cout << "Thanks for using our Airline Management System. Press any key to exit...";
	_getch();
    return 0;
}