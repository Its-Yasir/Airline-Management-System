#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <conio.h>
#include <limits>

#include "models.h"
#include "functions.h"


bool adminLogin(User arr[], int a);

bool isUserIDExists(std::string userId);

int showAdminMenu();

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

UsersDetails getUserDetailsAfterChange(UsersDetails det, int type);

UsersDetails getDetailsForOneUser(std::string userId, int noOfBalanceUsers, User myUsers[], int noOfUsers);

//Admin Menu Functions
void manageUsers(int& noOfBalanceUsers, User*& users, int& noOfUsers, UserBalance*& userBalances);
void manageFlights();
void viewReservationReportsAdmin();