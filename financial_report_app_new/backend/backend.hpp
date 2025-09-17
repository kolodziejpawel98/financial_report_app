#include <QObject>
#include <QDebug>
#include <QFileDialog>
#include "globals.hpp"
#include <iostream>
#include "xml/xmlParser.hpp"

class Backend : public QObject {
    Q_OBJECT
    Q_PROPERTY(int userDescriptionCurrentTagIndex
                   READ getUserDescriptionCurrentTagIndex
                       WRITE setUserDescriptionCurrentTagIndex
                           NOTIFY userDescriptionCurrentTagIndexChanged)
    Q_PROPERTY(QString userOperationDescriptionText
                   READ getUserOperationDescriptionText
                       WRITE setUserOperationDescriptionText
                           NOTIFY userOperationDescriptionTextChanged)

private:
    QString m_userDescriptionText;

    // Q_PROPERTY(QString userDescriptionCurrentText READ getUserDescriptionCurrentText WRITE setUserDescriptionCurrentText NOTIFY userDescriptionCurrentTextChanged)
public:
    explicit Backend(QObject *parent = nullptr) : QObject(parent)
    {
    }
    void setRootObject(QObject *root) { m_rootObject = root; }

    Q_INVOKABLE void printTestString();
    Q_INVOKABLE bool loadXmlButtonClicked();
    Q_INVOKABLE QStringList getComboBoxItems();
    Q_INVOKABLE QString getOperationDescriptionText() const;
    Q_INVOKABLE QString getuserOperationDescriptionTextArena() const;
    void setOperationDescriptionText(QString);
    void setuserOperationDescriptionTextArena(QString);
    Q_INVOKABLE void initDescribeUndefinedTagsScreen();
    void loadXmlData(bool = true);
    Q_INVOKABLE void nextOperation();

    int getUserDescriptionCurrentTagIndex() const;
    void setUserDescriptionCurrentTagIndex(int);
    QString getUserOperationDescriptionText() const;
    void setUserOperationDescriptionText(const QString &);
    // QString getUserDescriptionCurrentText() const;
    // void setUserDescriptionCurrentText(const QString &);

private:
    QObject *m_rootObject = nullptr;
    QString xmlFilePath = "";
    const std::string TRANSACTION_TAGS_JSON_FILE = "../xml/categoriesTags.json";
    Month selectedMonth = Month::April;
    QString operationDescriptionText = "<empty>";
    QString userOperationDescriptionTextArena = "<empty>";

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

    int userDescriptionCurrentTagIndex = -1;
    QString userOperationDescriptionText = "";
    // QString userDescriptionCurrentText = "";

signals:
    void userDescriptionCurrentTagIndexChanged();
    void userOperationDescriptionTextChanged();
    // void userDescriptionCurrentTextChanged();
};