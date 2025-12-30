#pragma once
#include "models.h"

#include <iostream>
#include <fstream>
#include <string>

int getValidInteger(int min, int max, bool& valid);

//Function for bookings
void createBookingFile();
void saveBookingToFile(SelectedFlight sec, std::string userID);
SelectedFlight* getBookingsByUserId(std::string userId, int& count);
SelectedFlight* loadBookings(int& size);


//Showing menu functions
int showMenu();


//Functions for Flights
void createFlightsFile();
void updateFlightsFile(Flight arr[], int size, std::string flightID, int seats, std::string clasS);
Flight* loadFlights(int& size);
void updateFlightFile(std::string flightId, std::string clasS, int seats);

UserBalance* loadBalanceForUsers(int& size);
void SaveBalanceForUsers(UserBalance arr[], int size);
void updateBalance(long long amount, std::string userId, int op);
void updateBookings(std::string userId, std::string flightId);
UserBalance* DeductBalanceForUser(std::string userId, long long amount, UserBalance arr[], int size, bool& isAmountOk);




//Functions for printing outputs in different colors
void printHeader();
void printBlue(std::string message);
void printSkyBlue(std::string message);
void printYellow(std::string text);
void printError(std::string message);
void printBold(std::string text);
void printSuccess(std::string message);
void displayFlightHeader();
