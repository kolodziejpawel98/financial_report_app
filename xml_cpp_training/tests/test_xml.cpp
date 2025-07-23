#include <gtest/gtest.h>
#include "../xml_training_lib.h"
#include "../external/tinyxml2-master/tinyxml2.h"

// TEST(OperationTest, getFirstOperation)
// {
//     std::unique_ptr<Operation> op;
//     op = getOperationObject("../example.xml");
//     ASSERT_NE(op, nullptr);

//     EXPECT_EQ(op->date.year, 2025);
//     EXPECT_EQ(op->date.month, 7);
//     EXPECT_EQ(op->date.day, 13);

//     EXPECT_EQ(op->category, "placeholder");
//     EXPECT_DOUBLE_EQ(op->amount, -41.00);
//     EXPECT_DOUBLE_EQ(op->totalBalanceAfterOperation, 2999.97);

//     EXPECT_EQ(op->description, "TRATTORIA RIALTO, KRAKOW");
// }

// TEST(OperationTest, getAllOperations)
// {
//     std::vector<Operation> operations;
//     const char *path = "../example.xml";
//     operations = getAllOperations(path);

//     for (auto &operation : operations)
//     {
//         operation.print();
//     }
// }

TEST(OperationTest, parsingCategoryToDescription)
{
    std::vector<Operation> operations;
    const char *path = "../example.xml";
    operations = getAllOperations(path);

    for (auto &operation : operations)
    {
        if (operation.setCategoryTag() == 1)
        {
            std::cout << operation.description << " " << "\033[30m jedzenie na miescie\033[0m\n"
                      << std::endl;
        }
        else if (operation.setCategoryTag() == 2)
        {
            std::cout << operation.description << " " << "\033[30m zakupy niespozywcze\033[0m\n"
                      << std::endl;
        }
        else if (operation.setCategoryTag() == 3)
        {
            std::cout << operation.description << " " << "\033[30m zakupy spozywcze\033[0m\n"
                      << std::endl;
        }
        else if (operation.setCategoryTag() == 4)
        {
            std::cout << operation.description << " " << "\033[30m transport\033[0m\n"
                      << std::endl;
        }
        else if (operation.setCategoryTag() == 5)
        {
            std::cout << operation.description << " " << "\033[30m oplaty stale\033[0m\n"
                      << std::endl;
        }
        else if (operation.setCategoryTag() == 6)
        {
            std::cout << operation.description << " " << "\033[30m inne\033[0m\n"
                      << std::endl;
        }
        else if (operation.setCategoryTag() == 7)
        {
            std::cout << operation.description << " " << "\033[30m fotografia\033[0m\n"
                      << std::endl;
        }
        else if (operation.setCategoryTag() == -1)
        {
            std::cout << operation.description << " " << "\033[31merror\033[0m\n"
                      << std::endl;
        }
        else if (operation.setCategoryTag() == 999)
        {
            std::cout << operation.description << " " << "\033[32m $$$ money !\033[0m\n"
                      << std::endl;
        }
    }
}