/*
** EPITECH PROJECT, 2020
** PortAudioRecord
** File description:
** PortAudioRecord
*/

#ifndef PORTAUDIORECORD_HPP_
#define PORTAUDIORECORD_HPP_

 /* #define SAMPLE_RATE  (17932) // Test failure to open with this value. */
#define SAMPLE_RATE  (44100)
#define FRAMES_PER_BUFFER (512)
#define NUM_SECONDS     (0.2)
#define NUM_CHANNELS    (2)
/* #define DITHER_FLAG     (paDitherOff) */
#define DITHER_FLAG     (0) 

#define WRITE_TO_FILE   (0)

/* Select sample format. */
#if 1
#define PA_SAMPLE_TYPE  paFloat32
typedef float SAMPLE;
#define SAMPLE_SILENCE  (0.0f)
#define PRINTF_S_FORMAT "%.8f"
#elif 1
#define PA_SAMPLE_TYPE  paInt16
typedef short SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#elif 0
#define PA_SAMPLE_TYPE  paInt8
typedef char SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#else
#define PA_SAMPLE_TYPE  paUInt8
typedef unsigned char SAMPLE;
#define SAMPLE_SILENCE  (128)
#define PRINTF_S_FORMAT "%d"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "portaudio.h"

typedef struct
{
    int          frameIndex;  /* Index into sample array. */
    int          maxFrameIndex;
    SAMPLE      *recordedSamples;
}
paTestData;

class PortAudioRecord {
    public:
        PortAudioRecord();
        ~PortAudioRecord();

        // static int RecordCallback(const void *inputBuffer, void *outputBuffer,
        //                     unsigned long framesPerBuffer,
        //                     const PaStreamCallbackTimeInfo* timeInfo,
        //                     PaStreamCallbackFlags statusFlags,
        //                     void *userData);
        // static int PlayCallback(const void *inputBuffer, void *outputBuffer,
        //                     unsigned long framesPerBuffer,
        //                     const PaStreamCallbackTimeInfo* timeInfo,
        //                     PaStreamCallbackFlags statusFlags,
        //                     void *userData);

        PaStream *Record();
        void Play(PaStream* _stream);

        void Start();

    protected:
    private:
        PaStreamParameters _inputParameters;
        PaStreamParameters _outputParameters;
        PaStream* _stream;
        PaError _err;
        paTestData _data;
        int _totalFrames;
        int _numSamples;
        int _numBytes;
        SAMPLE _max, _val;
        double _average;
};

#endif /* !PORTAUDIORECORD_HPP_ */
