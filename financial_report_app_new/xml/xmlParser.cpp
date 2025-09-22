#include "xmlParser.hpp"

using namespace tinyxml2;

std::unordered_map<std::string, int> cardTransactionCategories = {
    /*
    {"TRATTORIA", 1},
    {"llegro", 2},
    {"Good Lood", 1},
    {"RYNECZEK", 1},
    {"CARREFOUR", 3},
    {"ZABKA", 3},
    {"McDonalds", 1},
    {"jakdojade", 4},
    {"ALLEGRO", 2},
    {"ROSSMANN", 2},
    {"VINTED", 2},
    {"LIDL", 3},
    {"ALIEXPRESS", 2},
    {"LEWIATAN", 3},
    {"FLORA", 2},
    {"MCDONALDS", 1},
    {"EMPIK", 2},
    {"PADDLE", 5},
    {"SPORT EVOLUTION", 6},
    {"BUCZEK", 3},
    {"BIEDRONKA", 3},
    {"LOWICZ", 6},
    {"SPOTIFY", 5},
    {"KOLEO", 4},
    {"BACOWKA", 3},
    {"APPLE", 5},
    {"P4", 5},
    {"AIRBNB", 7},
    {"SPAR", 3},
    {"UBER", 4},
    {"Tauron", 5},
    {"LEROY", 2},
    {"Tkaniny", 7},
    {"RESTAURACJA", 1},
    {"KAUFLAND", 3},
    {"FOOD CARGO KULESZA", 1},
    {"NOTOPSTRYK", 7},
    {"KOLODZIEJCZYK", 3},
    {"NETFLIX", 5},
    {"Kwiaty", 2},
    {"ZIKO APTEKA", 2},
    {"FLORGARD", 2},
    {"PLUS KONRAD", 3},
    {"STOKROTKA", 3},
    {"KINGSMAN", 1},
    {"kfcdostawa", 1},
    {"Pharm", 2},
    {"PEPCO", 2},
    {"RESERVED", 2},
    {"HM", 2},
    {"ZARA", 2},
    {"Pyszne.pl", 1},
    {"AUTOMAT", 1},
    {"JYSK", 2},
    {"PASIBUS", 1},
    {"KFC", 1},
    {"MPK", 2},
    {"MYJNIA", 2},
    {"Hindus", 1},
    {"Tadeusz Skwarek", 1},
    {"APTEKA", 2},
    {"MERIDA", 2},
    {"SZAL DLA PLASTYKOW", 2},
    {"BISTRO JCI", 1},
    {"Action", 2},
    {"HALAMAKI", 1},
    {"REKOCZYNY CAFE", 1},
    {"BEEF", 1},
    {"użytkowanie karty", 5},
    {"PRZEMO WEBCON", 6},
    {"Revolut", 7},
    {"intercity", 4},
    {"maratonwarsza", 6},
    {"kartotekaonline", 5},
    {"DYNAMIKA", 5},
    {"cyfrowe", 7},
    {"infoto", 7},
    {"restaumatic", 1},
    {"dluta", 6},
    {"pomykalastudio", 6},
    {"TOTU", 5},
    {"RossmannRun", 6} */
};

namespace summary
{
    Operation operationsEatingOut{Date{}, "", "eating out", 0.0, 0.0, 1};
    Operation operationsNonGroceryShopping{Date{}, "", "non grocery shopping", 0.0, 0.0, 2};
    Operation operationsGroceryShopping{Date{}, "", "grocery shopping", 0.0, 0.0, 3};
    Operation operationsTransport{Date{}, "", "transport", 0.0, 0.0, 4};
    Operation operationsRegularExpenses{Date{}, "", "regular expenses", 0.0, 0.0, 5};
    Operation operationsOthers{Date{}, "", "others", 0.0, 0.0, 6};
    Operation operationsPhotography{Date{}, "", "photography", 0.0, 0.0, 7};
    Operation operationsIncoming{Date{}, "", "incoming", 0.0, 0.0, 9};
    Operation operationsTotal{Date{}, "", "total", 0.0, 0.0, 8};
}

