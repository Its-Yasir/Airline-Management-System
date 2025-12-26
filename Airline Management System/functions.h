#pragma once
#include "models.h"
#include <iostream>
#include <fstream>

User* loadUsers(int& size);
void printHeader();
void printError(std::string message);
void printSuccess(std::string message);
