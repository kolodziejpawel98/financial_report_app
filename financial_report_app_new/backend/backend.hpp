#pragma once
#include <QObject>
#include <QDebug>
#include <QFileDialog>
#include <QQmlListProperty>
#include "globals.hpp"
#include <iostream>
#include <type_traits>
#include <utility>
#include "xml/xmlParser.hpp"
#include "DescribeUndefinedTagsScreen.hpp"
#include "OperationsByTypeScreen.hpp"

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DescribeUndefinedTagsScreen::TagIndex *tagIndex READ getTagIndex CONSTANT)
    Q_PROPERTY(DescribeUndefinedTagsScreen::UserDescription *userDescription READ getUserDescription CONSTANT)
    Q_PROPERTY(DescribeUndefinedTagsScreen::OperationDescription *operationDescription READ getOperationDescription CONSTANT)
    Q_PROPERTY(OperationsByTypeScreen::OperationButtonList *operationButtonList_operationsEatingOut READ getOperationButtonList_operationsEatingOut CONSTANT)
    Q_PROPERTY(OperationsByTypeScreen::OperationButtonList *operationButtonList_operationsNonGroceryShopping READ getOperationButtonList_operationsNonGroceryShopping CONSTANT)
    Q_PROPERTY(OperationsByTypeScreen::OperationButtonList *operationButtonList_operationsGroceryShopping READ getOperationButtonList_operationsGroceryShopping CONSTANT)
    Q_PROPERTY(OperationsByTypeScreen::OperationButtonList *operationButtonList_operationsTransportation READ getOperationButtonList_operationsTransportation CONSTANT)
    Q_PROPERTY(OperationsByTypeScreen::OperationButtonList *operationButtonList_operationsRegularExpenses READ getOperationButtonList_operationsRegularExpenses CONSTANT)
    Q_PROPERTY(OperationsByTypeScreen::OperationButtonList *operationButtonList_operationsOtherExpenses READ getOperationButtonList_operationsOtherExpenses CONSTANT)
    Q_PROPERTY(OperationsByTypeScreen::OperationButtonList *operationButtonList_operationsPhotography READ getOperationButtonList_operationsPhotography CONSTANT)
    Q_PROPERTY(OperationsByTypeScreen::OperationButtonList *operationButtonList_operationsSelfDefined READ getOperationButtonList_operationsSelfDefined CONSTANT)
    Q_PROPERTY(OperationsByTypeScreen::OperationButtonList *operationButtonList_operationsIncoming READ getOperationButtonList_operationsIncoming CONSTANT)
    Q_PROPERTY(OperationsByTypeScreen::OperationButtonList *operationButtonList_operationsSummary READ getOperationButtonList_operationsSummary CONSTANT)
    Q_PROPERTY(QString selectedMonthAsQString READ getSelectedMonthAsQString WRITE setSelectedMonthAsQString NOTIFY selectedMonthAsQStringChanged)

