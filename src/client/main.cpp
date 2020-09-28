/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Epitech File
*/

#include <iostream>
#include <stdio.h>
#include <opus/opus.h>
#include <portaudio.h>
#include <QtWidgets>
#include <QMainWindow>
#include <QDesktopWidget>
#include <QFrame>
#include <QFont>
#include <QLine>
#include "LineWidget.hpp"

void create_menu(QMainWindow *mainWindow)
{
	QMenuBar menu = mainWindow->menuBar();
	QMenu actionFile = menu->addMenu(tr("&File"));
	actionFile->addAction("newAct");


}

int main(int argc, char **argv)
{
	QApplication app (argc, argv);
	QMainWindow mainWindow;
	QDesktopWidget dw;
	QLabel label ("Babel", &mainWindow);
	QFont font("Arial", 50, QFont::Bold);
	LineWidget myWidget(QLine(0, 100, 1400, 100), &mainWindow);
	LineWidget myWidget2(QLine(100, 0, 100, 1400), &mainWindow);

	mainWindow.setCentralWidget(&myWidget);
	// mainWindow.setCentralWidget(&myWidget2);

	if (app.setStyle("windows") == nullptr)
		std::cout << "Style error" << std::endl;

	int x=dw.width()*0.7;
	int y=dw.height()*0.7;
	mainWindow.setFixedSize(x,y);
	mainWindow.show();

	myWidget.show();
	myWidget2.show();

	label.setFont(font);
	label.show();

	return app.exec();
}
