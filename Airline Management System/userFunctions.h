#pragma once
#include "models.h"

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>


User* loadUsers(int& size);
int showUserMenu();
bool passengerLogin(User arr[], int a);


void bookFlights(Flight arr[], int size);
void cancelReservations();
void viewAvailableFlights(Flight arr[], int size);
void generateUserReservationReport();