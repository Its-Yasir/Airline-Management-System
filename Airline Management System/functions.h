#pragma once
#include "models.h"

#include <iostream>
#include <fstream>
#include <string>


//Login Functions
bool adminLogin(User arr[], int a);

//Function for bookings
void createBookingFile();
void saveBookingToFile(SelectedFlight sec, std::string userID);
SelectedFlight* getBookingsByUserId(std::string userId, int& count);
SelectedFlight* loadBookings(int& size);


//Showing menu functions
int showMenu();
int showAdminMenu();


//Functions for Flights
void createFlightsFile();
Flight* loadFlights(int& size);


User* loadAdmins(int& size);
void createAdminFile();
UserBalance* loadBalanceForUsers(int& size);
void SaveBalanceForUsers(UserBalance arr[], int size);
UserBalance* DeductBalanceForUser(std::string userId, long long amount, UserBalance arr[], int size, bool& isAmountOk);


//Admin Menu Functions
void managePassengers();
void manageUsers();
void manageFlights();
void viewReservationReportsAdmin();


//Functions for printing outputs in different colors
void printHeader();
void printBlue(std::string message);
void printSkyBlue(std::string message);
void printYellow(std::string text);
void printError(std::string message);
void printBold(std::string text);
void printSuccess(std::string message);
void displayFlightHeader();
