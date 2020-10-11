/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Epitech File
*/
#include <QMetaType>
#include <iostream>
#include <opus/opus.h>
#include <vector>

namespace Sound {
    const int SAMPLE_RATE = 44000;
    const int NB_CHANNELS = 2;
    const int FRAMES_PER_BUFFER = 256;

    struct Encoded {
        std::vector<unsigned char> buffer;
        int	size;
    };

    struct Decoded {
        std::vector<float> buffer;
        int	size;
    };
};

class EncoderSound { 

    public: 
        EncoderSound(); 
        ~EncoderSound();

    private: 
        EncoderSound(const EncoderSound &) {} 
        const EncoderSound &operator=(const EncoderSound &) { return *this; } 

    public: 
        Sound::Encoded encode(const Sound::Decoded &sound); 
        Sound::Decoded decode(const Sound::Encoded &sound); 

    private: 
        OpusEncoder *m_Encoder; 
        OpusDecoder *m_Decoder; 

};