public:
    explicit Backend(QObject *parent = nullptr)
        : QObject(parent),
          tagIndex(new DescribeUndefinedTagsScreen::TagIndex(this)),
          userDescription(new DescribeUndefinedTagsScreen::UserDescription(this)),
          operationDescription(new DescribeUndefinedTagsScreen::OperationDescription(this)),
          operationButtonList_operationsEatingOut(new OperationsByTypeScreen::OperationButtonList(this)),
          operationButtonList_operationsNonGroceryShopping(new OperationsByTypeScreen::OperationButtonList(this)),
          operationButtonList_operationsGroceryShopping(new OperationsByTypeScreen::OperationButtonList(this)),
          operationButtonList_operationsTransportation(new OperationsByTypeScreen::OperationButtonList(this)),
          operationButtonList_operationsRegularExpenses(new OperationsByTypeScreen::OperationButtonList(this)),
          operationButtonList_operationsOtherExpenses(new OperationsByTypeScreen::OperationButtonList(this)),
          operationButtonList_operationsPhotography(new OperationsByTypeScreen::OperationButtonList(this)),
          operationButtonList_operationsSelfDefined(new OperationsByTypeScreen::OperationButtonList(this)),
          operationButtonList_operationsIncoming(new OperationsByTypeScreen::OperationButtonList(this)),
          operationButtonList_operationsSummary(new OperationsByTypeScreen::OperationButtonList(this))
    {
    }

    void setRootObject(QObject *root) { m_rootObject = root; }
    Q_INVOKABLE void printTestString();
    Q_INVOKABLE bool loadXmlButtonClicked();
    Q_INVOKABLE QStringList getComboBoxItems();
    Q_INVOKABLE void initDescribeUndefinedTagsScreen();
    Q_INVOKABLE void initOperationsByTypeScreen();
    // Q_INVOKABLE void setMonthSelectorCurrentMonth();
    void addOperationButton(std::vector<Operation> &, OperationsByTypeScreen::OperationButtonList *) const;
    void loadXmlData(bool = true);
    void loadAllXmlData(bool = true);
    void printXmlDataOnScreen();
    void splitOperationsToCategories(Month);
    Q_INVOKABLE void nextOperation();
    Q_INVOKABLE void previousMonth();
    Q_INVOKABLE void nextMonth();

    DescribeUndefinedTagsScreen::TagIndex *getTagIndex() const { return tagIndex; }
    DescribeUndefinedTagsScreen::UserDescription *getUserDescription() const { return userDescription; }
    DescribeUndefinedTagsScreen::OperationDescription *getOperationDescription() const { return operationDescription; }

    OperationsByTypeScreen::OperationButtonList *getOperationButtonList_operationsEatingOut() const { return operationButtonList_operationsEatingOut; }
    OperationsByTypeScreen::OperationButtonList *getOperationButtonList_operationsNonGroceryShopping() const { return operationButtonList_operationsNonGroceryShopping; }
    OperationsByTypeScreen::OperationButtonList *getOperationButtonList_operationsGroceryShopping() const { return operationButtonList_operationsGroceryShopping; }
    OperationsByTypeScreen::OperationButtonList *getOperationButtonList_operationsTransportation() const { return operationButtonList_operationsTransportation; }
    OperationsByTypeScreen::OperationButtonList *getOperationButtonList_operationsRegularExpenses() const { return operationButtonList_operationsRegularExpenses; }
    OperationsByTypeScreen::OperationButtonList *getOperationButtonList_operationsOtherExpenses() const { return operationButtonList_operationsOtherExpenses; }
    OperationsByTypeScreen::OperationButtonList *getOperationButtonList_operationsPhotography() const { return operationButtonList_operationsPhotography; }
    OperationsByTypeScreen::OperationButtonList *getOperationButtonList_operationsSelfDefined() const { return operationButtonList_operationsSelfDefined; }
    OperationsByTypeScreen::OperationButtonList *getOperationButtonList_operationsIncoming() const { return operationButtonList_operationsIncoming; }
    OperationsByTypeScreen::OperationButtonList *getOperationButtonList_operationsSummary() const { return operationButtonList_operationsSummary; }

    void setSelectedMonth(Month month);
    void clearData();
    void setSelectedMonthAsQString(const QString &month);
    QString getSelectedMonthAsQString() const;

signals:
    void selectedMonthAsQStringChanged();

private:
    QObject *m_rootObject = nullptr;
    QString xmlFilePath = "";
    const std::string TRANSACTION_TAGS_JSON_FILE = "../xml/categoriesTags.json";
    Month selectedMonth = Month::April;
    QString selectedMonthAsQString = "April";
    std::map<Month, std::vector<Operation>> allOperationsByMonth;

    std::vector<Operation> allOperations;
    std::vector<Operation> operationsEatingOut;
    std::vector<Operation> operationsNonGroceryShopping;
    std::vector<Operation> operationsGroceryShopping;
    std::vector<Operation> operationsTransport;
    std::vector<Operation> operationsRegularExpenses;
    std::vector<Operation> operationsOtherExpenses;
    std::vector<Operation> operationsPhotography;
    std::vector<Operation> operationsOthers;
    std::vector<Operation> operationsSelfDefined;
    std::vector<Operation> operationsIncoming;
    std::vector<Operation> operationsSummary;
    std::vector<Operation>::iterator operationsSelfDefinedIterator;

    DescribeUndefinedTagsScreen::TagIndex *tagIndex;
    DescribeUndefinedTagsScreen::UserDescription *userDescription;
    DescribeUndefinedTagsScreen::OperationDescription *operationDescription;

    OperationsByTypeScreen::OperationButtonList *operationButtonList_operationsEatingOut;
    OperationsByTypeScreen::OperationButtonList *operationButtonList_operationsNonGroceryShopping;
    OperationsByTypeScreen::OperationButtonList *operationButtonList_operationsGroceryShopping;
    OperationsByTypeScreen::OperationButtonList *operationButtonList_operationsTransportation;
    OperationsByTypeScreen::OperationButtonList *operationButtonList_operationsRegularExpenses;
    OperationsByTypeScreen::OperationButtonList *operationButtonList_operationsOtherExpenses;
    OperationsByTypeScreen::OperationButtonList *operationButtonList_operationsPhotography;
    OperationsByTypeScreen::OperationButtonList *operationButtonList_operationsSelfDefined;
    OperationsByTypeScreen::OperationButtonList *operationButtonList_operationsIncoming;
    OperationsByTypeScreen::OperationButtonList *operationButtonList_operationsSummary;
};
