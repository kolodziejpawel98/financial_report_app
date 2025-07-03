#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->colorChangingButton, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onButtonClicked()
{
    if (isGreen)
    {
        ui->colorChangingButton->setStyleSheet("background-color: white;");
        isGreen = false;
    }
    else
    {
        ui->colorChangingButton->setStyleSheet("background-color: green;");
        isGreen = true;
    }
}
