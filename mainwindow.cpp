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
    ui->stackedWidget->setCurrentIndex(0);
    menuManager();
}

void MainWindow::menuManager()
{
    switch (currentScreen)
    {
    case Screen::LOAD_XML:
    {
        connect(ui->loadXmlButton, &QPushButton::clicked, this, &MainWindow::loadXmlButtonClicked);
        break;
    }
    case Screen::SET_OWN_TAGS_FOR_UNKNOWN_OPERATIONS:
    {
        ui->nextPageButton->setVisible(false);
        cardTransactionCategories = loadMapFromJson(TRANSACTION_TAGS_JSON_FILE);

        ui->tagsDropDownList->addItem("<wybierz kategorie>");
        ui->tagsDropDownList->addItem("Zakupy (spozywka)");
        ui->tagsDropDownList->addItem("Zakupy (inne)");
        ui->tagsDropDownList->addItem("Rzeczy na mieśćie");
        ui->tagsDropDownList->addItem("Transport");
        ui->tagsDropDownList->addItem("Opłaty stałe");
        ui->tagsDropDownList->addItem("Inne");
        ui->tagsDropDownList->addItem("Fotografia");

        loadXmlData();

        if (!operationsSelfDefined.empty())
        {
            operationsSelfDefinedIterator = operationsSelfDefined.begin();
            ui->operationForSettingTagLabel->setText(
                QString::fromStdString(operationsSelfDefinedIterator->description));
        }

        connect(ui->acceptOperationTag, &QPushButton::clicked, this, [this]()
                {
            if (operationsSelfDefinedIterator != operationsSelfDefined.end() && ui->tagsDropDownList->currentIndex() != 0) {
                cardTransactionCategories.insert({operationsSelfDefinedIterator->description, ui->tagsDropDownList->currentIndex()});
                // ui->tagsDropDownList->setCurrentText("<wybierz kategorie>");
                ++operationsSelfDefinedIterator;
                if (operationsSelfDefinedIterator != operationsSelfDefined.end()) {
                    ui->operationForSettingTagLabel->setText(
                        QString::fromStdString(operationsSelfDefinedIterator->description));
                }
            }else{
                ui->nextPageButton->setVisible(true);
        } });

        connect(ui->nextPageButton, &QPushButton::clicked, this, &MainWindow::openMainScreen);
        break;
    }
    case Screen::MAIN:
    {
        loadXmlData();
        printXmlData();
        connect(ui->nextMonth, &QPushButton::clicked, this, &MainWindow::nextMonthClicked);
        connect(ui->previousMonth, &QPushButton::clicked, this, &MainWindow::previousMonthClicked);
        manageSelectedMonth();
        break;
    }
    }
}

void MainWindow::manageSelectedMonth()
{
    std::string selectedMonthAsString;

    switch (selectedMonth)
    {
    case Month::January:
        selectedMonthAsString = "January";
        break;
    case Month::February:
        selectedMonthAsString = "February";
        break;
    case Month::March:
        selectedMonthAsString = "March";
        break;
    case Month::April:
        selectedMonthAsString = "April";
        break;
    case Month::May:
        selectedMonthAsString = "May";
        break;
    case Month::June:
        selectedMonthAsString = "June";
        break;
    case Month::July:
        selectedMonthAsString = "July";
        break;
    case Month::August:
        selectedMonthAsString = "August";
        break;
    case Month::September:
        selectedMonthAsString = "September";
        break;
    case Month::October:
        selectedMonthAsString = "October";
        break;
    case Month::November:
        selectedMonthAsString = "November";
        break;
    case Month::December:
        selectedMonthAsString = "December";
        break;
    }

    ui->monthName->setText(QString::fromStdString(selectedMonthAsString));
}

void MainWindow::clearData()
{
    for (auto label : expenseLabels)
    {
        delete label;
    }
    expenseLabels.clear();

    summary::operationsEatingOut.amount = 0.0;
    summary::operationsNonGroceryShopping.amount = 0.0;
    summary::operationsGroceryShopping.amount = 0.0;
    summary::operationsTransport.amount = 0.0;
    summary::operationsRegularExpenses.amount = 0.0;
    summary::operationsOthers.amount = 0.0;
    summary::operationsPhotography.amount = 0.0;
    summary::operationsTotal.amount = 0.0;
}

void MainWindow::nextMonthClicked()
{
    int val = static_cast<int>(selectedMonth);
    val++;
    if (val > 12)
        val = 1;
    selectedMonth = static_cast<Month>(val);

    manageSelectedMonth();
    clearData();
    loadXmlData();
    printXmlData();
}

void MainWindow::previousMonthClicked()
{
    int val = static_cast<int>(selectedMonth);
    val--;
    if (val < 1)
        val = 12;
    selectedMonth = static_cast<Month>(val);

    manageSelectedMonth();
    clearData();
    loadXmlData();
    printXmlData();
}

