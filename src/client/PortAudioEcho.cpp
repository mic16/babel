/*
** EPITECH PROJECT, 2020
** PortAudio
** File description:
** PortAudio
*/

#include "PortAudioEcho.hpp"

PortAudioEcho::PortAudioEcho()
{
    _stream = NULL;
    // _sampleBlock = NULL;

    _err = Pa_Initialize();

    // if(err != paNoError) goto error2;

    // printf("patest_read_write_wire.c\n"); fflush(stdout);
    // printf("sizeof(int) = %lu\n", sizeof(int)); fflush(stdout);
    // printf("sizeof(long) = %lu\n", sizeof(long)); fflush(stdout);


     /* default input device */
    _inputParameters.device = Pa_GetDefaultInputDevice();
    _inputInfo = Pa_GetDeviceInfo(_inputParameters.device);

    /* default output device */
    _outputParameters.device = Pa_GetDefaultOutputDevice();
    _outputInfo = Pa_GetDeviceInfo(_outputParameters.device);

    _numChannels = _inputInfo->maxInputChannels < _outputInfo->maxOutputChannels
            ? _inputInfo->maxInputChannels : _outputInfo->maxOutputChannels;

    _inputParameters.channelCount = _numChannels;
    _inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    _inputParameters.suggestedLatency = _inputInfo->defaultHighInputLatency ;
    _inputParameters.hostApiSpecificStreamInfo = NULL;

    _outputParameters.channelCount = _numChannels;
    _outputParameters.sampleFormat = PA_SAMPLE_TYPE;
    _outputParameters.suggestedLatency = _outputInfo->defaultHighOutputLatency;
    _outputParameters.hostApiSpecificStreamInfo = NULL;

    /* -- setup -- */

    _err = Pa_OpenStream(
              &_stream,
              &_inputParameters,
              &_outputParameters,
              SAMPLE_RATE,
              FRAMES_PER_BUFFER,
              paClipOff,      /* we won't output out of range samples so don't bother clipping them */
              NULL, /* no callback, use blocking API */
              NULL); /* no callback, so no callback userData */


    _numBytes = FRAMES_PER_BUFFER * _numChannels * SAMPLE_SIZE ;
}

PortAudioEcho::~PortAudioEcho()
{
}

void PortAudioEcho::Listen(char **input)
{
    input[0] = NULL;

    input[0] = (char *) malloc(_numBytes);
    if(input[0] == NULL)
    {
        printf("Could not allocate record array.\n");
        exit(0);
        // goto error1;
    }
    memset(input[0], SAMPLE_SILENCE, _numBytes);
    _err = Pa_StartStream(_stream);
    // if(_err != paNoError) goto error1;
    printf("Wire on. Will run %d seconds.\n", NUM_SECONDS); fflush(stdout);

    // for(int i = 0; i < (NUM_SECONDS*SAMPLE_RATE) / FRAMES_PER_BUFFER; i++)
    // {
        // You may get underruns or overruns if the output is not primed by PortAudio.
        _err = Pa_WriteStream(_stream, input[0], FRAMES_PER_BUFFER);
        // if(_err) goto xrun;
        _err = Pa_ReadStream(_stream, input[0], FRAMES_PER_BUFFER);
        // if(_err) goto xrun;
    // }
    printf("Wire off.\n"); fflush(stdout);


}

void PortAudioEcho::Read(char *input)
{
    printf("Start playing input.\n"); fflush(stdout);

    for(int i = 0; i < (NUM_SECONDS*SAMPLE_RATE) / FRAMES_PER_BUFFER; i++)
    {
        // You may get underruns or overruns if the output is not primed by PortAudio.
        // _err = Pa_WriteStream(_stream, input[0], FRAMES_PER_BUFFER);
        // if(_err) goto xrun;
        _err = Pa_ReadStream(_stream, input, FRAMES_PER_BUFFER);
        // if(_err) goto xrun;
    }
    _err = Pa_StopStream(_stream);
    // if(_err != paNoError) goto error1;

    // free(input[0]);

    Pa_Terminate();
}

void PortAudioEcho::error()
{
    xrun:
        printf("err = %d\n", _err); fflush(stdout);
        if(_stream) {
           Pa_AbortStream(_stream);
           Pa_CloseStream(_stream);
        }
        // free(_sampleBlock);
        Pa_Terminate();
        if(_err & paInputOverflow)
           fprintf(stderr, "Input Overflow.\n");
        if(_err & paOutputUnderflow)
           fprintf(stderr, "Output Underflow.\n");
        exit(-2);
    error1:
        // free(_sampleBlock);
    error2:
        if(_stream) {
           Pa_AbortStream(_stream);
           Pa_CloseStream(_stream);
        }
        Pa_Terminate();
        fprintf(stderr, "An error occured while using the portaudio stream\n");
        fprintf(stderr, "Error number: %d\n", _err);
        fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(_err));
        exit(-1);
}



    // printf("patest_read_write_wire.c\n"); fflush(stdout);
    // printf("sizeof(int) = %lu\n", sizeof(int)); fflush(stdout);
    // printf("sizeof(long) = %lu\n", sizeof(long)); fflush(stdout);


    // printf("Input device # %d.\n", inputParameters.device);

    // printf("    Name: %s\n", inputInfo->name);
    // printf("      LL: %g s\n", inputInfo->defaultLowInputLatency);
    // printf("      HL: %g s\n", inputInfo->defaultHighInputLatency);


    // printf("   Name: %s\n", outputInfo->name);
    // printf("     LL: %g s\n", outputInfo->defaultLowOutputLatency);
    // printf("     HL: %g s\n", outputInfo->defaultHighOutputLatency);


    // printf("Num channels = %d.\n", numChannels);




    // if(err != paNoError) goto error2;




