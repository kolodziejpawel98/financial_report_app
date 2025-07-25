#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "tinyxml2.h"

using namespace tinyxml2;

struct Date
{
    int day;
    int month;
    int year;

    Date();
    Date(int day, int month, int year);
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
