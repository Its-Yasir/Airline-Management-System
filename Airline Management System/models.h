#pragma once
#include <string>

struct User {
    std::string userID;
    std::string password;
};

struct Flight {
    std::string id = "";
    std::string origin = "";
    std::string destination = "";
    std::string depTime = "";
    std::string arrTime = "";

    long long priceEco = 0;
    long long priceBus = 0;
    long long priceFirst = 0;

    int seatsEco = 0;
    int seatsBus = 0;
    int seatsFirst = 0;

    int refund = 0;
};

struct SelectedFlight {
    std::string userId = "";
    std::string id = "";
    std::string origin = "";
    std::string destination = "";
    std::string depTime = "";
    std::string arrTime = "";
    std::string classSelected = "";
    int refund = 0;
    long long price = 0;

    int seats = 0;
};

struct UserBalance {
    std::string userId = "";
    long long balance = 0;
};

struct UsersDetails {
    std::string userName = "";
    std::string id = "";
    std::string address = "";
    std::string city = "";
    std::string province = "";
    std::string country = "";
    std::string contact = "";
    std::string passport = "";
    std::string password = "";
    long long balance = 0;
};