// #include <QGuiApplication>
// #include <QQmlApplicationEngine>
// #include <QQmlContext>
// #include "backend/backend.hpp"

// int main(int argc, char *argv[])
// {
//     QGuiApplication app(argc, argv);

//     Backend backend;
//     QQmlApplicationEngine engine;
//     engine.rootContext()->setContextProperty("backend", &backend);
//     QObject::connect(
//         &engine,
//         &QQmlApplicationEngine::objectCreationFailed,
//         &app,
//         []() { QCoreApplication::exit(-1); },
//         Qt::QueuedConnection);
//     engine.loadFromModule("financial_report_app_new", "Main");

//     return app.exec();
// }

#include <QApplication>  // zamiast QGuiApplication
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "backend/backend.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv); // <- tutaj QApplication
    Backend backend;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("backend", &backend);
    engine.loadFromModule("financial_report_app_new", "Main");
    return app.exec();
}
