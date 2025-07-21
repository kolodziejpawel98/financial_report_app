#include <gtest/gtest.h>
#include "../xml_training_lib.h"
#include "../external/tinyxml2-master/tinyxml2.h"

// // --- parseDate --------------------------------------------------

TEST(ParseDate, GoodFormat)
{
    // Date d = parseDate("2025-07-21");
    // EXPECT_EQ(d.year, 2025);
    // EXPECT_EQ(d.month, 7);
    // EXPECT_EQ(d.day, 21);

    XMLDocument doc;
    XMLElement *op = loadOperation(doc);

    // const char *description = op->FirstChildElement("description")->GetText();
    // std::cout << "description: " << description << "\n";

    // XMLElement *nextOperation = op->NextSiblingElement("operation");

    // Operation operation{};
    if (op != nullptr)
    {
        // std::string orderDate = op->FirstChildElement("order-date")->GetText();
        std::string execDate = op->FirstChildElement("exec-date")->GetText();
        std::string type = op->FirstChildElement("type")->GetText();
        std::string description = op->FirstChildElement("description")->GetText();
        std::string amount = op->FirstChildElement("amount")->GetText();
        std::string endingBalance = op->FirstChildElement("ending-balance")->GetText();

        Date date;
        try
        {
            date = parseDate(execDate);
            // std::cout << "Day: " << date.day << ", Month: " << date.month << ", Year: " << date.year << "\n";
        }
        catch (const std::exception &e)
        {
            std::cout << "Error: " << e.what() << "\n";
        }

        Operation operation{
            date,
            Description("placeholder", "placeholder"),
            type,
            std::stod(amount),
            std::stod(endingBalance)};

        operation.print();
    }
    else
    {
        std::cout << "No operation found\n";
    }
}

// TEST(ParseDate, BadFormatThrows)
// {
//     EXPECT_THROW(parseDate("21-07-2025"), std::invalid_argument);
//     EXPECT_THROW(parseDate("foo"), std::invalid_argument);
//     EXPECT_THROW(parseDate("2025/07/21"), std::invalid_argument);
// }

// // --- loadOperation ------------------------------------------------
// //
// // Używa example.xml z TEST_DATA_DIR (ustawione w CMake).
// //
// TEST(LoadOperation, LoadsFromExample)
// {
//     tinyxml2::XMLDocument doc;
//     auto *op = loadOperation(doc, TEST_DATA_DIR "/example.xml");
//     // Nie wiemy, czy example.xml ma operacje — testowy warunek minimalny:
//     SUCCEED(); // Po prostu upewniamy się, że nie crashuje.
//     (void)op;  // Jeśli chcesz, możesz EXPECT_NE(op, nullptr);
// }
