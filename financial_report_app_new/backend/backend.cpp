#include "backend.hpp"

void Backend::printTestString()
{
    std::cout << "xd = " << sampleText << std::endl;
}

bool Backend::loadXmlButtonClicked()
{
    xmlFilePath = QFileDialog::getOpenFileName(nullptr, "Choose a file", "", "All Files (*.*)");
    return xmlFilePath.isEmpty() ? false : true;
}

QStringList Backend::getComboBoxItems()
{
    return {"<choose category>", "groceries", "non-grocery shopping", "going-out expenses", "transportation", "regular payments", "others", "photography", "income"};
}

void Backend::initDescribeUndefinedTagsScreen()
{
    cardTransactionCategories = loadMapFromJson(TRANSACTION_TAGS_JSON_FILE);
    // loadXmlData(false);
    loadXmlData();
    QObject *buttonSaveChanges = m_rootObject->findChild<QObject *>("mainContent_button_saveChangesAndGoToNextScreen");
    if (buttonSaveChanges)
    {
        buttonSaveChanges->setProperty("enabled", false);
    }

    if (!operationsSelfDefined.empty())
    {
        operationsSelfDefinedIterator = operationsSelfDefined.begin();
        operationDescription->setOperationDescriptionText(QString::fromStdString(operationsSelfDefinedIterator->description));
        userDescription->setUserOperationDescriptionText(QString::fromStdString(operationsSelfDefinedIterator->description));
    }
}

void Backend::initOperationsByTypeScreen()
{
    loadXmlData();

    addOperationButton(operationsEatingOut, operationButtonList_operationsEatingOut);
    addOperationButton(operationsNonGroceryShopping, operationButtonList_operationsNonGroceryShopping);
    addOperationButton(operationsGroceryShopping, operationButtonList_operationsGroceryShopping);
    addOperationButton(operationsTransport, operationButtonList_operationsTransportation);
    addOperationButton(operationsRegularExpenses, operationButtonList_operationsRegularExpenses);
    addOperationButton(operationsPhotography, operationButtonList_operationsPhotography);
    addOperationButton(operationsOtherExpenses, operationButtonList_operationsOtherExpenses);
    addOperationButton(operationsSelfDefined, operationButtonList_operationsSelfDefined);
    addOperationButton(operationsIncoming, operationButtonList_operationsIncoming);
    addOperationButton(operationsSummary, operationButtonList_operationsSummary);

    setSelectedMonth(Month::June);
}

void Backend::previousMonth()
{
    int monthValue = static_cast<int>(selectedMonth);
    if (monthValue == 1)
        monthValue = 12;
    else
        monthValue--;

    setSelectedMonth(static_cast<Month>(monthValue));
}

void Backend::nextMonth()
{
    int monthValue = static_cast<int>(selectedMonth);
    if (monthValue == 12)
        monthValue = 1;
    else
        monthValue++;

    setSelectedMonth(static_cast<Month>(monthValue));
}

void Backend::addOperationButton(std::vector<Operation> &operationCategoryToDisplay, OperationsByTypeScreen::OperationButtonList *operationButtonListToDisplay) const
{
    std::string spaceBetweenInformations = "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
    std::string textColor = "";
    for (auto &operation : operationCategoryToDisplay)
    {
        if (operation.amount > 0)
        {
            textColor = "<span style='color:green;'>";
        }
        else
        {
            textColor = "<span style='color:red;'>";
        }
        std::string descriptionBannerText = operation.date.getDate() +
                                            spaceBetweenInformations +
                                            "<b>" +
                                            operation.description +
                                            "</b>" +
                                            spaceBetweenInformations +
                                            textColor +
                                            QString::number(operation.amount, 'f', 2).toStdString() +
                                            "</span>" +
                                            spaceBetweenInformations +
                                            QString::number(operation.totalBalanceAfterOperation, 'f', 2).toStdString() +
                                            " PLN";

        operationButtonListToDisplay->addButton(QString::number(operation.amount, 'f', 2), QString::fromStdString(descriptionBannerText), 50);
    }
}

