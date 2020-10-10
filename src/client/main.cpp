/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Epitech File
*/

#include <iostream>
#include <stdio.h>
#include <iostream>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "../utils/Utils.hpp"
#include "../utils/Request.hpp"
#include "backend.hpp"


int main(int argc, char *argv[])
{
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    qmlRegisterType<BackEnd>("my.own.backend", 1, 0, "BackEnd");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    Communication c;
    c.createUser("mic16", "aze");
    // c.connectUser("mic16", "aze");
    c.createUser("tho", "aze");
    // c.connectUser("tho", "aze");
    c.createUser("mic", "aze");
    c.connectUser("mic", "aze");
    c.createTeam("test");
    c.addUserToTeam("tho", "test");
    c.addUserToTeam("mic16", "test");
    c.removeUserFromTeam("mic16", "test");
    c.removeUserFromTeam("tho", "test");
    c.removeUserFromTeam("mic", "test");
    return app.exec();
}