/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Epitech File
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "portaudio.h"
// #include "PortAudioEcho.hpp"
#include "PortAudioRecord.hpp"

int main(void)
{
    PortAudioRecord *audio = new PortAudioRecord();
    // char *input = NULL;

    audio->Start();

    // audio->Listen(&input);
    // // audio->Read(input);



    return (0);
}