//         PaStreamParameters inputParameters, outputParameters;
//     // PaStream *_stream = NULL;
//     _stream = NULL;
//     PaError err;
//     const PaDeviceInfo* inputInfo;
//     const PaDeviceInfo* outputInfo;
//     // char *_sampleBlock = NULL;
//     _sampleBlock = NULL;
//     int i;
//     int numBytes;
//     int numChannels;


//     printf("patest_read_write_wire.c\n"); fflush(stdout);
//     printf("sizeof(int) = %lu\n", sizeof(int)); fflush(stdout);
//     printf("sizeof(long) = %lu\n", sizeof(long)); fflush(stdout);

//     err = Pa_Initialize();
//     if(err != paNoError) goto error2;

//     inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
//     printf("Input device # %d.\n", inputParameters.device);
//     inputInfo = Pa_GetDeviceInfo(inputParameters.device);
//     printf("    Name: %s\n", inputInfo->name);
//     printf("      LL: %g s\n", inputInfo->defaultLowInputLatency);
//     printf("      HL: %g s\n", inputInfo->defaultHighInputLatency);

//     outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
//     printf("Output device # %d.\n", outputParameters.device);
//     outputInfo = Pa_GetDeviceInfo(outputParameters.device);
//     printf("   Name: %s\n", outputInfo->name);
//     printf("     LL: %g s\n", outputInfo->defaultLowOutputLatency);
//     printf("     HL: %g s\n", outputInfo->defaultHighOutputLatency);

//     numChannels = inputInfo->maxInputChannels < outputInfo->maxOutputChannels
//             ? inputInfo->maxInputChannels : outputInfo->maxOutputChannels;
//     printf("Num channels = %d.\n", numChannels);

//     inputParameters.channelCount = numChannels;
//     inputParameters.sampleFormat = PA_SAMPLE_TYPE;
//     inputParameters.suggestedLatency = inputInfo->defaultHighInputLatency ;
//     inputParameters.hostApiSpecificStreamInfo = NULL;

//     outputParameters.channelCount = numChannels;
//     outputParameters.sampleFormat = PA_SAMPLE_TYPE;
//     outputParameters.suggestedLatency = outputInfo->defaultHighOutputLatency;
//     outputParameters.hostApiSpecificStreamInfo = NULL;

//     /* -- setup -- */

//     err = Pa_OpenStream(
//               &_stream,
//               &inputParameters,
//               &outputParameters,
//               SAMPLE_RATE,
//               FRAMES_PER_BUFFER,
//               paClipOff,      /* we won't output out of range samples so don't bother clipping them */
//               NULL, /* no callback, use blocking API */
//               NULL); /* no callback, so no callback userData */
//     // if(err != paNoError) goto error2;

//     numBytes = FRAMES_PER_BUFFER * numChannels * SAMPLE_SIZE ;
//     _sampleBlock = (char *) malloc(numBytes);
//     if(_sampleBlock == NULL)
//     {
//         printf("Could not allocate record array.\n");
//         goto error1;
//     }
//     memset(_sampleBlock, SAMPLE_SILENCE, numBytes);

//     err = Pa_StartStream(_stream);
//     if(err != paNoError) goto error1;
//     printf("Wire on. Will run %d seconds.\n", NUM_SECONDS); fflush(stdout);

//     for(i=0; i<(NUM_SECONDS*SAMPLE_RATE)/FRAMES_PER_BUFFER; ++i)
//     {
//         // You may get underruns or overruns if the output is not primed by PortAudio.
//         err = Pa_WriteStream(_stream, _sampleBlock, FRAMES_PER_BUFFER);
//         // if(err) goto xrun;
//         err = Pa_ReadStream(_stream, _sampleBlock, FRAMES_PER_BUFFER);
//         // if(err) goto xrun;
//     }
//     printf("Wire off.\n"); fflush(stdout);

//     err = Pa_StopStream(_stream);
//     if(err != paNoError) goto error1;

//     free(_sampleBlock);

//     Pa_Terminate();
//     exit(0);

// xrun:
//     printf("err = %d\n", err); fflush(stdout);
//     if(_stream) {
//        Pa_AbortStream(_stream);
//        Pa_CloseStream(_stream);
//     }
//     free(_sampleBlock);
//     Pa_Terminate();
//     if(err & paInputOverflow)
//        fprintf(stderr, "Input Overflow.\n");
//     if(err & paOutputUnderflow)
//        fprintf(stderr, "Output Underflow.\n");
//     exit(-2);
// error1:
//     free(_sampleBlock);
// error2:
//     if(_stream) {
//        Pa_AbortStream(_stream);
//        Pa_CloseStream(_stream);
//     }
//     Pa_Terminate();
//     fprintf(stderr, "An error occured while using the portaudio stream\n");
//     fprintf(stderr, "Error number: %d\n", err);
//     fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
//     exit(-1);