#include "header.h"
#include "audiomanager.h"

AudioManager::AudioManager()
{
    //ctor
}

AudioManager::~AudioManager()
{
    //dtor
}

void AudioManager::LoadAudio()
{
    coinBuffer.loadFromFile("audio/coin.wav");
    coinSound.setBuffer(coinBuffer);
}

void AudioManager::PlayAudio(string sound)
{
    if (sound == "coin")
    {
        coinSound.play();
    }
}