Date::Date() : day(0), month(0), year(0) {}
Date::Date(int day, int month, int year) : day(day), month(month), year(year) {}

Operation::Operation(Date date, std::string type, std::string description, double amount, double totalBalanceAfterOperation)
    : date(date), type(type), description(description),
      amount(amount), totalBalanceAfterOperation(totalBalanceAfterOperation)
{

    categoryTag = setCategoryTag();
}

Operation::Operation(Date date, std::string type, std::string description, double amount, double totalBalanceAfterOperation, int categoryTag)
    : date(date), type(type), description(description),
      amount(amount), totalBalanceAfterOperation(totalBalanceAfterOperation), categoryTag(categoryTag) {}

int Operation::setCategoryTag()
{
    if (amount > 0)
    {
        return INCOMING_MONEY;
    }

    for (const auto &pairTagAndId : cardTransactionCategories)
    {
        if (description.find(pairTagAndId.first) != std::string::npos)
        {
            return pairTagAndId.second;
        }
    }
    std::cout << "description = " << description << std::endl;
    std::cout << "amount = " << amount << std::endl;
    return SELF_DEFINED;
}

void Operation::print() const
{
    std::cout << "Operation details:\n";
    std::cout << "  Date: " << date.day << "-" << date.month << "-" << date.year << "\n";
    std::cout << "  Type: " << type << "\n";
    std::cout << "\033[31m  Description: " << description << "\033[0m\n";
    printf("  Amount: %.2f\n", amount);
    std::cout << "  Total balanceAfterOperation: " << totalBalanceAfterOperation << "\n\n";
}

Date parseDate(const std::string &str)
{
    int year, month, day;
    char dash1, dash2;
    std::istringstream iss(str);
    iss >> year >> dash1 >> month >> dash2 >> day;

    if (iss.fail() || dash1 != '-' || dash2 != '-')
        throw std::invalid_argument("Invalid date format");

    return Date(day, month, year);
}

std::string getSubstring(const std::string &text, std::string start, std::string end)
{
    size_t startPos = text.find(start);
    if (startPos == std::string::npos)
        return "";
    startPos += start.length();

    size_t endPos = text.find(end, startPos);
    if (endPos == std::string::npos)
        return "";

    std::string result = text.substr(startPos, endPos - startPos);
    size_t first = result.find_first_not_of(" ");
    size_t last = result.find_last_not_of(" ");
    return (first == std::string::npos) ? "" : result.substr(first, last - first + 1);
}

std::string extractAddress(const std::string &descriptionFull)
{
    std::string address = getSubstring(descriptionFull, "Adres : ", " Miasto");
    std::string city = getSubstring(descriptionFull, "Miasto :", " Kraj");
    return address.empty() ? "" : address + ", " + city;
}

std::string extractCrucialDescriptionData(const std::string &desc, const std::string &type)
{
    if (type == "Płatność kartą" || type == "Wypłata z bankomatu")
        return getSubstring(desc, "Adres :", "Kraj");
    else if (type == "Przelew na telefon przychodz. zew.")
        return desc.find("nadawcy") != std::string::npos ? getSubstring(desc, "Nazwa nadawcy :", "Tytuł :") : getSubstring(desc, "Nazwa odbiorcy :", "OD:");
    else if (type == "Przelew na telefon przychodz. wew.")
        return desc.find("odbiorcy :") != std::string::npos ? getSubstring(desc, "Nazwa odbiorcy :", "Tytuł :") : getSubstring(desc, "Nazwa nadawcy :", "Adres");
    else if (type == "Przelew na konto")
        return getSubstring(desc, "Nazwa nadawcy :", "Adres nadawcy :");
    else if (type == "Przelew z karty")
        return getSubstring(desc, "Adres :", "Miasto :");
    else if (type == "Opłata za użytkowanie karty")
        return type;
    else if (type == "Płatność web - kod mobilny")
        return getSubstring(desc, "Adres :", "Operacja");
    else if (type == "Przelew z rachunku")
        return getSubstring(desc, "Nazwa odbiorcy :", "Tytuł :");
    else
        throw std::runtime_error("Unknown type: " + type);
}

