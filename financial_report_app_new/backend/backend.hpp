#include <QObject>
#include <QDebug>
#include <QFileDialog>
#include "globals.hpp"
#include <iostream>

class Backend : public QObject {
    Q_OBJECT
public:
    explicit Backend(QObject* parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE void printTestString() {
        std::cout<<"xd = "<<sampleText<<std::endl;
    }

    Q_INVOKABLE void loadXmlButtonClicked()
    {
        xmlFilePath = QFileDialog::getOpenFileName(nullptr, "Choose a file", "", "All Files (*.*)");
        std::cout<<"path = "<<xmlFilePath.toStdString()<<std::endl;

        // if (!xmlFilePath.isEmpty())
        // {
        //     int nextIndex = (ui->stackedWidget->currentIndex() + 1) % ui->stackedWidget->count();
        //     ui->stackedWidget->setCurrentIndex(nextIndex);
        //     currentScreen = Screen::SET_OWN_TAGS_FOR_UNKNOWN_OPERATIONS;
        //     menuManager();
        // }
        // else
        // {
        //     throw std::invalid_argument("Cannot load file!");
        // }
    }

    QString xmlFilePath = "";
};
