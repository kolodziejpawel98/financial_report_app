#pragma once
#include <QObject>
#include <QString>

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