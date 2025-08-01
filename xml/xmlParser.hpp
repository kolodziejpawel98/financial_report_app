#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "tinyxml2.h"

using namespace tinyxml2;

#pragma once

const int EATING_OUT = 1;
const int NON_GROCERY_SHOPPING = 2;
const int GROCERY_SHOPPING = 3;
const int TRANSPORT = 4;
const int REGULAR_EXPENSES = 5;
const int OTHERS = 6;
const int PHOTOGRAPHY = 7;
const int SER_DEFINED = 8;
const int ERROR = -1;
const int INCOMING_MONEY = 999;

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
    int setCategoryTag();
    void print() const;
};

extern std::unordered_map<std::string, int> cardTransactionCategories;

Date parseDate(const std::string &str);
std::string extractAddress(const std::string &descriptionFull);
std::string getSubstring(const std::string &descriptionFull, std::string startToken, std::string endToken);
std::string extractCrucialData(const std::string &descriptionFull, const std::string &type);

XMLElement *getFirstOperationTag(XMLDocument &xmlDocument);
std::string getOperationChild(XMLElement *operationTag, const char *childName);
std::vector<Operation> getAllOperations(const char *path);