void Backend::nextOperation()
{
    if (operationsSelfDefinedIterator != operationsSelfDefined.end() && tagIndex->getUserDescriptionCurrentTagIndex() != 0)
    {
        // !!!!!!!!!!!!!!!!!! do not remove below (need to add implementation)
        // cardTransactionCategories.insert({operationsSelfDefinedIterator->description, tagIndex->getUserDescriptionCurrentTagIndex()});
        // !!!!!!!!!!!!!!!!!! do not remove
        ++operationsSelfDefinedIterator;
        if (operationsSelfDefinedIterator != operationsSelfDefined.end())
        {
            operationDescription->setOperationDescriptionText(QString::fromStdString(operationsSelfDefinedIterator->description));
            userDescription->setUserOperationDescriptionText(QString::fromStdString(operationsSelfDefinedIterator->description));
        }
    }
    else
    {
        QObject *buttonSaveChanges = m_rootObject->findChild<QObject *>("mainContent_button_saveChangesAndGoToNextScreen");
        if (buttonSaveChanges)
        {
            buttonSaveChanges->setProperty("enabled", true);
        }
    }
}

int DescribeUndefinedTagsScreen::TagIndex::getUserDescriptionCurrentTagIndex() const { return userDescriptionCurrentTagIndex; }

void DescribeUndefinedTagsScreen::TagIndex::setUserDescriptionCurrentTagIndex(int index)
{
    if (userDescriptionCurrentTagIndex != index)
    {
        userDescriptionCurrentTagIndex = index;
        emit userDescriptionCurrentTagIndexChanged();
    }
}

QString DescribeUndefinedTagsScreen::UserDescription::getUserOperationDescriptionText() const { return m_userOperationDescriptionText; }

void DescribeUndefinedTagsScreen::UserDescription::setUserOperationDescriptionText(const QString &text)
{
    if (m_userOperationDescriptionText != text)
    {
        m_userOperationDescriptionText = text;
        emit userOperationDescriptionTextChanged();
    }
}

QString DescribeUndefinedTagsScreen::OperationDescription::getOperationDescriptionText() const { return m_operationDescriptionText; }

void DescribeUndefinedTagsScreen::OperationDescription::setOperationDescriptionText(const QString &text)
{
    if (m_operationDescriptionText != text)
    {
        m_operationDescriptionText = text;
        emit operationDescriptionTextChanged();
    }
}

void Backend::loadXmlData(bool isDescriptionShortened)
{
    allOperations.clear();
    operationsEatingOut.clear();
    operationsNonGroceryShopping.clear();
    operationsGroceryShopping.clear();
    operationsTransport.clear();
    operationsRegularExpenses.clear();
    operationsPhotography.clear();
    operationsOthers.clear();
    operationsSummary.clear();

    std::string pathStr = xmlFilePath.toStdString();
    const char *path = pathStr.c_str();
    allOperations = getOperationsByDate(path, selectedMonth, isDescriptionShortened);

    for (auto &operation : allOperations)
    {
        if (operation.categoryTag == EATING_OUT)
        {
            operationsEatingOut.emplace_back(operation);
            summary::operationsEatingOut.amount += operation.amount;
            summary::operationsTotal.amount += operation.amount;
        }
        else if (operation.categoryTag == NON_GROCERY_SHOPPING)
        {
            operationsNonGroceryShopping.emplace_back(operation);
            summary::operationsNonGroceryShopping.amount += operation.amount;
            summary::operationsTotal.amount += operation.amount;
        }
        else if (operation.categoryTag == GROCERY_SHOPPING)
        {
            operationsGroceryShopping.emplace_back(operation);
            summary::operationsGroceryShopping.amount += operation.amount;
            summary::operationsTotal.amount += operation.amount;
        }
        else if (operation.categoryTag == TRANSPORT)
        {
            operationsTransport.emplace_back(operation);
            summary::operationsTransport.amount += operation.amount;
            summary::operationsTotal.amount += operation.amount;
        }
        else if (operation.categoryTag == REGULAR_EXPENSES)
        {
            operationsRegularExpenses.emplace_back(operation);
            summary::operationsRegularExpenses.amount += operation.amount;
            summary::operationsTotal.amount += operation.amount;
        }
        else if (operation.categoryTag == OTHERS)
        {
            operationsOthers.emplace_back(operation);
            summary::operationsOthers.amount += operation.amount;
            summary::operationsTotal.amount += operation.amount;
        }
        else if (operation.categoryTag == PHOTOGRAPHY)
        {
            operationsPhotography.emplace_back(operation);
            summary::operationsPhotography.amount += operation.amount;
            summary::operationsTotal.amount += operation.amount;
        }

        else if (operation.categoryTag == SELF_DEFINED)
        {
            operationsSelfDefined.emplace_back(operation);
        }
        else if (operation.categoryTag == INCOMING_MONEY)
        {
            operationsIncoming.emplace_back(operation);
        }
    }

    operationsSummary = {summary::operationsEatingOut,
                         summary::operationsNonGroceryShopping,
                         summary::operationsGroceryShopping,
                         summary::operationsTransport,
                         summary::operationsRegularExpenses,
                         summary::operationsOthers,
                         summary::operationsPhotography,
                         summary::operationsIncoming,
                         summary::operationsTotal};
    allOperations.clear();
}