void MainWindow::loadXmlButtonClicked()
{
    xmlFilePath = QFileDialog::getOpenFileName(this, "Choose a file", "", "All Files (*.*)");

    if (!xmlFilePath.isEmpty())
    {
        int nextIndex = (ui->stackedWidget->currentIndex() + 1) % ui->stackedWidget->count();
        ui->stackedWidget->setCurrentIndex(nextIndex);
        currentScreen = Screen::SET_OWN_TAGS_FOR_UNKNOWN_OPERATIONS;
        menuManager();
    }
    else
    {
        throw std::invalid_argument("Cannot load file!");
    }
}

void MainWindow::openMainScreen()
{
    int nextIndex = (ui->stackedWidget->currentIndex() + 1) % ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(nextIndex);
    saveMapToJson(cardTransactionCategories, "../xml/xd_test_file.json");
    currentScreen = Screen::MAIN;
    menuManager();
}

void MainWindow::loadXmlData()
{
    allOperations.clear();
    operationsEatingOut.clear();
    operationsNonGroceryShopping.clear();
    operationsGroceryShopping.clear();
    operationsTransport.clear();
    operationsRegularExpenses.clear();
    operationsPhotography.clear();
    operationsOthers.clear();
    operationsSummary.clear();

    std::string pathStr = xmlFilePath.toStdString();
    const char *path = pathStr.c_str();
    allOperations = getOperationsByDate(path, selectedMonth);

    for (auto &operation : allOperations)
    {
        if (operation.categoryTag == EATING_OUT)
        {
            operationsEatingOut.emplace_back(operation);
            summary::operationsEatingOut.amount += operation.amount;
            summary::operationsTotal.amount += operation.amount;
        }
        else if (operation.categoryTag == NON_GROCERY_SHOPPING)
        {
            operationsNonGroceryShopping.emplace_back(operation);
            summary::operationsNonGroceryShopping.amount += operation.amount;
            summary::operationsTotal.amount += operation.amount;
        }
        else if (operation.categoryTag == GROCERY_SHOPPING)
        {
            operationsGroceryShopping.emplace_back(operation);
            summary::operationsGroceryShopping.amount += operation.amount;
            summary::operationsTotal.amount += operation.amount;
        }
        else if (operation.categoryTag == TRANSPORT)
        {
            operationsTransport.emplace_back(operation);
            summary::operationsTransport.amount += operation.amount;
            summary::operationsTotal.amount += operation.amount;
        }
        else if (operation.categoryTag == REGULAR_EXPENSES)
        {
            operationsRegularExpenses.emplace_back(operation);
            summary::operationsRegularExpenses.amount += operation.amount;
            summary::operationsTotal.amount += operation.amount;
        }
        else if (operation.categoryTag == OTHERS)
        {
            operationsOthers.emplace_back(operation);
            summary::operationsOthers.amount += operation.amount;
            summary::operationsTotal.amount += operation.amount;
        }
        else if (operation.categoryTag == PHOTOGRAPHY)
        {
            operationsPhotography.emplace_back(operation);
            summary::operationsPhotography.amount += operation.amount;
            summary::operationsTotal.amount += operation.amount;
        }

        else if (operation.categoryTag == SELF_DEFINED)
        {
            operationsSelfDefined.emplace_back(operation);
        }
        else if (operation.categoryTag == INCOMING_MONEY)
        {
            operationsIncoming.emplace_back(operation);
        }
    }

    operationsSummary = {summary::operationsEatingOut,
                         summary::operationsNonGroceryShopping,
                         summary::operationsGroceryShopping,
                         summary::operationsTransport,
                         summary::operationsRegularExpenses,
                         summary::operationsOthers,
                         summary::operationsPhotography,
                         summary::operationsIncoming,
                         summary::operationsTotal};
    allOperations.clear();
}

void MainWindow::printXmlData()
{
    QPoint p0{290, 110};
    QPoint p1 = drawExpensesLabels(ui->eatingOutLabelsContainer, ui->eatingOutHeading, operationsEatingOut, EATING_OUT, p0);
    QPoint p2 = drawExpensesLabels(ui->nonGroceryShoppingLabelsContainer, ui->nonGroceryShoppingHeading, operationsNonGroceryShopping, NON_GROCERY_SHOPPING, p1);
    QPoint p3 = drawExpensesLabels(ui->groceryShoppingLabelsContainer, ui->groceryShoppingHeading, operationsGroceryShopping, GROCERY_SHOPPING, p2);
    QPoint p4 = drawExpensesLabels(ui->transportationLabelsContainer, ui->transportationHeading, operationsTransport, TRANSPORT, p3);
    QPoint p5 = drawExpensesLabels(ui->regularExpensesLabelsContainer, ui->regularExpensesHeading, operationsRegularExpenses, REGULAR_EXPENSES, p4);
    QPoint p6 = drawExpensesLabels(ui->otherSpendingsLabelsContainer, ui->otherSpendingsHeading, operationsOthers, OTHERS, p5);
    QPoint p7 = drawExpensesLabels(ui->photographyLabelsContainer, ui->photographyHeading, operationsPhotography, PHOTOGRAPHY, p6);
    // QPoint p8 = drawExpensesLabels(ui->incomingLabelsContainer, ui->incomingHeading, operationsIncoming, INCOMING_MONEY, p7);
    QPoint p8 = drawExpensesLabels(ui->totalSpendingsLabelsContainer, ui->totalSpendingsHeading, operationsSummary, SELF_DEFINED, p7);
}

