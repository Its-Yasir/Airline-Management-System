#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <conio.h>
#include <limits>

#include "models.h"
#include "functions.h"
#include "userFunctions.h"


bool adminLogin(User arr[], int a);

bool isUserIDExists(std::string userId);

int showAdminMenu();

void deleteUser(int& noOfUsers, User*& users, int& noOfBalanceUsers, UserBalance*& userBalances, std::string userId, Flight* flights, int& noOfFlights, SelectedFlight* userbookings);

void removeUser(int& noOfUsers, User*& users, int& noOfBalanceUsers, UserBalance*& userBalances, Flight* flights, int& noOfFlights, SelectedFlight* userbookings);

User* loadAdmins(int& size);

void createAdminFile();

int showManageUsersMenu();

std::string getBalanceForUser(std::string userId, int size);

void addUser(int& noOfUsers, User*& users, int& noOfBalanceUsers, UserBalance*& userBalances);

void viewAllUsersData(int noOfBalanceUsers);

void editUserDetails(User* users, int noOfUsers, int noOfBalanceUsers);

void displayUsersWithIDs(User* users, int noOfUsers);

void updatePassengersFile(std::string newUserId, std::string oldUserId, User users[], int noOfUsers);

void editAField(std::string userId, UsersDetails det, int type, int noOfBalanceUsers, User users[]);

void updateUserDetailsFile(UsersDetails userDetail);

void viewCreateNewUserHeader(UsersDetails newUserDetails, int detailsTaken);

UsersDetails getAllInputsForNewUser(UsersDetails newUserDetails, int detailsTaken);

bool checkBreakFunction(int detailsTaken, UsersDetails newUserDetails);

UsersDetails getUserDetailsAfterChange(UsersDetails det, int type);

UsersDetails getDetailsForOneUser(std::string userId, int noOfBalanceUsers, User myUsers[], int noOfUsers);

bool confirmDeleteUser(int& noOfUsers, std::string userId, User* users, int& noOfBalanceUsers, UserBalance* userBalances);

void addFlight(Flight*& flights, int& noOfFlights);

void printAddFlightHeader(Flight flight);

Flight getAllInputsForNewFlight(Flight flight, int detailsTaken);

bool isFlightIDExists(std::string flightID);

bool addFlightToFile(Flight newFlight);

int inputChoiceForFlightEdit(Flight flight);

Flight editFlightField(Flight flight, int choice);

bool updateFlightToFile(Flight* flights, Flight flight, int noOfFlights);

void editFlight(Flight*& flights, int noOfFlights);

bool removeFlightFromFile(std::string flightID, Flight* flights, int& noOfFlights);

void viewReservationsForAdmin(SelectedFlight* bookings, int size);

void removeBooking(SelectedFlight*& bookings, int& noOfBookings);

void manageFlights(Flight*& flights, int& noOfFlights, SelectedFlight*& bookings, int& noOfBookings);

void printBookingsTableHeaderForAdmin();

bool removeBookingFromFileUsingIndex(int bookingIndex, SelectedFlight*& bookings, int& noOfBookings);

void removeFlight(Flight*& flights, int& noOfFlights);

void removeBookingUsingUserID(SelectedFlight*& bookings, int& noOfBookings);

bool isUserIDExistsInBookings(std::string userId, int noOfBookings, SelectedFlight* bookings);

bool deleteBookingsFromFileUsingUserId(std::string userId, SelectedFlight* bookings, int& noOfBookings);

void removeBookingUsingIndex(SelectedFlight*& bookings, int& noOfFlights);


//Admin Menu Functions
void manageUsers(int& noOfBalanceUsers, User*& users, int& noOfUsers, UserBalance*& userBalances, Flight* flights, int noOfFlights, SelectedFlight* userbookings);
void manageFlights(Flight*& flights, int& noOfFlights, SelectedFlight*& bookings, int& noOfBookings);
void viewReservationReportsAdmin();