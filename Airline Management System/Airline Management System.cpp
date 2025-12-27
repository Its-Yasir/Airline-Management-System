#include <iostream>
#include <stdlib.h>
#include <conio.h>

#include "functions.h"
#include "models.h"

int main()
{
    bool tr = false;
    int choice = showMenu();
    int totalUsers = 0;
    User* myUsers = loadUsers(totalUsers);
    switch (choice) {
    case 1:
        tr = adminLogin(myUsers, totalUsers);
    case 2:
        tr = passengerLogin(myUsers, totalUsers);
        break;
    default:
        std::cout << "E";
    }







    delete[] myUsers;
	std::cout << "Thanks for using our Airline Management System. Press any key to exit...";
	_getch();
    return 0;
}