QPoint MainWindow::drawExpensesLabels(QWidget *labelsContainer,
                                      QLabel *labelsContainerHeader,
                                      const std::vector<Operation> &operations,
                                      int categoryTagToPrint,
                                      QPoint movingPoints)
{
    labelsContainerHeader->move(movingPoints.x(), movingPoints.y() + 20);
    labelsContainer->move(movingPoints.x(), movingPoints.y() + 40);

    int xCoordinateOfLabelInContainer = 0;
    int yCoordinateOfLabelInContainer = 0;
    int spacingBetweenLabels = 5;
    int maxWidthOfLabelsContainer = labelsContainer->width();

    for (auto &operation : operations)
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

    labelsContainer->resize(maxWidthOfLabelsContainer, yCoordinateOfLabelInContainer + 20);
    QPoint posRelativeToMainWindow = labelsContainer->mapTo(this, labelsContainer->rect().bottomLeft());
    return posRelativeToMainWindow;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    OperationLabel *operationLabel = qobject_cast<OperationLabel *>(watched);
    const Operation &operation = operationLabel->operation;
    std::string descriptionBannerText;
    std::string spaceBetweenInformations = "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
    std::string textColor = "";

    if (operationLabel && expenseLabels.contains(operationLabel))
    {
        if (event->type() == QEvent::Enter)
        {
            enableHoverStyleSheet(operationLabel);

            if (operation.amount > 0)
            {
                textColor = "<span style='color:green;'>";
            }
            else
            {
                textColor = "<span style='color:red;'>";
            }
            descriptionBannerText = operation.date.getDate() +
                                    spaceBetweenInformations +
                                    "<b>" +
                                    operation.description +
                                    "</b>" +
                                    spaceBetweenInformations +
                                    textColor +
                                    QString::number(operation.amount, 'f', 2).toStdString() +
                                    "</span>" +
                                    spaceBetweenInformations +
                                    QString::number(operation.totalBalanceAfterOperation, 'f', 2).toStdString() +
                                    " PLN";

            ui->expenseDescriptionBanner->setText(QString::fromStdString(descriptionBannerText));
            ui->expenseDescriptionBanner->setFixedSize(getStringWidth(descriptionBannerText, ui->expenseDescriptionBanner->font()) - 600, 43);

            setPositionOfOperationDescriptionBanner(operationLabel, descriptionBannerText);
            setStyleSheetOfOperationDescriptionBanner();
        }
        else if (event->type() == QEvent::Leave)
        {
            operationLabel->setStyleSheet("color: #000000; font-family: Roboto; font-size: 12px; font-style: normal;");
            ui->expenseDescriptionBanner->setVisible(false);
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

void MainWindow::enableHoverStyleSheet(OperationLabel *operationLabel)
{
    operationLabel->setStyleSheet("color: #6750A4; font-family: Roboto; font-size: 12px; font-style: normal; font-weight: bold; border-radius: 5px; background: rgba(187, 134, 252, 0.20);");
    int operationLabelWidth = getStringWidth((operationLabel->text()).toStdString(), operationLabel->font());
    operationLabel->setFixedWidth(operationLabelWidth);
}

void MainWindow::setStyleSheetOfOperationDescriptionBanner()
{
    ui->expenseDescriptionBanner->setVisible(true);
    ui->expenseDescriptionBanner->raise();
    ui->expenseDescriptionBanner->setStyleSheet("background: #DDDDDD; border-radius: 4px; padding-right: 15px; padding-left: 15px;");
    auto *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(10);
    shadow->setOffset(0, 3);
    shadow->setColor(QColor(0, 0, 0, 36));
    ui->expenseDescriptionBanner->setGraphicsEffect(shadow);
}

void MainWindow::setPositionOfOperationDescriptionBanner(OperationLabel *operationLabel, std::string &text)
{
    QPoint labelGlobalPos = operationLabel->mapToGlobal(QPoint(0, 0));
    QPoint labelPos = this->mapFromGlobal(labelGlobalPos);
    int bannerWidth = ui->expenseDescriptionBanner->width();
    int bannerHeight = ui->expenseDescriptionBanner->height();
    int screenMiddleX = (290 + this->width()) / 2;
    if (labelPos.x() > screenMiddleX)
    {
        int x = labelPos.x() - getStringWidth(text, ui->expenseDescriptionBanner->font()) + 630;
        int y = labelPos.y() - bannerHeight - 5;
        ui->expenseDescriptionBanner->move(x, y);
    }
    else
    {
        int x = labelPos.x() - 30;
        int y = labelPos.y() - bannerHeight - 5;
        ui->expenseDescriptionBanner->move(x, y);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
