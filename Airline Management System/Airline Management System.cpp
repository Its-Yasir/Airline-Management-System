#include <iostream>
#include <stdlib.h>
#include <conio.h>

#include "functions.h"
#include "models.h"

int main()
{
    int choice = showMenu();
    int totalUsers = 0;
    User* myUsers = loadUsers(totalUsers);








    delete[] myUsers;
	std::cout << "Thanks for using our Airline Management System. Press any key to exit...";
	_getch();
    return 0;
}