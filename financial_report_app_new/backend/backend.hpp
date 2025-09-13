#include <QObject>
#include <QDebug>
#include "globals.hpp"
#include <iostream>

class Backend : public QObject {
    Q_OBJECT
public:
    explicit Backend(QObject* parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE void printTestString() {
        std::cout<<"xd = "<<sampleText<<std::endl;
    }
};
