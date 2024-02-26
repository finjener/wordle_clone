#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "WordleBackend.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    qmlRegisterType<WordleBackend>("Wordle", 1, 0, "WordleBackend");

    QQmlApplicationEngine engine;

    WordleBackend wordleBackend;
    engine.rootContext()->setContextProperty("wordleBackend", &wordleBackend);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
