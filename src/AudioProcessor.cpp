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
    std::size_t count = buffer.getSampleCount();
    
    std::vector<float> frequencies;
    for (std::size_t i = 0; i < std::min(count, size_t(64)); i++) {
        frequencies.push_back(static_cast<float>(samples[i]) / 32768.0f);
    }
    return frequencies;
}