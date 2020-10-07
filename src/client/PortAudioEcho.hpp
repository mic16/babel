/*
** EPITECH PROJECT, 2020
** PortAudioEcho
** File description:
** PortAudio
*/

#ifndef PORTAUDIOECHO_HPP_
#define PORTAUDIOECHO_HPP_

/* #define SAMPLE_RATE  (17932) // Test failure to open with this value. */
#define SAMPLE_RATE       (44100)
#define FRAMES_PER_BUFFER   (512)
#define NUM_SECONDS          (10)
/* #define DITHER_FLAG     (paDitherOff)  */
#define DITHER_FLAG           (0)

/* Select sample format. */
#if 1
#define PA_SAMPLE_TYPE  paFloat32
#define SAMPLE_SIZE (4)
#define SAMPLE_SILENCE  (0.0f)
#define PRINTF_S_FORMAT "%.8f"
#elif 0
#define PA_SAMPLE_TYPE  paInt16
#define SAMPLE_SIZE (2)
#define SAMPLE_SILENCE (0)
#define PRINTF_S_FORMAT "%d"
#elif 0
#define PA_SAMPLE_TYPE  paInt24
#define SAMPLE_SIZE (3)
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#elif 0
#define PA_SAMPLE_TYPE  paInt8
#define SAMPLE_SIZE (1)
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#else
#define PA_SAMPLE_TYPE  paUInt8
#define SAMPLE_SIZE (1)
#define SAMPLE_SILENCE  (128)
#define PRINTF_S_FORMAT "%d"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "portaudio.h"

class PortAudioEcho {
    public:
        PortAudioEcho();
        ~PortAudioEcho();

        void Listen(char **input);
        void Read(char *input);
        void error();

    protected:
    private:
        PaStreamParameters _inputParameters;
        PaStreamParameters _outputParameters;
        PaStream *_stream;
        PaError _err;
        const PaDeviceInfo* _inputInfo;
        const PaDeviceInfo* _outputInfo;
        int _numBytes;
        int _numChannels;
};

#endif /* !PORTAUDIOECHO_HPP_ */