#include "mainwindow.h"
#include "./ui_mainwindow.h"

QT_CHARTS_USE_NAMESPACE

// MainWindow::MainWindow(QWidget *parent)
//     : QMainWindow(parent), ui(new Ui::MainWindow)
// {
//     ui->setupUi(this);
//     connect(ui->loadXmlButton, &QPushButton::clicked, this, &MainWindow::loadXmlButtonClicked);

//     ui->priceLabelDescription->setVisible(false);
//     ui->priceLabel->setStyleSheet("color: #000000; font-family: Roboto; font-size: 12px; font-style: normal;");

//     ui->priceLabel->installEventFilter(this);

//     for (int i = 0; i < 20; ++i)
//     {
//         QLabel *label = new QLabel(QString("Transakcja %1: %2 PLN").arg(i + 1).arg((i + 1) * 10.25), this);
//         label->setStyleSheet("color: black; padding: 5px; font-size: 14px;");
//         label->installEventFilter(this);
//         priceLabels.push_back(label);
//         // ui->pricesContainer->layout()->addWidget(label);
//         label->show();
//     }
// }

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->loadXmlButton, &QPushButton::clicked, this, &MainWindow::loadXmlButtonClicked);

    // ui->priceLabelDescription->setParent(this);
    // ui->priceLabelDescription->resize(150, 30);
    // ui->priceLabelDescription->setVisible(false);
    // ui->priceLabelDescription->setTextFormat(Qt::RichText);
    // ui->priceLabelDescription->setStyleSheet("background: #DDDDDD; border-radius: 4px;");

    // ui->priceLabel->setStyleSheet("color: #000000; font-family: Roboto; font-size: 12px; font-style: normal;");
    // // ui->priceLabel->installEventFilter(this);

    for (int i = 0; i < 20; ++i)
    {
        QLabel *label = new QLabel(QString("Transakcja %1: %2 PLN").arg(i + 1).arg((i + 1) * 10.25), this);
        label->setStyleSheet("color: black; padding: 5px; font-size: 14px;");
        label->installEventFilter(this);
        priceLabels.push_back(label);

        int row = i / 4;
        int col = i % 4;

        ui->gridLayout->addWidget(label, row, col);
    }

    // int columns = 4;
    // int row = 0;
    // int col = 0;

    // for (int i = 0; i < 20; ++i)
    // {
    //     QLabel *label = new QLabel(QString("Transakcja %1: %2 PLN").arg(i + 1).arg((i + 1) * 10.25));
    //     label->setStyleSheet("color: black; padding: 5px; font-size: 14px;");
    //     label->installEventFilter(this);

    //     priceLabels.push_back(label);

    //     ui->gridLayout->layout()->addWidget(label, row, col);

    //     col++;
    //     if (col >= columns)
    //     {
    //         col = 0;
    //         row++;
    //     }
    // }
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
    if (label && priceLabels.contains(label))
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
