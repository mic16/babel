/*
** EPITECH PROJECT, 2020
** PortAudio
** File description:
** PortAudio
*/

#include "PortAudio.hpp"

PortAudio::PortAudio()
{
    PaError err = Pa_Initialize();
    _stream = NULL;

    _inputParameters.device = Pa_GetDefaultInputDevice();
    _inputParameters.channelCount = 2;
    _inputParameters.sampleFormat = paFloat32;
    _inputParameters.suggestedLatency = Pa_GetDeviceInfo(_inputParameters.device)->defaultHighInputLatency ;
    _inputParameters.hostApiSpecificStreamInfo = NULL;

    _outputParameters.device = Pa_GetDefaultOutputDevice();
    _outputParameters.channelCount = 2;
    _outputParameters.sampleFormat = paFloat32;
    _outputParameters.suggestedLatency = Pa_GetDeviceInfo(_outputParameters.device)->defaultHighOutputLatency;
    _outputParameters.hostApiSpecificStreamInfo = NULL;

    err = Pa_OpenStream(
              &_stream,
              &_inputParameters,
              &_outputParameters,
              44100,
              FRAMES_PER_BUFFER,
              paClipOff,
              NULL,
              NULL);
    _numBytes = FRAMES_PER_BUFFER * _numChannels * SAMPLE_SIZE ;
    _sampleBlock = new std::vector<uint32_t>(FRAMES_PER_BUFFER * 2);
}

PortAudio::~PortAudio()
{
    Pa_Terminate();
}

void PortAudio::Start(void)
{
    PaError _err = Pa_StartStream(_stream);
}

void PortAudio::Stop(void)
{
    PaError _err = Pa_CloseStream(_stream);
}

std::vector<uint32_t> *PortAudio::Read(void)
{
    PaError err = paNoError;

    size_t size = Pa_GetStreamReadAvailable(_stream);

    _sampleBlock->clear();
    if (size < FRAMES_PER_BUFFER)
        err = Pa_ReadStream(_stream, _sampleBlock->data(), size);
    else
        err = Pa_ReadStream(_stream, _sampleBlock->data(), FRAMES_PER_BUFFER);
    return (_sampleBlock);
}

void PortAudio::Write(std::vector<uint32_t> *sample)
{
    PaError err = paNoError;

    while (Pa_GetStreamWriteAvailable(_stream) < sample->size());
    err = Pa_WriteStream(_stream, sample->data(), FRAMES_PER_BUFFER);
}

void PortAudio::error()
{
    // xrun:
    //     printf("err = %d\n", _err); fflush(stdout);
    //     if(_stream) {
    //        Pa_AbortStream(_stream);
    //        Pa_CloseStream(_stream);
    //     }
    //     // free(_sampleBlock);
    //     Pa_Terminate();
    //     if(_err & paInputOverflow)
    //        fprintf(stderr, "Input Overflow.\n");
    //     if(_err & paOutputUnderflow)
    //        fprintf(stderr, "Output Underflow.\n");
    //     exit(-2);
    // error1:
    //     // free(_sampleBlock);
    // error2:
    //     if(_stream) {
    //        Pa_AbortStream(_stream);
    //        Pa_CloseStream(_stream);
    //     }
    //     Pa_Terminate();
    //     fprintf(stderr, "An error occured while using the portaudio stream\n");
    //     fprintf(stderr, "Error number: %d\n", _err);
    //     fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(_err));
    //     exit(-1);
}