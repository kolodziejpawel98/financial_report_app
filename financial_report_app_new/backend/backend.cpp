#include "backend.hpp"
#include <unistd.h>

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
    loadAllXmlData();

    getAllSelfDefinedOperations();

    // TODO: how about operations from different months (below)?

    QObject *buttonSaveChanges = m_rootObject->findChild<QObject *>("mainContent_button_saveChangesAndGoToNextScreen");
    if (buttonSaveChanges)
    {
        buttonSaveChanges->setProperty("enabled", false);
    }

    splitOperationsToCategories(selectedMonth);
    if (!temporarySelfDefinedOperations.empty())
    {
        operationsSelfDefinedIterator = temporarySelfDefinedOperations.begin();
        operationDescription->setOperationDescriptionText(QString::fromStdString(operationsSelfDefinedIterator->description));
        userDescription->setUserOperationDescriptionText(QString::fromStdString(operationsSelfDefinedIterator->description));
    }
}

void Backend::nextOperation()
{
    if (operationsSelfDefinedIterator != temporarySelfDefinedOperations.end() && tagIndex->getUserDescriptionCurrentTagIndex() != 0)
    {
        // !!!!!!!!!!!!!!!!!! do not remove below (need to add implementation)
        cardTransactionCategories.insert({operationsSelfDefinedIterator->description, tagIndex->getUserDescriptionCurrentTagIndex()});
        // !!!!!!!!!!!!!!!!!! do not remove
        ++operationsSelfDefinedIterator;
        if (operationsSelfDefinedIterator != temporarySelfDefinedOperations.end())
        {
            operationDescription->setOperationDescriptionText(QString::fromStdString(operationsSelfDefinedIterator->description));
            userDescription->setUserOperationDescriptionText(QString::fromStdString(operationsSelfDefinedIterator->description));
        }
    }
    else
    {
        saveMapToJson(cardTransactionCategories, TRANSACTION_TAGS_JSON_FILE);
        QObject *buttonSaveChanges = m_rootObject->findChild<QObject *>("mainContent_button_saveChangesAndGoToNextScreen");
        if (buttonSaveChanges)
        {
            buttonSaveChanges->setProperty("enabled", true);
        }
    }
}

void Backend::initOperationsByTypeScreen()
{
    loadAllXmlData();
    splitOperationsToCategories(selectedMonth);

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
}

void Backend::updateOperationsByTypeScreen()
{
    splitOperationsToCategories(selectedMonth);

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
    operationButtonListToDisplay->emitOperationsChangedSignal();
}

void Backend::setSelectedMonth(Month month)
{
    selectedMonth = month;

    QString monthName;
    switch (month)
    {
    case Month::January:
        monthName = "January";
        break;
    case Month::February:
        monthName = "February";
        break;
    case Month::March:
        monthName = "March";
        break;
    case Month::April:
        monthName = "April";
        break;
    case Month::May:
        monthName = "May";
        break;
    case Month::June:
        monthName = "June";
        break;
    case Month::July:
        monthName = "July";
        break;
    case Month::August:
        monthName = "August";
        break;
    case Month::September:
        monthName = "September";
        break;
    case Month::October:
        monthName = "October";
        break;
    case Month::November:
        monthName = "November";
        break;
    case Month::December:
        monthName = "December";
        break;
    default:
        throw std::runtime_error("Month selection error");
    }
    setSelectedMonthAsQString(monthName);
    clearData();
    updateOperationsByTypeScreen();
}

void Backend::setSelectedMonthAsQString(const QString &month)
{
    if (selectedMonthAsQString != month)
    {
        selectedMonthAsQString = month;
        emit selectedMonthAsQStringChanged();
    }
}

QString Backend::getSelectedMonthAsQString() const
{
    return selectedMonthAsQString;
}

void Backend::clearData()
{
    operationButtonList_operationsEatingOut->clear();
    operationButtonList_operationsNonGroceryShopping->clear();
    operationButtonList_operationsGroceryShopping->clear();
    operationButtonList_operationsTransportation->clear();
    operationButtonList_operationsRegularExpenses->clear();
    operationButtonList_operationsOtherExpenses->clear();
    operationButtonList_operationsPhotography->clear();
    operationButtonList_operationsSelfDefined->clear();
    operationButtonList_operationsIncoming->clear();
    operationButtonList_operationsSummary->clear();

    allOperations.clear();
    operationsEatingOut.clear();
    operationsNonGroceryShopping.clear();
    operationsGroceryShopping.clear();
    operationsTransport.clear();
    operationsRegularExpenses.clear();
    operationsOtherExpenses.clear();
    operationsPhotography.clear();
    operationsOtherExpenses.clear();
    operationsSelfDefined.clear();
    operationsIncoming.clear();
    operationsSummary.clear();

    summary::operationsEatingOut.amount = 0.0;
    summary::operationsNonGroceryShopping.amount = 0.0;
    summary::operationsGroceryShopping.amount = 0.0;
    summary::operationsTransport.amount = 0.0;
    summary::operationsRegularExpenses.amount = 0.0;
    summary::operationsOtherExpenses.amount = 0.0;
    summary::operationsPhotography.amount = 0.0;
    summary::operationsTotal.amount = 0.0;
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

void Backend::loadAllXmlData(bool isDescriptionShortened)
{
    std::string pathStr = xmlFilePath.toStdString();
    const char *path = pathStr.c_str();
    allOperationsByMonth.clear();

    // TODO!!!!! separate months for different years!!!!!!!!!!!!!

    for (int month = 1; month <= std::to_underlying(Month::December); ++month)
    {
        Month currentMonth = static_cast<Month>(month);
        allOperationsByMonth.insert({currentMonth, getOperationsByDate(path, currentMonth, isDescriptionShortened)});
    }
}

void Backend::getAllSelfDefinedOperations()
{
    for (const auto &[month, operations] : allOperationsByMonth)
    {
        for (const auto &operation : operations)
        {
            if (operation.categoryTag == SELF_DEFINED)
            {
                temporarySelfDefinedOperations.push_back(operation);
                // std::cout << "Found operation with tag 6 in month " << static_cast<int>(month)
                //   << ": " << operation.description << std::endl;
            }
        }
    }
}

void Backend::splitOperationsToCategories(Month currentMonth)
{
    std::vector<Operation> operationInDefinedMonth;

    allOperations.clear();
    operationsEatingOut.clear();
    operationsNonGroceryShopping.clear();
    operationsGroceryShopping.clear();
    operationsTransport.clear();
    operationsRegularExpenses.clear();
    operationsPhotography.clear();
    operationsOtherExpenses.clear();
    operationsSummary.clear();

    auto it = allOperationsByMonth.find(currentMonth);
    if (it != allOperationsByMonth.end())
    {
        operationInDefinedMonth = it->second;
    }

    for (auto &operation : operationInDefinedMonth)
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
            operationsOtherExpenses.emplace_back(operation);
            summary::operationsOtherExpenses.amount += operation.amount;
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
                         summary::operationsOtherExpenses,
                         summary::operationsPhotography,
                         summary::operationsIncoming,
                         summary::operationsTotal};
}