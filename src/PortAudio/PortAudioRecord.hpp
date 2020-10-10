/*
** EPITECH PROJECT, 2020
** PortAudio
** File description:
** PortAudio
*/

#ifndef PORTAUDIO_HPP_
#define PORTAUDIO_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "portaudio.h"

// classe que tu vas devoir hériter de client
class IAudioStreamCallback {
    public:
        // /!\ pour avoir la taille totale de inputSamples/outSamples tu dois faire samplesCount * sizeof(float)

        // dans inputSamples il y a la data de l'audio que tu dois envoyer à l'autre user udp
        virtual int onAudioReady(const float *inputSamples, unsigned long samplesCount) = 0; // Called when Audio frames has been recorded
        // outputSamples c'est un float * (déjà malloc) et tu dois écrire le son dedans pour que portaudio le play tout seul
        virtual int onAudioNeeded(float *outputSamples, unsigned long samplesCount) = 0; // Called when Audio frames are needed to be played
};

class PortAudio {
    public:
        PortAudio(int sampleRate, int framePerBuffer, int nbChannels);
        ~PortAudio();

        static int outputCallback(const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData);
        static int inputCallback(const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData);

        int getNbChannels();
        void start();
        void stop();
        void setCallback(IAudioStreamCallback *callback);
    protected:
    private:
        IAudioStreamCallback *_callback = nullptr;
        PaStream *_inputStream;
        PaStream *_outputStream;
        PaError _err;
        int _sampleRate;
        int _framePerBuffer;
        int _nbChannels;
};

#endif /* !PORTAUDIO_HPP_ */
