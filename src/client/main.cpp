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
#include "PortAudio.hpp"

int main(void)
{
    PortAudio *audio = new PortAudio();

    audio->Start();

    while (1) {
        audio->Read();
        audio->Write();
    }

    audio->Stop();

    return (0);
}