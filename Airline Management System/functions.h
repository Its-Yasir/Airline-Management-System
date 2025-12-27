#pragma once
#include "models.h"
#include <iostream>
#include <fstream>


//Login Functions
bool passengerLogin(User arr[], int a);
bool adminLogin(User arr[], int a);


//Showing menu functions
int showMenu();
int showUserMenu();
int showAdminMenu();


//Loading Users and admins functions
User* loadUsers(int& size);
User* loadAdmins(int& size);
void createAdminFile();


//Users Menu Functions
void bookFlights();
void cancelReservations();
void viewAvailableFlights();
void generateUserReservationReport();


//Admin Menu Functions
void managePassengers();
void manageUsers();
void manageFlights();
void viewReservationReportsAdmin();


//Functions for printing outputs in different colors
void printHeader();
void printBlue(std::string message);
void printSkyBlue(std::string message);
void printError(std::string message);
void printSuccess(std::string message);
