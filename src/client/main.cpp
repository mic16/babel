/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Epitech File
*/
/** @file */
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
    // BackEnd *backend = BackEnd::get();
    // while (true) {
    //     backend = BackEnd::get();
    //     if (backend->getQuit()) {
    //         std::cout << "QUIT" << std::endl;
    //         break;
    //     }
    // }
    return app.exec();
}