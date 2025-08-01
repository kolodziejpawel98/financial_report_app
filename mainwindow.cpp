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
            OperationLabel *label = new OperationLabel(operation, labelsContainer);
            label->setText(QString::number(operation.amount, 'f', 2));

            label->setStyleSheet("color: black; font-size: 12px; font-family: Roboto; font-size: 12px; font-style: normal;");
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

    allExpensesLabelsHeadings = {ui->eatingOutHeading,
                                 ui->nonGroceryShoppingHeading,
                                 ui->groceryShoppingHeading,
                                 ui->transportationHeading,
                                 ui->regularExpensesHeading,
                                 ui->photographyHeading,
                                 ui->otherSpendingsHeading};
    allExpensesLabelsContainers = {ui->eatingOutLabelsContainer,
                                   ui->nonGroceryShoppingLabelsContainer,
                                   ui->groceryShoppingLabelsContainer,
                                   ui->transportationLabelsContainer,
                                   ui->regularExpensesLabelsContainer,
                                   ui->photographyLabelsContainer,
                                   ui->otherSpendingsLabelsContainer};

    connect(ui->loadXmlButton, &QPushButton::clicked, this, &MainWindow::loadXmlButtonClicked);

    std::vector<Operation> operations;
    std::string pathStr = xmlFilePath.toStdString();
    const char *path = pathStr.c_str();
    operations = getAllOperations(path);

    std::vector<Operation> operationsEatingOut;
    std::vector<Operation> operationsNonGroceryShopping;
    std::vector<Operation> operationsGroceryShopping;
    std::vector<Operation> operationsTransport;
    std::vector<Operation> operationsRegularExpenses;
    std::vector<Operation> operationsPhotography;
    std::vector<Operation> operationsOthers;
    for (auto &operation : operations)
    {
        if (operation.categoryTag == EATING_OUT)
        {
            operationsEatingOut.emplace_back(operation);
        }
        else if (operation.categoryTag == NON_GROCERY_SHOPPING)
        {
            operationsNonGroceryShopping.emplace_back(operation);
        }
        else if (operation.categoryTag == GROCERY_SHOPPING)
        {
            operationsGroceryShopping.emplace_back(operation);
        }
        else if (operation.categoryTag == TRANSPORT)
        {
            operationsTransport.emplace_back(operation);
        }
        else if (operation.categoryTag == REGULAR_EXPENSES)
        {
            operationsRegularExpenses.emplace_back(operation);
        }
        else if (operation.categoryTag == PHOTOGRAPHY)
        {
            operationsPhotography.emplace_back(operation);
        }
        else if (operation.categoryTag == OTHERS)
        {
            operationsOthers.emplace_back(operation);
        }
    }

    QPoint p0{290, 110};
    QPoint p1 = drawExpensesLabels(ui->eatingOutLabelsContainer, ui->eatingOutHeading, operationsEatingOut, EATING_OUT, p0);
    QPoint p2 = drawExpensesLabels(ui->nonGroceryShoppingLabelsContainer, ui->nonGroceryShoppingHeading, operationsNonGroceryShopping, NON_GROCERY_SHOPPING, p1);
    QPoint p3 = drawExpensesLabels(ui->groceryShoppingLabelsContainer, ui->groceryShoppingHeading, operationsGroceryShopping, GROCERY_SHOPPING, p2);
    QPoint p4 = drawExpensesLabels(ui->transportationLabelsContainer, ui->transportationHeading, operationsTransport, TRANSPORT, p3);
    QPoint p5 = drawExpensesLabels(ui->regularExpensesLabelsContainer, ui->regularExpensesHeading, operationsRegularExpenses, REGULAR_EXPENSES, p4);
    QPoint p6 = drawExpensesLabels(ui->photographyLabelsContainer, ui->photographyHeading, operationsOthers, OTHERS, p5);
    QPoint p7 = drawExpensesLabels(ui->otherSpendingsLabelsContainer, ui->otherSpendingsHeading, operationsPhotography, PHOTOGRAPHY, p6);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    OperationLabel *operationLabel = qobject_cast<OperationLabel *>(watched);
    if (operationLabel && expenseLabels.contains(operationLabel))
    {
        if (event->type() == QEvent::Enter)
        {
            const Operation &op = operationLabel->operation;
            operationLabel->setStyleSheet("color: #6750A4; font-family: Roboto; font-size: 12px; font-style: normal; font-weight: bold; border-radius: 5px; background: rgba(187, 134, 252, 0.20);");
            // QPoint posOfLabel = operationLabel->mapToGlobal(QPoint(0, 0));
            int operationLabelWidth = getStringWidth((operationLabel->text()).toStdString(), operationLabel->font());
            operationLabel->setFixedWidth(operationLabelWidth);

            // operationLabel->raise();

            // posOfLabel = this->mapFromGlobal(posOfLabel);
            // ui->expenseDescriptionBanner->setFixedSize(665, 43);
            // ui->expenseDescriptionBanner->move(posOfLabel.x(), posOfLabel.y() - ui->expenseDescriptionBanner->height() - 5);

            std::string descriptionBannerText;
            std::string spaceBetweenInformations = "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
            if (op.amount > 0)
            {
                descriptionBannerText = op.date.getDate() + spaceBetweenInformations + "<b>" + op.description + "</b>" + spaceBetweenInformations + "<span style='color:green;'>" + QString::number(op.amount, 'f', 2).toStdString() + "</span>" + spaceBetweenInformations + std::to_string(op.totalBalanceAfterOperation);
            }
            else
            {
                descriptionBannerText = op.date.getDate() + spaceBetweenInformations + "<b>" + op.description + "</b>" + spaceBetweenInformations + "<span style='color:red;'>" + QString::number(op.amount, 'f', 2).toStdString() + "</span>" + spaceBetweenInformations + std::to_string(op.totalBalanceAfterOperation);
            }
            ui->expenseDescriptionBanner->setText(QString::fromStdString(descriptionBannerText));
            ui->expenseDescriptionBanner->setFixedSize(getStringWidth(descriptionBannerText, ui->expenseDescriptionBanner->font()) - 700, 43);

            QPoint labelGlobalPos = operationLabel->mapToGlobal(QPoint(0, 0));
            QPoint labelPos = this->mapFromGlobal(labelGlobalPos);

            int bannerWidth = ui->expenseDescriptionBanner->width();
            int bannerHeight = ui->expenseDescriptionBanner->height();
            int screenMiddleX = (290 + this->width()) / 2;

            if (labelPos.x() > screenMiddleX)
            {
                int x = labelPos.x() - getStringWidth(descriptionBannerText, ui->expenseDescriptionBanner->font()) + 730;
                int y = labelPos.y() - bannerHeight - 5;
                ui->expenseDescriptionBanner->move(x, y);
            }
            else
            {
                int x = labelPos.x() - 30;
                int y = labelPos.y() - bannerHeight - 5;
                ui->expenseDescriptionBanner->move(x, y);
            }

            ui->expenseDescriptionBanner->setVisible(true);
            ui->expenseDescriptionBanner->raise();
            ui->expenseDescriptionBanner->setStyleSheet("background: #DDDDDD; border-radius: 4px; padding-right: 15px; padding-left: 15px;");
            auto *shadow = new QGraphicsDropShadowEffect(this);
            shadow->setBlurRadius(10);
            shadow->setOffset(0, 3);
            shadow->setColor(QColor(0, 0, 0, 36));
            ui->expenseDescriptionBanner->setGraphicsEffect(shadow);
        }
        else if (event->type() == QEvent::Leave)
        {
            operationLabel->setStyleSheet("color: #000000; font-family: Roboto; font-size: 12px; font-style: normal;");
            // ui->expenseDescriptionBanner->lower();
            ui->expenseDescriptionBanner->setVisible(false);
            // operationLabel->lower();
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

int MainWindow::getStringWidth(const std::string &text, const QFont &font)
{
    QString qtext = QString::fromStdString(text);
    QFontMetrics metrics(font);
    return metrics.horizontalAdvance(qtext);
}

MainWindow::~MainWindow()
{
    delete ui;
}
