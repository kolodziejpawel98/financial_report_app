#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "backend/backend.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Backend backend;
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("backend", &backend);

    engine.loadFromModule("financial_report_app_new", "Main");

    if (!engine.rootObjects().isEmpty())
    {
        QObject *rootObject = engine.rootObjects().first();
    }

    return app.exec();
}
