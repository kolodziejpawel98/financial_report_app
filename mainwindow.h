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
    int getStringWidth(const std::string &text, const QFont &font);
    void enableHoverStyleSheet(OperationLabel *);
    void setPositionOfOperationDescriptionBanner(OperationLabel *, std::string &);
    void setStyleSheetOfOperationDescriptionBanner();
    void manageSelectedMonth();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::MainWindow *ui;
    QVector<QLabel *> expenseLabels;
    QGridLayout *griLayout;
    std::vector<QWidget *> allExpensesLabelsContainers;
    std::vector<QLabel *> allExpensesLabelsHeadings;
    QString xmlFilePath = "";
    Month selectedMonth = Month::September;
};

#endif // MAINWINDOW_H
