#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class AudioManager
{
    public:
        AudioManager();
        ~AudioManager();

        void Add(const std::string& sound, bool looping)
        {
            auto music = std::make_unique<sf::Music>();
            music->openFromFile(sound);
            music->setVolume(50);
            music->setLoop(looping);
            musics.push_back(std::move(music));
        }
        void SetCurrent(int index) {current = index;}
        std::unique_ptr<sf::Music>& GetCurrent() {return musics[current];}
        void Clear() {musics.clear();}
        void LoadAudio();
        void PlayAudio(std::string sound);

    private:
        std::vector<std::unique_ptr<sf::Music>> musics;
        int current;

        sf::SoundBuffer coinBuffer;
        sf::Sound coinSound;
};

