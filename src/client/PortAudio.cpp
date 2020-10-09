/*
** EPITECH PROJECT, 2020
** PortAudio
** File description:
** PortAudio
*/

#include "PortAudio.hpp"

PortAudio::PortAudio()
{
    _err = paNoError;
}

PortAudio::~PortAudio()
{
}

static int Callback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
    paTestData *data = (paTestData*)userData;
    const SAMPLE *rptr = (const SAMPLE*)inputBuffer;
    SAMPLE *wptr = &data->edSamples[data->frameIndex * NUM_CHANNELS];
    long framesToCalc;
    long i;
    int finished;
    unsigned long framesLeft = data->maxFrameIndex - data->frameIndex;

    if(framesLeft < framesPerBuffer) {
        framesToCalc = framesLeft;
        finished = paComplete;
    } else {
        framesToCalc = framesPerBuffer;
        finished = paContinue;
    }
    if(inputBuffer == NULL) {
        for(i = 0; i < framesToCalc; i++) {
            *wptr++ = SAMPLE_SILENCE;  /* left */
            if(NUM_CHANNELS == 2) *wptr++ = SAMPLE_SILENCE;  /* right */
        }
    } else {
        for(i = 0; i < framesToCalc; i++) {
            *wptr++ = *rptr++;  /* left */
            if(NUM_CHANNELS == 2) *wptr++ = *rptr++;  /* right */
        }
    }
    data->frameIndex += framesToCalc;
    return finished;
}

static int PlayCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
    paTestData *data = (paTestData*)userData;
    SAMPLE *rptr = &data->edSamples[data->frameIndex * NUM_CHANNELS];
    SAMPLE *wptr = (SAMPLE*)outputBuffer;
    unsigned int i;
    int finished;
    unsigned int framesLeft = data->maxFrameIndex - data->frameIndex;

    if(framesLeft < framesPerBuffer) {
        for(i = 0; i < framesLeft; i++) {
            *wptr++ = *rptr++;  /* left */
            if(NUM_CHANNELS == 2) *wptr++ = *rptr++;  /* right */
        }
        for(; i < framesPerBuffer; i++) {
            *wptr++ = 0;  /* left */
            if(NUM_CHANNELS == 2) *wptr++ = 0;  /* right */
        }
        data->frameIndex += framesLeft;
        finished = paComplete;
    } else {
        for(i = 0; i < framesPerBuffer; i++) {
            *wptr++ = *rptr++;  /* left */
            if(NUM_CHANNELS == 2) *wptr++ = *rptr++;  /* right */
        }
        data->frameIndex += framesPerBuffer;
        finished = paContinue;
    }
    return finished;
}

void PortAudio::()
{
    _err = Pa_OpenStream(
               &_stream,
               &_inputParameters,
               NULL,                  /* &outputParameters, */
               SAMPLE_RATE,
               FRAMES_PER_BUFFER,
               paClipOff,      /* we won't output out of range samples so don't bother clipping them */
               Callback,
               &_data );
    // if( _err != paNoError ) goto done;
    _err = Pa_StartStream( _stream );
    // if( _err != paNoError ) goto done;
    std::cout << "\n=== Now ing!! Please speak into the microphone. ===\n" << std::endl; fflush(stdout);
    while( ( _err = Pa_IsStreamActive( _stream ) ) == 1 ) {
        Pa_Sleep(1000);
        std::cout << "index = %d\n" << _data.frameIndex << std::endl; fflush(stdout);
    }
    // if( _err < 0 ) goto done;
    _err = Pa_CloseStream( _stream );
    // if( _err != paNoError ) goto done;

    /* Measure maximum peak amplitude. */
    _max = 0;
    _average = 0.0;
    for(int i=0; i<_numSamples; i++ ) {
        _val = _data.edSamples[i];
        if( _val < 0 ) _val = -_val; /* ABS */
        if( _val > _max ) _max = _val;
        _average += _val;
    }
    _average = _average / (double)_numSamples;
    // std::cout << "sample max amplitude = "PRINTF_S_FORMAT"\n" << _max << std::endl;
    std::cout << "sample average = %lf\n" << _average << std::endl;
}

