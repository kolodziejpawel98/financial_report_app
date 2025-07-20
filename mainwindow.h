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
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadXmlButtonClicked();
    QPoint drawExpensesLabels(QWidget *, QLabel *, int, const std::vector<std::string> &, QPoint);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::MainWindow *ui;
    QVector<QLabel *> expenseLabels;
    QGridLayout *griLayout;
    std::vector<QWidget *> allExpensesLabelsContainers;
    std::vector<QLabel *> allExpensesLabelsHeadings;
};
#endif // MAINWINDOW_H
