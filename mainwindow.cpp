#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QTextCharFormat>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->modeChangeButton, &QPushButton::clicked, this, &MainWindow::modeChangeButtonClicked);
    connect(ui->backToXmlLoadButton, &QPushButton::clicked, this, &MainWindow::backToXmlLoadButtonClicked);
    connect(ui->exportPdfButton, &QPushButton::clicked, this, &MainWindow::exportPdfButtonClicked);
    connect(ui->nextDateButton, &QPushButton::clicked, this, &MainWindow::nextDateButtonClicked);
    connect(ui->previousDateButton, &QPushButton::clicked, this, &MainWindow::previousDateButtonClicked);
    QDate selectedDate = ui->calendarWidget->selectedDate();
    qDebug() << "Selected date:" << selectedDate.toString();
    QTextCharFormat highlightFormat;
    highlightFormat.setBackground(Qt::yellow);
    QDate dateToHighlight(2025, 7, 12);
    ui->calendarWidget->setDateTextFormat(dateToHighlight, highlightFormat);
}

void MainWindow::modeChangeButtonClicked()
{
    ui->totalLabel->setText("modeChangeButtonClicked");
}

void MainWindow::backToXmlLoadButtonClicked()
{
    ui->totalLabel->setText("backToXmlLoadButtonClicked ");
}

void MainWindow::exportPdfButtonClicked()
{
    ui->totalLabel->setText("exportPdfButtonClicked ");
}

void MainWindow::nextDateButtonClicked()
{
    ui->totalLabel->setText("nextDateButtonClicked ");
}

void MainWindow::previousDateButtonClicked()
{
    ui->totalLabel->setText("previousDateButtonClicked");
}

// ###################################

MainWindow::~MainWindow()
{
    delete ui;
}
