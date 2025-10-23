#pragma once
#pragma once
#include <QObject>
#include <QQmlListProperty>
#include <iostream>

namespace OperationsByTypeScreen
{
    class OperationButtonItem : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString buttonText READ getButtonText WRITE setButtonText NOTIFY buttonTextChanged)
        Q_PROPERTY(QString buttonDescriptionRectangleText READ getButtonDescriptionRectangleText WRITE setButtonDescriptionRectangleText NOTIFY buttonDescriptionRectangleTextChanged)
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
        explicit OperationButtonList(QObject *parent = nullptr) : QObject(parent) {}

        QQmlListProperty<OperationsByTypeScreen::OperationButtonItem> getOperationButtons()
        {
            return QQmlListProperty<OperationsByTypeScreen::OperationButtonItem>(this, &m_buttons);
        }

        Q_INVOKABLE void addButton(const QString &buttonText, const QString &operationDescriptionRectangleText, int width)
        {
            m_buttons.append(new OperationButtonItem(buttonText, operationDescriptionRectangleText, width, this));
        }

        void emitOperationsChangedSignal()
        {
            std::cout << "xd" << this->getSize() << std::endl;
            emit operationButtonsChanged();
        }

        int getSize() const
        {
            return m_buttons.size();
        }

        void clear()
        {
            qDeleteAll(m_buttons);
            m_buttons.clear();

            emit operationButtonsChanged();
        }

    signals:
        void operationButtonsChanged();
        void operationButtonsHovered(QString text);

    private:
        QList<OperationsByTypeScreen::OperationButtonItem *> m_buttons;
    };
}

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