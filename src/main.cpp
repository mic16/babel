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
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>

int main(int argc, char **argv)
{
	QApplication app (argc, argv);
	QPushButton button ("Hello world !");

	button.show();
	return app.exec();
}
