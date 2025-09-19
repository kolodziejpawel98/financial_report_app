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
    loadXmlData(false);

    if (!operationsSelfDefined.empty())
    {
        operationsSelfDefinedIterator = operationsSelfDefined.begin();
        operationDescription->setOperationDescriptionText(QString::fromStdString(operationsSelfDefinedIterator->description));
        userDescription->setUserOperationDescriptionText(QString::fromStdString(operationsSelfDefinedIterator->description));
    }
}

void Backend::nextOperation()
{
    if (operationsSelfDefinedIterator != operationsSelfDefined.end() && tagIndex->getUserDescriptionCurrentTagIndex() != 0)
    {
        cardTransactionCategories.insert({operationsSelfDefinedIterator->description, tagIndex->getUserDescriptionCurrentTagIndex()});
        ++operationsSelfDefinedIterator;
        if (operationsSelfDefinedIterator != operationsSelfDefined.end())
        {
            operationDescription->setOperationDescriptionText(QString::fromStdString(operationsSelfDefinedIterator->description));
            userDescription->setUserOperationDescriptionText(QString::fromStdString(operationsSelfDefinedIterator->description));
            // std::cout << "operationDescriptionText = " << operationDescriptionText.toStdString() << std::endl;
            // ui->operationForSettingTagLabel->setText(
            //     QString::fromStdString(operationsSelfDefinedIterator->description));
        }
    }
    else
    {
        std::cout << "koniec" << std::endl;
        // ui->nextPageButton->setVisible(true);
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