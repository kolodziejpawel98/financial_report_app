#pragma once
#include <string>
#include <stdexcept>
#include <iostream>
#include "external/tinyxml2-master/tinyxml2.h"
#include <sstream>
#include <vector>
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

class Operation
{
public:
    Date date;
    std::string category;
    std::string description;
    double amount;
    double totalBalanceAfterOperation;

    Operation(Date date, std::string category, std::string description, double amount, double totalBalanceAfterOperation)
        : date(date), category(category), description(description),
          amount(amount), totalBalanceAfterOperation(totalBalanceAfterOperation) {}

    void print() const
    {
        std::cout << "Operation details:\n";
        std::cout << "  Date: " << date.day << "-" << date.month << "-" << date.year << "\n";
        std::cout << "  Category: " << category << "\n";
        std::cout << "  \033[31mDescription: " << description << "\033[0m\n";
        // std::cout << "  Description: " << description << "\n";
        // std::cout << "  Amount: " << amount << "\n";
        printf("  Amount: %.2f\n", amount);
        std::cout << "  Total balanceAfterOperation: " << totalBalanceAfterOperation << "\n\n";
    }
};

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

std::string getSubstring(const std::string &descriptionFull, std::string startToken, std::string endToken)
{
    size_t startPos = descriptionFull.find(startToken);
    if (startPos == std::string::npos)
        return "";
    startPos += startToken.length();

    size_t endPos = descriptionFull.find(endToken, startPos);
    if (endPos == std::string::npos)
        return "";

    std::string result = descriptionFull.substr(startPos, endPos - startPos);

    size_t first = result.find_first_not_of(" ");
    size_t last = result.find_last_not_of(" ");
    if (first == std::string::npos)
        return "";
    return result.substr(first, last - first + 1);
}

std::string extractCrucialData(const std::string &descriptionFull, const std::string &type)
{
    if (type == "Płatność kartą")
    {
        return getSubstring(descriptionFull, "Adres :", "Kraj");
    }
    else if (type == "Wypłata z bankomatu")
    {
        return getSubstring(descriptionFull, "Adres :", "Kraj");
    }
    else if (type == "Przelew na telefon przychodz. zew.")
    {
        if (descriptionFull.find("nadawcy") != std::string::npos)
        {
            return getSubstring(descriptionFull, "Nazwa nadawcy :", "Tytuł :");
        }
        else if (descriptionFull.find("OD") != std::string::npos)
        {
            return getSubstring(descriptionFull, "Nazwa odbiorcy :", "OD:");
        }
        else
        {
            return getSubstring(descriptionFull, "Nazwa odbiorcy :", "Tytuł :");
        }
    }
    else if (type == "Przelew na telefon przychodz. wew.")
    {
        if (descriptionFull.find("odbiorcy :") != std::string::npos)
        {
            return getSubstring(descriptionFull, "Nazwa odbiorcy :", "Tytuł :");
        }
        else
        {
            return getSubstring(descriptionFull, "Nazwa nadawcy :", "Adres");
        }
    }
    else if (type == "Przelew na konto")
    {
        return getSubstring(descriptionFull, "Nazwa nadawcy :", "Adres nadawcy :");
    }
    else if (type == "Przelew z karty")
    {
        return getSubstring(descriptionFull, "Adres :", "Miasto :");
    }
    else if (type == "Opłata za użytkowanie karty")
    {
        return type;
    }
    else if (type == "Płatność web - kod mobilny")
    {
        return getSubstring(descriptionFull, "Adres :", "Operacja");
    }
    else if (type == "Przelew z rachunku")
    {
        return getSubstring(descriptionFull, "Nazwa odbiorcy :", "Tytuł :");
    }
    else
    {
        throw std::runtime_error(std::string("Wrong description for " + descriptionFull));
    }
}

XMLElement *getFirstOperationTag(XMLDocument &xmlDocument)
{
    XMLElement *accountHistory = xmlDocument.FirstChildElement("account-history");
    if (!accountHistory)
        return nullptr;

    XMLElement *operations = accountHistory->FirstChildElement("operations");
    if (!operations)
        return nullptr;

    XMLElement *operation = operations->FirstChildElement("operation");
    return operation;
}

std::string getOperationChild(XMLElement *operationTag, const char *childName)
{
    XMLElement *child = operationTag->FirstChildElement(childName);
    if (!child || !child->GetText())
        throw std::runtime_error(std::string("Missing <") + childName + "> tag");
    return std::string(child->GetText());
}

std::vector<Operation> getAllOperations(const char *path)
{
    std::vector<Operation> operations;
    XMLDocument xmlDocument;
    XMLError fileLoadResult = xmlDocument.LoadFile(path);

    if (fileLoadResult != XML_SUCCESS)
    {
        throw std::runtime_error("Failed to load file");
    }

    XMLElement *operationTag = getFirstOperationTag(xmlDocument);

    while (operationTag != nullptr)
    {
        std::string execDate = getOperationChild(operationTag, "exec-date");
        std::string type = getOperationChild(operationTag, "type");
        std::string description = getOperationChild(operationTag, "description");
        std::string amount = getOperationChild(operationTag, "amount");
        std::string endingBalance = getOperationChild(operationTag, "ending-balance");

        Date date = parseDate(execDate);
        std::string descriptionCrucialData = extractCrucialData(description, type);

        operations.emplace_back(date, type, descriptionCrucialData, std::stod(amount), std::stod(endingBalance));
        operationTag = operationTag->NextSiblingElement("operation");
    }

    return std::move(operations);
}
