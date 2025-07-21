#pragma once
#include <string>
#include <stdexcept>
#include <iostream>
#include "external/tinyxml2-master/tinyxml2.h"
#include <sstream>

using namespace tinyxml2;
namespace tinyxml2
{
    class XMLDocument;
    class XMLElement;
}
// <operation>
//      <order-date>2025-07-01</order-date>
//      <exec-date>2025-07-03</exec-date>
//      <type>Płatność kartą</type>
//      <description>21321 1111222233334444 Lokalizacja : Adres : TRATTORIA RIALTO Miasto : KRAKOW Kraj : POLSKA Data wykonania operacji : 2025-07-01 02:00 Oryginalna kwota operacji : 41,00 PLN Numer karty : 32142******1234</description>
//      <amount curr="PLN">-41.00</amount>
//      <ending-balance curr="PLN">+2999.97</ending-balance>
// </operation>

struct Date
{
    int day;
    int month;
    int year;

    Date() : day(0), month(0), year(0) {}
    Date(int day, int month, int year) : day(day), month(month), year(year) {}
};
struct Description
{
    std::string shopAddress;
    std::string shopCity;

    Description(const std::string &shopAddress, const std::string &shopCity)
        : shopAddress(shopAddress), shopCity(shopCity) {}
};

class Operation
{
public:
    Date date;
    Description description;
    std::string type;
    double amount;
    double endingBalance;

    Operation(Date date, Description description, std::string type, double amount, double endingBalance)
        : date(date), description(description), type(type),
          amount(amount), endingBalance(endingBalance) {}

    void print() const
    {
        std::cout << "Operation details:\n";
        std::cout << "  Date: " << date.day << "-" << date.month << "-" << date.year << "\n";
        std::cout << "  Type: " << type << "\n";
        std::cout << "  Shop address: " << description.shopAddress << "\n";
        std::cout << "  Shop city: " << description.shopCity << "\n";
        std::cout << "  Amount: " << amount << "\n";
        std::cout << "  Ending balance: " << endingBalance << "\n";
    }
};

XMLElement *loadOperation(XMLDocument &doc)
{
    XMLError result = doc.LoadFile("../example.xml");

    if (result != XML_SUCCESS)
    {
        std::cout << "Failed to load file\n";
        return nullptr;
    }

    XMLElement *accountHistory = doc.FirstChildElement("account-history");
    if (accountHistory == nullptr)
    {
        std::cout << "No 'accountHistory' element\n";
        return nullptr;
    }

    XMLElement *operations = accountHistory->FirstChildElement("operations");
    if (operations == nullptr)
    {
        std::cout << "No 'operations' element\n";
        return nullptr;
    }

    XMLElement *operation = operations->FirstChildElement("operation");
    if (operation != nullptr)
    {
        return operation;
    }
    else
    {
        return nullptr;
    }
}

Date parseDate(const std::string &str)
{
    int year, month, day;
    char dash1, dash2;

    std::istringstream iss(str);
    iss >> year >> dash1 >> month >> dash2 >> day;

    if (iss.fail() || dash1 != '-' || dash2 != '-')
    {
        throw std::invalid_argument("Invalid date format");
    }

    return Date(day, month, year);
}
