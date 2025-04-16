#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "controller/GameController.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    qmlRegisterType<GameController>("Wordle", 1, 0, "GameController");
    qmlRegisterType<GameModel>("Wordle", 1, 0, "GameModel");
    qmlRegisterType<WordModel>("Wordle", 1, 0, "WordModel");
    qmlRegisterType<WordEvaluator>("Wordle", 1, 0, "WordEvaluator");

    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/src/view/MainView.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
} 