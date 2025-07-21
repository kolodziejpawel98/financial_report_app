#include <iostream>
#include "external/tinyxml2-master/tinyxml2.h"
#include "xml_training_lib.h"

using namespace tinyxml2;

// int main()
// {
//     XMLDocument doc;
//     XMLElement *op = loadOperation(doc, "example.xml");

//     if (!op)
//     {
//         std::cout << "No operation found\n";
//         return 0;
//     }

//     auto getText = [](XMLElement *e) -> const char *
//     {
//         return (e && e->GetText()) ? e->GetText() : "";
//     };

//     std::string execDate = getText(op->FirstChildElement("exec-date"));
//     std::string type = getText(op->FirstChildElement("type"));
//     std::string description = getText(op->FirstChildElement("description"));
//     std::string amountStr = getText(op->FirstChildElement("amount"));
//     std::string endingStr = getText(op->FirstChildElement("ending-balance"));

//     Date date;
//     try
//     {
//         date = parseDate(execDate);
//     }
//     catch (const std::exception &e)
//     {
//         std::cout << "Error: " << e.what() << "\n";
//     }

//     Operation operation{
//         date,
//         Description("placeholder", "placeholder"),
//         type,
//         amountStr.empty() ? 0.0 : std::stod(amountStr),
//         endingStr.empty() ? 0.0 : std::stod(endingStr)};

//     operation.print();
//     return 0;
// }

int main()
{

    return 0;
}