#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "RecordWheatModel.h"
#include <QQmlContext>
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    qmlRegisterUncreatableType<WheatItem>("App.Class",0,1,"WheatItem","12");
    RecordWheatModel model;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Tabmodel",&model);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
