#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QTextCharFormat>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QVBoxLayout>
#include <QPainter>
#include <QFileDialog>
#include <QGraphicsDropShadowEffect>

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->loadXmlButton, &QPushButton::clicked, this, &MainWindow::loadXmlButtonClicked);

    ui->priceLabelDescription->setVisible(false);
    ui->priceLabel->setStyleSheet("color: #000000; font-family: Roboto; font-size: 12px; font-style: normal;");

    ui->priceLabel->installEventFilter(this);
}

void MainWindow::loadXmlButtonClicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Choose a file", "", "All Files (*.*)");

    if (!filePath.isEmpty())
    {
        int nextIndex = (ui->stackedWidget->currentIndex() + 1) % ui->stackedWidget->count();
        ui->stackedWidget->setCurrentIndex(nextIndex);
    }
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    QLabel *label = qobject_cast<QLabel *>(watched);
    if (label)
    {
        if (event->type() == QEvent::Enter)
        {
            qDebug() << "XDDDDDDDDDDDDD\n";
            label->setStyleSheet("color: #6750A4; font-family: Roboto; font-size: 12px; font-style: normal; font-weight: bold; border-radius: 5px; background: rgba(187, 134, 252, 0.20);");
            QPoint pos = label->mapToGlobal(QPoint(0, 0));
            pos = this->mapFromGlobal(pos);
            ui->priceLabelDescription->move(pos.x(), pos.y() - ui->priceLabelDescription->height() - 5);
            ui->priceLabelDescription->setText("01/04/2025 spozywka Lidl -12.99PLN<b>1400.99PLN</b>");
            ui->priceLabelDescription->setVisible(true);
            ui->priceLabelDescription->setStyleSheet("background: #DDDDDD; border-radius: 4px;");
            auto *shadow = new QGraphicsDropShadowEffect(this);
            shadow->setBlurRadius(10);
            shadow->setOffset(0, 3);
            shadow->setColor(QColor(0, 0, 0, 36));
            ui->priceLabelDescription->setGraphicsEffect(shadow);
        }
        else if (event->type() == QEvent::Leave)
        {
            label->setStyleSheet("color: #000000; font-family: Roboto; font-size: 12px; font-style: normal;");
            ui->priceLabelDescription->setVisible(false);
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

// ###################################

MainWindow::~MainWindow()
{
    delete ui;
}
