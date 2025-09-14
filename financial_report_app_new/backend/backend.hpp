#include <QObject>
#include <QDebug>
#include <QFileDialog>
#include "globals.hpp"
#include <iostream>

class Backend : public QObject {
    Q_OBJECT
public:
    explicit Backend(QObject* parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE void printTestString();
    Q_INVOKABLE bool loadXmlButtonClicked();

private:
    QString xmlFilePath = "";
};
