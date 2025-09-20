#include <QObject>
#include <QDebug>
#include <QFileDialog>
#include "globals.hpp"
#include <iostream>
#include "xml/xmlParser.hpp"

namespace DescribeUndefinedTagsScreen
{
    class TagIndex : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(int userDescriptionCurrentTagIndex
                       READ getUserDescriptionCurrentTagIndex
                           WRITE setUserDescriptionCurrentTagIndex
                               NOTIFY userDescriptionCurrentTagIndexChanged)
    public:
        explicit TagIndex(QObject *parent = nullptr) : QObject(parent) {}

        int getUserDescriptionCurrentTagIndex() const;
        void setUserDescriptionCurrentTagIndex(int);

    signals:
        void userDescriptionCurrentTagIndexChanged();

    private:
        int userDescriptionCurrentTagIndex = -1;
    };

    class OperationDescription : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString operationDescriptionText
                       READ getOperationDescriptionText
                           WRITE setOperationDescriptionText
                               NOTIFY operationDescriptionTextChanged)
    public:
        explicit OperationDescription(QObject *parent = nullptr) : QObject(parent) {}

        QString getOperationDescriptionText() const;
        void setOperationDescriptionText(const QString &);

    signals:
        void operationDescriptionTextChanged();

    private:
        QString m_operationDescriptionText = "";
    };

    class UserDescription : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString userOperationDescriptionText
                       READ getUserOperationDescriptionText
                           WRITE setUserOperationDescriptionText
                               NOTIFY userOperationDescriptionTextChanged)
    public:
        explicit UserDescription(QObject *parent = nullptr) : QObject(parent) {}

        QString getUserOperationDescriptionText() const;
        void setUserOperationDescriptionText(const QString &);

    signals:
        void userOperationDescriptionTextChanged();

    private:
        QString m_userOperationDescriptionText = "";
    };
}

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DescribeUndefinedTagsScreen::TagIndex *tagIndex READ getTagIndex CONSTANT)
    Q_PROPERTY(DescribeUndefinedTagsScreen::UserDescription *userDescription READ getUserDescription CONSTANT)
    Q_PROPERTY(DescribeUndefinedTagsScreen::OperationDescription *operationDescription READ getOperationDescription CONSTANT)

    Q_PROPERTY(QStringList dynamicButtons READ getDynamicButtons CONSTANT)

public:
    explicit Backend(QObject *parent = nullptr) : QObject(parent),
                                                  tagIndex(new DescribeUndefinedTagsScreen::TagIndex(this)),
                                                  userDescription(new DescribeUndefinedTagsScreen::UserDescription(this)),
                                                  operationDescription(new DescribeUndefinedTagsScreen::OperationDescription(this)) {}

public:
    QStringList getDynamicButtons() const
    {
        return {"One", "Two", "Three", "Four", "Five", "Six"};
    }

    Q_INVOKABLE void printTestString();
    Q_INVOKABLE bool loadXmlButtonClicked();
    Q_INVOKABLE QStringList getComboBoxItems();
    Q_INVOKABLE void initDescribeUndefinedTagsScreen();
    void loadXmlData(bool = true);
    Q_INVOKABLE void nextOperation();

    DescribeUndefinedTagsScreen::TagIndex *getTagIndex() const { return tagIndex; }
    DescribeUndefinedTagsScreen::UserDescription *getUserDescription() const { return userDescription; }
    DescribeUndefinedTagsScreen::OperationDescription *getOperationDescription() const { return operationDescription; }

private:
    QString xmlFilePath = "";
    const std::string TRANSACTION_TAGS_JSON_FILE = "../xml/categoriesTags.json";
    Month selectedMonth = Month::April;

    std::vector<Operation> allOperations;
    std::vector<Operation> operationsEatingOut;
    std::vector<Operation> operationsNonGroceryShopping;
    std::vector<Operation> operationsGroceryShopping;
    std::vector<Operation> operationsTransport;
    std::vector<Operation> operationsRegularExpenses;
    std::vector<Operation> operationsPhotography;
    std::vector<Operation> operationsOthers;
    std::vector<Operation> operationsSelfDefined;
    std::vector<Operation> operationsIncoming;
    std::vector<Operation> operationsSummary;
    std::vector<Operation>::iterator operationsSelfDefinedIterator;

    DescribeUndefinedTagsScreen::TagIndex *tagIndex;
    DescribeUndefinedTagsScreen::UserDescription *userDescription;
    DescribeUndefinedTagsScreen::OperationDescription *operationDescription;
};