void Backend::printXmlDataOnScreen()
{
    // QPoint p0{290, 110};
    // QPoint p1 = drawExpensesLabels(ui->eatingOutLabelsContainer, ui->eatingOutHeading, operationsEatingOut, EATING_OUT, p0);
    // QPoint p2 = drawExpensesLabels(ui->nonGroceryShoppingLabelsContainer, ui->nonGroceryShoppingHeading, operationsNonGroceryShopping, NON_GROCERY_SHOPPING, p1);
    // QPoint p3 = drawExpensesLabels(ui->groceryShoppingLabelsContainer, ui->groceryShoppingHeading, operationsGroceryShopping, GROCERY_SHOPPING, p2);
    // QPoint p4 = drawExpensesLabels(ui->transportationLabelsContainer, ui->transportationHeading, operationsTransport, TRANSPORT, p3);
    // QPoint p5 = drawExpensesLabels(ui->regularExpensesLabelsContainer, ui->regularExpensesHeading, operationsRegularExpenses, REGULAR_EXPENSES, p4);
    // QPoint p6 = drawExpensesLabels(ui->otherSpendingsLabelsContainer, ui->otherSpendingsHeading, operationsOthers, OTHERS, p5);
    // QPoint p7 = drawExpensesLabels(ui->photographyLabelsContainer, ui->photographyHeading, operationsPhotography, PHOTOGRAPHY, p6);
    // // QPoint p8 = drawExpensesLabels(ui->incomingLabelsContainer, ui->incomingHeading, operationsIncoming, INCOMING_MONEY, p7);
    // QPoint p8 = drawExpensesLabels(ui->totalSpendingsLabelsContainer, ui->totalSpendingsHeading, operationsSummary, SELF_DEFINED, p7);
}

// QPoint MainWindow::drawExpensesLabels(QWidget *labelsContainer,
//                                       QLabel *labelsContainerHeader,
//                                       const std::vector<Operation> &operations,
//                                       int categoryTagToPrint,
//                                       QPoint movingPoints)
// {
//     labelsContainerHeader->move(movingPoints.x(), movingPoints.y() + 20);
//     labelsContainer->move(movingPoints.x(), movingPoints.y() + 40);

//     int xCoordinateOfLabelInContainer = 0;
//     int yCoordinateOfLabelInContainer = 0;
//     int spacingBetweenLabels = 5;
//     int maxWidthOfLabelsContainer = labelsContainer->width();

//     for (auto &operation : operations)
//     {
//         OperationLabel *label = new OperationLabel(operation, labelsContainer);
//         label->setText(QString::number(operation.amount, 'f', 2));

//         label->setStyleSheet("color: black; font-size: 12px; font-family: Roboto; font-size: 12px; font-style: normal;");
//         label->adjustSize();
//         label->setCursor(Qt::PointingHandCursor);
//         label->installEventFilter(this);

//         expenseLabels.push_back(label);

//         int predictedWidthOfLabel = xCoordinateOfLabelInContainer + label->width();
//         if (predictedWidthOfLabel > maxWidthOfLabelsContainer)
//         {
//             xCoordinateOfLabelInContainer = 0;
//             yCoordinateOfLabelInContainer += label->height() + spacingBetweenLabels;
//         }
//         label->move(xCoordinateOfLabelInContainer, yCoordinateOfLabelInContainer);
//         label->show();
//         xCoordinateOfLabelInContainer += label->width() + spacingBetweenLabels;
//     }

//     labelsContainer->resize(maxWidthOfLabelsContainer, yCoordinateOfLabelInContainer + 20);
//     QPoint posRelativeToMainWindow = labelsContainer->mapTo(this, labelsContainer->rect().bottomLeft());
//     return posRelativeToMainWindow;
// }