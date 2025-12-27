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

    int priceEco;
    int priceBus;
    int priceFirst;

    int seatsEco;
    int seatsBus;
    int seatsFirst;
};
