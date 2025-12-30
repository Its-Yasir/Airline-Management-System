#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "models.h"
#include "functions.h"


bool adminLogin(User arr[], int a);

int showAdminMenu();

User* loadAdmins(int& size);

void createAdminFile();

int showManageUsersMenu();

std::string getBalanceForUser(std::string userId, int size);

void viewAllUsersData(int noOfBalanceUsers);

//Admin Menu Functions
void manageUsers(int noOfBalanceUsers);
void manageFlights();
void viewReservationReportsAdmin();