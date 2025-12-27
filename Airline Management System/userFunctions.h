#pragma once
#include "models.h"

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>


User* loadUsers(int& size);
int showUserMenu();
bool passengerLogin(User arr[], int a, std::string& userID);

SelectedFlight handleClassSeatsInput(Flight selectedFlight);
SelectedFlight bookFlights(Flight arr[], int size);
bool handleFinalBookFlight(SelectedFlight sec);
void cancelReservations();
void viewAvailableFlights(Flight arr[], int size);
void generateUserReservationReport();