void PortAudio::Play()
{
    _data.frameIndex = 0;
    _outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
    // if (_outputParameters.device == paNoDevice) {
    //     goto done;
    // }
    _outputParameters.channelCount = 2;                     /* stereo output */
    _outputParameters.sampleFormat =  PA_SAMPLE_TYPE;
    _outputParameters.suggestedLatency = Pa_GetDeviceInfo( _outputParameters.device )->defaultLowOutputLatency;
    _outputParameters.hostApiSpecificStreamInfo = NULL;
    std::cout << "\n=== Now playing back. ===\n" << std::endl; fflush(stdout);
     _err = Pa_OpenStream(
               &_stream,
               NULL, /* no input */
               &_outputParameters,
               SAMPLE_RATE,
               FRAMES_PER_BUFFER,
               paClipOff,      /* we won't output out of range samples so don't bother clipping them */
               PlayCallback,
               &_data );
    // if( _err != paNoError ) goto done;
    if( _stream ) {
        _err = Pa_StartStream( _stream );
        // if( _err != paNoError ) goto done;
        std::cout << "Waiting for playback to finish.\n" << std::endl; fflush(stdout);
        while( ( _err = Pa_IsStreamActive( _stream ) ) == 1 ) Pa_Sleep(100);
        // if( _err < 0 ) goto done;
        _err = Pa_CloseStream( _stream );
        // if( _err != paNoError ) goto done;
        std::cout << "Done.\n" << std::endl; fflush(stdout);
    }
}

void PortAudio::Start()
{
    _data.maxFrameIndex = _totalFrames = NUM_SECONDS * SAMPLE_RATE; /*  for a few seconds. */
    _data.frameIndex = 0;
    _numSamples = _totalFrames * NUM_CHANNELS;
    _numBytes = _numSamples * sizeof(SAMPLE);
    _data.edSamples = (SAMPLE *) malloc( _numBytes ); /* From now on, edSamples is initialised. */
    // if( _data.edSamples == NULL ) {
    //     std::cout << "Could not allocate  array.\n" << std::endl;
    //     goto done;
    // }
    for(int i=0; i<_numSamples; i++ ) _data.edSamples[i] = 0;
    _err = Pa_Initialize();
    // if( _err != paNoError ) goto done;
    _inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
    // if (_inputParameters.device == paNoDevice) {
    //     goto done;
    // }
    _inputParameters.channelCount = 2;                    /* stereo input */
    _inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    _inputParameters.suggestedLatency = Pa_GetDeviceInfo( _inputParameters.device )->defaultLowInputLatency;
    _inputParameters.hostApiSpecificStreamInfo = NULL;

    /*  some audio. -------------------------------------------- */
    this->();

    /* Playback ed _data.  -------------------------------------------- */
    this->Play();

done:
    Pa_Terminate();
    if( _data.edSamples )       /* Sure it is NULL or valid. */
        free( _data.edSamples );
    if( _err != paNoError ) {
        _err = 1;          /* Always return 0 or 1, but no other return codes. */
    }
    exit(0);
}


//     /* Write ed _data to a file. */
//  #if WRITE_TO_FILE
//      {
//          FILE  *fid;
//          fid = fopen("ed.raw" << "wb" << std::endl;
//          if( fid == NULL )
//          {
//              std::cout << "Could not open file." << std::endl;
//          }
//          else
//          {
//              fwrite( _data.edSamples, NUM_CHANNELS * sizeof(SAMPLE), _totalFrames, fid );
//              fclose( fid );
//              std::cout << "Wrote _data to 'ed.raw'\n" << std::endl;
//          }
//      }
//  #endif