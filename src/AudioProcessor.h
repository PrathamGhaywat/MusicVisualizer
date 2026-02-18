#ifndef AUDIOPROCESSOR_H
#define AUDIOPROCESSOR_H

#include <SFML/Audio.hpp>
#include <string>
#include <vector>

class AudioProcessor {
    private:
        sf::Music music; //member var to hold the music
        sf::SoundBuffer soundBuffer;  //load all file into memory
        sf::Sound* sound;  // Just declare it, don't initialize
    
    public:
    //constructor
    AudioProcessor();

    //load music file by taking filename as parameter
    bool loadMusic(const std::string& filename);

    //play music
    void play();

    bool isPlaying() const;

    void unloadMusic();

    bool isLoaded() const;

    std::vector<float> getFrequencyData();
};

#endif