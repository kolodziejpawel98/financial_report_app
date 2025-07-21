#pragma once
#include <string>
#include <stdexcept>
#include <iostream>
#include "external/tinyxml2-master/tinyxml2.h"
#include <sstream>
#include <memory>

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
    // std::string shopCity;

    Description(const std::string &shopAddress /*, const std::string &shopCity*/)
        : shopAddress(shopAddress) /*, shopCity(shopCity)*/ {}
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
        // std::cout << "  Shop city: " << description.shopCity << "\n";
        std::cout << "  Amount: " << amount << "\n";
        std::cout << "  Ending balance: " << endingBalance << "\n";
    }
};

XMLElement *loadOperation(XMLDocument &doc, int index = 0)
{
    XMLError result = doc.LoadFile("../example.xml");
    if (result != XML_SUCCESS)
    {
        std::cout << "Failed to load file\n";
        return nullptr;
    }

    XMLElement *accountHistory = doc.FirstChildElement("account-history");
    if (!accountHistory)
        return nullptr;

    XMLElement *operations = accountHistory->FirstChildElement("operations");
    if (!operations)
        return nullptr;

    XMLElement *operation = operations->FirstChildElement("operation");
    int currentIndex = 0;

    while (operation && currentIndex < index)
    {
        operation = operation->NextSiblingElement("operation");
        ++currentIndex;
    }

    return operation;
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

std::string extractAddress(const std::string &descriptionFull)
{
    std::string addressToken = "Adres : ";
    std::string cityToken = "Miasto :";

    size_t addressStart = descriptionFull.find(addressToken);
    if (addressStart == std::string::npos)
        return "";

    addressStart += addressToken.length();
    size_t addressEnd = descriptionFull.find(" Miasto", addressStart);
    if (addressEnd == std::string::npos)
        return "";

    std::string address = descriptionFull.substr(addressStart, addressEnd - addressStart);

    size_t cityStart = descriptionFull.find(cityToken, addressEnd);
    if (cityStart == std::string::npos)
        return address;

    cityStart += cityToken.length();
    size_t cityEnd = descriptionFull.find(" Kraj", cityStart);
    if (cityEnd == std::string::npos)
        cityEnd = descriptionFull.length();

    std::string city = descriptionFull.substr(cityStart, cityEnd - cityStart);

    auto trim = [](std::string &s)
    {
        size_t first = s.find_first_not_of(" ");
        size_t last = s.find_last_not_of(" ");
        if (first == std::string::npos)
        {
            s.clear();
            return;
        }
        s = s.substr(first, (last - first + 1));
    };

    trim(address);
    trim(city);

    return address + ", " + city;
}

std::unique_ptr<Operation> getOperation(int index = 0)
{
    XMLDocument doc;
    XMLElement *operationTag = loadOperation(doc, index);

    if (!operationTag)
        throw std::runtime_error("Operation not found");

    std::string execDate = operationTag->FirstChildElement("exec-date")->GetText();
    std::string type = operationTag->FirstChildElement("type")->GetText();
    std::string description = operationTag->FirstChildElement("description")->GetText();
    std::string amount = operationTag->FirstChildElement("amount")->GetText();
    std::string endingBalance = operationTag->FirstChildElement("ending-balance")->GetText();

    Date date = parseDate(execDate);
    std::string address = extractAddress(description);

    return std::make_unique<Operation>(date, Description(address), type, std::stod(amount), std::stod(endingBalance));
}
