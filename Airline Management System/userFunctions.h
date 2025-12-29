#pragma once
#include "models.h"

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <conio.h>

User* loadUsers(int& size);
int showUserMenu();
bool passengerLogin(User arr[], int a, std::string& userID);
void generateFileForUsersExtraInfo();

SelectedFlight handleClassSeatsInput(Flight selectedFlight);
SelectedFlight bookFlights(Flight arr[], int size, std::string userId, UserBalance* balanceArr, int sizeOfBalanceUsers, int flightSize);
bool handleFinalBookFlight(SelectedFlight sec, std::string userId, UserBalance* arr, int size, Flight flightArr[], int flightSize);
void viewAvailableFlights(Flight arr[], int size);

void cancelReservations(SelectedFlight* bookings, int size, std::string userId);
void viewReservations(SelectedFlight* bookings, int size);
void printBookingsTableHeader();

void generateUserReservationReport(std::string userId, int& count, UserBalance* userBalance, int size);