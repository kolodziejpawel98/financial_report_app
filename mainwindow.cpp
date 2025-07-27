#include "mainwindow.h"
#include "./ui_mainwindow.h"

QT_CHARTS_USE_NAMESPACE
std::ostream &operator<<(std::ostream &os, const QPoint &point)
{
    os << "(" << point.x() << ", " << point.y() << ")";
    return os;
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->loadXmlButton, &QPushButton::clicked, this, &MainWindow::loadXmlButtonClicked);
}

QPoint MainWindow::drawExpensesLabels(QWidget *labelsContainer, QLabel *labelsContainerHeader, const std::vector<Operation> &operations, int categoryTagToPrint, QPoint movingPoints)
{
    labelsContainerHeader->move(movingPoints.x(), movingPoints.y() + 20);
    labelsContainer->move(movingPoints.x(), movingPoints.y() + 40);
    int xCoordinateOfLabelInContainer = 0;
    int yCoordinateOfLabelInContainer = 0;
    int spacingBetweenLabels = 5;
    int maxWidthOfLabelsContainer = labelsContainer->width();
    int i = 0;
    for (auto &operation : operations)
    {
        if (operation.categoryTag == categoryTagToPrint)
        {
            QLabel *label = new QLabel(QString::number(operation.amount, 'f', 2), labelsContainer);
            label->setStyleSheet("color: black; font-size: 10px;");
            label->adjustSize();
            label->setCursor(Qt::PointingHandCursor);
            label->installEventFilter(this);
            expenseLabels.push_back(label);

            int predictedWidthOfLabel = xCoordinateOfLabelInContainer + label->width();

            if (predictedWidthOfLabel > maxWidthOfLabelsContainer)
            {
                xCoordinateOfLabelInContainer = 0;
                yCoordinateOfLabelInContainer += label->height() + spacingBetweenLabels;
            }

            label->move(xCoordinateOfLabelInContainer, yCoordinateOfLabelInContainer);
            label->show();

            xCoordinateOfLabelInContainer += label->width() + spacingBetweenLabels;
        }
        i++;
    }

    labelsContainer->resize(maxWidthOfLabelsContainer, yCoordinateOfLabelInContainer + 20);
    QPoint posRelativeToMainWindow = labelsContainer->mapTo(this, labelsContainer->rect().bottomLeft());
    return posRelativeToMainWindow;
}

void MainWindow::loadXmlButtonClicked()
{
    xmlFilePath = QFileDialog::getOpenFileName(this, "Choose a file", "", "All Files (*.*)");

    if (!xmlFilePath.isEmpty())
    {
        int nextIndex = (ui->stackedWidget->currentIndex() + 1) % ui->stackedWidget->count();
        ui->stackedWidget->setCurrentIndex(nextIndex);
        loadXmlData();
    }
}

void MainWindow::loadXmlData()
{
    allExpensesLabelsHeadings = {ui->groceriesHeading,
                                 ui->nonGroceriesHeading,
                                 ui->citySpendingsHeading,
                                 ui->transportationHeading,
                                 ui->regularPaymentsHeading,
                                 ui->photographyHeading,
                                 ui->otherSpendingsHeading};
    allExpensesLabelsContainers = {ui->groceriesLabelsContainer,
                                   ui->nonGroceriesLabelsContainer,
                                   ui->citySpendingsLabelsContainer,
                                   ui->transportationLabelsContainer,
                                   ui->regularPaymentsLabelsContainer,
                                   ui->photographyLabelsContainer,
                                   ui->otherSpendingsLabelsContainer};

    connect(ui->loadXmlButton, &QPushButton::clicked, this, &MainWindow::loadXmlButtonClicked);

    std::vector<Operation> operations;
    std::string pathStr = xmlFilePath.toStdString();
    const char *path = pathStr.c_str();
    operations = getAllOperations(path);

    QPoint p0{290, 110};
    QPoint p1 = drawExpensesLabels(ui->groceriesLabelsContainer, ui->groceriesHeading, operations, EATING_OUT, p0);
    QPoint p2 = drawExpensesLabels(ui->nonGroceriesLabelsContainer, ui->nonGroceriesHeading, operations, NON_GROCERY_SHOPPING, p1);
    QPoint p3 = drawExpensesLabels(ui->citySpendingsLabelsContainer, ui->citySpendingsHeading, operations, GROCERY_SHOPPING, p2);
    QPoint p4 = drawExpensesLabels(ui->transportationLabelsContainer, ui->transportationHeading, operations, TRANSPORT, p3);
    QPoint p5 = drawExpensesLabels(ui->regularPaymentsLabelsContainer, ui->regularPaymentsHeading, operations, REGULAR_EXPENSES, p4);
    QPoint p6 = drawExpensesLabels(ui->photographyLabelsContainer, ui->photographyHeading, operations, OTHERS, p5);
    QPoint p7 = drawExpensesLabels(ui->otherSpendingsLabelsContainer, ui->otherSpendingsHeading, operations, PHOTOGRAPHY, p6);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    QLabel *label = qobject_cast<QLabel *>(watched);
    if (label && expenseLabels.contains(label))
    {
        if (event->type() == QEvent::Enter)
        {
            label->setStyleSheet("color: #6750A4; font-family: Roboto; font-size: 10px; font-style: normal; font-weight: bold; border-radius: 5px; background: rgba(187, 134, 252, 0.20);");
            QPoint posOfLabel = label->mapToGlobal(QPoint(0, 0));
            posOfLabel = this->mapFromGlobal(posOfLabel);
            ui->expenseDescriptionBanner->setFixedSize(465, 43);
            ui->expenseDescriptionBanner->move(posOfLabel.x(), posOfLabel.y() - ui->expenseDescriptionBanner->height() - 5);
            ui->expenseDescriptionBanner->setText("01/04/2025   spozywka   Lidl   -12.99PLN    <b>1400.99PLN</b>");
            ui->expenseDescriptionBanner->setVisible(true);
            ui->expenseDescriptionBanner->raise();
            ui->expenseDescriptionBanner->setStyleSheet("background: #DDDDDD; border-radius: 4px;");
            auto *shadow = new QGraphicsDropShadowEffect(this);
            shadow->setBlurRadius(10);
            shadow->setOffset(0, 3);
            shadow->setColor(QColor(0, 0, 0, 36));
            ui->expenseDescriptionBanner->setGraphicsEffect(shadow);
        }
        else if (event->type() == QEvent::Leave)
        {
            label->setStyleSheet("color: #000000; font-family: Roboto; font-size: 10px; font-style: normal;");
            ui->expenseDescriptionBanner->setVisible(false);
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

MainWindow::~MainWindow()
{
    delete ui;
}
