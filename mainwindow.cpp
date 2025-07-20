#include "mainwindow.h"
#include "./ui_mainwindow.h"

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->loadXmlButton, &QPushButton::clicked, this, &MainWindow::loadXmlButtonClicked);

    int x = 0;
    int y = 0;
    int spacing = 5;
    int maxWidth = ui->groceriesLabelsContainer->width();
    int numOfExpenses = 65;

    for (int i = 0; i < numOfExpenses; ++i)
    {
        QLabel *label = new QLabel(QString("%1 PLN").arg((i + 1) * 10.32), ui->groceriesLabelsContainer);
        label->setStyleSheet("color: black; font-size: 12px;");
        label->adjustSize();
        label->setCursor(Qt::PointingHandCursor);
        label->installEventFilter(this);
        priceLabels.push_back(label);

        int predictedWidth = x + label->width();
        if (i < numOfExpenses - 1)
            predictedWidth += spacing + 10;

        if (predictedWidth > maxWidth)
        {
            x = 0;
            y += label->height() + spacing;
        }

        label->move(x, y);
        label->show();

        x += label->width();

        if (i < numOfExpenses - 1)
        {
            QLabel *plusLabel = new QLabel("+", ui->groceriesLabelsContainer);
            plusLabel->setStyleSheet("color: gray; font-size: 12px;");
            plusLabel->adjustSize();
            plusLabel->move(x + spacing - 2, y);
            plusLabel->show();

            x += plusLabel->width() + spacing;
        }
    }

    ui->groceriesLabelsContainer->setMinimumHeight(y + 50);
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
            label->setStyleSheet("color: #6750A4; font-family: Roboto; font-size: 12px; font-style: normal; font-weight: bold; border-radius: 5px; background: rgba(187, 134, 252, 0.20);");
            QPoint pos = label->mapToGlobal(QPoint(0, 0));
            pos = this->mapFromGlobal(pos);
            ui->priceLabelDescription->move(pos.x(), pos.y() - ui->priceLabelDescription->height() - 5);
            ui->priceLabelDescription->setText("01/04/2025 spozywka Lidl -12.99PLN<b>1400.99PLN</b>");
            ui->priceLabelDescription->setVisible(true);
            ui->priceLabelDescription->raise();
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

MainWindow::~MainWindow()
{
    delete ui;
}
