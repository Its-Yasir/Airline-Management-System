#pragma once
#include "models.h"
#include <iostream>
#include <fstream>

bool passengerLogin(User arr[], int a);
bool adminLogin(User arr[], int a);
int showMenu();
User* loadUsers(int& size);

void printHeader();
void printBlue(std::string message);
void printSkyBlue(std::string message);
void printError(std::string message);
void printSuccess(std::string message);
