#pragma once
#include <string>

struct User {
    std::string userID;
    std::string password;
};

struct Flight {
    std::string id;
    std::string origin;
    std::string destination;
    std::string depTime;
    std::string arrTime;

    long long priceEco;
    long long priceBus;
    long long priceFirst;

    int seatsEco;
    int seatsBus;
    int seatsFirst;
};
