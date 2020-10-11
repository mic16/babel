/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Epitech File
*/

#include "EncoderSound.hpp"

EncoderSound::EncoderSound()
{
    int error; 

    m_Encoder = opus_encoder_create(Sound::SAMPLE_RATE, Sound::NB_CHANNELS, OPUS_APPLICATION_VOIP, &error); 

    m_Decoder = opus_decoder_create(Sound::SAMPLE_RATE, Sound::NB_CHANNELS, &error); 
} 

EncoderSound::~EncoderSound()
{
    if (m_Encoder) 
     opus_encoder_destroy(m_Encoder); 

    if (m_Decoder) 
     opus_decoder_destroy(m_Decoder); 
} 

Sound::Encoded EncoderSound::encode(const Sound::Decoded &sound)
{
    Sound::Encoded encoded; 

    encoded.buffer.resize(sound.size);
    encoded.size = opus_encode_float(m_Encoder, sound.buffer.data(), Sound::FRAMES_PER_BUFFER, encoded.buffer.data(), sound.size);


    return encoded; 
} 

Sound::Decoded EncoderSound::decode(const Sound::Encoded &sound)
{
    Sound::Decoded decoded; 

    decoded.buffer.resize(Sound::FRAMES_PER_BUFFER * Sound::NB_CHANNELS);
    decoded.size = opus_decode_float(m_Decoder, sound.buffer.data(), sound.size, decoded.buffer.data(), Sound::FRAMES_PER_BUFFER, 0) * Sound::NB_CHANNELS;


    return decoded; 
} 