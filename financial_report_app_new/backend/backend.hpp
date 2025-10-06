#include <QObject>
#include <QDebug>
#include <QFileDialog>
#include <QQmlListProperty>
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

namespace OperationsByTypeScreen
{

    class OperationButtonItem : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString buttonText READ getButtonText WRITE setButtonText NOTIFY buttonTextChanged)
        Q_PROPERTY(QString buttonDescriptionRectangleText
                       READ getButtonDescriptionRectangleText
                           WRITE setButtonDescriptionRectangleText
                               NOTIFY buttonDescriptionRectangleTextChanged)
        Q_PROPERTY(int buttonWidth READ getButtonWidth WRITE setButtonWidth NOTIFY buttonWidthChanged)
    public:
        OperationButtonItem(QString buttonText, QString operationDescriptionRectangleText, int width, QObject *parent = nullptr)
            : QObject(parent), m_buttonText(buttonText), m_buttonDescriptionRectangleText(operationDescriptionRectangleText), m_buttonWidth(width) {}

        QString getButtonText() const { return m_buttonText; }
        QString getButtonDescriptionRectangleText() const { return m_buttonDescriptionRectangleText; }
        void setButtonText(const QString &text)
        {
            if (m_buttonText != text)
            {
                m_buttonText = text;
                emit buttonTextChanged();
            }
        }

        void setButtonDescriptionRectangleText(const QString &text)
        {
            if (m_buttonDescriptionRectangleText != text)
            {
                m_buttonDescriptionRectangleText = text;
                emit buttonDescriptionRectangleTextChanged();
            }
        }

        int getButtonWidth() const { return m_buttonWidth; }
        void setButtonWidth(int w)
        {
            if (m_buttonWidth != w)
            {
                m_buttonWidth = w;
                emit buttonWidthChanged();
            }
        }

    signals:
        void buttonTextChanged();
        void buttonWidthChanged();
        void buttonDescriptionRectangleTextChanged();

    private:
        QString m_buttonText;
        QString m_buttonDescriptionRectangleText;
        int m_buttonWidth;
    };

    class OperationButtonList : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QQmlListProperty<OperationsByTypeScreen::OperationButtonItem> operationButtons READ getOperationButtons NOTIFY operationButtonsChanged)

    public:
        explicit OperationButtonList(QObject *parent = nullptr) : QObject(parent)
        {
        }

        QQmlListProperty<OperationsByTypeScreen::OperationButtonItem> getOperationButtons()
        {
            return QQmlListProperty<OperationsByTypeScreen::OperationButtonItem>(this, &m_buttons);
        }

        Q_INVOKABLE void addButton(const QString &buttonText, const QString &operationDescriptionRectangleText, int width)
        {
            m_buttons.append(new OperationButtonItem(buttonText, operationDescriptionRectangleText, width, this));
            emit operationButtonsChanged();
        }

    signals:
        void operationButtonsChanged();
        void operationButtonsHovered(QString text);

    private:
        QList<OperationsByTypeScreen::OperationButtonItem *> m_buttons;
    };
}

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DescribeUndefinedTagsScreen::TagIndex *tagIndex READ getTagIndex CONSTANT)
    Q_PROPERTY(DescribeUndefinedTagsScreen::UserDescription *userDescription READ getUserDescription CONSTANT)
    Q_PROPERTY(DescribeUndefinedTagsScreen::OperationDescription *operationDescription READ getOperationDescription CONSTANT)
    Q_PROPERTY(OperationsByTypeScreen::OperationButtonList *operationButtonList_operationsEatingOut READ getOperationButtonList_operationsEatingOut CONSTANT)
    Q_PROPERTY(OperationsByTypeScreen::OperationButtonList *operationButtonList_operationsNonGroceryShopping READ getOperationButtonList_operationsNonGroceryShopping CONSTANT)
    Q_PROPERTY(OperationsByTypeScreen::OperationButtonList *operationButtonList_operationsGroceryShopping READ getOperationButtonList_operationsGroceryShopping CONSTANT)

public:
    explicit Backend(QObject *parent = nullptr) : QObject(parent),
                                                  tagIndex(new DescribeUndefinedTagsScreen::TagIndex(this)),
                                                  userDescription(new DescribeUndefinedTagsScreen::UserDescription(this)),
                                                  operationDescription(new DescribeUndefinedTagsScreen::OperationDescription(this)),
                                                  operationButtonList_operationsEatingOut(new OperationsByTypeScreen::OperationButtonList(this)),
                                                  operationButtonList_operationsNonGroceryShopping(new OperationsByTypeScreen::OperationButtonList(this)),
                                                  operationButtonList_operationsGroceryShopping(new OperationsByTypeScreen::OperationButtonList(this))
    {
    }

    void setRootObject(QObject *root) { m_rootObject = root; }
    Q_INVOKABLE void printTestString();
    Q_INVOKABLE bool loadXmlButtonClicked();
    Q_INVOKABLE QStringList getComboBoxItems();
    Q_INVOKABLE void initDescribeUndefinedTagsScreen();
    Q_INVOKABLE void initOperationsByTypeScreen();
    void addOperationButton(std::vector<Operation> &, OperationsByTypeScreen::OperationButtonList *) const;
    void loadXmlData(bool = true);
    void printXmlDataOnScreen();
    Q_INVOKABLE void nextOperation();

    DescribeUndefinedTagsScreen::TagIndex *getTagIndex() const { return tagIndex; }
    DescribeUndefinedTagsScreen::UserDescription *getUserDescription() const { return userDescription; }
    DescribeUndefinedTagsScreen::OperationDescription *getOperationDescription() const { return operationDescription; }
    OperationsByTypeScreen::OperationButtonList *getOperationButtonList_operationsEatingOut() const { return operationButtonList_operationsEatingOut; }
    OperationsByTypeScreen::OperationButtonList *getOperationButtonList_operationsNonGroceryShopping() const { return operationButtonList_operationsNonGroceryShopping; }
    OperationsByTypeScreen::OperationButtonList *getOperationButtonList_operationsGroceryShopping() const { return operationButtonList_operationsGroceryShopping; }

private:
    QObject *m_rootObject = nullptr;
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
    OperationsByTypeScreen::OperationButtonList *operationButtonList_operationsEatingOut;
    OperationsByTypeScreen::OperationButtonList *operationButtonList_operationsNonGroceryShopping;
    OperationsByTypeScreen::OperationButtonList *operationButtonList_operationsGroceryShopping;
};
