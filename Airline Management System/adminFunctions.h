#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "models.h"
#include "functions.h"


bool adminLogin(User arr[], int a);

int showAdminMenu();

User* loadAdmins(int& size);

void createAdminFile();

//Admin Menu Functions
void manageUsers();
void manageFlights();
void viewReservationReportsAdmin();