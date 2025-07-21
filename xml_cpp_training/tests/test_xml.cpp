#include <gtest/gtest.h>
#include "../xml_training_lib.h"
#include "../external/tinyxml2-master/tinyxml2.h"

// TEST(ParseDate, basicPrint)
// {
//     getOperation()->print();
// }

TEST(OperationTest, MatchesXmlData)
{
    std::unique_ptr<Operation> op = getOperation();

    ASSERT_NE(op, nullptr);

    EXPECT_EQ(op->date.year, 2025);
    EXPECT_EQ(op->date.month, 7);
    EXPECT_EQ(op->date.day, 13);

    EXPECT_EQ(op->type, "Płatność kartą");
    EXPECT_DOUBLE_EQ(op->amount, -41.00);
    EXPECT_DOUBLE_EQ(op->endingBalance, 2999.97);

    EXPECT_EQ(op->description.shopAddress, "TRATTORIA RIALTO, KRAKOW");
}
