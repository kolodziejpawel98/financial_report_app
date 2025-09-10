#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTextCharFormat>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QVBoxLayout>
#include <QPainter>
#include <QFileDialog>
#include <QGraphicsDropShadowEffect>
#include <QLabel>
#include <QDate>

#include <iostream>
#include "xml/xmlParser.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class OperationLabel : public QLabel
{
    Q_OBJECT
public:
    Operation operation;

    OperationLabel(const Operation &op, QWidget *parent = nullptr)
        : QLabel(parent), operation(op) {}
};

enum class Screen
{
    LOAD_XML = 0,
    SET_OWN_TAGS_FOR_UNKNOWN_OPERATIONS,
    MAIN
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadXmlButtonClicked();
    void nextMonthClicked();
    void previousMonthClicked();
    QPoint drawExpensesLabels(QWidget *, QLabel *, const std::vector<Operation> &, int, QPoint);
    void loadXmlData();
    void printXmlData();
    int getStringWidth(const std::string &text, const QFont &font);
    void enableHoverStyleSheet(OperationLabel *);
    void setPositionOfOperationDescriptionBanner(OperationLabel *, std::string &);
    void setStyleSheetOfOperationDescriptionBanner();
    void manageSelectedMonth();
    void clearData();
    void openMainScreen();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::MainWindow *ui;
    void menuManager();
    QVector<QLabel *> expenseLabels;
    QGridLayout *griLayout;
    std::vector<QWidget *> allExpensesLabelsContainers;
    std::vector<QLabel *> allExpensesLabelsHeadings;
    QWidget *totalSpendingsContainer;
    QLabel *totalSpendingsHeading;
    QString xmlFilePath = "";
    Month selectedMonth = Month::April;
    const std::string TRANSACTION_TAGS_JSON_FILE = "../xml/categoriesTags.json";
    Screen currentScreen = Screen::LOAD_XML;

    std::vector<Operation> allOperations;
    std::vector<Operation> operationsEatingOut;
    std::vector<Operation> operationsNonGroceryShopping;
    std::vector<Operation> operationsGroceryShopping;
    std::vector<Operation> operationsTransport;
    std::vector<Operation> operationsRegularExpenses;
    std::vector<Operation> operationsPhotography;
    std::vector<Operation> operationsOthers;
    std::vector<Operation> operationsSelfDefined;
    std::vector<Operation> operationsSummary;
    std::vector<Operation>::iterator operationsSelfDefinedIterator;
};

#endif // MAINWINDOW_H
