// #pragma once

#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include "tinyxml2.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include <fstream>

using namespace tinyxml2;

#pragma once

constexpr int EATING_OUT = 1;
constexpr int NON_GROCERY_SHOPPING = 2;
constexpr int GROCERY_SHOPPING = 3;
constexpr int TRANSPORT = 4;
constexpr int REGULAR_EXPENSES = 5;
constexpr int OTHERS = 6;
constexpr int PHOTOGRAPHY = 7;
constexpr int SELF_DEFINED = 8;
constexpr int INCOMING_MONEY = 9;
constexpr int ERROR = -1;

enum class Month
{
    January = 1,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December
};

struct Date
{
    int day;
    int month;
    int year;

    Date();
    Date(int day, int month, int year);

    std::string getDate() const
    {
        std::string textFormatDay = (day < 10) ? "0" + std::to_string(day) : std::to_string(day);
        std::string textFormatMonth = (month < 10) ? "0" + std::to_string(month) : std::to_string(month);
        std::string date = textFormatDay + "/" + textFormatMonth + "/" + std::to_string(year);
        return date;
    }

    int getMonth() const
    {
        return month;
    }
};

class Operation
{
public:
    Date date;
    std::string type;
    std::string description;
    double amount;
    double totalBalanceAfterOperation;
    int categoryTag;

    Operation(Date date, std::string type, std::string description, double amount, double totalBalanceAfterOperation);
    Operation(Date date, std::string type, std::string description, double amount, double totalBalanceAfterOperation, int categoryTag);

    int setCategoryTag();
    void print() const;
};

extern std::unordered_map<std::string, int> cardTransactionCategories;

Date parseDate(const std::string &str);
std::string extractAddress(const std::string &descriptionFull);
std::string getSubstring(const std::string &descriptionFull, std::string startToken, std::string endToken);
std::string extractCrucialDescriptionData(const std::string &descriptionFull, const std::string &type);

XMLElement *getFirstOperationTag(XMLDocument &xmlDocument);
std::string getOperationChild(XMLElement *operationTag, const char *childName);
std::vector<Operation> getAllOperations(const char *path);
std::vector<Operation> getOperationsByDate(const char *path, Month);
double myStringToDouble(const std::string &str);
std::string cleanBalanceString(const std::string &input);

namespace summary
{
    extern Operation operationsEatingOut;
    extern Operation operationsNonGroceryShopping;
    extern Operation operationsGroceryShopping;
    extern Operation operationsTransport;
    extern Operation operationsRegularExpenses;
    extern Operation operationsOthers;
    extern Operation operationsPhotography;
    extern Operation operationsIncoming;
    extern Operation operationsTotal;
}

void saveMapToJson(const std::unordered_map<std::string, int> &map, const std::string &filename);

std::unordered_map<std::string, int> loadMapFromJson(const std::string &filename);

// saveMapToJson(cardTransactionCategories, "categories.json");

// auto loaded = loadMapFromJson("categories.json");
