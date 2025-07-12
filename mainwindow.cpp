#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QTextCharFormat>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QVBoxLayout>
#include <QPainter>

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->modeChangeButton, &QPushButton::clicked, this, &MainWindow::modeChangeButtonClicked);
    // connect(ui->modeChangeButton_2, &QPushButton::clicked, this, &MainWindow::modeChangeButtonClicked); // todo: change variable name
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

    QWidget *placeholder = ui->page_2->findChild<QWidget *>("chartWidget");

    QLineSeries *series = new QLineSeries();
    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->createDefaultAxes();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(placeholder);
    layout->addWidget(chartView);
}

void MainWindow::modeChangeButtonClicked()
{
    int nextIndex = (ui->stackedWidget->currentIndex() + 1) % ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(nextIndex);
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
