#include "AudioProcessor.h"


AudioProcessor::AudioProcessor() : sound(nullptr) {
    //initialize as null
}

bool AudioProcessor::loadMusic(const std::string& filename) {
    if (!soundBuffer.loadFromFile(filename)) {
        return false;
    }
    sound = new sf::Sound(soundBuffer); 
    return true;
}

void AudioProcessor::play() {
    sound->play();
}

bool AudioProcessor::isPlaying() const {
    return sound->getStatus() == sf::SoundSource::Status::Playing;
}

std::vector<float> AudioProcessor::getFrequencyData() {
    if (!sound) return {};
    
    const sf::SoundBuffer& buffer = sound->getBuffer();
    const std::int16_t* samples = buffer.getSamples();
    std::size_t totalSamples = buffer.getSampleCount();
    
    // Get current playback position in samples
    sf::Time playbackTime = sound->getPlayingOffset();
    std::size_t currentSample = playbackTime.asMilliseconds() * buffer.getSampleRate() / 1000;
    
    std::vector<float> frequencies;
    
    // Get 64 samples from current position
    for (int i = 0; i < 64 && (currentSample + i) < totalSamples; i++) {
        float sample = static_cast<float>(samples[currentSample + i]) / 32768.0f;
        frequencies.push_back(std::abs(sample));  // Use absolute value
    }
    
    return frequencies;
}

void AudioProcessor::unloadMusic() {
    if (sound) {
        sound ->stop();
        delete sound;
        sound = nullptr;
    }
}

bool AudioProcessor::isLoaded() const {
    return sound != nullptr;
}