XMLElement *getFirstOperationTag(XMLDocument &doc)
{
    XMLElement *root = doc.FirstChildElement("account-history");
    if (!root)
        return nullptr;

    XMLElement *ops = root->FirstChildElement("operations");
    if (!ops)
        return nullptr;

    return ops->FirstChildElement("operation");
}

std::string getOperationChild(XMLElement *tag, const char *child)
{
    XMLElement *el = tag->FirstChildElement(child);
    if (!el || !el->GetText())
        throw std::runtime_error(std::string("Missing <") + child + "> tag");
    return el->GetText();
}

// std::vector<Operation> getAllOperations(const char *path)
// {
//     std::vector<Operation> result;
//     XMLDocument doc;
//     if (doc.LoadFile(path) != XML_SUCCESS)
//         throw std::runtime_error("Failed to load file");

//     XMLElement *op = getFirstOperationTag(doc);
//     while (op != nullptr)
//     {
//         std::string dateStr = getOperationChild(op, "exec-date");
//         std::string type = getOperationChild(op, "type");
//         std::string desc = getOperationChild(op, "description");
//         std::string amountStr = getOperationChild(op, "amount");
//         std::string balanceStr = getOperationChild(op, "ending-balance");

//         Date date = parseDate(dateStr);
//         std::string cleanDesc = extractCrucialDescriptionData(desc, type);

//         result.emplace_back(date, type, cleanDesc, myStringToDouble(amountStr), myStringToDouble(cleanBalanceString(balanceStr)));
//         op = op->NextSiblingElement("operation");
//     }

//     return result;
// }

std::vector<Operation> getOperationsByDate(const char *path, Month selectedMonth, bool isDescriptionShortened)
{
    std::vector<Operation> result;
    XMLDocument doc;
    if (doc.LoadFile(path) != XML_SUCCESS)
        throw std::runtime_error("Failed to load file");

    XMLElement *op = getFirstOperationTag(doc);
    while (op != nullptr)
    {
        std::string dateStr = getOperationChild(op, "exec-date");
        Date date = parseDate(dateStr);

        if (date.getMonth() == static_cast<int>(selectedMonth))
        {
            std::string type = getOperationChild(op, "type");
            std::string desc = getOperationChild(op, "description");
            std::string amountStr = getOperationChild(op, "amount");
            std::string balanceStr = getOperationChild(op, "ending-balance");

            std::string processedDescription = isDescriptionShortened ? extractCrucialDescriptionData(desc, type) : desc;

            result.emplace_back(date, type, processedDescription, myStringToDouble(amountStr), myStringToDouble(cleanBalanceString(balanceStr)));
        }
        op = op->NextSiblingElement("operation");
    }
    // std::cout << "cardTransactionCategories.size = " << cardTransactionCategories.size() << std::endl;
    std::reverse(result.begin(), result.end());

    return result;
}

double myStringToDouble(const std::string &str)
{
    double result = 0.0;
    bool negative = false;
    size_t i = 0;

    if (str[i] == '-')
    {
        negative = true;
        ++i;
    }
    else if (str[i] == '+')
    {
        ++i;
    }

    while (i < str.length() && isdigit(str[i]))
    {
        result = result * 10 + (str[i] - '0');
        ++i;
    }

    if (i < str.length() && str[i] == '.')
    {
        ++i;
        double fraction = 0.0;
        double divider = 10.0;

        while (i < str.length() && isdigit(str[i]))
        {
            fraction += (str[i] - '0') / divider;
            divider *= 10.0;
            ++i;
        }

        result += fraction;
    }

    return negative ? -result : result;
}

std::string cleanBalanceString(const std::string &input)
{
    if (!input.empty() && input[0] == '+')
    {
        return input.substr(1);
    }
    return input;
}

void saveMapToJson(const std::unordered_map<std::string, int> &map, const std::string &filename)
{
    nlohmann::json j(map);
    std::ofstream out(filename);
    out << j.dump(4);
}

std::unordered_map<std::string, int> loadMapFromJson(const std::string &filename)
{
    std::ifstream in(filename);
    nlohmann::json j;
    in >> j;
    return j.get<std::unordered_map<std::string, int>>();
}
