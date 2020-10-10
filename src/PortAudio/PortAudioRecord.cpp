/*
** EPITECH PROJECT, 2020
** PortAudio
** File description:
** PortAudio
*/

#include "PortAudioRecord.hpp"

// samplerate = 48000 (hz)
// frameperbuffer = 256
// channels = 2
PortAudio::PortAudio(int sampleRate, int framePerBuffer, int nbChannels) :
    _sampleRate(sampleRate), _framePerBuffer(framePerBuffer), _nbChannels(nbChannels)
{
    _err = Pa_Initialize();
}

PortAudio::~PortAudio()
{
    Pa_Terminate();
}

int PortAudio::inputCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
    PortAudio *stream = reinterpret_cast<PortAudio *>(userData);

    if (stream != nullptr && stream->_callback != nullptr)
        return (stream->_callback->onAudioReady(reinterpret_cast<const float *>(inputBuffer), framesPerBuffer * stream->getNbChannels()));
    else
        return (paAbort);
}

int PortAudio::outputCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
    PortAudio *stream = reinterpret_cast<PortAudio *>(userData);

    if (stream != nullptr && stream->_callback != nullptr)
        return (stream->_callback->onAudioNeeded(reinterpret_cast<float *>(outputBuffer), framesPerBuffer * stream->getNbChannels()));
    else
        return (paAbort);
}

int PortAudio::getNbChannels()
{
    return (_nbChannels);
}

void PortAudio::start()
{
    _err = Pa_OpenDefaultStream(&_inputStream,
                        _nbChannels,
                        0,
                        paFloat32,
                        _sampleRate,
                        _framePerBuffer,
                        &inputCallback,
                        this);
    Pa_StartStream(_inputStream);

    _err = Pa_OpenDefaultStream(&_outputStream,
                        0,
                        _nbChannels,
                        paFloat32,
                        _sampleRate,
                        _framePerBuffer,
                        &outputCallback,
                        this);
    Pa_StartStream(_outputStream);
}

void PortAudio::stop()
{
    if (Pa_IsStreamActive(_inputStream))
        Pa_StopStream(_inputStream);
    if (Pa_IsStreamActive(_outputStream))
        Pa_StopStream(_outputStream);
}

void PortAudio::setCallback(IAudioStreamCallback *callback)
{
    _callback = callback;
}